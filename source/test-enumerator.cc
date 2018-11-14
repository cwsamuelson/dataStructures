#include<vector>

#include<catch.hpp>

#include<enumerator.hh>

using namespace gsw;
using namespace std;

TEST_CASE( "", "[enumerator]" ){
  vector<int> v1{1, 2, 3};
  vector<int> v2{1, 2, 3};
  vector<int> v3{6, 7, 8};

  size_t count = 0;
  for( auto [i, it] : enumerate( v1 ) ){
    REQUIRE( it == v1[i] );
    REQUIRE( v1[i] == v2[i] );
    REQUIRE( count == i );
    it += 5; // changes propogate
    ++i; // robust against modifying counter
    ++count;
  }
  REQUIRE( count == 3 );

  count = 0;
  for( auto [i, it] : enumerate( v1 ) ){
    REQUIRE( it == v1[i] );
    REQUIRE( v1[i] == v3[i] );
    REQUIRE( count == i );
    ++count;
  }
  REQUIRE( count == 3 );
}
