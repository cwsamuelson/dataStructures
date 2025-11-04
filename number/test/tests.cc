#include <core/number.hh>

#include <core/range.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/catch.h>

using namespace flp;

TEST_CASE("`Number`::Comparison") {
  SECTION("Equality comparison with intrinsics") {
    rc::prop("uint64_t", [](const uint64_t integer) {
      return Number{integer} == integer;
    });

    rc::prop("int64_t", [](const int64_t integer) {
      return Number{integer} == integer;
    });
  }

  SECTION("Inequality comparison with intrinsics") {
    rc::prop("uint64_t", [](const uint64_t integer) {
      return Number{integer} == integer;
    });

    rc::prop("int64_t", [](const int64_t integer) {
      return Number{integer} == integer;
    });
  }

  SECTION("Type and sign changes") {
    rc::prop("int64_t", [](const int64_t integer) {
      RC_PRE(integer != 0);
      return Number{integer} != -integer;
    });

    rc::prop("int32_t", [](const int32_t integer) {
      RC_PRE(integer != 0);
      return Number{integer} != -integer;
    });

    rc::prop("uint64_t -> uint8_t", [](const uint64_t start, const uint8_t finish) {
      Number number{start};
      number = finish;
      return number == finish;
    });

    rc::prop("uint8_t -> uint64_t", [](const uint8_t start, const uint64_t finish) {
      Number number{start};
      number = finish;
      return number == finish;
    });
  }

  SECTION("Zero equality") {
    STATIC_CHECK(Number{} == static_cast< uint8_t>(0));
    STATIC_CHECK(Number{} == static_cast<  int8_t>(0));
    STATIC_CHECK(Number{} == static_cast<uint16_t>(0));
    STATIC_CHECK(Number{} == static_cast< int16_t>(0));
    STATIC_CHECK(Number{} == static_cast<uint32_t>(0));
    STATIC_CHECK(Number{} == static_cast< int32_t>(0));
    STATIC_CHECK(Number{} == static_cast<uint64_t>(0));
    STATIC_CHECK(Number{} == static_cast< int64_t>(0));
  }

  SECTION("Basic inequality") {
    STATIC_CHECK(Number{} != static_cast< uint8_t>(1));
    STATIC_CHECK(Number{} != static_cast< uint8_t>(-1));
    STATIC_CHECK(Number{} != static_cast<  int8_t>(1));
    STATIC_CHECK(Number{} != static_cast<  int8_t>(-1));
    STATIC_CHECK(Number{} != static_cast<uint16_t>(1));
    STATIC_CHECK(Number{} != static_cast<uint16_t>(-1));
    STATIC_CHECK(Number{} != static_cast< int16_t>(1));
    STATIC_CHECK(Number{} != static_cast< int16_t>(-1));
    STATIC_CHECK(Number{} != static_cast<uint32_t>(1));
    STATIC_CHECK(Number{} != static_cast<uint32_t>(-1));
    STATIC_CHECK(Number{} != static_cast< int32_t>(1));
    STATIC_CHECK(Number{} != static_cast< int32_t>(-1));
    STATIC_CHECK(Number{} != static_cast<uint64_t>(1));
    STATIC_CHECK(Number{} != static_cast<uint64_t>(-1));
    STATIC_CHECK(Number{} != static_cast< int64_t>(1));
    STATIC_CHECK(Number{} != static_cast< int64_t>(-1));
  }

  SECTION("Basic less") {
    STATIC_CHECK(Number{} <= static_cast< uint8_t>(1));
    STATIC_CHECK(Number{} <  static_cast< uint8_t>(1));
    STATIC_CHECK(Number{} <= static_cast<  int8_t>(1));
    STATIC_CHECK(Number{} <  static_cast<  int8_t>(1));
    STATIC_CHECK(Number{} <= static_cast<uint16_t>(1));
    STATIC_CHECK(Number{} <  static_cast<uint16_t>(1));
    STATIC_CHECK(Number{} <= static_cast< int16_t>(1));
    STATIC_CHECK(Number{} <  static_cast< int16_t>(1));
    STATIC_CHECK(Number{} <= static_cast<uint32_t>(1));
    STATIC_CHECK(Number{} <  static_cast<uint32_t>(1));
    STATIC_CHECK(Number{} <= static_cast< int32_t>(1));
    STATIC_CHECK(Number{} <  static_cast< int32_t>(1));
    STATIC_CHECK(Number{} <= static_cast<uint64_t>(1));
    STATIC_CHECK(Number{} <  static_cast<uint64_t>(1));
    STATIC_CHECK(Number{} <= static_cast< int64_t>(1));
    STATIC_CHECK(Number{} <  static_cast< int64_t>(1));
  }

  SECTION("Basic greater") {
    STATIC_CHECK(Number{} >= static_cast< int8_t>(-1));
    STATIC_CHECK(Number{} >  static_cast< int8_t>(-1));
    STATIC_CHECK(Number{} >= static_cast< int16_t>(-1));
    STATIC_CHECK(Number{} >  static_cast< int16_t>(-1));
    STATIC_CHECK(Number{} >= static_cast< int32_t>(-1));
    STATIC_CHECK(Number{} >  static_cast< int32_t>(-1));
    STATIC_CHECK(Number{} >= static_cast< int64_t>(-1));
    STATIC_CHECK(Number{} >  static_cast< int64_t>(-1));

    STATIC_CHECK(Number{1} >= static_cast< uint8_t>(0));
    STATIC_CHECK(Number{1} >  static_cast< uint8_t>(0));
    STATIC_CHECK(Number{1} >= static_cast<uint16_t>(0));
    STATIC_CHECK(Number{1} >  static_cast<uint16_t>(0));
    STATIC_CHECK(Number{1} >= static_cast<uint32_t>(0));
    STATIC_CHECK(Number{1} >  static_cast<uint32_t>(0));
    STATIC_CHECK(Number{1} >= static_cast<uint64_t>(0));
    STATIC_CHECK(Number{1} >  static_cast<uint64_t>(0));
  }
}

template<auto Type>
struct Foo1 {};
template<Range range>
struct Foo2 {};

TEST_CASE("`Number`::TemplateParameter") {
  // not much to test/check here
  // this is more a 'compile' test

  Foo1<Number{0}> a{};
  Range<Number> b{0, 0};
  Foo2<{Number{}, Number{}}> c{};
}
