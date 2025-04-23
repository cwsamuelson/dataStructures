#include <pack/resource_pack.hh>

#include <catch2/catch_all.hpp>

SCENARIO("`ResourcePack`") {
  {
    Pack::ResourcePack new_pack;
    auto& abc_vec = new_pack["abc"];
    abc_vec.resize(sizeof(size_t));
    const size_t abc{42};
    std::memcpy(abc_vec.data(), &abc, sizeof(size_t));

    new_pack.save("file.pack");
  }

  {
    Pack::ResourcePack old_pack("file.pack");

    CHECK(old_pack.contains("abc"));
    auto& abc_vec = old_pack["abc"];
    CHECK(abc_vec.size() == sizeof(size_t));
    size_t abc{};
    std::memcpy(&abc, abc_vec.data(), sizeof(size_t));
  }
}

