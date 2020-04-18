#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <regex.hh>

using namespace gsw;

TEST_CASE("Simple string", "[]"){
  regex re("abcd");

  SECTION("Exact match") {
    auto answer = re("abcd");

    REQUIRE(answer.size() == 1);
    CHECK(answer.front().view == "abcd");
    CHECK(answer.front().index == 0);
  }

  SECTION("No match"){
    SECTION("No match exists") {
      auto answer = re("htns");

      CHECK(answer.empty());
    }

    SECTION("Partial matches"){
      auto answer0 = re("ahtns");
      CHECK(answer0.empty());

      auto answer1 = re("abchtns");
      CHECK(answer1.empty());
    }
  }

  SECTION("Full matches"){
    SECTION("Exact"){
      auto answer = re("abcd");

      REQUIRE(answer.size() == 1);
      CHECK(answer.front().view == "abcd");
      CHECK(answer.front().index == 0);
    }

    SECTION("partway through"){
      auto answer = re("aoeuabcdhtns");

      REQUIRE(answer.size() == 1);
      CHECK(answer.front().view == "abcd");
      CHECK(answer.front().index == 4);
    }

    SECTION("end"){
      auto answer = re("aoeuabcd");

      REQUIRE(answer.size() == 1);
      CHECK(answer.front().view == "abcd");
      CHECK(answer.front().index == 4);
    }
  }

  SECTION("Multiple matches"){
    auto answer = re("abcdabcd");

    REQUIRE(answer.size() == 2);
    CHECK(answer[0].view == "abcd");
    CHECK(answer[0].index == 0);
    CHECK(answer[1].view == "abcd");
    CHECK(answer[1].index == 4);
  }
}

TEST_CASE("Simple Regex", "[]"){
  regex re("m.x");

  SECTION("Single answers"){
    auto answer = re("mix");
    REQUIRE(answer.size() == 1);
    CHECK(answer[0].view == "mix");
    CHECK(answer[0].index == 0);
  }

  SECTION("Multiple answers"){
    auto answer = re("mixmax");

    REQUIRE(answer.size() == 2);
    if(answer[0].view == "mix"){
      CHECK(answer[0].index == 0);

      CHECK(answer[1].view == "max");
      CHECK(answer[1].index == 3);
    } else {
      CHECK(answer[0].view == "max");
      CHECK(answer[0].index == 3);

      CHECK(answer[1].view == "mix");
      CHECK(answer[1].index == 0);
    }
  }
}

TEST_CASE("Matches numbers", "[]"){
  gsw::regex re("\\d\\d");

  SECTION(""){
    auto answer = re("the answer to life the universe and everything is: 42");

    REQUIRE(answer.size() == 1);
    CHECK(answer[0].view == "42");
    CHECK(answer[0].index == 51);
  }
}

