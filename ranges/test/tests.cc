#include <ranges/all.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <list>
#include <vector>

using namespace flp;

TEMPLATE_TEST_CASE("all", "", std::vector<int>, std::list<int>) {
  TestType container{0, 1, 2, 3};

  for (const auto& element : container | ranges::all) {}
}

TEST_CASE("`Ranges`::Sandbox") {
  std::array<int, 4> array{0, 1, 2, 3};

  for(const auto& element : array | ranges::all) {
  }

  int x[42];
  for (const auto& element : x | ranges::all) {
  }
}
