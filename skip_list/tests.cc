#include<string>

#include<catch.hpp>

#include<skip_list.hh>

using namespace std;

TEST_CASE( "skip_lists are associative containers", "[skip_list]" ){
  const int nIters = 10;
  gsw::skip_list<int, int> sl;

  SECTION( "skip_lists initialize empty" ){
    REQUIRE( sl.empty() );
  }

  for( int i = 0; i < nIters; ++i ){
    sl[i] = i + 1;
  }

  SECTION( "Basic value skip_listping" ){
    for( int i = 0; i < nIters; ++i ){
      REQUIRE( sl[i] == i + 1 );
    }
  }

  SECTION( "More detailed value skip_listping, and value changing" ){
    gsw::skip_list<string, string> sl;

    sl["test"] = "foo";

    REQUIRE( sl["test"] == "foo" );

    sl["test"] = "bar";

    REQUIRE( sl["test"] == "bar" );

    sl["test2"] = "foo";

    REQUIRE( sl["test2"] == "foo" );
    REQUIRE( sl["test"] == "bar" );

    auto it = sl.begin();
    REQUIRE( std::get<0>( *it ) == "test" );
    REQUIRE( std::get<1>( *it ) == "bar" );
    ++it;
    REQUIRE( std::get<0>( *it ) == "test2" );
    REQUIRE( std::get<1>( *it ) == "foo" );
  }
}

