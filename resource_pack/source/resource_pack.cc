#include "pack/resource_pack.hh"

#include <error_help.hh>

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

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

}

namespace Pack {

PackFile::PackFile() = default;

PackFile::PackFile(const std::filesystem::path& path)
  : file_path(path) {
  data = read_binary(file_path);

  std::span<const std::byte> file_span(data);

  file_blob = file_span;

  index_size = convert<size_t>(file_span);

  index_blob = safe_subspan(file_span, index_size);

  data_blob = file_span;

  generate_index();
  VERIFY(check_index_integrity(), "Inconsistent resource index generated from file");
}

bool PackFile::check_index_integrity() const {
  size_t data_size{};

  for (const auto& entry : index) {
    data_size += entry.size;
  }

  VERIFY(data_size == data_blob.size(), "Index/pack format is invalid. Index indicates {} bytes, and the found blob size was {}", data_size, data_blob.size());

  return true;
}

void PackFile::clear() {
  *this = PackFile();
}

void PackFile::generate_index() {
  std::span<const std::byte> span = index_blob;

  while (not span.empty()) {
    const auto key_size = convert<size_t>(span);

    const std::string_view null_termed_str(reinterpret_cast<const char*>(span.data()));

    VERIFY(null_termed_str.size() == key_size, "Index entry key isn't null terminated");

    const auto key_span = safe_subspan(span, key_size);

    // trim null byte
    VERIFY(static_cast<char>(safe_subspan(span, 1)[0]) == '\0', "Index entry isn't properly null terminated");

    const auto offset = convert<size_t>(span);
    const auto size = convert<size_t>(span);

    const IndexEntry::Key key {
      key_size,
      {reinterpret_cast<const char*>(key_span.data()), key_span.size()}
    };

    index.emplace_back(key, offset, size);
  }
}

ResourcePack::ResourcePack() = default;

ResourcePack::ResourcePack(const std::filesystem::path& path)
  : pack_file(path) {

  for (const auto& entry : pack_file.index) {
    VERIFY(not index.contains(entry.key.text), "Redundant key found in index: {}", entry.key.text);

    index.try_emplace(entry.key.text, pack_file.data_blob.data() + entry.offset, pack_file.data_blob.data() + entry.offset + entry.size);
  }
}

void ResourcePack::load(const std::filesystem::path& path) {
  *this = ResourcePack(path);
}

void ResourcePack::save(const std::filesystem::path& path) {
  // create binary blob
  //   tracking offsets/sizes for keys
  // create index blob
  //   from tracked offsets/sizes
  // write index size
  // write index
  // write binary

  auto key_sizes =
      index
    | std::views::keys
    | std::views::transform([](const auto& key) {
      return key.size();
    })
  ;

  const auto total_index_size = std::views::feld_left_first(key_sizes).value_or(0) + (index.size() * (3 * 8));

  const auto binary_segment =
      index
    | std::views::values
    | std::views::join
  ;

  const auto blob_size = std::distance(binary_segment.begin(), binary_segment.end());

  std::vector<std::byte> buffer(blob_size + total_index_size + 8);

  std::span<std::byte> buf_span(buffer.data(), buffer.size());

  std::memcpy(buf_span.data(), &total_index_size, 8);

  index
    | std::views::transform([](const auto& pair) {
      const auto& [key, value] = pair;
      return std::views::concat(key, value);
    })
    | std::views::join
  ;
  // copy index
  // copy blob
}

void ResourcePack::clear() {
  pack_file.clear();
  index.clear();
}

}

