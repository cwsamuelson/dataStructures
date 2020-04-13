#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <regex.hh>

using namespace gsw;

TEST_CASE("Simple string", "[]"){
  regex re("abcd");

  SECTION("Exact match") {
    re("abcd");
  }

  SECTION("No match"){
    SECTION("No match exists") {
      re("htns");
    }

    SECTION("Partial matches"){
      re("ahtns");
      re("abchtns");
    }
  }

  SECTION("Full matches"){
    SECTION("Exact"){
      re("abcd");
    }

    SECTION("partway through"){
      re("aoeuabcdhtns");
    }

    SECTION("end"){
      re("aoeuabcd");
    }
  }
}
