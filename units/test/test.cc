#include <catch2/catch_all.hpp>

template<typename Type>
concept System = requires(Type system) {
  Type();
};

struct SI {};
struct CSG {};
struct Imperial {};

struct DimensionSet {
  size_t length{};
  size_t time{};
};

constexpr DimensionSet LengthSet {
  .length = 1,
  .time = 0,
};

template<DimensionSet>
struct Dimension {};

using LengthDim = Dimension<LengthSet>;

template<Dimension, System>
struct Unit {};

template<System system>
using LengthUnit = Unit<LengthDim, system>;

template<Unit>
struct Quantity {};

template<System system>
using Length = Quantity<LengthUnit<system>>;

TEST_CASE("Units experimentation") {
  Length length1;
  Length length2;

  //length1 + length2;
}
