#include <catch2/catch_all.hpp>

#include <optional.hh>

using namespace flp;

// this struct should maybe be put into a shared location?
struct RAIISignaler {
  bool parameterized1_constructor = false;
  bool parameterized2_constructor = false;
  bool default_constructor = false;
  bool copy_constructor = false;
  bool move_constructor = false;
  bool copy_assignment = false;
  bool move_assignment = false;
  std::shared_ptr<bool> destructor = std::make_shared<bool>(false); // probably should be external?

  RAIISignaler(int)
    : parameterized1_constructor(true)
  {}
  RAIISignaler(int, int)
    : parameterized2_constructor(true)
  {}
  RAIISignaler()
    : default_constructor(true)
  {}
  RAIISignaler(const RAIISignaler&)
    : copy_constructor(true)
  {}
  RAIISignaler(RAIISignaler&&) noexcept
    : move_constructor(true)
  {}
  RAIISignaler& operator=(const RAIISignaler&) {
    copy_assignment = true;
    return *this;
  }
  RAIISignaler& operator=(RAIISignaler&&) noexcept {
    move_assignment = true;
    return *this;
  }
  ~RAIISignaler() {
    *destructor = true;
  }
};

TEST_CASE("using an optional") {
  SECTION("Defaults empty") {
    Optional<int> optional;
    CHECK(not optional);
    CHECK(not optional.has_value());
    CHECK_THROWS(optional.value());
  }

  SECTION("Giving a value") {
    SECTION("Constructors") {
      SECTION("R value") {
        Optional optional(RAIISignaler{});
        CHECK(optional);
        CHECK(optional.has_value());
        REQUIRE_NOTHROW(optional.value());

        CHECK(not optional.value().default_constructor);
        CHECK(not optional.value().parameterized1_constructor);
        CHECK(not optional.value().parameterized2_constructor);
        CHECK(not optional.value().copy_constructor);
        CHECK(optional.value().move_constructor);
        CHECK(not optional.value().copy_assignment);
        CHECK(not optional.value().move_assignment);
        CHECK(not *optional.value().destructor);
      }
      SECTION("L value") {
        RAIISignaler signaler;
        Optional optional(signaler);
        CHECK(optional);
        CHECK(optional.has_value());
        REQUIRE_NOTHROW(optional.value());

        CHECK(not optional.value().default_constructor);
        CHECK(not optional.value().parameterized1_constructor);
        CHECK(not optional.value().parameterized2_constructor);
        CHECK(optional.value().copy_constructor);
        CHECK(not optional.value().move_constructor);
        CHECK(not optional.value().copy_assignment);
        CHECK(not optional.value().move_assignment);
        CHECK(not *optional.value().destructor);
      }
    }
    SECTION("Assignment") {
      SECTION("R value") {
        Optional<RAIISignaler> optional;
        CHECK(not optional);
        CHECK(not optional.has_value());
        REQUIRE_THROWS(optional.value());

        optional = RAIISignaler{};
        CHECK(optional);
        CHECK(optional.has_value());
        REQUIRE_NOTHROW(optional.value());

        CHECK(not optional.value().default_constructor);
        CHECK(not optional.value().parameterized1_constructor);
        CHECK(not optional.value().parameterized2_constructor);
        CHECK(not optional.value().copy_constructor);
        CHECK(optional.value().move_constructor);
        CHECK(not optional.value().copy_assignment);
        CHECK(not optional.value().move_assignment);
        CHECK(not *optional.value().destructor);
      }
      SECTION("L value") {
        Optional<RAIISignaler> optional;
        CHECK(not optional);
        CHECK(not optional.has_value());
        REQUIRE_THROWS(optional.value());

        RAIISignaler signaler;
        optional = signaler;
        CHECK(optional);
        CHECK(optional.has_value());
        REQUIRE_NOTHROW(optional.value());

        CHECK(not optional.value().default_constructor);
        CHECK(not optional.value().parameterized1_constructor);
        CHECK(not optional.value().parameterized2_constructor);
        CHECK(optional.value().copy_constructor);
        CHECK(not optional.value().move_constructor);
        CHECK(not optional.value().copy_assignment);
        CHECK(not optional.value().move_assignment);
        CHECK(not *optional.value().destructor);
      }
    }
    SECTION("Emplacement") {
      Optional<RAIISignaler> optional;
      CHECK(not optional);
      CHECK(not optional.has_value());
      REQUIRE_THROWS(optional.value());

      optional.emplace(42, 1138);
      CHECK(optional);
      CHECK(optional.has_value());
      REQUIRE_NOTHROW(optional.value());

      CHECK(not optional.value().default_constructor);
      CHECK(not optional.value().parameterized1_constructor);
      CHECK(optional.value().parameterized2_constructor);
      CHECK(not optional.value().copy_constructor);
      CHECK(not optional.value().move_constructor);
      CHECK(not optional.value().copy_assignment);
      CHECK(not optional.value().move_assignment);
      CHECK(not *optional.value().destructor);
    }
  }

  SECTION("Clear existing value") {
    Optional optional(RAIISignaler{});
    auto destructor = optional.value().destructor;
    CHECK(not *destructor);

    optional.reset();
    CHECK(*destructor);
  }

  SECTION("Monadic operations") {
    SECTION("transform") {
      SECTION("With existing value") {
        Optional optional(RAIISignaler{});
        auto stage2 = optional.transform([](RAIISignaler&) {
          return 42;
        });

        CHECK(stage2);
        CHECK(stage2.has_value());
        CHECK_NOTHROW(stage2.value());
        CHECK(stage2.value() == 42);
      }
      SECTION("Without existing value") {
        Optional<RAIISignaler> optional;
        auto stage2 = optional.transform([](RAIISignaler&) {
          FAIL();
          return 42;
        });

        CHECK(not stage2);
        CHECK(not stage2.has_value());
        CHECK_THROWS(stage2.value());
      }
    }
    SECTION("and_then") {
      SECTION("With existing value") {
        Optional optional(RAIISignaler{});
        auto stage2 = optional.and_then([](RAIISignaler&) {
          return Optional(42);
        });

        CHECK(stage2);
        CHECK(stage2.has_value());
        CHECK_NOTHROW(stage2.value());
        CHECK(stage2.value() == 42);
      }
      SECTION("Without existing value") {
        Optional<RAIISignaler> optional;
        auto stage2 = optional.and_then([](RAIISignaler&) {
          FAIL();
          return Optional<RAIISignaler>{};
        });

        CHECK(not stage2);
        CHECK(not stage2.has_value());
        CHECK_THROWS(stage2.value());
      }
    }
    SECTION("or_else") {
      SECTION("With existing value") {
        Optional optional(42);
        auto stage2 = optional.or_else([]() {
          FAIL();
          return Optional(1138);
        });

        CHECK(stage2);
        CHECK(stage2.has_value());
        CHECK_NOTHROW(stage2.value());
        CHECK(stage2.value() == 42);
      }
      SECTION("Without existing value") {
        Optional<int> optional;
        auto stage2 = optional.or_else([]() {
          return Optional(42);
        });

        CHECK(stage2);
        CHECK(stage2.has_value());
        CHECK_NOTHROW(stage2.value());
        CHECK(stage2.value() == 42);
      }
    }
    SECTION("value_or") {
      SECTION("With existing value") {
        Optional optional(42);
        CHECK(optional.value_or(1138) == 42);
      }
      SECTION("Without existing value") {
        Optional<int> optional;
        CHECK(optional.value_or(42) == 42);
      }
    }
  }
}

