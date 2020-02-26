#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include <named_type.hh>

TEST_CASE("Named type testing", "[named]"){
  gsw::named_type<int, struct foo> x;
  CHECK(x == 0);
  CHECK(x.get() == 0);

  gsw::named_type<int, struct bar> y(1);
  //x = y;//not possible
  x = y.get();
  CHECK(x == 1);
  CHECK(y.get() == 1);

  x = 5;
  CHECK(x == 5);
  CHECK(x.get() == 5);
}

