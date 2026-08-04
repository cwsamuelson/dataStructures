#include <ranges/iota.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/Gen.h>
#include <rapidcheck/gen/Numeric.h>

using namespace flp;

TEST_CASE("`Ranges`::`IotaView`") {
  rc::prop("Iota increments by one every time", [](const size_t start, const uint16_t count){
    for (size_t counter{start}; const auto item : ranges::iota(start)) {
      RC_ASSERT(item == counter++);

      if (counter >= count) {
        break;
      }
    }
  });

  // uint16_t used to constrain possible values, but allow rc to check with max values etc
  rc::prop("Results remain in bounds", [](const uint16_t start){
    const auto end = *rc::gen::suchThat<uint16_t>([start](const uint16_t x) {
      return x >= start;
    });

    for (size_t counter{start}; const auto& element : ranges::iota(start, end)) {
      RC_ASSERT(element == counter++);

      RC_ASSERT(element >= start);
      RC_ASSERT(element < end);
    }
  });
}
