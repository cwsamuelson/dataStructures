#include<string>

#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<skip_list.hh>

using namespace std;

TEST_CASE("", "[]"){
  CHECK(false);
}

#if 0
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
      CHECK( sl[i] == i + 1 );
    }
  }

  SECTION( "More detailed value skip_listping, and value changing" ){
    gsw::skip_list<string, string> sl;

    sl["test"] = "foo";

    CHECK( sl["test"] == "foo" );

    sl["test"] = "bar";

    CHECK( sl["test"] == "bar" );

    sl["test2"] = "foo";

    CHECK( sl["test2"] == "foo" );
    CHECK( sl["test"] == "bar" );

    auto it = sl.begin();
    CHECK( std::get<0>( *it ) == "test" );
    CHECK( std::get<1>( *it ) == "bar" );
    ++it;
    CHECK( std::get<0>( *it ) == "test2" );
    CHECK( std::get<1>( *it ) == "foo" );
  }
}
#endif
