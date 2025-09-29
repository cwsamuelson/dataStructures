#include <pack/resource_pack.hh>

#include <catch2/catch_all.hpp>

SCENARIO("`ResourcePack`") {
  {
    Pack::ResourcePack new_pack;
    auto& abc_vec = new_pack["abc"];
    abc_vec.resize(sizeof(size_t));
    const size_t abc{42};
    std::memcpy(abc_vec.data(), &abc, sizeof(size_t));

    Pack::ResourcePack::save(new_pack, "file.pack");
  }

  {
    const Pack::ResourcePack old_pack = Pack::ResourcePack::load("file.pack");

    CHECK(old_pack.contains("abc"));
    /*auto& abc_vec = old_pack["abc"];
    CHECK(abc_vec.size() == sizeof(size_t));
    size_t abc{};
    std::memcpy(&abc, abc_vec.data(), sizeof(size_t));*/
    REQUIRE(old_pack.data.size() == 1);
    CHECK(old_pack.data.contains("abc"));
    CHECK(old_pack["abc"].size() == sizeof(size_t));
  }
}

SCENARIO("`ResourcePack`: sandbox") {
  SECTION("Empty pack properties") {
    const Pack::ResourcePack empty_pack;

    auto blob = Pack::ResourcePack::write(empty_pack);
    CHECK(not blob.empty());
    CHECK(blob.size() == 8);

    const auto pack = Pack::ResourcePack::read(blob);
    CHECK(pack.data.empty());
  }

  SECTION("Pack filled with data") {
    Pack::ResourcePack filled_pack;

    const auto long_key = "this is the key, it's weirdly long";
    filled_pack.data[long_key] = {};
    filled_pack.data["shrt"] = { static_cast<std::byte>(0xFF), static_cast<std::byte>(0x40) };

    auto blob = Pack::ResourcePack::write(filled_pack);
    CHECK(not blob.empty());
    CHECK(blob.size() >= 62);

    const auto pack = Pack::ResourcePack::read(blob);
    CHECK(pack.data.size() == 2);

    CHECK(pack.data.contains("shrt"));
    CHECK(pack.data.contains(long_key));

    CHECK(pack.data.at(long_key).empty());
    CHECK(pack.data.at("shrt").size() == 2);
    CHECK(pack.data.at("shrt").at(0) == static_cast<std::byte>(0xFF));
    CHECK(pack.data.at("shrt").at(1) == static_cast<std::byte>(0x40));
  }

  SECTION("File reading/writing") {
    const std::filesystem::path file_path = "data.rpk";

    {
      std::filesystem::remove(file_path);
      REQUIRE(not std::filesystem::exists(file_path));

      Pack::ResourcePack res_pack;

      res_pack["A"] = { static_cast<std::byte>(0x40) };
      res_pack["B"] = { static_cast<std::byte>(0xFF) };
      res_pack["C"] = { static_cast<std::byte>(0xFF), static_cast<std::byte>(0x40) };
      res_pack["D"] = {
        static_cast<std::byte>(0x12),
        static_cast<std::byte>(0x21),
        static_cast<std::byte>(0x12),
        static_cast<std::byte>(0x21),
        static_cast<std::byte>(0x11),
        static_cast<std::byte>(0x38),
        static_cast<std::byte>(0x38),
        static_cast<std::byte>(0x11),
      };
      res_pack["E"] = { static_cast<std::byte>(0x42), static_cast<std::byte>(0x24) };

      Pack::ResourcePack::save(res_pack, file_path);

      REQUIRE(std::filesystem::exists(file_path));
    }

    {
      REQUIRE(std::filesystem::exists(file_path));
      const auto res_pack = Pack::ResourcePack::load(file_path);

      CHECK(res_pack.contains("A"));
      CHECK(res_pack.contains("B"));
      CHECK(res_pack.contains("C"));
      CHECK(res_pack.contains("D"));
      CHECK(res_pack.contains("E"));

      CHECK(res_pack["A"].size() == 1);
      CHECK(res_pack["B"].size() == 1);
      CHECK(res_pack["C"].size() == 2);
      CHECK(res_pack["D"].size() == 8);
      CHECK(res_pack["E"].size() == 2);

      CHECK(res_pack["A"][0] == static_cast<std::byte>(0x40));
      CHECK(res_pack["B"][0] == static_cast<std::byte>(0xFF));
      CHECK(res_pack["C"][0] == static_cast<std::byte>(0xFF));
      CHECK(res_pack["C"][1] == static_cast<std::byte>(0x40));
      CHECK(res_pack["D"][0] == static_cast<std::byte>(0x12));
      CHECK(res_pack["D"][1] == static_cast<std::byte>(0x21));
      CHECK(res_pack["D"][2] == static_cast<std::byte>(0x12));
      CHECK(res_pack["D"][3] == static_cast<std::byte>(0x21));
      CHECK(res_pack["D"][4] == static_cast<std::byte>(0x11));
      CHECK(res_pack["D"][5] == static_cast<std::byte>(0x38));
      CHECK(res_pack["D"][6] == static_cast<std::byte>(0x38));
      CHECK(res_pack["D"][7] == static_cast<std::byte>(0x11));
      CHECK(res_pack["E"][0] == static_cast<std::byte>(0x42));
      CHECK(res_pack["E"][1] == static_cast<std::byte>(0x24));
    }
  }
}
