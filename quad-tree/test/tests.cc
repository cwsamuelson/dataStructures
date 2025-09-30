#include <quad-tree.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`QuadTree`") {
  QuadTree<int> quad_tree({{0.f, 0.f}, {1.f, 1.f}});

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.insert({}, 0);

  CHECK(not quad_tree.empty());
  CHECK(quad_tree.size() == 1);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.insert({2.f, 2.f}, 0);

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.insert({ .5f, .5f }, 0);
  quad_tree.insert({ .1f, .1f }, 1);

  {
    const auto full_map_results = quad_tree.query({{ 0.f, 0.f }, { 1.f, 1.f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = quad_tree.query({{ .1f, .1f }, { .5f, .5f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = quad_tree.query({{ .6f, .6f }, { .9f, .9f }});
    CHECK(full_map_results.empty());
  }
}
