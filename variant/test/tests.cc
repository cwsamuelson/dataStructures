#include <core/variant.hh>

#include <catch2/catch_all.hpp>

#include <variant>

using namespace flp;

template<size_t Size>
struct Buffer {
  char buffer[Size];
};

TEST_CASE("`Variant`") {
  STATIC_CHECK(sizeof(Variant<int>) == sizeof(int) + 4);
  STATIC_CHECK(sizeof(Variant<int, int>) == sizeof(int) + 4);
  STATIC_CHECK(sizeof(Variant<float, double>) == sizeof(double) + 4);
  STATIC_CHECK(sizeof(Variant<Buffer<0>, Buffer<0>>) == 1) + 4;
  STATIC_CHECK(sizeof(Variant<Buffer<1>, Buffer<0>>) == 1 + 4);
  STATIC_CHECK(sizeof(Variant<Buffer<0>, Buffer<1>>) == 1 + 4);
  STATIC_CHECK(sizeof(Variant<Buffer<1>, Buffer<1>>) == 1 + 4);
  STATIC_CHECK(sizeof(Variant<Buffer<10>, Buffer<1>>) == 10 + 4);
}
