#include<catch.hpp>

#include<reference_wrapper.hh>

TEST_CASE( "", "[reference_wrapper]"){
  int i = 1;
  int j = 2;

  reference_wrapper<int> ref( i );
  reference_wrapper<int> refs[2]{ i, j };

  i = 3;
  REQUIRE( ref == 3 );
  REQUIRE( refs[0] == 3 );
}

