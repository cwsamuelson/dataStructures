#include "pack/resource_pack.hh"

#include <error_help.hh>

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace Pack {

[[nodiscard]]
bool ResourcePack::contains(const std::string_view key) const {
  return data.contains(key);
}

void ResourcePack::clear() {
  data.clear();
}

ResourcePack::Blob& ResourcePack::operator[](const std::string_view key) {
  return data[std::string{key}];
}

const ResourcePack::Blob& ResourcePack::operator[](const std::string_view key) const {
  return data.at(std::string{key});
}

void ResourcePack::save(const ResourcePack& pack, const std::filesystem::path destination) {
  std::ofstream file_stream(destination);
  VERIFY(file_stream, "Couldn't open file({})", destination.string());

  write(pack, file_stream);
}

ResourcePack ResourcePack::load(const std::filesystem::path source) {
  std::ifstream file_stream(source);
  VERIFY(file_stream, "Couldn't open file({})", source.string());

  return read(file_stream);
}

ResourcePack::Blob ResourcePack::write(const ResourcePack& pack) {
  // 8 bytes initially for the entry count
  size_t blob_size{8};

  for (const auto& [key, blob] : pack.data) {
    // <key length>"key string"<data offset><data length>
    // Key length, data offset, and data length each use 8 bytes for storage.
    // Plus whatever the length of the key string is, plus the amount of blob
    // storage itself.
    blob_size += 8 + key.size() + 8 + 8 + blob.size();
  }

  Blob blob;
  blob.resize(blob_size);

  write(pack, std::span{ blob.data(), blob.size() });
  return blob;
}

void ResourcePack::write(const ResourcePack& pack, const std::span<std::byte> span) {
  std::basic_spanstream blob_stream(span);

  write(pack, blob_stream);
}

ResourcePack ResourcePack::read(const std::span<std::byte> span) {
  std::basic_ispanstream blob_stream(span);

  return read(blob_stream);
}

}
