#include <sparse_set.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("sparse_set") {
  SparseSet<size_t> sparse_set;

  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());

  sparse_set.insert(1);
  CHECK(sparse_set.size() == 1);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(1));

  CHECK(*sparse_set.begin() == 1);
  CHECK(sparse_set.begin() != sparse_set.end());

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());

  sparse_set.insert(1);
  sparse_set.insert(2);

  CHECK(sparse_set.size() == 2);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(1));
  CHECK(sparse_set.contains(2));

  CHECK(*sparse_set.begin() == 1);
  CHECK(*(++sparse_set.begin()) == 2);
  CHECK(sparse_set.begin() != sparse_set.end());

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
}
