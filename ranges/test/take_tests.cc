#include <ranges/take.hh>

#include <catch2/catch_all.hpp>

#include <vector>

using namespace flp;

TEST_CASE("`Ranges`::`TakeView`") {
  std::vector<int> container{ 0, 1, 2, 3, 4, 5, 6 };

  for (auto i = 0uz; const auto& element : container | views::take(4)) {
    CHECK(i < 4);
    CHECK(element == i++);
  }
}
