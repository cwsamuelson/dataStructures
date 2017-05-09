#include<catch.hpp>

#include<function.hh>

int testfn(){
  return 5;
}

TEST_CASE( "Function objects are used as normal functions.", "[function]" ){
  function<int( int )> fn;
  function<int( int, int )> nf;
  function<int()> tst;
  
  fn = []( int x ){ return 1 + x; };
  nf = []( int x, int y ){ return x + y; };
  tst = testfn;
  
  SECTION( "Calling functions produce expected results." ){
    REQUIRE( fn( 3 ) == 4 );
    REQUIRE( nf( 1, 2 ) == 3 );
    REQUIRE( tst() == 5 );
  }
}

