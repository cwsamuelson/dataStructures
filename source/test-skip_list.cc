#include<string>

#include<catch.hpp>

#include<skip_list.hh>

using namespace std;

TEST_CASE( "skip_lists are associative containers", "[skip_list]" ){
  const int nIters = 10;
  gsw::skip_list<int, int> mp;

  SECTION( "skip_lists initialize empty" ){
    REQUIRE( mp.empty() );
  }

  for( int i = 0; i < nIters; ++i ){
    mp[i] = i + 1;
  }

  SECTION( "Basic value skip_listping" ){
    for( int i = 0; i < nIters; ++i ){
      REQUIRE( mp[i] == i + 1 );
    }
  }

  SECTION( "More detailed value skip_listping, and value changing" ){
    gsw::skip_list<string, string> m;

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

