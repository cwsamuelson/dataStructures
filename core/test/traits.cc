#include <catch2/catch_all.hpp>

#include <core/traits.hh>

// trying to be pretty comprehensive..
TEST_CASE("Add/remove const") {
  STATIC_CHECK(std::same_as<flp::AddConst<int>,       const int>);
  STATIC_CHECK(std::same_as<flp::AddConst<const int>, const int>);

  STATIC_CHECK(std::same_as<flp::AddConst<volatile       int>, const volatile int>);
  STATIC_CHECK(std::same_as<flp::AddConst<volatile const int>, const volatile int>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<int>,       int>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<const int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile       int>, volatile int>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile const int>, volatile int>);

  STATIC_CHECK(std::same_as<flp::AddConst<int*>,             int* const>);
  STATIC_CHECK(std::same_as<flp::AddConst<const int*>, const int* const>);

  STATIC_CHECK(std::same_as<flp::AddConst<volatile       int*>, volatile       int* const>);
  STATIC_CHECK(std::same_as<flp::AddConst<volatile const int*>, volatile const int* const>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<int*>,             int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<const int*>, const int*>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile       int*>, volatile int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile const int*>, volatile const int*>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<int* const>,             int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<const int* const>, const int*>);

  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile       int* const>, volatile int*>);
  STATIC_CHECK(std::same_as<flp::RemoveConst<volatile const int* const>, volatile const int*>);
}

TEST_CASE("Add/remove volatile") {
  STATIC_CHECK(std::same_as<flp::AddVolatile<int>,          volatile int>);
  STATIC_CHECK(std::same_as<flp::AddVolatile<volatile int>, volatile int>);

  STATIC_CHECK(std::same_as<flp::AddVolatile<const          int>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::AddVolatile<const volatile int>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::RemoveVolatile<int>,          int>);
  STATIC_CHECK(std::same_as<flp::RemoveVolatile<volatile int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveVolatile<const int>,          const int>);
  STATIC_CHECK(std::same_as<flp::RemoveVolatile<const volatile int>, const int>);
}

TEST_CASE("Add/remove CV") {
  STATIC_CHECK(std::same_as<flp::AddCV<int>,          const volatile int>);
  STATIC_CHECK(std::same_as<flp::AddCV<volatile int>, const volatile int>);

  STATIC_CHECK(std::same_as<flp::AddCV<const          int>, volatile const int>);
  STATIC_CHECK(std::same_as<flp::AddCV<const volatile int>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::RemoveCV<int>,          int>);
  STATIC_CHECK(std::same_as<flp::RemoveCV<volatile int>, int>);

  STATIC_CHECK(std::same_as<flp::RemoveCV<const int>,          int>);
  STATIC_CHECK(std::same_as<flp::RemoveCV<const volatile int>, int>);
}

TEST_CASE("Add/remove reference") {
  STATIC_CHECK(std::same_as<flp::RemoveReference<         int>,                        int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<         int&>,                       int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<         int&&>,                      int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<         const int>,            const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<         const int&>,           const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<         const int&&>,          const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile int>,         volatile       int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile int&>,        volatile       int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile int&&>,       volatile       int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile const int>,   volatile const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile const int&>,  volatile const int>);
  STATIC_CHECK(std::same_as<flp::RemoveReference<volatile const int&&>, volatile const int>);

  STATIC_CHECK(std::same_as<flp::AddLValueReference<               int>,                int&>);
  STATIC_CHECK(std::same_as<flp::AddLValueReference<const          int>, const          int&>);
  STATIC_CHECK(std::same_as<flp::AddLValueReference<const volatile int>, const volatile int&>);
  STATIC_CHECK(std::same_as<flp::AddRValueReference<               int>,                int&&>);
  STATIC_CHECK(std::same_as<flp::AddRValueReference<const          int>, const          int&&>);
  STATIC_CHECK(std::same_as<flp::AddRValueReference<const volatile int>, const volatile int&&>);
}

TEST_CASE("Add/remove pointer") {
  STATIC_CHECK(std::same_as<flp::RemovePointer<int>,   int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<int*>,  int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<int**>, int*>);

  STATIC_CHECK(std::same_as<flp::AddPointer<int>,   int*>);
  STATIC_CHECK(std::same_as<flp::AddPointer<int*>,  int**>);
  STATIC_CHECK(std::same_as<flp::AddPointer<int**>, int***>);

  STATIC_CHECK(std::same_as<flp::RemovePointer<const int>,   const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int*>,  const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int**>, const int*>);

  STATIC_CHECK(std::same_as<flp::AddPointer<const int>,   const int*>);
  STATIC_CHECK(std::same_as<flp::AddPointer<const int*>,  const int**>);
  STATIC_CHECK(std::same_as<flp::AddPointer<const int**>, const int***>);

  STATIC_CHECK(std::same_as<flp::RemovePointer<      int* const>,           int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int* const>,     const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<      int* volatile>,        int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int* volatile>,  const int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<      int* const volatile>,        int>);
  STATIC_CHECK(std::same_as<flp::RemovePointer<const int* const volatile>,  const int>);
}

