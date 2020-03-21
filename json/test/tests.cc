#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <json.hh>

TEST_CASE("", "[json]") {
  SECTION("'uninit' type"){
    gsw::json j;

    CHECK(!j.is_object());
    CHECK(!j.is_array());
    CHECK(!j.is_string());
    CHECK(!j.is_integer());
    CHECK(!j.is_floating());
    CHECK(!j.is_bool());
    CHECK(!j.is_signed());
    CHECK(!j.is_unsigned());
  }

  SECTION("'object' type") {
    gsw::json j;

    CHECK( j.is_object());
    CHECK(!j.is_array());
    CHECK(!j.is_string());
    CHECK(!j.is_integer());
    CHECK(!j.is_floating());
    CHECK(!j.is_bool());
    CHECK(!j.is_signed());
    CHECK(!j.is_unsigned());
  }

  SECTION("'array' type") {
    SECTION("std::vector"){
      gsw::json j(std::vector<int>{1, 2, 3, 4, 5});

      CHECK(!j.is_object());
      CHECK( j.is_array());
      CHECK(!j.is_string());
      CHECK(!j.is_integer());
      CHECK(!j.is_floating());
      CHECK(!j.is_bool());
      CHECK(!j.is_signed());
      CHECK(!j.is_unsigned());
    }
  }

  SECTION("'string' type") {
    gsw::json j("");

    CHECK(!j.is_object());
    CHECK(!j.is_array());
    CHECK( j.is_string());
    CHECK(!j.is_integer());
    CHECK(!j.is_floating());
    CHECK(!j.is_bool());
    CHECK(!j.is_signed());
    CHECK(!j.is_unsigned());
  }

  SECTION("'signed integer' type") {
    SECTION("signed short"){
      signed short i = 5;
      gsw::json j(i);

      CHECK(!j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK( j.is_integer());
      CHECK(!j.is_floating());
      CHECK(!j.is_bool());
      CHECK( j.is_signed());
      CHECK(!j.is_unsigned());
    }

    SECTION("signed int"){
      signed int i = 5;
      gsw::json j(i);

      CHECK(!j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK( j.is_integer());
      CHECK(!j.is_floating());
      CHECK(!j.is_bool());
      CHECK( j.is_signed());
      CHECK(!j.is_unsigned());
    }

    SECTION("signed long"){
      signed long i = 5;
      gsw::json j(i);

      CHECK(!j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK( j.is_integer());
      CHECK(!j.is_floating());
      CHECK(!j.is_bool());
      CHECK( j.is_signed());
      CHECK(!j.is_unsigned());
    }

    SECTION("signed long long"){
      signed long long i = 5;
      gsw::json j(i);

      CHECK(!j.is_object());
      CHECK(!j.is_array());
    CHECK(!j.is_string());
    CHECK( j.is_integer());
    CHECK(!j.is_floating());
    CHECK(!j.is_bool());
      CHECK( j.is_signed());
      CHECK(!j.is_unsigned());
    }
  }

  SECTION("'unsigned integer' type") {
    gsw::json j(5ULL);

    CHECK(!j.is_object());
    CHECK(!j.is_array());
    CHECK(!j.is_string());
    CHECK( j.is_integer());
    CHECK(!j.is_floating());
    CHECK(!j.is_bool());
    CHECK(!j.is_signed());
    CHECK( j.is_unsigned());
  }

  SECTION("'floating point' type") {
    SECTION("float"){
      gsw::json j(0.0f);

      CHECK(!j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK(!j.is_integer());
      CHECK( j.is_floating());
      CHECK(!j.is_bool());
      CHECK( j.is_signed());
      CHECK(!j.is_unsigned());
    }

    SECTION("double"){
      gsw::json j(0.0);

      CHECK(!j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK(!j.is_integer());
      CHECK( j.is_floating());
      CHECK(!j.is_bool());
      CHECK( j.is_signed());
      CHECK(!j.is_unsigned());
    }
  }

  SECTION("'boolean' type") {
    gsw::json j(true);

    CHECK(!j.is_object());
    CHECK(!j.is_array());
    CHECK(!j.is_string());
    CHECK(!j.is_integer());
    CHECK(!j.is_floating());
    CHECK( j.is_bool());
    CHECK(!j.is_signed());
    CHECK(!j.is_unsigned());
  }
}

