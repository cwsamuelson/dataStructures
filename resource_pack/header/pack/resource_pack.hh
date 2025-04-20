#pragma once

#include <filesystem>
#include <map>
#include <span>
#include <vector>

namespace Pack {

// tar-like, packed file data
// first 8 bytes is index size
// index contains a list of entries
// each entry contains:
//  - Entry key
//  - an offset into the 'blob' section
//  - size of data
//  Entry key is:
//  first 8 bytes key length, excluding null term
//  the remainder is the key string text, including null term
// After the index the rest of the file is the 'blob' data

// this represents the actual pack file, and handles file reading, and data
// storage as well as the structures will vaguely reflect file structure
struct PackFile {
  struct IndexEntry {
    struct Key {
      size_t length{};
      std::string_view text;
    };

    Key key;
    size_t offset{};
    size_t size{};
  };

  std::filesystem::path file_path;
  std::vector<std::byte> data;
  std::span<const std::byte> file_blob;
  std::span<const std::byte> index_blob;
  std::span<const std::byte> data_blob;

  size_t index_size{};
  std::vector<IndexEntry> index;

  PackFile();
  PackFile(const std::filesystem::path& path);

  [[nodiscard]]
  bool check_index_integrity() const;
  void clear();

private:
  void generate_index();
};

// this represents the usable side of the resource pack, and doesn't reflect the file directly
struct ResourcePack {
  using IndexEntry = std::span<const std::byte>;

  ResourcePack();
  ResourcePack(const std::filesystem::path& path);

  void load(const std::filesystem::path& path);
  void save(const std::filesystem::path& path);
  void clear();

  PackFile pack_file;
  std::map<std::string_view, IndexEntry> index;
};

}

