#include <b-tree.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`BTree`") {
  BTree<int, int, 5> btree;

  CHECK(btree.empty());
}
