#include <core/random/random.hh>
#include <core/random/engine/branching.hh>
#include <core/random/engine/linear-congruential.hh>
#include <core/random/engine/mersenne-twister.hh>
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

TEST_CASE("`Random`::Engines") {
  SECTION("Engines produce deterministic results") {
    rc::prop("Monotonic Engine", [](const Random::Monotonic::Seed seed, const uint8_t iterations) {
      std::set<Random::Monotonic::Result> gen_set;

      for (size_t i = 0; i < iterations; ++i) {
        Random::Monotonic monotonic_engine(seed);
        gen_set.insert(monotonic_engine());
      }

      RC_ASSERT(gen_set.size() <= 1);
    });
  }

  SECTION("Monotonic") {
    Random::Monotonic engine;

    CHECK(engine.seed() == 0);
    for (size_t i = 0; i < 100; ++i) {
      CHECK(engine() == i);
    }

    engine.seed(0);
    for (size_t i = 0; i < 100; ++i) {
      CHECK(engine() == i);
    }

    engine.discard();
    CHECK(engine() == 100);
    engine.discard(5);
    CHECK(engine() == 105);
  }

  SECTION("Linear Congruential") {
    Random::LinearCongruential engine;

    engine.discard(10'000);
    CHECK(engine() == 399'268'537);
  }

  SECTION("Mersenne Twister") {
    Random::MT19937 engine;
  }

  SECTION("Branching") {
    // static_assert(Random::Engine<Random::Branching<Random::MT19937>>);
    // static_assert(Random::Engine<Random::Branching<Random::LinearCongruential>>);
    // static_assert(Random::Engine<Random::Branching<Random::Monotonic>>);

    Random::Branching<Random::MT19937> branching_mt;
    // Random::Branching<Random::LinearCongruential> branching_lc;
    Random::Branching<Random::Monotonic> branching_m;
  }
}
