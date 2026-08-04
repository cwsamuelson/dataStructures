#include <ranges/generate.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <list>
#include <vector>

using namespace flp;

TEMPLATE_TEST_CASE("`Ranges`::`GenerateView`", "", std::vector<int>, std::list<int>, (std::array<int, 4>), (std::array<const int, 4>)) {
  for (size_t i{}; const auto item : ranges::generate([] {
      return 0;
    })) {
    CHECK(item == 0);
    if (++i >= 10) {
      break;
    }
  }
}
