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
  }

  SECTION("'array' type") {
    gsw::json j;
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
    gsw::json j(5LL);

    CHECK(!j.is_object());
    CHECK(!j.is_array());
    CHECK(!j.is_string());
    CHECK( j.is_integer());
    CHECK(!j.is_floating());
    CHECK(!j.is_bool());
    CHECK( j.is_signed());
    CHECK(!j.is_unsigned());
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

