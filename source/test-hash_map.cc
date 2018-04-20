#include<string>

#include<catch.hpp>

#include<hash_map.hh>

using namespace gsw;
using namespace std;

TEST_CASE( "hash_Maps are associative containers", "[hash_map]" ){
  const int nIters = 10;
  gsw::hash_map<int, int> mp;

  SECTION( "hash_Maps initialize empty" ){
    REQUIRE( mp.empty() );
  }

  for( int i = 0; i < nIters; ++i ){
    mp[i] = i + 1;
  }

  SECTION( "Basic value hash_mapping" ){
    for( int i = 0; i < nIters; ++i ){
      REQUIRE( mp[i] == i + 1 );
    }
  }

  SECTION( "More detailed value hash_mapping, and value changing" ){
    gsw::hash_map<string, string> m;

    m["test"] = "foo";

    REQUIRE( m["test"] == "foo" );

    m["test"] = "bar";

    REQUIRE( m["test"] == "bar" );

    m["test2"] = "foo";

    REQUIRE( m["test2"] == "foo" );
    REQUIRE( m["test"] == "bar" );

    auto it = m.begin();
    REQUIRE( std::get<0>( *it ) == "test" );
    REQUIRE( std::get<1>( *it ) == "bar" );
    ++it;
    REQUIRE( std::get<0>( *it ) == "test2" );
    REQUIRE( std::get<1>( *it ) == "foo" );
  }
}

