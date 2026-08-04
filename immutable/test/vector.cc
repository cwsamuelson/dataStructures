#include <immutable/vector.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

#include <print>

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

  rc::prop("Single initial value", [](const int value) {
    const imm::Vector vector{value};

    RC_ASSERT(not vector.empty());
    RC_ASSERT(vector.size() == 1);
    RC_ASSERT(vector.front() == value);
    RC_ASSERT(vector.back() == value);
    RC_ASSERT(vector[0] == value);
  });

  rc::prop("Multi initial value", [](const int value1, const int value2) {
    const imm::Vector vector{value1, value2};

    RC_ASSERT(not vector.empty());
    RC_ASSERT(vector.size() == 2);
    RC_ASSERT(vector.front() == value1);
    RC_ASSERT(vector.back() == value2);
    RC_ASSERT(vector[0] == value1);
    RC_ASSERT(vector[1] == value2);
  });

  rc::prop("Copy constructor", [](const std::vector<int> initial_data) {
    const imm::Vector vector0(initial_data);
    const imm::Vector vector1(vector0);

    RC_ASSERT(vector0.empty() == vector1.empty());
    RC_ASSERT(vector0.size()  == vector1.size());
    if (not vector0.empty() and not vector1.empty()) {
      RC_ASSERT(vector0.front() == vector1.front());
      RC_ASSERT(vector0.back()  == vector1.back());
    }
  });

  rc::prop("Copy from std::vector", [](const std::vector<int> initial_data) {
    const imm::Vector vector(initial_data);

    RC_ASSERT(vector.empty() == initial_data.empty());
    RC_ASSERT(vector.size() == initial_data.size());
    if (not vector.empty() and not initial_data.empty()) {
      RC_ASSERT(vector.front() == initial_data.front());
      RC_ASSERT(vector.back()  == initial_data.back());
    }
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
