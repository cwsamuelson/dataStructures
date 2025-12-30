#include <ranged_int.hh>
#include <std_ints.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/Gen.h>
#include <rapidcheck/gen/Numeric.h>

#include <limits>
#include <memory>

using namespace flp;

#define TEST_TYPE_BOUNDS(TYPE) \
  STATIC_CHECK(std::same_as<DeducedType<Range{ std::numeric_limits<TYPE>::min(), std::numeric_limits<TYPE>::max() }>, TYPE>)

template<class F, std::size_t... Is>
void static_for(F func, std::index_sequence<Is...>) {
  (func(Is), ...);
}

TEST_CASE("`DeducedType`::Range type deduction from bounds") {
  SECTION("Intrinsic types, limits bounds") {
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
    STATIC_CHECK(std::same_as<DeducedType<Range{ 0, 1 }>, uint8_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ 0, 256 }>, uint16_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ 254, 255 }>, uint8_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ 256, 65535 }>, uint16_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ 256, 257 }>, uint16_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ -1, 127 }>, int8_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ -1, 255 }>, int16_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ -1, 65535 }>, int32_t>);
    STATIC_CHECK(std::same_as<DeducedType<Range{ 0, 65536 }>, uint32_t>);
  }
}

TEST_CASE("`Range`::Range bounds testing") {
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

TEST_CASE("`Range`::Ranges math") {
  STATIC_CHECK(Range{0, 0} == Range{0, 0});
  STATIC_CHECK(Range{0, 1} != Range{0, 0});
  STATIC_CHECK(Range{0, 0} != Range{0, 1});
  STATIC_CHECK(Range{1, 0} != Range{0, 0});
  STATIC_CHECK(Range{0, 0} != Range{1, 0});

  STATIC_CHECK(Range{0, 0} + 1 == Range{1, 1});
  STATIC_CHECK(Range{0, 0} - 1 == Range{-1, -1});

  STATIC_CHECK(Range{0, 0} + Range{1, 2} == Range{1, 2});
  STATIC_CHECK(Range{0, 0} - Range{1, 2} == Range{-1, -2});
}

TEST_CASE("`RangedInt`::Using ranged integers") {
  SECTION("Expected underlying types") {
    STATIC_CHECK(std::same_as<u8::Type, uint8_t>);
    STATIC_CHECK(std::same_as<s8::Type, int8_t>);

    STATIC_CHECK(std::same_as<u16::Type, uint16_t>);
    STATIC_CHECK(std::same_as<s16::Type, int16_t>);

    STATIC_CHECK(std::same_as<u32::Type, uint32_t>);
    STATIC_CHECK(std::same_as<s32::Type, int32_t>);

    STATIC_CHECK(std::same_as<u64::Type, uint64_t>);
    STATIC_CHECK(std::same_as<s64::Type, int64_t>);
  }

  SECTION("Ranges determine semantically valid underlying types") {
    STATIC_CHECK(std::same_as<RangedInt<Range{ 0, 255 }>::Type, uint8_t>);
    STATIC_CHECK(std::same_as<RangedInt<Range{ 0, 65535 }>::Type, uint16_t>);
    STATIC_CHECK(std::same_as<RangedInt<Range{ 0ULL, 4294967295ULL }>::Type, uint32_t>);
    STATIC_CHECK(std::same_as<RangedInt<Range{ 0ULL, 18446744073709551615ULL }>::Type, uint64_t>);
    STATIC_CHECK(std::same_as<RangedInt<Range{ -128, 127 }>::Type, int8_t>);
    STATIC_CHECK(std::same_as<RangedInt<Range{ -32768, 32767 }>::Type, int16_t>);
    STATIC_CHECK(std::same_as<RangedInt<Range{ -2147483648LL, 2147483647LL }>::Type, int32_t>);
    // STATIC_CHECK(std::same_as<RangedInt<{ -9223372036854775808, 9223372036854775807LL }>::Type, int64_t>);

    STATIC_CHECK(std::same_as<RangedInt<Range{ -255, 1 }>::Type, int16_t>);
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

  SECTION("STD types") {
    STATIC_CHECK(std::same_as<u8::Type,  uint8_t>);
    STATIC_CHECK(std::same_as<u16::Type, uint16_t>);
    STATIC_CHECK(std::same_as<u32::Type, uint32_t>);
    STATIC_CHECK(std::same_as<u64::Type, uint64_t>);

    STATIC_CHECK(std::same_as<s8::Type,  int8_t>);
    STATIC_CHECK(std::same_as<s16::Type, int16_t>);
    STATIC_CHECK(std::same_as<s32::Type, int32_t>);
    STATIC_CHECK(std::same_as<s64::Type, int64_t>);
  }

  SECTION("Testing") {
    WorstCaseRange<{0u, std::numeric_limits<uint32_t>::max()}, {0, 0}, std::plus<>>{};
    WorstCaseRange<{0u, std::numeric_limits<uint32_t>::max()}, {0, 1}, std::plus<>>{};

    STATIC_CHECK(WorstCaseRange<{0u, std::numeric_limits<uint32_t>::max()}, {0, 0}, std::plus<>>::range == u32::range);
    STATIC_CHECK(WorstCaseRange<{0u, std::numeric_limits<uint32_t>::max()}, {0, 1}, std::plus<>>::range == u32::range);

    // STATIC_CHECK(Range{0u, std::numeric_limits<uint32_t>::max()} + Range{0, 1} == Range{0, 0});

    // STATIC_CHECK(std::same_as<WorstCaseRange<{0u, std::numeric_limits<uint32_t>::max()}, {0, 1}, std::plus<>>::Type, u64::Type>);
  }

  SECTION("Math with no risk of overflow") {
    SECTION("Safe type promotion guarantee") {
      STATIC_CHECK(std::same_as<decltype(u8 {} + u8 {})::Type, u16::Type>);
      STATIC_CHECK(std::same_as<decltype(u16 {} + u16 {})::Type, u32::Type>);
      // STATIC_CHECK(std::same_as<decltype(u32 {} + u32 {})::Type, u64::Type>);
      // STATIC_CHECK(std::same_as<decltype(u64{} + u64{})::Type, ...::Type>);

      STATIC_CHECK(std::same_as<decltype(s8 {} + s8 {})::Type, s16::Type>);
      STATIC_CHECK(std::same_as<decltype(s16 {} + s16 {})::Type, s32::Type>);
      // STATIC_CHECK(std::same_as<decltype(s32 {} + s32 {})::Type, s64::Type>);
      // STATIC_CHECK(std::same_as<decltype(s64{} + s64{}), ...>);

      /*STATIC_CHECK(std::same_as<decltype(u8 {} - u8 {}), s16>); // worst case 0 - 255 == -255
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

  SECTION("Basics") {
    SECTION("Using ranged integers together") {
      STATIC_CHECK(RangedInt<{10, 20}>{} == RangedInt<{10, 30}>{});
      STATIC_CHECK(RangedInt<{10, 20}>{15} == RangedInt<{5, 30}>{15});
    }

    SECTION("Mixed use with intrinsics") {
      STATIC_CHECK(RangedInt<{10, 20}>{} == 10);
      STATIC_CHECK(RangedInt<{10, 20}>{15} == 15);
      STATIC_CHECK(RangedInt<{10, 20}>{15} <= 16);
      STATIC_CHECK(RangedInt<{10, 20}>{15} >= 14);
      STATIC_CHECK(RangedInt<{10, 20}>{15} < 16);
      STATIC_CHECK(RangedInt<{10, 20}>{15} > 14);

      RangedInt<{10, 20}> r_int{};

      CHECK_NOTHROW(r_int = 15);
      CHECK(r_int == 15);
      CHECK(r_int <= 15);
      CHECK(r_int >= 15);

      CHECK(r_int >= 14);
      CHECK(r_int <= 16);
      CHECK(r_int > 14);
      CHECK(r_int < 16);

      CHECK_THROWS(r_int = 21);
      CHECK(r_int != 21);
      CHECK(r_int == 15);
    }
  }
}

TEST_CASE("Mixed sign arithmetic") {}

TEST_CASE("`RangedInt`::Props") {
  SECTION("u8") {
    rc::prop("Within Range", [] {
      const auto value = *rc::gen::inRange(0, 255);
      const RangedInt<{0, 255}> ranged_value = value;
      RC_ASSERT(ranged_value == value);
    });

    rc::prop("Out of Range", [] {
      const auto value = *rc::gen::inRange(256, 100'000'000);
      RC_ASSERT_THROWS(u8{value});
    });
  }

  SECTION("u16") {
    rc::prop("Within Range", [] {
      const auto value = *rc::gen::inRange(0, 65535);
      const RangedInt<{0, 65535}> ranged_value = value;
      RC_ASSERT(ranged_value == value);
    });

    rc::prop("Out of Range", [] {
      const auto value = *rc::gen::inRange(65536, 100'000'000);
      RC_ASSERT_THROWS(u16{value});
    });
  }

  SECTION("Arbitrary") {
    rc::prop("Out of Range", [] {
      const auto value = *rc::gen::inRange(0, 255);
      using Integer = RangedInt<{256, 10'000}>;
      RC_ASSERT_THROWS(Integer{value});
    });

    rc::prop("Within Range", [] {
      const auto value = *rc::gen::inRange(15, 100);
      const RangedInt<{15, 100}> ranged_value = value;
      RC_ASSERT(ranged_value == value);
    });
  }
}

TEST_CASE("`RangedInt`::Arithmetic Props") {
  SECTION("Arithmetic shifts range bounds") {
    rc::prop("Addition", [] {
      const u8 x = *rc::gen::inRange(0, 255);
      const u8 y = *rc::gen::inRange(0, 255);
      auto z = x + y;

      SECTION("In range") {
        const auto value = *rc::gen::inRange(0, 510);
        z = value;

        RC_ASSERT(z == value);
      }

      SECTION("Out of Range") {
        const auto value = *rc::gen::inRange(511, 100'000'000);
        RC_ASSERT_THROWS(decltype(z){value});
      }
    });

    rc::prop("subtraction", [] {
      const u8 x = *rc::gen::inRange(0, 255);
      const u8 y = *rc::gen::inRange(0, 255);
      auto z = x - y;

      SECTION("In range") {
        const auto value = *rc::gen::inRange(-255, 255);
        z = value;

        RC_ASSERT(z == value);
      }

      SECTION("Above Range") {
        const auto value = *rc::gen::inRange(256, 100'000'000);
        RC_ASSERT_THROWS(decltype(z){value});
      }

      SECTION("Below Range") {
        const auto value = *rc::gen::inRange(-100'000'000, -254);
        RC_ASSERT_THROWS(decltype(z){value});
      }
    });
  }
}
