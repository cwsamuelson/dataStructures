#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <error_handling.hh>

inline static auto special_line_number = 0;

void thrower(bool should_throw) {
  GSW_VERIFY(!should_throw, "bah, humbug");
  special_line_number = __LINE__ - 1;
}

TEST_CASE("Simple GSW_THROW macro checks", "") {
  CHECK_THROWS_AS(thrower(true), gsw::exception);
  CHECK_NOTHROW(thrower(false));
}

TEST_CASE("gsw::exception and GSW_THROW can be caught be std exception", "") {
  try {
    thrower(true);
  } catch(std::exception& e) {
    std::string w(e.what());
    CHECK(!w.empty());
#if __cpp_lib_starts_ends_with
    w.ends_with("bah, humbug");
#endif
  }
}

TEST_CASE("gsw::exception captures location information", "") {
  try {
    thrower(true);
    REQUIRE(false);
  } catch(gsw::exception& e) {
    CHECK(e.line() == special_line_number);
    CHECK(e.message() == "bah, humbug");
    CHECK(!e.file().empty());
    std::string w(e.what());
    CHECK(!w.empty());
    CHECK(w != e.message());
#if __cpp_lib_starts_ends_with
    w.starts_with("bah, humbug");
    w.ends_with("!should_throw");
#endif
    CHECK(e.expression() == "!should_throw");

    std::cout << e.line() << std::endl;
    std::cout << e.message() << std::endl;
    std::cout << e.file() << std::endl;
    std::cout << e.what() << std::endl;
    std::cout << e.message() << std::endl;
    std::cout << e.expression() << std::endl;
  }
}
