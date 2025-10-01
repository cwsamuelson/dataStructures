#include <quad-tree.hh>

#include <catch2/catch_all.hpp>

#include <string>

using namespace flp;

TEST_CASE("`QuadTree`") {
  QuadTree<int> quad_tree({{0.f, 0.f}, {1.f, 1.f}});

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  CHECK(quad_tree.insert({}, 0));

  CHECK(not quad_tree.empty());
  CHECK(quad_tree.size() == 1);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  CHECK(not quad_tree.insert({2.f, 2.f}, 0));

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  CHECK(quad_tree.insert({ .5f, .5f }, 0));
  CHECK(quad_tree.insert({ .1f, .1f }, 1));

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ 0.f, 0.f }, { 1.f, 1.f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ .1f, .1f }, { .5f, .5f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ .6f, .6f }, { .9f, .9f }});
    CHECK(full_map_results.empty());
  }

  for (size_t i{2}; i < 10; ++i) {
    CHECK(quad_tree.insert({ .1f * i, .1f * i }, i));
    CHECK(quad_tree.size() == i + 1);
  }
  CHECK(quad_tree.size() == 10);

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ 0.f, 0.f }, { 1.f, 1.f }});
    CAPTURE(full_map_results);
    CHECK(full_map_results.size() == 10);
  }

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);
}
