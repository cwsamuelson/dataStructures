#include <catch2/catch_all.hpp>

#include <allocator/base.hh>
#include <context.hh>

using namespace flp;

TEST_CASE("Placement-new") {
  auto* x = new (flp::allocator()) int;
}
