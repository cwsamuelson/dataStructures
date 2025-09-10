#include <text/format.hh>
#include <text/string.hh>
#include <text/string_view.hh>

#include <catch2/catch_all.hpp>

#include <sstream>

using namespace flp;

TEST_CASE("`String`") {
  SECTION("Equality") {
    SECTION("Default constructor") {
      const String string;

      CHECK(string == "");
      CHECK(string == String());
      CHECK(string == StringView());
    }

    SECTION("Simple c-strings") {
      const char* value = GENERATE("", "a", "b", "abc", "ABC");
      CAPTURE(value);

      const String string(value);

      CHECK(string == value);
      CHECK(string == String(value));
      CHECK(string == StringView(value));
    }
  }

  SECTION("Inequality") {
    SECTION("Default constructor") {
      const String string;

      CHECK(string != "---");
      CHECK(string != String("---"));
      CHECK(string != StringView("---"));
    }

    SECTION("Simple c-strings") {
      const char* value = GENERATE("", "a", "b", "abc", "ABC");
      CAPTURE(value);

      const String string(value);

      CHECK(string != "---");
      CHECK(string != String("---"));
      CHECK(string != StringView("---"));
    }
  }

  SECTION("Basic properties") {
    String string;

    CHECK(string.empty());
    CHECK(string.size() == 0);
    CHECK(string.capacity() == 0);
    CHECK(string.data() == nullptr);
    CHECK(string.begin() == nullptr);
    CHECK(string.end() == nullptr);

    CHECK_NOTHROW(string.clear());

    CHECK(string.empty());
    CHECK(string.size() == 0);
    CHECK(string.capacity() == 0);
    CHECK(string.data() == nullptr);
    CHECK(string.begin() == nullptr);
    CHECK(string.end() == nullptr);
  }
}

TEST_CASE("`StringView`") {
  SECTION("Equality") {
    SECTION("Default constructor") {
      StringView string_view;

      CHECK(string_view == "");
      CHECK(string_view == String());
      CHECK(string_view == StringView());
    }

    SECTION("Simple c-strings") {
      const char* value = GENERATE("", "a", "b", "abc", "ABC");
      CAPTURE(value);

      StringView string_view(value);

      CHECK(string_view == value);
      CHECK(string_view == String(value));
      CHECK(string_view == StringView(value));
    }
  }

  SECTION("Inequality") {
    SECTION("Default constructor") {
      StringView string_view;

      CHECK(string_view != "---");
      CHECK(string_view != String("---"));
      CHECK(string_view != StringView("---"));
    }

    SECTION("Simple c-strings") {
      const char* value = GENERATE("", "a", "b", "abc", "ABC");
      CAPTURE(value);

      StringView string_view(value);

      CHECK(string_view != "---");
      CHECK(string_view != String("---"));
      CHECK(string_view != StringView("---"));
    }
  }
}
