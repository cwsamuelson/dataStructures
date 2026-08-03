#include <ranges/filter.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <list>
#include <vector>

using namespace flp;

TEMPLATE_TEST_CASE("`Ranges`::`FilterView`", "", std::vector<int>, std::list<int>, (std::array<int, 11>), (std::array<const int, 11>)) {
  TestType container{ 0, 0, 1, 2, 3, 4, 0, 0, 5, 6, 7 };

  for (size_t i{}; const auto& element : container | views::filter([](const auto& element) {
        return element == 0;
    })) {
    CHECK(element == 0);
  }

  for (size_t i{}; const auto& element : container | views::filter([](const auto& element) {
        return element != 0;
    })) {
    CHECK(element != 0);
  }
}
