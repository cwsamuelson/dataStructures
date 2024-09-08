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

TEST_CASE("Using ranged integers") {
  SECTION("Expected underlying types") {
    STATIC_CHECK(std::same_as<u8::Type, uint8_t>);
    STATIC_CHECK(std::same_as<u16::Type, uint16_t>);
    STATIC_CHECK(std::same_as<u32::Type, uint32_t>);
    STATIC_CHECK(std::same_as<u64::Type, uint64_t>);
    STATIC_CHECK(std::same_as<s8::Type, int8_t>);
    STATIC_CHECK(std::same_as<s16::Type, int16_t>);
    STATIC_CHECK(std::same_as<s32::Type, int32_t>);
    STATIC_CHECK(std::same_as<s64::Type, int64_t>);
  }

  SECTION("Ranges determine semantically valid underlying types") {
    STATIC_CHECK(std::same_as<RangedInt<{ 0, 255 }>::Type, uint8_t>);
    STATIC_CHECK(std::same_as<RangedInt<{ 0, 65535 }>::Type, uint16_t>);
    STATIC_CHECK(std::same_as<RangedInt<{ 0ULL, 4294967295ULL }>::Type, uint32_t>);
    STATIC_CHECK(std::same_as<RangedInt<{ 0ULL, 18446744073709551615ULL }>::Type, uint64_t>);
    STATIC_CHECK(std::same_as<RangedInt<{ -128, 127 }>::Type, int8_t>);
    STATIC_CHECK(std::same_as<RangedInt<{ -32768, 32767 }>::Type, int16_t>);
    STATIC_CHECK(std::same_as<RangedInt<{ -2147483648LL, 2147483647LL }>::Type, int32_t>);
    // STATIC_CHECK(std::same_as<RangedInt<{ -9223372036854775808, 9223372036854775807LL }>::Type, int64_t>);

    STATIC_CHECK(std::same_as<RangedInt<{ -255, 1 }>::Type, int16_t>);
  }

  SECTION("Worst case ranges") {
    STATIC_CHECK(WorstCaseRange<{ 0, 0 }, { 0, 0 }, std::plus<>>::range == Range { 0, 0 });
    STATIC_CHECK(WorstCaseRange<{ 0, 10 }, { 0, 10 }, std::plus<>>::range != Range { 0, 0 });
    STATIC_CHECK(WorstCaseRange<{ 0, 10 }, { 0, 10 }, std::plus<>>::range == Range { 0, 20 });
    STATIC_CHECK(WorstCaseRange<{ 0, 255 }, { 0, 255 }, std::plus<>>::range == Range { 0, 510 });
    STATIC_CHECK(WorstCaseRange<{ 0, 65535 }, { 0, 65535 }, std::plus<>>::range == Range { 0, 131070 });
    STATIC_CHECK(WorstCaseRange<{ -1, 255 }, { -1, 255 }, std::plus<>>::range == Range { -2, 510 });
    STATIC_CHECK(WorstCaseRange<{ -128, 127 }, { -128, 127 }, std::plus<>>::range == Range { -256, 254 });
    STATIC_CHECK(WorstCaseRange<{ -128, 127 }, { 0, 255 }, std::plus<>>::range == Range { -128, 382 });

    STATIC_CHECK(WorstCaseRange<{ 0, 255 }, { 0, 255 }, std::minus<>>::range == Range { -255, 255 });
    STATIC_CHECK(WorstCaseRange<{ -128, 127 }, { 0, 255 }, std::minus<>>::range == Range { -383, 127 });
    STATIC_CHECK(WorstCaseRange<{ 0, 255 }, { -128, 127 }, std::minus<>>::range == Range { -127, 383 });
    STATIC_CHECK(WorstCaseRange<{ -128, 127 }, { -128, 127 }, std::minus<>>::range == Range { -255, 255 });
    STATIC_CHECK(WorstCaseRange<{ -128, 127 }, { -128, 127 }, std::minus<>>::range == Range { -255, 255 });

    STATIC_CHECK(WorstCaseRange<{ 0, 255 }, { 0, 255 }, std::multiplies<>>::range == Range { 0, 65025 });
    STATIC_CHECK(WorstCaseRange<{ 0, 255 }, { -128, 127 }, std::multiplies<>>::range == Range { -32640, 32385 });
    STATIC_CHECK(WorstCaseRange<{ -128, 127 }, { 0, 255 }, std::multiplies<>>::range == Range { -32640, 32385 });
    STATIC_CHECK(WorstCaseRange<{ -128, 127 }, { -128, 127 }, std::multiplies<>>::range == Range { -16256, 16384 });
  }

  SECTION("Math with no risk of overflow") {
    SECTION("Safe type promotion guarantee") {
      STATIC_CHECK(std::same_as<decltype(u8 {} + u8 {})::Type, u16::Type>);
      // STATIC_CHECK(std::same_as<decltype(u16 {} + u16 {})::Type, u32::Type>);
      // STATIC_CHECK(std::same_as<decltype(u32 {} + u32 {})::Type, u64::Type>);
      // STATIC_CHECK(std::same_as<decltype(u64{} + u64{})::Type, ...::Type>);
      /*STATIC_CHECK(std::same_as<decltype(s8 {} + s8 {}), u16>);
      STATIC_CHECK(std::same_as<decltype(s16 {} + s16 {}), u32>);
      STATIC_CHECK(std::same_as<decltype(s32 {} + s32 {}), u64>);
      // STATIC_CHECK(std::same_as<decltype(s64{} + s64{}), ...>);

      STATIC_CHECK(std::same_as<decltype(u8 {} - u8 {}), s16>); // worst case 0 - 255 == -255
      STATIC_CHECK(std::same_as<decltype(s8 {} - u8 {}), s16>); // worst case -128 - 255 == -383
      STATIC_CHECK(std::same_as<decltype(s8 {} - s8 {}), s16>); // worst case -128 - -128 == -256

      STATIC_CHECK(std::same_as<decltype(u8{} * u8{}), u16>);
      STATIC_CHECK(std::same_as<decltype(u8{} * s8{}), s16>); // worst case 255 * -128 == -32640
      STATIC_CHECK(std::same_as<decltype(s8{} * s8{}), s16>); // -128 * -128 == 16384; -128 * 127 == -16256
      // I assume this pattern will continue with other types
      */
    }

    /*u8 x1 = 256;
    u8 x2 = 256;

    STATIC_CHECK(x1 + x2 == 512);*/
  }
}

template<typename, typename>
struct X;

template<std::signed_integral LType, std::signed_integral RType>
struct X<LType, RType> {};

template<std::unsigned_integral LType, std::unsigned_integral RType>
struct X<LType, RType> {
  // std::common_type_t<LType, RType>;
};

template<std::signed_integral LType, std::unsigned_integral RType>
struct X<LType, RType> {};

template<std::unsigned_integral LType, std::signed_integral RType>
struct X<LType, RType> {
private:
  X<RType, LType> helper;

public:
};

TEST_CASE("Mixed sign arithmetic") {}
