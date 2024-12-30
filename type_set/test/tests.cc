#include <type_set.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("Type Set") {
  SECTION("Static style") {
    SECTION("Contains") {
      SECTION("Empty set") {
        STATIC_CHECK(not TypeSet<>::contains<float>());
        STATIC_CHECK(not TypeSet<>::contains<signed int>());
        STATIC_CHECK(not TypeSet<>::contains<unsigned int>());
      }

      SECTION("Single value") {
        STATIC_CHECK(not TypeSet<float>::contains<unsigned int>());
        STATIC_CHECK(not TypeSet<float>::contains<signed int>());

        STATIC_CHECK(not TypeSet<unsigned int>::contains<signed int>());
        STATIC_CHECK(not TypeSet<unsigned int>::contains<float>());

        STATIC_CHECK(not TypeSet<signed int>::contains<unsigned int>());
        STATIC_CHECK(not TypeSet<signed int>::contains<float>());

        STATIC_CHECK(TypeSet<float>::contains<float>());
        STATIC_CHECK(TypeSet<unsigned int>::contains<unsigned int>());
        STATIC_CHECK(TypeSet<signed int>::contains<signed int>());
      }

      SECTION("Multiple values") {
        STATIC_CHECK(TypeSet<signed int, unsigned int, float>::contains<signed int>());
        STATIC_CHECK(TypeSet<signed int, unsigned int, float>::contains<unsigned int>());
        STATIC_CHECK(TypeSet<signed int, unsigned int, float>::contains<float>());

        STATIC_CHECK(not TypeSet<unsigned int, float>::contains<signed int>());
        STATIC_CHECK(not TypeSet<signed int, float>::contains<unsigned int>());
        STATIC_CHECK(not TypeSet<signed int, unsigned int>::contains<float>());
      }
    }
  }

  SECTION("Runtime style") {
    SECTION("Contains") {
      SECTION("Empty set") {
        constexpr TypeSet<> ts;

        STATIC_CHECK(not ts.contains<float>());
        STATIC_CHECK(not ts.contains<signed int>());
        STATIC_CHECK(not ts.contains<unsigned int>());
      }

      SECTION("Single value") {
        constexpr TypeSet<float>        float_ts;
        constexpr TypeSet<signed int>   signed_int_ts;
        constexpr TypeSet<unsigned int> unsigned_int_ts;

        STATIC_CHECK(not float_ts.contains<unsigned int>());
        STATIC_CHECK(not float_ts.contains<signed int>());

        STATIC_CHECK(not unsigned_int_ts.contains<signed int>());
        STATIC_CHECK(not unsigned_int_ts.contains<float>());

        STATIC_CHECK(not signed_int_ts.contains<unsigned int>());
        STATIC_CHECK(not signed_int_ts.contains<float>());

        STATIC_CHECK(float_ts.contains<float>());
        STATIC_CHECK(unsigned_int_ts.contains<unsigned int>());
        STATIC_CHECK(signed_int_ts.contains<signed int>());
      }

      SECTION("Multiple values") {
        constexpr TypeSet<float, signed int, unsigned int> ts;
        constexpr TypeSet<signed int, unsigned int>        si_ui_ts;
        constexpr TypeSet<float, unsigned int>             f_ui_ts;
        constexpr TypeSet<float, signed int>               f_si_ts;

        STATIC_CHECK(ts.contains<signed int>());
        STATIC_CHECK(ts.contains<unsigned int>());
        STATIC_CHECK(ts.contains<float>());

        STATIC_CHECK(not f_ui_ts.contains<signed int>());
        STATIC_CHECK(not f_si_ts.contains<unsigned int>());
        STATIC_CHECK(not si_ui_ts.contains<float>());
      }
    }
  }
}
