#include <base64.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

#include <memory>

using namespace flp;

TEST_CASE("`Base64`::encode") {
  SECTION("Knowns") {
    SECTION("Many hands make light work.") {
      const auto encoding = Base64::encode("Many hands make light work.");
      CHECK(encoding == "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
    }

    SECTION("Man") {
      const auto encoding = Base64::encode("Man");
      CHECK(encoding == "TWFu");
    }

    SECTION("Ma") {
      const auto encoding = Base64::encode("Ma");
      CHECK(encoding == "TWE=");
    }

    SECTION("M") {
      const auto encoding = Base64::encode("M");
      CHECK(encoding == "TQ==");
    }
  }
}

TEST_CASE("`Base64`::decode") {
  SECTION("Knowns") {
    SECTION("Many hands make light work.") {
      const auto message = Base64::decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
      CHECK(message == "Many hands make light work.");
    }

    SECTION("Man") {
      const auto message = Base64::decode("TWFu");
      CHECK(message == "Man");
    }

    SECTION("Ma") {
      const auto message = Base64::decode("TWE=");
      CHECK(message == "Ma");
    }

    SECTION("M") {
      const auto message = Base64::decode("TQ==");
      CHECK(message == "M");
    }
  }
}
