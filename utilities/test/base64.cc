#include <base64.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

#include <memory>

using namespace flp;

TEST_CASE("`Base64`::encode") {
  SECTION("Knowns") {
    SECTION("Many hands make light work.") {
      const auto message = "Many hands make light work.";
      CAPTURE(message);

      const auto encoding = Base64::encode(message);
      CHECK(encoding == "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
    }

    SECTION("Man") {
      const auto message = "Man";
      CAPTURE(message);

      const auto encoding = Base64::encode(message);
      CHECK(encoding == "TWFu");
    }

    SECTION("Ma") {
      const auto message = "Ma";
      CAPTURE(message);

      const auto encoding = Base64::encode(message);
      CHECK(encoding == "TWE=");
    }

    SECTION("M") {
      const auto message = "M";
      CAPTURE(message);

      const auto encoding = Base64::encode(message);
      CHECK(encoding == "TQ==");
    }

    SECTION("light w") {
      const auto message = "light w";
      CAPTURE(message);

      const auto encoding = Base64::encode(message);
      CHECK(encoding == "bGlnaHQgdw==");
    }

    SECTION("light wo") {
      const auto message = "light wo";
      CAPTURE(message);

      const auto encoding = Base64::encode(message);
      CHECK(encoding == "bGlnaHQgd28=");
    }

    SECTION("light wor") {
      const auto message = "light wor";
      CAPTURE(message);

      const auto encoding = Base64::encode(message);
      CHECK(encoding == "bGlnaHQgd29y");
    }
  }
}

TEST_CASE("`Base64`::decode") {
  SECTION("Knowns") {
    SECTION("Many hands make light work.") {
      const auto encoding = "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu";
      CAPTURE(encoding);

      const auto message = Base64::decode(encoding);
      CHECK(message == "Many hands make light work.");
    }

    SECTION("Man") {
      const auto encoding = "TWFu";
      CAPTURE(encoding);

      const auto message = Base64::decode(encoding);
      CHECK(message == "Man");
    }

    SECTION("Ma") {
      const auto encoding = "TWE=";
      CAPTURE(encoding);

      const auto message = Base64::decode(encoding);
      CHECK(message == "Ma");
    }

    SECTION("M") {
      const auto encoding = "TQ==";
      CAPTURE(encoding);

      const auto message = Base64::decode(encoding);
      CHECK(message == "M");
    }

    SECTION("light w") {
      const auto encoding = "bGlnaHQgdw==";
      CAPTURE(encoding);

      const auto message = Base64::decode(encoding);
      CHECK(message == "light w");
    }

    SECTION("light wo") {
      const auto encoding = "bGlnaHQgd28=";
      CAPTURE(encoding);

      const auto message = Base64::decode(encoding);
      CHECK(message == "light wo");
    }

    SECTION("light wor") {
      const auto encoding = "bGlnaHQgd29y";
      CAPTURE(encoding);

      const auto message = Base64::decode(encoding);
      CHECK(message == "light wor");
    }
  }
}
