#pragma once

#include <error_help.hh>

#include <filesystem>
#include <fstream>
#include <map>
#include <span>
#include <spanstream>
#include <string>
#include <vector>

namespace Pack {

// The biggest limitation of this design in my mind is that all the data is
// fully copied.  Theoretically the image blob could be read into memory once
// and the `Pack` would only contain views/spans into that blob, making the
// `Pack` incredibly lightweight, but the `PackFile` would still be 'heavy',
// and must be maintained 'somewhere'; perhaps a `Pack` could hold a
// `shared_ptr` to the `PackFile` to assist with lifetimes etc., but then if
// the user wants to update the contents and save it back out, other packs
// would then also be modified.  Or maybe a `Pack` is simply a non-owning view.

// tar-like, packed file data
// first 8 bytes is index size
// the index is comprised of a list of entries
// each entry contains:
//  - entry key
//  - an offset into the 'blob' section
//  - size of data
//  Entry key is:
//  first 8 bytes key length, excluding null term
//  the remainder is the key string text, including null term
// After the index the rest of the file is the 'blob' data
struct ResourcePack {
  using Blob = std::vector<std::byte>;

  [[nodiscard]]
  bool contains(const std::string_view key) const;

  void clear();

  Blob& operator[](const std::string_view key);

  const Blob& operator[](const std::string_view key) const;

  static
  void save(const ResourcePack& pack, const std::filesystem::path destination);

  static
  ResourcePack load(const std::filesystem::path source);

  static
  Blob write(const ResourcePack& pack);

  template<typename OSTREAM>
  static
  void write(const ResourcePack& pack, OSTREAM& ostream) {
    const auto index_size = pack.data.size();
    ostream.write(reinterpret_cast<const OSTREAM::char_type*>(&index_size), 8);

    // write index; keys and offsets
    for (size_t offset{}; const auto& [key, blob] : pack.data) {
      // <key length>"key string"<data offset><data length>
      const auto key_length = key.size();
      ostream.write(reinterpret_cast<const OSTREAM::char_type*>(&key_length), 8);
      ostream.write(reinterpret_cast<const OSTREAM::char_type*>(key.data()), key.size());
      ostream.write(reinterpret_cast<const OSTREAM::char_type*>(&offset), 8);

      const auto blob_size = blob.size();
      ostream.write(reinterpret_cast<const OSTREAM::char_type*>(&blob_size), 8);

      offset += blob_size;
    }

    // write blob section; binary data
    for (const auto& [key, blob] : pack.data) {
      ostream.write(reinterpret_cast<const OSTREAM::char_type*>(blob.data()), blob.size());
    }
  }

  static
  void write(const ResourcePack& pack, const std::span<std::byte> span);

  template<typename ISTREAM>
    requires requires(ISTREAM istream, ISTREAM::char_type* data, const size_t count) {
      istream.read(data, count);
    }
  static
  ResourcePack read(ISTREAM& istream) {
    size_t entries{};
    istream.read(reinterpret_cast<ISTREAM::char_type*>(&entries), 8);

    struct Index {
      struct Entry {
        std::string key;
        // offset into data section of data associated with key
        size_t offset{};
        // size of the blob data associated with the key
        size_t size{};
      };

      std::vector<Entry> entries;
    };

    Index index;

    // read index data
    for (size_t i{}; i < entries; ++i) {
      size_t key_length{};
      istream.read(reinterpret_cast<ISTREAM::char_type*>(&key_length), 8);

      std::string key;
      key.resize(key_length);
      istream.read(reinterpret_cast<ISTREAM::char_type*>(key.data()), key_length);

      size_t data_offset{};
      istream.read(reinterpret_cast<ISTREAM::char_type*>(&data_offset), 8);

      size_t data_size{};
      istream.read(reinterpret_cast<ISTREAM::char_type*>(&data_size), 8);

      VERIFY(key.size() == key_length, "Inconsistent key string sizes.");

      index.entries.emplace_back(key, data_offset, data_size);
    }

    // read blob data
    ResourcePack pack;
    for (const auto& entry : index.entries) {
      std::vector<std::byte> blob;
      blob.resize(entry.size);
      istream.read(reinterpret_cast<ISTREAM::char_type*>(blob.data()), entry.size);
      pack.data[entry.key] = std::move(blob);
    }

    return pack;
  }

  // this should be able to be `std::span<const std::byte>`, but it fails to
  // build.  It seems that `std::basic_spanstream` erroneously requires its type
  // to be non-const.  Even `ispanstream` seems to have this issue, even though
  // especially the input stream would have no need for the type to be non-const.
  static
  ResourcePack read(const std::span<std::byte> span);

  std::map<std::string, Blob, std::less<>> data;
};

}
