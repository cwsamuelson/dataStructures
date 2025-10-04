#include <ranges/filter.hh>

#include <catch2/catch_all.hpp>

#include <print>
#include <vector>

using namespace flp;

TEST_CASE("`Ranges`::`FilterView`") {
  std::vector<int> vector{ 0, 0, 1, 2, 3, 4, 0, 0, 5, 6, 7 };

  for (const auto& element : vector | views::filter([](const auto& element) {
    return element == 0;
  })) {
    CHECK(element == 0);
  }

  for (const auto& element : vector | views::filter([](const auto& element) {
    return element != 0;
  })) {
    std::println("{}", element);
    CHECK(element != 0);
  }
}
