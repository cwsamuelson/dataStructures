#include<string>

#include<catch.hpp>

#include<trie.hh>

using namespace std;
using namespace gsw;

TEST_CASE( "", "[trie]" ){
  prefix_tree<string, int> tree;

  tree.insert( "1", 2 );
  REQUIRE( tree.contains( "1" ) );
  REQUIRE( tree.find( "1" ).size() == 1 );

  tree.insert( "12", 3 );
  REQUIRE( tree.find( "1" ).size() == 2 );
  REQUIRE( tree.find( "1" ) == set<int>{2, 3} );
  REQUIRE( tree.contains( "1" ) );
  REQUIRE( tree.contains( "12" ) );
}
