#include <catch2/catch_all.hpp>

#include <filesystem>
#include <fstream>
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

  decltype(auto) operator[](this auto&& self, std::string_view key) {
    return self.data.at[key];
  }

  static
  void save(const ResourcePack& pack, const std::filesystem::path destination) {
    std::ofstream file_stream(destination);
    // VERIFY(file_stream, "Couldn't open file({})", destination.string());

    write(pack, file_stream);
  }

  static
  ResourcePack load(const std::filesystem::path source) {
    std::ifstream file_stream(source);
    // VERIFY(file_stream, "Couldn't open file({})", destination.string());

    return read(file_stream);
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

    write(pack, std::span{ blob.data(), blob.size() });
    return blob;
  }

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
  void write(const ResourcePack& pack, const std::span<std::byte> span) {
    std::basic_spanstream blob_stream(span);

    write(pack, blob_stream);
  }

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

      // VERIFY(key.size() == key_length, "Inconsistent key string sizes.");

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
  ResourcePack read(const std::span<std::byte> span) {
    std::basic_ispanstream blob_stream(span);

    return read(blob_stream);
  }

  std::map<std::string, Blob, std::less<>> data;
};

SCENARIO("`ResourcePack`: sandbox") {
  SECTION("Empty pack properties") {
    const ResourcePack empty_pack;

    auto blob = ResourcePack::write(empty_pack);
    CHECK(not blob.empty());
    CHECK(blob.size() == 8);

    const auto pack = ResourcePack::read(blob);
    CHECK(pack.data.empty());
  }

  SECTION("Pack filled with data") {
    ResourcePack filled_pack;

    const auto long_key = "this is the key, it's weirdly long";
    filled_pack.data[long_key] = {};
    filled_pack.data["shrt"] = { static_cast<std::byte>(0xFF), static_cast<std::byte>(0x40) };

    auto blob = ResourcePack::write(filled_pack);
    CHECK(not blob.empty());
    CHECK(blob.size() >= 62);

    const auto pack = ResourcePack::read(blob);
    CHECK(pack.data.size() == 2);

    CHECK(pack.data.contains("shrt"));
    CHECK(pack.data.contains(long_key));

    CHECK(pack.data.at(long_key).empty());
    CHECK(pack.data.at("shrt").size() == 2);
    CHECK(pack.data.at("shrt").at(0) == static_cast<std::byte>(0xFF));
    CHECK(pack.data.at("shrt").at(1) == static_cast<std::byte>(0x40));
  }
}
