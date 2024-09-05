#include <catch2/catch_all.hpp>

#include <core/traits.hh>

TEST_CASE("Add const") {
// const
  STATIC_CHECK(std::same_as<flp::AddConst<int>,       const int>);
  STATIC_CHECK(std::same_as<flp::AddConst<const int>, const int>);

  STATIC_CHECK(std::same_as<flp::AddConst<volatile       int>, const volatile int>);
  STATIC_CHECK(std::same_as<flp::AddConst<volatile const int>, const volatile int>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<int>,       int>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<const int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile       int>, volatile int>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile const int>, volatile int>);

// volatile
  STATIC_CHECK(std::same_as<flp::AddVolatile<int>,          volatile int>);
  STATIC_CHECK(std::same_as<flp::AddVolatile<volatile int>, volatile int>);

  STATIC_CHECK(std::same_as<flp::AddVolatile<const          int>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::AddVolatile<const volatile int>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::RemoveVolatile<int>,          int>);
  STATIC_CHECK(std::same_as<flp::RemoveVolatile<volatile int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveVolatile<const int>,          const int>);
  STATIC_CHECK(std::same_as<flp::RemoveVolatile<const volatile int>, const int>);

// CV
  STATIC_CHECK(std::same_as<flp::AddCV<int>,          const volatile int>);
  STATIC_CHECK(std::same_as<flp::AddCV<volatile int>, const volatile int>);

  STATIC_CHECK(std::same_as<flp::AddCV<const          int>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::AddCV<const volatile int>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::RemoveCV<int>,          int>);
  STATIC_CHECK(std::same_as<flp::RemoveCV<volatile int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveCV<const int>,          int>);
  STATIC_CHECK(std::same_as<flp::RemoveCV<const volatile int>, int>);
}

