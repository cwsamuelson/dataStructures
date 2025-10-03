#include <ranges/all.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <list>
#include <vector>

using namespace flp;

TEMPLATE_TEST_CASE("`Ranges`::AllView", "", std::vector<int>, std::list<int>/*, std::vector<const int>, std::list<const int>*/) {
  TestType container{0, 1, 2, 3};

  for (size_t i{}; const auto& element : container | ranges::all) {
    CHECK(element == i++);
  }
}

TEST_CASE("`Ranges`::AllView") {
  std::array<int, 4> array{0, 1, 2, 3};
  for (size_t i{}; const auto& element : array | ranges::all) {
    CHECK(element == i++);
  }

  int x[]{0, 1, 2, 3};
  for (size_t i{}; const auto& element : x | ranges::all) {
    CHECK(element == i++);
  }

  // for (size_t i{}; const auto& element : {0, 1, 2, 3} | ranges::all) {
  //   CHECK(element == i++);
  // }
}
