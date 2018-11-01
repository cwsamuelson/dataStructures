#include<string>

#include<catch.hpp>

#include<prefix_tree.hh>

using namespace std;
using namespace gsw;

TEST_CASE( "", "[trie]" ){
  prefix_tree<string, int> tree;

  REQUIRE( tree.empty() );

  tree.insert( "1", 2 );
  REQUIRE( !tree.empty() );
  REQUIRE( tree.count() == 1 );
  REQUIRE( tree.count( "1" ) == 1 );
  REQUIRE( tree.contains( "1" ) );
  REQUIRE( tree.find( "1" ).size() == 1 );
  REQUIRE( tree.find( "1" ) == set<int>{2} );

  tree.insert( "12", 3 );
  REQUIRE( !tree.empty() );
  REQUIRE( tree.count() == 2 );
  REQUIRE( tree.count( "1" ) == 2 );
  REQUIRE( tree.find( "1" ).size() == 2 );
  REQUIRE( tree.find( "1" ) == set<int>{2, 3} );
  REQUIRE( tree.contains( "1" ) );
  REQUIRE( tree.contains( "12" ) );

  tree.erase( "1" );
  REQUIRE( !tree.empty() );
  REQUIRE( tree.count() == 1 );
  REQUIRE( tree.count( "1" ) == 1 );
  REQUIRE( tree.find( "1" ).size() == 1 );
  REQUIRE( tree.find( "12" ).size() == 1 );
  REQUIRE( !tree.contains( "1" ) );

  tree.clear();
  REQUIRE( tree.empty() );
  REQUIRE( tree.count() == 0 );
  REQUIRE( tree.count( "1" ) == 0 );
  REQUIRE( tree.count( "12" ) == 0 );
  REQUIRE( !tree.contains( "1" ) );
  REQUIRE( !tree.contains( "12" ) );
}
