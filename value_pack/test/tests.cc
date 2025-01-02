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

  STATIC_CHECK(ValuePack<1>::Prepend<0> {} == ValuePack<0, 1> {});
  STATIC_CHECK(ValuePack<0>::Append<1> {} == ValuePack<0, 1> {});

  STATIC_CHECK(ValuePack<1, 2>::Prepend<0> {} == ValuePack<0, 1, 2> {});
  STATIC_CHECK(ValuePack<0, 1>::Append<2> {} == ValuePack<0, 1, 2> {});
}

template<auto Value>
struct Identity {
  static constexpr auto value = Value;
};

TEST_CASE("ValuePack Transform") {
  // STATIC_CHECK(ValuePack<>::Transform<Identity> {} == ValuePack<> {});
}
