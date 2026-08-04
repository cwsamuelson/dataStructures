#include <ranges/transform.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/Gen.h>
#include <rapidcheck/gen/Numeric.h>

using namespace flp;

TEST_CASE("`Ranges`::`TransformView`") {
  rc::prop("Change to a single value of the same type",
    [](const std::vector<int>& container) {
      for (const auto& element : container | views::transform([](const auto& element) {
        return 1138;
      })) {
        RC_ASSERT(element == 1138);
      }
    }
  );

  rc::prop("Change to a single value a different type",
    [](const std::vector<int>& container) {
      for (const auto& element : container | views::transform([](const auto& element) {
        return 11.38;
      })) {
        RC_ASSERT(element == 11.38);
      }
    }
  );
}
