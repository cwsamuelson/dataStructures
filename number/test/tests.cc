#include <core/number.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Number`::Comparison") {
  STATIC_CHECK(Number{} == static_cast<uint8_t>(0));
  STATIC_CHECK(Number{} != static_cast<uint8_t>(1));
  STATIC_CHECK(Number{} <= static_cast<uint8_t>(1));
  STATIC_CHECK(Number{} <  static_cast<uint8_t>(1));
  STATIC_CHECK(Number{} != static_cast<uint8_t>(-1));
  STATIC_CHECK(Number{} == static_cast< int8_t>(0));
  STATIC_CHECK(Number{} != static_cast< int8_t>(1));
  STATIC_CHECK(Number{} <= static_cast< int8_t>(1));
  STATIC_CHECK(Number{} <  static_cast< int8_t>(1));
  STATIC_CHECK(Number{} != static_cast< int8_t>(-1));
  STATIC_CHECK(Number{} >= static_cast< int8_t>(-1));
  STATIC_CHECK(Number{} >  static_cast< int8_t>(-1));
  STATIC_CHECK(Number{} == static_cast<uint16_t>(0));
  STATIC_CHECK(Number{} != static_cast<uint16_t>(1));
  STATIC_CHECK(Number{} <= static_cast<uint16_t>(1));
  STATIC_CHECK(Number{} <  static_cast<uint16_t>(1));
  STATIC_CHECK(Number{} != static_cast<uint16_t>(-1));
  STATIC_CHECK(Number{} == static_cast< int16_t>(0));
  STATIC_CHECK(Number{} != static_cast< int16_t>(1));
  STATIC_CHECK(Number{} <= static_cast< int16_t>(1));
  STATIC_CHECK(Number{} <  static_cast< int16_t>(1));
  STATIC_CHECK(Number{} != static_cast< int16_t>(-1));
  STATIC_CHECK(Number{} >= static_cast< int16_t>(-1));
  STATIC_CHECK(Number{} >  static_cast< int16_t>(-1));
  STATIC_CHECK(Number{} == static_cast<uint32_t>(0));
  STATIC_CHECK(Number{} != static_cast<uint32_t>(1));
  STATIC_CHECK(Number{} <= static_cast<uint32_t>(1));
  STATIC_CHECK(Number{} <  static_cast<uint32_t>(1));
  STATIC_CHECK(Number{} != static_cast<uint32_t>(-1));
  STATIC_CHECK(Number{} == static_cast< int32_t>(0));
  STATIC_CHECK(Number{} != static_cast< int32_t>(1));
  STATIC_CHECK(Number{} <= static_cast< int32_t>(1));
  STATIC_CHECK(Number{} <  static_cast< int32_t>(1));
  STATIC_CHECK(Number{} != static_cast< int32_t>(-1));
  STATIC_CHECK(Number{} >= static_cast< int32_t>(-1));
  STATIC_CHECK(Number{} >  static_cast< int32_t>(-1));
  STATIC_CHECK(Number{} == static_cast<uint64_t>(0));
  STATIC_CHECK(Number{} != static_cast<uint64_t>(1));
  STATIC_CHECK(Number{} <= static_cast<uint64_t>(1));
  STATIC_CHECK(Number{} <  static_cast<uint64_t>(1));
  STATIC_CHECK(Number{} != static_cast<uint64_t>(-1));
  STATIC_CHECK(Number{} == static_cast< int64_t>(0));
  STATIC_CHECK(Number{} != static_cast< int64_t>(1));
  STATIC_CHECK(Number{} <= static_cast< int64_t>(1));
  STATIC_CHECK(Number{} <  static_cast< int64_t>(1));
  STATIC_CHECK(Number{} != static_cast< int64_t>(-1));
  STATIC_CHECK(Number{} >= static_cast< int64_t>(-1));
  STATIC_CHECK(Number{} >  static_cast< int64_t>(-1));
}
