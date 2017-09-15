#include<string>

#include<catch.hpp>

#include<map.hh>

using namespace std;

TEST_CASE( "Maps are associative containers", "[map]" ){
  const int nIters = 10;
  gsw::map<int, int> mp;

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
  
  SECTION( "" ){
    gsw::map<string, string> m;

    m["test"] = "foo";

    REQUIRE( m["test"] == "foo" );

    m["test"] = "bar";

    REQUIRE( m["test"] == "bar" );

    m["test2"] = "foo";

    REQUIRE( m["test2"] == "foo" );
    REQUIRE( m["test"] == "bar" );

    auto it = m.begin();
    REQUIRE( gsw::get<0>( *it ) == "test" );
    REQUIRE( gsw::get<1>( *it ) == "bar" );
    ++it;
    REQUIRE( gsw::get<0>( *it ) == "test2" );
    REQUIRE( gsw::get<1>( *it ) == "foo" );
  }
}

