#include <ranges/transform.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Ranges`", "`TransformView`") {
  std::vector<int> vector{ 0, 0, 1, 2, 3, 4, 0, 0, 5, 6, 7 };

  for (const auto& element : vector | views::transform([](const auto& element) {
    return 1138;
  })) {
    CHECK(element == 1138);
  }

  for (const auto& element : vector | views::transform([](const auto& element) {
    return 11.38;
  })) {
    CHECK(element == 11.38);
  }
}
