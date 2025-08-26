#include <chunked_array.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`ChunkedArray`: `ChunkedString`") {
  ChunkedString string;
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
  CHECK(string[0] == 'T');
  CHECK(string[1] == 'E');
  CHECK(string[2] == 'S');
  CHECK(string[3] == 'T');
  CHECK(string.front() == 'T');
  CHECK(string.back() == 'T');
  string.front() = 'A';
  string.back() = 'B';
  CHECK(string.front() == 'A');
  CHECK(string.back() == 'B');
  CHECK(string == "AEST TEXB");

  string = std::string("TEST TEXT");
  CHECK(string.size() == 9);
  CHECK(string.capacity() >= 10);
  CHECK(not string.empty());
  CHECK(string == "TEST TEXT");
  CHECK(string == std::string("TEST TEXT"));
  CHECK(string[0] == 'T');
  CHECK(string[1] == 'E');
  CHECK(string[2] == 'S');
  CHECK(string[3] == 'T');
  CHECK(string.front() == 'T');
  CHECK(string.back() == 'T');

  string = "xxx";
  CHECK(string < "xxxx");
  CHECK(string > "xx");
  CHECK(string < ChunkedString("xxxx"));
  CHECK(string > ChunkedString("xx"));
  CHECK(string[0] == 'x');
  CHECK(string[1] == 'x');
  CHECK(string[2] == 'x');
  CHECK(string.front() == 'x');
  CHECK(string.back() == 'x');

  string = "A";
  CHECK(string < "B");
  CHECK(string < ChunkedString("B"));
  CHECK(string[0] == 'A');
  CHECK(string.front() == 'A');
  CHECK(string.back() == 'A');
}
