#include<catch.hpp>

#include<tuple.hh>

TEST_CASE( "Tuples can be of varying size and type", "[tuple]" ){
  SECTION( "Single element tuple" ){
    tuple<int> t1;

    get<0>( t1 ) = 1;

    REQUIRE( get<0>( t1 ) == 1 );
  }

  SECTION( "Multi element tuple" ){
    tuple<int, int> t2;

    get<0>( t2 ) = 2;
    get<1>( t2 ) = 3;

    REQUIRE( get<0>( t2 ) == 2 );
    REQUIRE( get<1>( t2 ) == 3 );
  }

  SECTION( "Multi element and type tuple" ){
    tuple<char, int, char> t3;

    get<0>( t3 ) = 'a';
    get<1>( t3 ) = 4;
    get<2>( t3 ) = 'b';
  
    REQUIRE( get<0>( t3 ) == 'a' );
    REQUIRE( get<1>( t3 ) == 4 );
    REQUIRE( get<2>( t3 ) == 'b' );
  }

  SECTION( "Tuples can be initialized from ctor" ){
    tuple<int, int> t4( 1, 2 );
    
    REQUIRE( get<0>( t4 ) == 1 );
    REQUIRE( get<1>( t4 ) == 2 );
  }

  SECTION( "Tuples can be constructed using make_tuple" ){
    auto t1 = make_tuple( 1, 3.0 );
    auto t2 = make_tuple( 'c', 1, 6.0 );

    REQUIRE( get<0>( t1 ) == 1 );
    REQUIRE( get<1>( t1 ) == 3.0 );
    REQUIRE( get<0>( t2 ) == 'c' );
    REQUIRE( get<1>( t2 ) == 1 );
    REQUIRE( get<2>( t2 ) == 6.0 );
  }
}

