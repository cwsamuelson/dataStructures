#include <core/number.hh>

#include <core/range.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/catch.h>

using namespace flp;

TEST_CASE("`Number`::Comparison") {
  SECTION("Equality comparison with intrinsics") {
    rc::prop("uint64_t", [](const uint64_t integer) {
      RC_ASSERT(Number{integer} == integer);
    });

    rc::prop("int64_t", [](const int64_t integer) {
      RC_ASSERT(Number{integer} == integer);
    });
  }

  SECTION("Inequality comparison with intrinsics") {
    rc::prop("uint64_t", [](const uint64_t integer) {
      RC_ASSERT(Number{integer} == integer);
    });

    rc::prop("int64_t", [](const int64_t integer) {
      RC_ASSERT(Number{integer} == integer);
    });
  }

  SECTION("Type and sign changes") {
    rc::prop("int64_t", [] {
      const auto integer = *rc::gen::nonZero<int64_t>();
      RC_ASSERT(Number{integer} != -integer);
    });

    rc::prop("int32_t", [] {
      const auto integer = *rc::gen::nonZero<int64_t>();
      RC_ASSERT(Number{integer} != -integer);
    });

    rc::prop("-int64_t", [] {
      const auto integer = *rc::gen::nonZero<int64_t>();
      RC_ASSERT(-Number{integer} == -integer);
    });

    rc::prop("-int32_t", [] {
      const auto integer = *rc::gen::nonZero<int64_t>();
      RC_ASSERT(-Number{integer} == -integer);
    });

    rc::prop("uint64_t -> uint8_t", [](const uint64_t start, const uint8_t finish) {
      Number number{start};
      number = finish;
      RC_ASSERT(number == finish);
    });

    rc::prop("uint8_t -> uint64_t", [](const uint8_t start, const uint64_t finish) {
      Number number{start};
      number = finish;
      RC_ASSERT(number == finish);
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
    STATIC_CHECK(Number{} != static_cast< uint8_t>( 1));
    STATIC_CHECK(Number{} != static_cast< uint8_t>(-1));
    STATIC_CHECK(Number{} != static_cast<  int8_t>( 1));
    STATIC_CHECK(Number{} != static_cast<  int8_t>(-1));
    STATIC_CHECK(Number{} != static_cast<uint16_t>( 1));
    STATIC_CHECK(Number{} != static_cast<uint16_t>(-1));
    STATIC_CHECK(Number{} != static_cast< int16_t>( 1));
    STATIC_CHECK(Number{} != static_cast< int16_t>(-1));
    STATIC_CHECK(Number{} != static_cast<uint32_t>( 1));
    STATIC_CHECK(Number{} != static_cast<uint32_t>(-1));
    STATIC_CHECK(Number{} != static_cast< int32_t>( 1));
    STATIC_CHECK(Number{} != static_cast< int32_t>(-1));
    STATIC_CHECK(Number{} != static_cast<uint64_t>( 1));
    STATIC_CHECK(Number{} != static_cast<uint64_t>(-1));
    STATIC_CHECK(Number{} != static_cast< int64_t>( 1));
    STATIC_CHECK(Number{} != static_cast< int64_t>(-1));

    rc::prop("N != N", [] {
      const auto integers = *rc::gen::unique<std::vector<uint64_t>>(2, rc::gen::arbitrary<uint64_t>());
      RC_ASSERT(Number{integers[0]} != Number{integers[1]});
    });

    rc::prop("N != u64_t", [](const uint64_t left, const uint64_t right) {
      const auto integers = *rc::gen::unique<std::vector<uint64_t>>(2, rc::gen::arbitrary<uint64_t>());
      RC_ASSERT(Number{integers[0]} != integers[1]);
    });

    rc::prop("u64_t != N", [](const uint64_t left, const uint64_t right) {
      const auto integers = *rc::gen::unique<std::vector<uint64_t>>(2, rc::gen::arbitrary<uint64_t>());
      RC_ASSERT(integers[0] != Number{integers[1]});
    });
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
    rc::prop("uint32_t >", [] {
      const auto integer = *rc::gen::nonZero<uint32_t>();
      RC_ASSERT(integer > Number{});
    });

    rc::prop("uint32_t >=", [](const uint32_t integer) {
      RC_ASSERT(integer >= Number{});
    });

    rc::prop("> -1", [](const uint64_t integer) {
      RC_ASSERT(Number{integer} > -1);
    });

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

TEST_CASE("`Number`::Arithmetic") {
  SECTION("Addition") {
    rc::prop("N + N : 64", [] {
      const auto&& [lhs ,rhs] = *rc::gen::suchThat<std::tuple<uint64_t, uint64_t>>(
        [](const std::tuple<uint64_t, uint64_t>& values) {
          const auto [lhs, rhs] = values;
          return (std::numeric_limits<uint64_t>::max() - lhs) < rhs;
        }
      );

      RC_ASSERT((Number{lhs} + Number{rhs}) == (lhs + rhs));
    });

    rc::prop("N + N", [](const uint32_t number, const uint32_t integer) {
      RC_ASSERT((Number{number} + Number{integer}) == static_cast<int64_t>((static_cast<uint64_t>(number) + static_cast<uint64_t>(integer))));
    });

    rc::prop("N + u32_t", [](const uint32_t number, const uint32_t integer) {
      RC_ASSERT((Number{number} + integer) == (static_cast<uint64_t>(number) + static_cast<uint64_t>(integer)));
    });

    rc::prop("N + s32_t", [](const uint32_t number, const int32_t integer) {
      RC_ASSERT((Number{number} + integer) == (static_cast<int64_t>(number) + static_cast<int32_t>(integer)));
    });

    rc::prop("u32_t + N", [](const uint32_t integer, const uint32_t number) {
      RC_ASSERT((integer + Number{number}) == (static_cast<uint64_t>(integer) + static_cast<uint64_t>(number)));
    });

    rc::prop("s32_t + N", [](const int32_t integer, const uint32_t number) {
      RC_ASSERT((integer + Number{number}) == static_cast<int64_t>((static_cast<int64_t>(integer) + static_cast<uint64_t>(number))));
    });
  }

  SECTION("Subtraction") {
  }

  SECTION("Multiplication") {
  }

  SECTION("Division") {
  }

  SECTION("Modulus") {
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
