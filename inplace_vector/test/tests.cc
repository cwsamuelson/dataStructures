#include <inplace_vector.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`InplaceVector`") {
  InplaceVector<int, 10> vector;

  CHECK(vector.capacity() == 10);
  CHECK(vector.size() == 0);
  CHECK(vector.empty());
  CHECK(vector.begin() == vector.end());

  CHECK_THROWS(vector.front());
  CHECK_THROWS(vector.back());

  vector.push_back(42);

  CHECK(vector.capacity() == 10);
  CHECK(vector.size() == 1);
  CHECK(not vector.empty());
  CHECK(vector.begin() != vector.end());

  CHECK(vector.front() == 42);
  CHECK(vector.back() == 42);

  CHECK(vector[0] == 42);
  CHECK(vector.at(0) == 42);

  vector.pop_back();

  CHECK(vector.capacity() == 10);
  CHECK(vector.size() == 0);
  CHECK(vector.empty());
  CHECK(vector.begin() == vector.end());

  CHECK_THROWS(vector.front());
  CHECK_THROWS(vector.back());
}
