#include <sparse_set.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("sparse_set") {
  SparseSet<size_t> sparse_set;

  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.insert(1);
  CHECK(sparse_set.size() == 1);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(1));
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(5));
  CHECK(*sparse_set.begin() == 1);

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.insert(1);
  sparse_set.insert(2);

  CHECK(sparse_set.size() == 2);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(1));
  CHECK(sparse_set.contains(2));
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(5));
  CHECK(*sparse_set.begin() == 1);
  CHECK(*(++sparse_set.begin()) == 2);

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.insert(3);
  sparse_set.insert(8);
  sparse_set.insert(15);
  CHECK(sparse_set.size() == 3);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(3));
  CHECK(sparse_set.contains(8));
  CHECK(sparse_set.contains(15));
  CHECK(*sparse_set.begin() == 3);
  CHECK(*(++sparse_set.begin()) == 8);
  CHECK(*(++(++sparse_set.begin())) == 15);
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.erase(8);
  CHECK(not sparse_set.contains(8));
  CHECK(sparse_set.size() == 2);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(3));
  CHECK(sparse_set.contains(15));
  CHECK(*sparse_set.begin() == 3);
  CHECK(*(++sparse_set.begin()) == 15);
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));
}
