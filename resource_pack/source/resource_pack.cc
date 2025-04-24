#include "pack/resource_pack.hh"

#include <error_help.hh>

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <print>

namespace {

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

