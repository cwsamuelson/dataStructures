#include <immutable/vector.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

TEST_CASE("Immutable `Vector`") {
  rc::prop("Default Construction", [] {
    const imm::Vector<int> vector;

    RC_ASSERT(vector.empty());
    RC_ASSERT(vector.size() == 0);
    RC_ASSERT_THROWS(vector.front());
    RC_ASSERT_THROWS(vector.back());
    RC_ASSERT_THROWS(vector[0]);
  });

  rc::prop("Initial value", [](const int value) {
    const imm::Vector vector{value};

    RC_ASSERT(not vector.empty());
    RC_ASSERT(vector.size() == 1);
    // RC_ASSERT(vector.front() == value);
    // RC_ASSERT(vector.back() == value);
    // RC_ASSERT(vector[0] == value);
  });

  rc::prop("push_back", [](const int value) {
    const imm::Vector<int> vector;

    // const auto vec = vector.push_back(value);
    // RC_ASSERT(not vec.empty());
    // RC_ASSERT(vec.size() == 1);
    // RC_ASSERT(vec.front() == value);
    // RC_ASSERT(vec.back() == value);
    // RC_ASSERT(vec[0] == value);
  });
}
