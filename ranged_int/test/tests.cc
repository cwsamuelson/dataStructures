#include <ranged_int.hh>

#include <catch2/catch_all.hpp>

#include <limits>
#include <memory>

using namespace flp;

#define TEST_TYPE_BOUNDS(TYPE)                                                                                         \
  STATIC_CHECK(std::same_as<DeducedType<{ std::numeric_limits<TYPE>::min(), std::numeric_limits<TYPE>::max() }>, TYPE>)

template<class F, std::size_t... Is>
void static_for(F func, std::index_sequence<Is...>) {
  (func(Is), ...);
}

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

TEST_CASE("Range bounds testing") {
  SECTION("Uint8_t equivalent") {
    constexpr Range range(0, 255);
    STATIC_CHECK(-1 < range);
    STATIC_CHECK(256 > range);

    STATIC_CHECK(0 == range);
    STATIC_CHECK(255 == range);
  }

  SECTION("Narrow band") {
    constexpr Range range(15, 20);
    STATIC_CHECK(0 < range);
    STATIC_CHECK(255 > range);

    STATIC_CHECK(14 < range);
    STATIC_CHECK(21 > range);

    static_for(
      [&range](const auto index) {
        CHECK((index == range));
      },
      std::integer_sequence<size_t, 15, 16, 17, 18, 19, 20> {});
  }
}

TEST_CASE("Ranges math") {}
