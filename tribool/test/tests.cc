#include <tribool.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("template") {
  STATIC_CHECK(not static_cast<bool>(TriBool{}));
  STATIC_CHECK(not (not TriBool{}));
  STATIC_CHECK(TriBool{true});
  STATIC_CHECK(not TriBool{false});

  constexpr TriBool tb{};
  if constexpr (tb) {
    CHECK(false);
  } else if constexpr (!tb) {
    CHECK(false);
  } else {
    CHECK(true);
  }
}
