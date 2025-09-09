#include <text/format.hh>
#include <text/string.hh>
#include <text/string_view.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`String`") {
  SECTION("Equality") {
    SECTION("Default constructor") {
      String string;

      CHECK(string == "");
      CHECK(string == String());
      CHECK(string == StringView());
    }

    SECTION("Simple c-strings") {
      const char* value = GENERATE("", "a", "b", "abc", "ABC");

      String string(value);

      CHECK(string == value);
      CHECK(string == String(value));
      CHECK(string == StringView(value));
    }
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

      StringView string_view(value);

      CHECK(string_view == value);
      CHECK(string_view == String(value));
      CHECK(string_view == StringView(value));
    }
  }
}
