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

    SECTION("light w") {
      const auto message = Base64::encode("light w");
      CHECK(message == "bGlnaHQgdw==");
    }

    SECTION("light wo") {
      const auto message = Base64::encode("light wo");
      CHECK(message == "bGlnaHQgd28=");
    }

    SECTION("light wor") {
      const auto message = Base64::encode("light wor");
      CHECK(message == "bGlnaHQgd29y");
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

    SECTION("light w") {
      const auto message = Base64::decode("bGlnaHQgdw==");
      CHECK(message == "light w");
    }

    SECTION("light wo") {
      const auto message = Base64::decode("bGlnaHQgd28=");
      CHECK(message == "light wo");
    }

    SECTION("light wor") {
      const auto message = Base64::decode("bGlnaHQgd29y");
      CHECK(message == "light wor");
    }
  }
}
