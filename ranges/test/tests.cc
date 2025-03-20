#include <ranges/all.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <list>
#include <vector>

using namespace flp;

TEMPLATE_TEST_CASE("all", "", std::vector, std::array, std::list) {
  TestType<int> container{0, 1, 2, 3};

  ranges::All(container);
}

