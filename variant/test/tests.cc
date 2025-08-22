#include <core/variant.hh>

#include <catch2/catch_all.hpp>

#include <variant>

using namespace flp;

template<size_t Size>
struct Buffer {
  char buffer[Size];
};

TEST_CASE("`Variant`") {
  // Padding and alignment overhead makes these tests not so straight forward
  //STATIC_CHECK(sizeof(Variant<int>) == sizeof(int) + 4);
  //STATIC_CHECK(sizeof(Variant<int, int>) == sizeof(int) + 4);
  //STATIC_CHECK(sizeof(Variant<float, double>) == sizeof(double) + 4);
  //STATIC_CHECK(sizeof(Variant<Buffer<0>, Buffer<0>>) == 1) + 4;
  //STATIC_CHECK(sizeof(Variant<Buffer<1>, Buffer<0>>) == 1 + 4);
  //STATIC_CHECK(sizeof(Variant<Buffer<0>, Buffer<1>>) == 1 + 4);
  //STATIC_CHECK(sizeof(Variant<Buffer<1>, Buffer<1>>) == 1 + 4);
  //STATIC_CHECK(sizeof(Variant<Buffer<10>, Buffer<1>>) == 10 + 4);

  STATIC_CHECK(sizeof(Variant<int>) >= sizeof(int));
  STATIC_CHECK(sizeof(Variant<int, int, int, int>) == sizeof(Variant<int>));
  STATIC_CHECK(sizeof(Variant<uint8_t, double>) == sizeof(Variant<double>));
}

TEST_CASE("`Variant`: get") {
  Variant<int, float> variant;

  STATIC_CHECK(std::same_as<std::remove_reference_t<decltype(get<0>(variant))>, int>);
  STATIC_CHECK(std::same_as<std::remove_reference_t<decltype(get<1>(variant))>, float>);
}
