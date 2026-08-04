#include <immutable/vector.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

TEST_CASE("`Immutable`::`Vector`") {
  SECTION("Default Construction") {
    const imm::Vector<int> vector;

    CHECK(vector.empty());
    CHECK(vector.size() == 0);
    CHECK_THROWS(vector.front());
    CHECK_THROWS(vector.back());
    CHECK_THROWS(vector[0]);
  }

  rc::prop("Initial value", [](const int value) {
    const imm::Vector vector{value};

    RC_ASSERT(not vector.empty());
    RC_ASSERT(vector.size() == 1);
    RC_ASSERT(vector.front() == value);
    RC_ASSERT(vector.back() == value);
    RC_ASSERT(vector[0] == value);
  });

  rc::prop("push_back", [](const int value) {
    const imm::Vector<int> vector;

    const auto vec = vector.push_back(value);
    RC_ASSERT(not vec.empty());
    RC_ASSERT(vec.size() == 1);
    RC_ASSERT(vec.front() == value);
    RC_ASSERT(vec.back() == value);
    RC_ASSERT(vec[0] == value);
  });
}
