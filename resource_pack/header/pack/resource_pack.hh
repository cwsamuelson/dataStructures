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
      std::string text;
    };

    Key key;
    size_t offset{};
    size_t size{};
  };

  std::filesystem::path file_path;
  size_t entry_count{};
  std::vector<IndexEntry> index;

  PackFile();
  PackFile(const std::filesystem::path& path);

  void check_index_integrity() const;
  void clear();
};

// this represents the usable side of the resource pack, and doesn't reflect the file directly
struct ResourcePack {
  using Blob = std::vector<std::byte>;

  ResourcePack();
  ResourcePack(const std::filesystem::path& path);

  void load(const std::filesystem::path& path);
  void save(const std::filesystem::path& path) const;
  void clear();

  [[nodiscard]]
  decltype(auto)operator[](this auto&& self, const std::string& key) {
    return self.index[key];
  }

  [[nodiscard]]
  bool contains(const std::string& key) const;

  /*template<typename Type, typename ...Args>
  [[nodiscard]]
  Type& emplace(std::string key, Args&& ...args) {
    return index.try_emplace(std::move(key), std::forward<Args>(args)...);
  }

  template<typename Type>
  [[nodiscard]]
  decltype(auto) get(this auto&& self, const std::string& key) {
    if (self.index.contains(key)) {
      VERIFY(self.index.at(key).size() == sizeof(Type), "Existing key (key) of unexpected size ({} vs {})", key, self.index.at(key).size(), sizeof(Type));
    }
  }*/

  PackFile pack_file;
  std::map<std::string, Blob> index;
};

}

