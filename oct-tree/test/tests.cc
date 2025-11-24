#include <oct-tree.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`OctTree`") {
  OctTree<int> oct_tree({{0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}});

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  CHECK(oct_tree.insert({}, 0));

  CHECK(not oct_tree.empty());
  CHECK(oct_tree.size() == 1);

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  CHECK(not oct_tree.insert({ 2.f, 2.f, .2f }, 0));

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  CHECK(oct_tree.insert({ .5f, .5f, .5f }, 0));
  CHECK(oct_tree.insert({ .1f, .1f, .1f }, 1));

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB{{ 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB{{ .1f, .1f, .1f }, { .5f, .5f, .5f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB{{ .6f, .6f, .6f }, { .9f, .9f, .9f }});
    CHECK(full_map_results.empty());
  }

  for (size_t i{2}; i < 10; ++i) {
    CHECK(oct_tree.insert({ .1f * i, .1f * i, .1f * i }, i));
    CHECK(oct_tree.size() == i + 1);
  }
  CHECK(oct_tree.size() == 10);

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB{{ 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }});
    CAPTURE(full_map_results);
    CHECK(full_map_results.size() == oct_tree.size());
    CHECK(oct_tree.size() == 10);
  }

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);
}
