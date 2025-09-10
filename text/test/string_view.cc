#include <text/string.hh>
#include <text/string_view.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`StringView`") {
  SECTION("Equality") {
    SECTION("Default constructor") {
      StringView string_view;

      CHECK(string_view == "");
      CHECK(string_view == String(""));
      CHECK(string_view == StringView(""));
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

  SECTION("Basic properties") {
    SECTION("Empty constructed") {
      StringView string_view;

      CHECK(string_view.empty());
      CHECK(string_view.size() == 0);
      CHECK(string_view.data() == nullptr);
      CHECK(string_view.begin() == nullptr);
      CHECK(string_view.end() == nullptr);

      CHECK_NOTHROW(string_view.clear());

      CHECK(string_view.empty());
      CHECK(string_view.size() == 0);
      CHECK(string_view.data() == nullptr);
      CHECK(string_view.begin() == nullptr);
      CHECK(string_view.end() == nullptr);

      CHECK(string_view == "");
      CHECK(string_view == String());
      CHECK(string_view == StringView());
      CHECK(string_view == String(""));
      CHECK(string_view == StringView(""));
    }

    SECTION("Simple constructed") {
      const char* value = GENERATE("a", "b", "abc", "ABC");
      StringView string_view = value;
      const auto length = flp::strlen(value);

      CHECK(not string_view.empty());
      CHECK(string_view.size() == length);
      CHECK(string_view.data() != nullptr);
      CHECK(string_view.begin() != nullptr);
      CHECK(string_view.data() == string_view.begin());
      CHECK(string_view.end() != nullptr);
      CHECK(string_view.end() == string_view.begin() + length);

      CHECK_NOTHROW(string_view.clear());

      CHECK(string_view.empty());
      CHECK(string_view.size() == 0);
      CHECK(string_view.data() == string_view.begin());
      CHECK(string_view.begin() == string_view.end());

      CHECK(string_view == "");
      CHECK(string_view == String());
      CHECK(string_view == StringView());
      CHECK(string_view == String(""));
      CHECK(string_view == StringView(""));
    }
  }
}
