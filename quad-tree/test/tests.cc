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
}
