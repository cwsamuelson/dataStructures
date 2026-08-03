#include <core/any.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Any`") {
  Any any;
  Any any1;
  Any any2;

  any = any1;
  any = std::move(any2);
  any = Any{};
}
