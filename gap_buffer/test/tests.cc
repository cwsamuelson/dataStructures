#include <gap_buffer.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`GapBuffer`: `GapString`") {
  GapString string;
  CHECK(string.size() == 0);
  CHECK(string.capacity() == 0);
  CHECK(string.empty());
  CHECK(string == "");
  CHECK(string == std::string(""));

  string = "";
  CHECK(string.size() == 0);
  // even on an empty string, a buffer will be allocated to accomodate
  CHECK(string.capacity() != 0);
  CHECK(string.empty());
  CHECK(string == "");
  CHECK(string == std::string(""));

  string = "TEST TEXT";
  CHECK(string.size() == 9);
  CHECK(string.capacity() >= 10);
  CHECK(not string.empty());
  CHECK(string == "TEST TEXT");
  CHECK(string == std::string("TEST TEXT"));

  string = std::string("TEST TEXT");
  CHECK(string.size() == 9);
  CHECK(string.capacity() >= 10);
  CHECK(not string.empty());
  CHECK(string == "TEST TEXT");
  CHECK(string == std::string("TEST TEXT"));

  string = "xxx";
  CHECK(string < "xxxx");
  CHECK(string > "xx");
  CHECK(string < GapString("xxxx"));
  CHECK(string > GapString("xx"));
  string = "A";
  CHECK(string < "B");
  CHECK(string < GapString("B"));
}
