#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<array.hh>

TEST_CASE("Arrays can be used as builtin arrays.", "[array]") {
  gsw::array<char[3]> arr;

  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';

  SECTION("Array basics.") {
    CHECK(arr[0] == 'a');
    CHECK(arr[1] == 'b');
    CHECK(arr[2] == 'c');
  }

  SECTION("Array range-based for.") {
    unsigned int i = 0;
    for(auto it : arr) {
      CHECK(it == arr[i++]);
    }
  }

  SECTION("Assignment") {
    arr[0] = 'd';
    CHECK(arr[0] == 'd');
    CHECK(arr[1] == 'b');
    CHECK(arr[2] == 'c');

    arr[1] = 'e';
    CHECK(arr[0] == 'd');
    CHECK(arr[1] == 'e');
    CHECK(arr[2] == 'c');

    arr[2] = 'f';
    CHECK(arr[0] == 'd');
    CHECK(arr[1] == 'e');
    CHECK(arr[2] == 'f');
  }
}

TEST_CASE("Arrays can be 'spliced'.", "[array]") {
  gsw::array<char[10]> arr;

  for(unsigned int i = 0; i < arr.size(); ++i) {
    arr[i] = char(i + 'a');
  }

  SECTION("Basic splice indeces.") {
    arr[arr > 8] = 'z';
    arr[arr < 2] = 'y';

    for(unsigned int i = 0; i < 2; ++i) {
      CHECK(arr[i] == 'y');
    }
    for(unsigned int i = 9; i < 10; ++i) {
      CHECK(arr[i] == 'z');
    }

    arr[arr >= 6] = 'x';
    arr[arr <= 4] = 'w';

    for(unsigned int i = 0; i <= 4; ++i) {
      CHECK(arr[i] == 'w');
    }
    for(unsigned int i = 6; i < 10; ++i) {
      CHECK(arr[i] == 'x');
    }
  }

  SECTION("Spliced by another container") {
    gsw::array<unsigned int[3]> ids;

    ids[0] = 1;
    ids[1] = 3;
    ids[2] = 5;

    arr[ids] = 'z';

    for(auto it : ids) {
      CHECK(arr[it] == 'z');
    }

    for(unsigned int i = 6; i < 10; ++i) {
      CHECK(arr[i] == ('a' + i));
    }
  }
}

/*!
 * @todo change some of these to compile-time checks
 * REQUIRE( arr[0] == 1 );
 * may execute at run time since operator[] is not declared constexpr, and not
 * sure it can/should be.  the goal here is that it won't execute at run-time,
 * only compile-time
 */
TEST_CASE("Brace initialization", "[array]") {
  const gsw::array<int[5]> arr{ 1, 2, 3, 4, 5 };
  const int i = arr[0];

  CHECK(arr[0] == 1);
  CHECK(i == 1);
  CHECK(arr.size() == 5);
}
