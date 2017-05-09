#include<catch.hpp>

#include<map.hh>

TEST_CASE( "Maps are associative containers", "[map]" ){
  const int nIters = 10;
  map<int, int> mp;

  SECTION( "Maps initialize empty" ){
    REQUIRE( mp.empty() );
  }

  for( int i = 0; i < nIters; ++i ){
    mp[i] = i + 1;
  }

  SECTION( "" ){
    for( int i = 0; i < nIters; ++i ){
      REQUIRE( mp[i] == i + 1 );
    }
  }
}

