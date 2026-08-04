#include <ranges/take.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/Gen.h>
#include <rapidcheck/gen/Numeric.h>

#include <vector>

using namespace flp;

TEST_CASE("`Ranges`::`TakeView`") {
  rc::prop("Only take what's available", [](const uint16_t size, const uint16_t amount) {
    const auto container = *rc::gen::container<std::vector<int>>(size, rc::gen::arbitrary<int>());

    size_t count{};
    for (const auto& item : container | views::take(amount)) {
      RC_ASSERT(item == container.at(count++));
    }

    RC_ASSERT(count <= size);
    RC_ASSERT(count <= amount);
    RC_ASSERT(count == std::min(amount, size));
  });
}
