#include <core/number.hh>

#include <core/range.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Number`::Comparison") {
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
