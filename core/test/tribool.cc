#include <core/tribool.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`TriBool`::constexpr") {
  STATIC_CHECK(not static_cast<bool>(TriBool{}));
  STATIC_CHECK(not (not TriBool{}));
  STATIC_CHECK(TriBool{true});
  STATIC_CHECK(not TriBool{false});

  {
    constexpr TriBool tb{};
    if constexpr (tb) {
      CHECK(false);
    } else if constexpr (!tb) {
      CHECK(false);
    } else {
      CHECK(true);
    }
  }

  {
    constexpr TriBool tb{TriBool::State::True};
    if constexpr (tb) {
      CHECK(true);
    } else if constexpr (!tb) {
      CHECK(false);
    } else {
      CHECK(false);
    }
  }

  {
    constexpr TriBool tb{TriBool::State::False};
    if constexpr (tb) {
      CHECK(false);
    } else if constexpr (!tb) {
      CHECK(true);
    } else {
      CHECK(false);
    }
  }
}

// keep in mind, TriBool default state is 'indeterminate', so the below
// behaviour will look very strange relative to a standard bool.
TEST_CASE("`TriBool`::stateful") {
  TriBool tb;
  CHECK(not static_cast<bool>(tb));
  CHECK(not (not tb));

  tb = true;
  CHECK(tb);
  CHECK(not (not tb));

  tb.clear();
  CHECK(not static_cast<bool>(tb));
  CHECK(not (not tb));
}
