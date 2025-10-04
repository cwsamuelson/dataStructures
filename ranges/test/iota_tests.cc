#include <ranges/iota.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Ranges`::`IotaView`") {
  for (size_t counter{}; const auto& element : ranges::iota(0)) {
    CHECK(element == counter++);
  }

  for (size_t counter{10}; const auto& element : ranges::iota(10)) {
    CHECK(element == counter++);
  }
}
