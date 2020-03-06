#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include <errors.hh>

void thrower(bool should_throw){
  GSW_THROW(!should_throw, "bah, humbug");
}

TEST_CASE("Simple GSW_THROW macro checks", ""){
  CHECK_THROWS_AS(thrower(true), gsw::exception);
  CHECK_NOTHROW(thrower(false));
}

TEST_CASE("gsw::exception and GSW_THROW can be caught be std exception", ""){
  try{
    thrower(true);
  } catch(std::exception& e) {
    CHECK(true);
  }
}

TEST_CASE("gsw::exception captures location information", ""){
  try{
    thrower(true);
  } catch(gsw::exception& e){
    CHECK(e.line() == 7);
    CHECK(e.message() == "bah, humbug");
    CHECK(!e.file().empty());
    std::string w(e.what());
    CHECK(!w.empty());
    CHECK(w != e.message());
  }
}
