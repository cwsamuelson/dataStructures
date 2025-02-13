#include <polymorphic_value.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct Base {
};

struct Derived : Base {
};

TEST_CASE("template") {
  PolymorphicValue<Base> node;
}

