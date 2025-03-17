#include <core/traits.hh>

#include <catch2/catch_all.hpp>

// trying to be pretty comprehensive..
TEST_CASE("Add/remove const") {
  STATIC_CHECK(std::same_as<flp::AddConst<int>, const int>);
  STATIC_CHECK(std::same_as<flp::AddConst<const int>, const int>);

  STATIC_CHECK(std::same_as<flp::AddConst<volatile int>, const volatile int>);
  STATIC_CHECK(std::same_as<flp::AddConst<volatile const int>, const volatile int>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<int>, int>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<const int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile int>, volatile int>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile const int>, volatile int>);

  STATIC_CHECK(std::same_as<flp::AddConst<int*>, int* const>);
  STATIC_CHECK(std::same_as<flp::AddConst<const int*>, const int* const>);

  STATIC_CHECK(std::same_as<flp::AddConst<volatile int*>, volatile int* const>);
  STATIC_CHECK(std::same_as<flp::AddConst<volatile const int*>, volatile const int* const>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<int*>, int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<const int*>, const int*>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile int*>, volatile int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile const int*>, volatile const int*>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<int* const>, int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<const int* const>, const int*>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile int* const>, volatile int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile const int* const>, volatile const int*>);
}

TEST_CASE("Add/remove volatile") {
  STATIC_CHECK(std::same_as<flp::AddVolatile<int>, volatile int>);
  STATIC_CHECK(std::same_as<flp::AddVolatile<volatile int>, volatile int>);

  STATIC_CHECK(std::same_as<flp::AddVolatile<const int>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::AddVolatile<const volatile int>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::RemoveVolatile<int>, int>);
  STATIC_CHECK(std::same_as<flp::RemoveVolatile<volatile int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveVolatile<const int>, const int>);
  STATIC_CHECK(std::same_as<flp::RemoveVolatile<const volatile int>, const int>);
}

TEST_CASE("Add/remove CV") {
  STATIC_CHECK(std::same_as<flp::AddCV<int>, const volatile int>);
  STATIC_CHECK(std::same_as<flp::AddCV<volatile int>, const volatile int>);

  STATIC_CHECK(std::same_as<flp::AddCV<const int>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::AddCV<const volatile int>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::RemoveCV<int>, int>);
  STATIC_CHECK(std::same_as<flp::RemoveCV<volatile int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveCV<const int>, int>);
  STATIC_CHECK(std::same_as<flp::RemoveCV<const volatile int>, int>);
}

TEST_CASE("Add/remove reference") {
  STATIC_CHECK(std::same_as<flp::RemoveReference<int>, int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<int&>, int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<int&&>, int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<const int>, const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<const int&>, const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<const int&&>, const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile int>, volatile int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile int&>, volatile int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile int&&>, volatile int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile const int>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile const int&>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile const int&&>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::AddLValueReference<int>, int&>);
  STATIC_CHECK(std::same_as<flp::AddLValueReference<const int>, const int&>);
  STATIC_CHECK(std::same_as<flp::AddLValueReference<const volatile int>, const volatile int&>);
  STATIC_CHECK(std::same_as<flp::AddRValueReference<int>, int&&>);
  STATIC_CHECK(std::same_as<flp::AddRValueReference<const int>, const int&&>);
  STATIC_CHECK(std::same_as<flp::AddRValueReference<const volatile int>, const volatile int&&>);
}

TEST_CASE("Add/remove pointer") {
  STATIC_CHECK(std::same_as<flp::RemovePointer<int>, int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<int*>, int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<int**>, int*>);

  STATIC_CHECK(std::same_as<flp::AddPointer<int>, int*>);
  STATIC_CHECK(std::same_as<flp::AddPointer<int*>, int**>);
  STATIC_CHECK(std::same_as<flp::AddPointer<int**>, int***>);

  STATIC_CHECK(std::same_as<flp::RemovePointer<const int>, const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int*>, const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int**>, const int*>);

  STATIC_CHECK(std::same_as<flp::AddPointer<const int>, const int*>);
  STATIC_CHECK(std::same_as<flp::AddPointer<const int*>, const int**>);
  STATIC_CHECK(std::same_as<flp::AddPointer<const int**>, const int***>);

  STATIC_CHECK(std::same_as<flp::RemovePointer<int* const>, int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int* const>, const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<int* volatile>, int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int* volatile>, const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<int* const volatile>, int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int* const volatile>, const int>);
}

