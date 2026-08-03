#include <core/property.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Property") {
  Property<int> property(42);

  Property<int> px = property;

  CHECK(property == 42);
  CHECK(px == 42);

  property = 1138;

  CHECK(property == 1138);
  CHECK(px == 1138);

  Property<int> py = px;
  Property<int> pz = property;

  CHECK(py == 1138);
  CHECK(pz == 1138);

  property = 12;

  CHECK(property == 12);
  CHECK(px == 12);
  CHECK(py == 12);
  CHECK(pz == 12);
}
