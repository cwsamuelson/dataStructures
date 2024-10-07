#include <sparse_map.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct S {
  int x;

  friend auto operator<=>(const S&, const S&) noexcept = default;
};

// this struct should maybe be put into a shared location?
TEST_CASE("sparse map") {
  SparseMap<size_t, S> sparse_map;

  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.clear();
  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.insert(5, { 6 });
  CHECK(sparse_map.size() == 1);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(*sparse_map.begin() == S { 6 });

  sparse_map.clear();
  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.insert(5, { 6 });
  sparse_map.insert(10, { 12 });
  CHECK(sparse_map.size() == 2);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(sparse_map.contains(10));
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(*sparse_map.begin() == S { 6 });

  sparse_map.clear();
  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.insert(5, { 6 });
  sparse_map.insert(10, { 12 });
  sparse_map.insert(15, { 18 });
  CHECK(sparse_map.size() == 3);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(sparse_map.contains(10));
  CHECK(sparse_map.contains(15));
  CHECK(*sparse_map.begin() == S { 6 });
  CHECK(*(++sparse_map.begin()) == S { 12 });
  CHECK(*(++(++sparse_map.begin())) == S { 18 });
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));

  sparse_map.erase(10);
  CHECK(not sparse_map.contains(10));
  CHECK(sparse_map.size() == 2);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(sparse_map.contains(15));
  CHECK(*sparse_map.begin() == S { 6 });
  CHECK(*(++sparse_map.begin()) == S { 18 });
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
}