TEST_CASE("Integral Constants") {
  STATIC_CHECK(flp::IntegralConstant<42> {} == 42);
  STATIC_CHECK(flp::IntegralConstant<1138> {} == 1138);
  STATIC_CHECK(flp::IntegralConstant<42>::value == 42);
  STATIC_CHECK(flp::IntegralConstant<1138>::value == 1138);

  STATIC_CHECK(flp::BoolConstant<true> {});
  STATIC_CHECK(not flp::BoolConstant<false> {});
  STATIC_CHECK(flp::BoolConstant<true>::value);
  STATIC_CHECK(not flp::BoolConstant<false>::value);

  STATIC_CHECK(flp::TrueType {});
  STATIC_CHECK(flp::True);
  STATIC_CHECK(not flp::FalseType {});
  STATIC_CHECK(not flp::False);
  STATIC_CHECK(flp::TrueType::value);
  STATIC_CHECK(not flp::FalseType::value);
}

TEST_CASE("Predicates") {
  SECTION("Identity") {
    STATIC_CHECK(flp::Identity<true> {});
    STATIC_CHECK(flp::Identity<true>::value);

    STATIC_CHECK(flp::Identity<42> {} == 42);
    STATIC_CHECK(flp::Identity<42>::value == 42);
    STATIC_CHECK(flp::Identity<4.2> {} == 4.2);
    STATIC_CHECK(flp::Identity<4.2>::value == 4.2);
  }

  SECTION("Addition") {
    STATIC_CHECK(flp::Addition<4, 2> {} == 6);
    STATIC_CHECK(flp::Addition<4, 2>::value == 6);
  }

  SECTION("Subtraction") {
    STATIC_CHECK(flp::Subtraction<4, 2> {} == 2);
    STATIC_CHECK(flp::Subtraction<4, 2>::value == 2);
  }

  SECTION("Multiplication") {
    STATIC_CHECK(flp::Multiplication<4, 2> {} == 8);
    STATIC_CHECK(flp::Multiplication<4, 2>::value == 8);
  }

  SECTION("Division") {
    STATIC_CHECK(flp::Division<4, 2> {} == 2);
    STATIC_CHECK(flp::Division<4, 2>::value == 2);
  }
}

TEST_CASE("Trait testing") {
  SECTION("Is const") {
    STATIC_CHECK(flp::IsConst<const int>);
    STATIC_CHECK(not flp::IsConst<int>);
    STATIC_CHECK(flp::IsConst<const float>);
    STATIC_CHECK(not flp::IsConst<float>);

    STATIC_CHECK(flp::IsConst<flp::AddConst<int>>);
    STATIC_CHECK(not flp::IsConst<flp::RemoveConst<const int>>);

    STATIC_CHECK(flp::IsConst<const int&>);
    STATIC_CHECK(not flp::IsConst<int&>);
    STATIC_CHECK(flp::IsConst<const int&>);
    STATIC_CHECK(not flp::IsConst<int&>);

    STATIC_CHECK(flp::IsConst<const int*>);
    STATIC_CHECK(not flp::IsConst<int*>);
    STATIC_CHECK(flp::IsConst<const int*>);
    STATIC_CHECK(not flp::IsConst<int*>);
  }

  SECTION("Is volatile") {
    STATIC_CHECK(flp::IsVolatile<volatile int>);
    STATIC_CHECK(not flp::IsVolatile<int>);
    STATIC_CHECK(flp::IsVolatile<volatile float>);
    STATIC_CHECK(not flp::IsVolatile<float>);
    STATIC_CHECK(flp::IsVolatile<flp::AddVolatile<int>>);
  }

  SECTION("Is pointer") {
    STATIC_CHECK(flp::IsPointer<int*>);
    STATIC_CHECK(not flp::IsPointer<int>);
    STATIC_CHECK(flp::IsPointer<float*>);
    STATIC_CHECK(not flp::IsPointer<float>);
    STATIC_CHECK(flp::IsPointer<flp::AddPointer<int>>);
  }

  SECTION("Is reference") {
    STATIC_CHECK(flp::IsReference<int&>);
    STATIC_CHECK(not flp::IsReference<int>);
    STATIC_CHECK(flp::IsReference<float&>);
    STATIC_CHECK(not flp::IsReference<float>);
    STATIC_CHECK(flp::IsReference<flp::AddLValueReference<int>>);
    STATIC_CHECK(flp::IsReference<flp::AddRValueReference<int>>);
  }

  SECTION("Is CV") {
    STATIC_CHECK(flp::IsCV<const volatile int>);
    STATIC_CHECK(not flp::IsCV<int>);
    STATIC_CHECK(not flp::IsCV<const int>);
    STATIC_CHECK(not flp::IsCV<volatile int>);
    STATIC_CHECK(flp::IsCV<const volatile float>);
    STATIC_CHECK(not flp::IsCV<float>);
    STATIC_CHECK(not flp::IsCV<const float>);
    STATIC_CHECK(not flp::IsCV<volatile float>);
    STATIC_CHECK(flp::IsCV<flp::AddCV<int>>);
  }
}

