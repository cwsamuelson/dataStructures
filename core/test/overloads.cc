#include <core/overloads.hh>

#include <catch2/catch_all.hpp>

TEST_CASE("core::Lambda Overloads") {
  flp::Overloads overloads{
    [](){},
    [](int){},
    [](float){}
  };

  CHECK_NOTHROW(overloads());
  CHECK_NOTHROW(overloads(1138));
  CHECK_NOTHROW(overloads(4.2F));
}
