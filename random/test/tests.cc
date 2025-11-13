#include <core/random/random.hh>
#include <core/random/engine/monotonic.hh>
#include <core/random/source/dev-random.hh>
#include <core/random/source/dev-urandom.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

#include <set>
#include <vector>

using namespace flp;

TEST_CASE("`Random`::Sources") {
  SECTION("DevRandom") {
    constexpr size_t iterations = 15;

    std::set<size_t> gen_set;

    for (size_t i = 0; i < iterations; ++i) {
      Random::DevRandom dev_random;

      const auto random = dev_random();
      gen_set.insert(random);
    }

    // technically not guaranteed
    CHECK(gen_set.size() == iterations);
  }

  SECTION("DevURandom") {
    constexpr size_t iterations = 15;

    std::set<size_t> gen_set;

    for (size_t i = 0; i < iterations; ++i) {
      Random::DevURandom dev_random;

      const auto random = dev_random();
      gen_set.insert(random);
    }

    // technically not guaranteed
    CHECK(gen_set.size() == iterations);
  }
}
