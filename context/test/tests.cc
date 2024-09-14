#include <context.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("Logger type erasure") {
  struct S {
    void log(const trait::Logger::LogMessage& message) {
      (void)message;
    }
  };

  SECTION("Constructor/assignment") {
    S s;

    trait::Logger erased_logger  = S {};
    trait::Logger erased_logger2 = s;
    trait::Logger erased_logger3(S {});
    trait::Logger erased_logger4(s);
  }

  SECTION("Using member functions") {
    trait::Logger erased_logger = S {};
    erased_logger.log({}, {}, {});
  }
}

TEST_CASE("Allocator type erasure") {}

TEST_CASE("Error contracts type erasure") {}
