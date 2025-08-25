#include <gap_buffer.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`GapBuffer`: `GapString`") {
  GapString string;
  CHECK(string.size() == 0);
  CHECK(string.capacity() == 0);
  CHECK(string.empty());

  string = "";
  CHECK(string.size() == 0);
  // even on an empty string, a buffer will be allocated to accomodate
  CHECK(string.capacity() != 0);
  CHECK(string.empty());

  string = "TEST TEXT";
  CHECK(string.size() == 9);
  CHECK(string.capacity() >= 10);
  CHECK(not string.empty());

  string = std::string("TEST TEXT");
  CHECK(string.size() == 9);
  CHECK(string.capacity() >= 10);
  CHECK(not string.empty());
}
