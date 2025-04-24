#include "pack/resource_pack.hh"

#include <error_help.hh>

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <print>

struct bytes_view : std::ranges::view_interface<bytes_view> {
  std::span<unsigned char> byte_span;

  template<typename Range>
  bytes_view(Range&& range) {
    std::span source_span(range.begin(), range.end());
    byte_span = std::span<unsigned char>(source_span.data(), source_span.size_bytes());
  }

  auto begin() {
    return byte_span.begin();
  }

  auto end() {
    return byte_span.end();
  }
};

template<std::ranges::viewable_range Range>
std::ranges::view auto bytes(Range&& range) {
  return bytes_view();
}

namespace {

std::string read_file(const std::filesystem::path& path) {
  std::ifstream file(path);
  VERIFY(file, "Could not open file \"{}\"", path.string());

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}

std::vector<std::byte> read_binary(const std::filesystem::path& path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  VERIFY(file, "Could not open file ({})", path.string());

  const auto size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<std::byte> buffer(static_cast<size_t>(size));
  VERIFY(file.read(reinterpret_cast<char*>(buffer.data()), size), "Couldn't read all bytes from file ({}).  Expected {} bytes.", path.string(), static_cast<size_t>(size));

  return buffer;
}

template<typename Type, size_t Size>
std::span<const Type, Size> static_subspan(std::span<const std::byte>& span) {
  constexpr size_t SizeBytes = Size * sizeof(Type);
  VERIFY(span.size_bytes() >= SizeBytes, "Insufficient data to create subpsan {} {}s ({}) from {}", Size, sizeof(Type), SizeBytes, span.size_bytes());

  std::span<const Type, Size> subspan(reinterpret_cast<const Type*>(span.data()), SizeBytes);

  span = span.subspan(SizeBytes);

  return subspan;
}

template<typename Type>
std::span<const Type> safe_subspan(std::span<const Type>& span, const size_t offset) {
  VERIFY(span.size() >= offset, "Insufficient data to create subspan (offset {} into {} items)", offset, span.size());

  std::span<const Type> new_span(span.data(), offset);
  span = span.subspan(offset);

  return new_span;
}

template<typename Type>
Type convert(std::span<const std::byte>& span) {
  return static_subspan<Type, 1>(span)[0];
}

template<typename IStream>
IStream& operator>>(IStream& istream, Pack::PackFile::IndexEntry::Key& key) {
  VERIFY(istream.read(reinterpret_cast<char*>(&key.length), sizeof(key.length)), "Couldn't read key length from file.");

  key.text.resize(key.length);
  VERIFY(istream.read(reinterpret_cast<char*>(key.text.data()), key.length), "Couldn't read all bytes from file.  Expected {} bytes.", key.length);

  return istream;
}

template<typename IStream>
IStream& operator>>(IStream& istream, Pack::PackFile::IndexEntry& entry) {
  VERIFY(istream >> entry.key, "Could not read index entry keysize");
  VERIFY(istream.read(reinterpret_cast<char*>(&entry.offset), sizeof(entry.offset)), "Could not read index entry offset");
  VERIFY(istream.read(reinterpret_cast<char*>(&entry.size), sizeof(entry.size)), "Could not read index entry size");

  return istream;
}

}

namespace Pack {

PackFile::PackFile() = default;

PackFile::PackFile(const std::filesystem::path& path)
  : file_path(path) {
  try {
    std::ifstream file(file_path, std::ios::binary);
    VERIFY(file, "Could not open file", file_path.string());

    VERIFY(file.read(reinterpret_cast<char*>(&entry_count), sizeof(entry_count)), "Could not read index size from file");

    for (size_t i{}; i < entry_count and file; ++i) {
      auto& entry = index.emplace_back();
      VERIFY(file >> entry, "Could not read {}th index entry", index.size());
    }

    check_index_integrity();
  } CATCH_AND_NEST("Error parsing file ({})", path.string())
}

void PackFile::check_index_integrity() const {
  VERIFY(entry_count == index.size(), "Expected {} index entries, found {}", entry_count, index.size());
}

void PackFile::clear() {
  *this = PackFile();
}

ResourcePack::ResourcePack() = default;

ResourcePack::ResourcePack(const std::filesystem::path& path)
  : pack_file(path)
{}

void ResourcePack::load(const std::filesystem::path& path) {
  *this = ResourcePack(path);
}

void ResourcePack::save(const std::filesystem::path& path) const {
  try {
    std::ofstream file(path, std::ios::binary);
    VERIFY(file, "Could not open file ({})", path.string());

    auto s = index.size();

    file.write(reinterpret_cast<const char*>(&s), sizeof(s));

    for (size_t cursor{}; const auto& [key, value] : index) {
      s = key.size();
      file.write(reinterpret_cast<const char*>(&s), sizeof(s));
      file << key;
      s = cursor;
      file.write(reinterpret_cast<const char*>(&s), sizeof(s));
      s = value.size();
      file.write(reinterpret_cast<const char*>(&s), sizeof(s));
    }

    for (const auto& [key, value] : index) {
      file.write(reinterpret_cast<const char*>(value.data()), value.size());
    }
  } CATCH_AND_NEST("Error writing file ({})", path.string())
}

void ResourcePack::clear() {
  pack_file.clear();
  index.clear();
}

bool ResourcePack::contains(const std::string& key) const {
  return index.contains(key);
}

}

