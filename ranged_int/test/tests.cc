#include <ranged_int.hh>

#include <catch2/catch_all.hpp>

#include <limits>
#include <memory>

using namespace flp;

#define TEST_TYPE_BOUNDS(TYPE)                                                                                         \
  STATIC_CHECK(std::same_as<DeducedType<{ std::numeric_limits<TYPE>::min(), std::numeric_limits<TYPE>::max() }>, TYPE>)

TEST_CASE("Range type deduction from bounds") {
  SECTION("Intrinsic types, lmits bounds") {
    TEST_TYPE_BOUNDS(uint8_t);
    TEST_TYPE_BOUNDS(uint16_t);
    TEST_TYPE_BOUNDS(uint32_t);
    TEST_TYPE_BOUNDS(uint64_t);
    TEST_TYPE_BOUNDS(int8_t);
    TEST_TYPE_BOUNDS(int16_t);
    TEST_TYPE_BOUNDS(int32_t);
    TEST_TYPE_BOUNDS(int64_t);
  }

  SECTION("Checking some simple cases, and some edge cases") {
    STATIC_CHECK(std::same_as<DeducedType<{ 0, 1 }>, uint8_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ 0, 256 }>, uint16_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ 254, 255 }>, uint8_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ 256, 65535 }>, uint16_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ 256, 257 }>, uint16_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ -1, 127 }>, int8_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ -1, 255 }>, int16_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ -1, 65535 }>, int32_t>);
    STATIC_CHECK(std::same_as<DeducedType<{ 0, 65536 }>, uint32_t>);
  }
}
