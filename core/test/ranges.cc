#include "core/ranges.hh"

#include <catch2/catch_all.hpp>

#include <vector>

TEST_CASE("core::Ranges") {
  SECTION("C-Array") {
    const int c_array[] = { 0, 1, 2, 3, 4 };

    auto view = flp::views::All(c_array);
  }

  SECTION("std containers") {
    const std::vector<int> vector{ 0, 1, 2, 3, 4 };

    auto view = flp::views::All(vector);
  }
}
