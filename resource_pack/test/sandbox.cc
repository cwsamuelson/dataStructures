#include <catch2/catch_all.hpp>

#include <filesystem>
#include <map>
#include <spanstream>
#include <string>
#include <vector>

// The biggest limitation of this design in my mind is that all the data is
// fully copied.  Theoretically the image blob could be read into memory once
// and the `Pack` would only contain views/spans into that blob, making the
// `Pack` incredibly lightweight, but the `PackFile` would still be 'heavy',
// and must be maintained 'somewhere'; perhaps a `Pack` could hold a
// `shared_ptr` to the `PackFile` to assist with lifetimes etc., but then if
// the user wants to update the contents and save it back out, other packs
// would then also be modified.  Or maybe a `Pack` is simply a non-owning view.
struct ResourcePack {
  using Blob = std::vector<std::byte>;

  [[nodiscard]]
  bool contains(const std::string_view key) {
    return data.contains(key);
  }

  void clear() {
    data.clear();
  }

  void operator[](std::string_view key) {
  }

  static
  void save(const ResourcePack& pack, const std::filesystem::path destination) {
    struct Index {
      struct Entry {
        struct Key {
          size_t length{};
          std::string text;
        };

        Key key;
        // offset into data section of data associated with key
        size_t offset{};
        // size of the blob data associated with the key
        size_t size{};
      };

      std::vector<Entry> entries;
    };
  }

  static
  void load(const std::filesystem::path source) {
  }

  static
  Blob write(const ResourcePack& pack) {
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

    write(pack, blob);
    return blob;
  }

  static
  void write(const ResourcePack& pack, const std::span<std::byte> span) {
    std::basic_spanstream blob_stream(span);

    const auto index_size = pack.data.size();
    blob_stream.write(reinterpret_cast<const std::byte*>(&index_size), 8);

    for (size_t offset{}; const auto& [key, blob] : pack.data) {
      // <key length>"key string"<data offset><data length>
      const auto key_length = key.size();
      blob_stream.write(reinterpret_cast<const std::byte*>(&key_length), 8);
      blob_stream.write(reinterpret_cast<const std::byte*>(key.data()), key.size());
      blob_stream.write(reinterpret_cast<const std::byte*>(&offset), 8);
      const auto blob_size = blob.size();
      blob_stream.write(reinterpret_cast<const std::byte*>(&blob_size), 8);

      offset += blob_size;
    }
  }

  // this should be able to be `std::span<const std::byte>`, but it fails to
  // build.  It seems that `std::basic_spanstream` erroneously requires its type
  // to be non-const.  Even `ispanstream` seems to have this issue, even though
  // especially the input stream would have no need for the type to be non-const.
  static
  ResourcePack read(const std::span<std::byte> span) {
    std::basic_ispanstream blob_stream(span);

    size_t entries{};
    blob_stream.read(reinterpret_cast<std::byte*>(&entries), 8);

    struct Index {
      struct Entry {
        struct Key {
          size_t length{};
          std::string text;
        };

        Key key;
        // offset into data section of data associated with key
        size_t offset{};
        // size of the blob data associated with the key
        size_t size{};
      };

      std::vector<Entry> entries;
    };

    Index index;

    for (size_t i{}; i < entries; ++i) {
      size_t key_length{};
      blob_stream.read(reinterpret_cast<std::byte*>(&key_length), 8);

      std::string key_text;
      key_text.resize(key_length);
      blob_stream.read(reinterpret_cast<std::byte*>(key_text.data()), key_length);

      size_t data_offset{};
      blob_stream.read(reinterpret_cast<std::byte*>(&data_offset), 8);

      size_t data_size{};
      blob_stream.read(reinterpret_cast<std::byte*>(&data_size), 8);

      const Index::Entry::Key key{ key_length, key_text };

      index.entries.emplace_back(key, data_offset, data_size);
    }

    ResourcePack pack;
    for (const auto& entry : index.entries) {
      std::vector<std::byte> blob;
      blob.resize(entry.size);
      blob_stream.read(reinterpret_cast<std::byte*>(blob.data()), entry.size);
      pack.data[entry.key.text] = std::move(blob);
    }

    return pack;
  }

  std::map<std::string, Blob, std::less<>> data;
};

SCENARIO("`ResourcePack`: sandbox") {
  {
    const ResourcePack empty_pack;

    auto blob = ResourcePack::write(empty_pack);
    CHECK(not blob.empty());
    CHECK(blob.size() == 8);

    const auto pack = ResourcePack::read(blob);
    CHECK(pack.data.empty());
  }

  {
    ResourcePack filled_pack;

    filled_pack.data["this is the key, it's weirdly long"] = {};
    filled_pack.data["shrt"] = { static_cast<std::byte>(0xFF), static_cast<std::byte>(0x40) };

    auto blob = ResourcePack::write(filled_pack);
    CHECK(not blob.empty());
    CHECK(blob.size() >= 62);

    const auto pack = ResourcePack::read(blob);
    CHECK(pack.data.size() == 2);

    CHECK(pack.data.contains("shrt"));
    CHECK(pack.data.contains("this is the key, it's weirdly long"));

    CHECK(pack.data.at("shrt").empty());
    CHECK(pack.data.at("this is the key, it's weirdly long").size() == 2);
  }
}
