#include <ranges/drop.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/Gen.h>
#include <rapidcheck/gen/Numeric.h>

using namespace flp;

TEST_CASE("`Ranges`::`DropView`") {
  rc::prop("", [](const uint16_t size, const uint16_t amount) {
    const auto container = *rc::gen::container<std::vector<int>>(size, rc::gen::arbitrary<int>());

    size_t count{};
    for (const auto& item : container | views::drop(amount)) {
      RC_ASSERT(item == container.at(amount + count++));
    }

    const uint16_t post_drop_count = size - (amount <= size ? amount : size);

    RC_ASSERT(count <= size);
    RC_ASSERT(count <= post_drop_count);
    RC_ASSERT(count == std::min(size, post_drop_count));
  });
}
