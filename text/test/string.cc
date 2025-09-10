#include <text/string.hh>
#include <text/string_view.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`String`") {
  SECTION("Equality") {
    SECTION("Default constructor") {
      const String string;

      CHECK(string == "");
      CHECK(string == String(""));
      CHECK(string == StringView(""));
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
    SECTION("Empty constructed") {
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

      CHECK(string == "");
      CHECK(string == String());
      CHECK(string == StringView());
      CHECK(string == String(""));
      CHECK(string == StringView(""));
    }

    SECTION("Simple constructed") {
      const char* value = GENERATE("a", "b", "abc", "ABC");
      String string = value;
      const auto length = flp::strlen(value);

      CHECK(not string.empty());
      CHECK(string.size() == length);
      CHECK(string.capacity() >= length);
      CHECK(string.data() != nullptr);
      CHECK(string.begin() != nullptr);
      CHECK(string.data() == string.begin());
      CHECK(string.end() != nullptr);
      CHECK(string.end() == string.begin() + length);

      CHECK_NOTHROW(string.clear());

      CHECK(string.empty());
      CHECK(string.size() == 0);
      CHECK(string.data() == string.begin());
      CHECK(string.data() == string.end());

      CHECK(string == "");
      CHECK(string == String());
      CHECK(string == StringView());
      CHECK(string == String(""));
      CHECK(string == StringView(""));
    }
  }
}
