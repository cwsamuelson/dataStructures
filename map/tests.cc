#include<string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

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

  SECTION( "Basic value mapping" ){
    for( int i = 0; i < nIters; ++i ){
      CHECK( mp[i] == i + 1 );
    }
  }

  SECTION( "More detailed value mapping, and value changing" ){
    gsw::map<string, string> m;

    m["test"] = "foo";

    CHECK( m["test"] == "foo" );

    m["test"] = "bar";

    CHECK( m["test"] == "bar" );

    m["test2"] = "foo";

    CHECK( m["test2"] == "foo" );
    CHECK( m["test"] == "bar" );

    auto it = m.begin();
    CHECK( gsw::get<0>( *it ) == "test" );
    CHECK( gsw::get<1>( *it ) == "bar" );
    ++it;
    CHECK( gsw::get<0>( *it ) == "test2" );
    CHECK( gsw::get<1>( *it ) == "foo" );
  }
}
