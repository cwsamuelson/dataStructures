#include <ranges/iota.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Ranges`::`IotaView`") {
  auto iota_range = ranges::iota(0);
  auto iota_iter = iota_range.begin();
  
  for (auto i = 0uz; i < 100; ++i) {
    CHECK(*(iota_iter++) == i);
  }

  for (size_t counter{}; const auto& element : ranges::iota(0, 1000)) {
    CHECK(element == counter++);
    CHECK(element < 1000);
  }
}
