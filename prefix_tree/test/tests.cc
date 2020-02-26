#include<string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include<prefix_tree.hh>

using namespace std;
using namespace gsw;

TEST_CASE( "", "[prefix_tree]" ){
  prefix_tree<string, int> tree;

  REQUIRE( tree.empty() );

  tree.insert( "1", 2 );
  REQUIRE( !tree.empty() );
  REQUIRE( tree.count() == 1 );
  REQUIRE( tree.count( "1" ) == 1 );
  REQUIRE( tree.count( "12" ) == 0 );
  REQUIRE( tree.count( "123" ) == 0 );
  CHECK( tree.contains( "1" ) );
  CHECK( !tree.contains( "12" ) );
  CHECK( !tree.contains( "123" ) );
  CHECK( tree.find( "1" ).size() == 1 );
  CHECK( tree.find( "1" ) == set<int>{2} );

  tree.insert( "12", 3 );
  REQUIRE( !tree.empty() );
  REQUIRE( tree.count() == 2 );
  REQUIRE( tree.count( "1" ) == 2 );
  REQUIRE( tree.count( "12" ) == 1 );
  REQUIRE( tree.count( "123" ) == 0 );
  CHECK( tree.find( "1" ).size() == 2 );
  CHECK( tree.find( "1" ) == set<int>{2, 3} );
  CHECK( tree.contains( "1" ) );
  CHECK( tree.contains( "12" ) );
  CHECK( !tree.contains( "123" ) );

  tree.erase( "1" );
  REQUIRE( !tree.empty() );
  REQUIRE( tree.count() == 1 );
  REQUIRE( tree.count( "1" ) == 1 );
  CHECK( tree.find( "1" ).size() == 1 );
  CHECK( tree.find( "12" ).size() == 1 );
  CHECK( !tree.contains( "1" ) );

  tree.clear();
  REQUIRE( tree.empty() );
  REQUIRE( tree.count() == 0 );
  REQUIRE( tree.count( "1" ) == 0 );
  REQUIRE( tree.count( "12" ) == 0 );
  CHECK( !tree.contains( "1" ) );
  CHECK( !tree.contains( "12" ) );
}
