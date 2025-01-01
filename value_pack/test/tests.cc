#include <value_pack.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("Value Pack") {
  STATIC_CHECK(ValuePack<> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<0> {} == ValuePack<0> {});
  STATIC_CHECK(ValuePack<0, 1> {} == ValuePack<0, 1> {});

  STATIC_CHECK(ValuePack<0, 1> {} != ValuePack<1> {});
  STATIC_CHECK(ValuePack<0, 1> {} != ValuePack<1, 0> {});

  STATIC_CHECK(ValuePack<>::Prepend<0> {} == ValuePack<0> {});
  STATIC_CHECK(ValuePack<>::Append<0> {} == ValuePack<0> {});
}
