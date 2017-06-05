#include<catch.hpp>

#include<tuple.hh>

TEST_CASE( "Tuples can be of varying size and type", "[tuple]" ){
  SECTION( "Single element tuple" ){
    gsw::tuple<int> t1;

    gsw::get<0>( t1 ) = 1;

    REQUIRE( gsw::get<0>( t1 ) == 1 );
  }

  SECTION( "Multi element tuple" ){
    gsw::tuple<int, int> t2;

    gsw::get<0>( t2 ) = 2;
    gsw::get<1>( t2 ) = 3;

    REQUIRE( gsw::get<0>( t2 ) == 2 );
    REQUIRE( gsw::get<1>( t2 ) == 3 );
  }

  SECTION( "Multi element and type tuple" ){
    gsw::tuple<char, int, char> t3;

    gsw::get<0>( t3 ) = 'a';
    gsw::get<1>( t3 ) = 4;
    gsw::get<2>( t3 ) = 'b';
  
    REQUIRE( gsw::get<0>( t3 ) == 'a' );
    REQUIRE( gsw::get<1>( t3 ) == 4 );
    REQUIRE( gsw::get<2>( t3 ) == 'b' );
  }

  SECTION( "Tuples can be initialized from ctor" ){
    gsw::tuple<int, int> t4( 1, 2 );
    
    REQUIRE( gsw::get<0>( t4 ) == 1 );
    REQUIRE( gsw::get<1>( t4 ) == 2 );
  }

  SECTION( "Tuples can be constructed using make_tuple" ){
    auto t1 = gsw::make_tuple( 1, 3.0 );
    auto t2 = gsw::make_tuple( 'c', 1, 6.0 );

    REQUIRE( gsw::get<0>( t1 ) == 1 );
    REQUIRE( gsw::get<1>( t1 ) == 3.0 );
    REQUIRE( gsw::get<0>( t2 ) == 'c' );
    REQUIRE( gsw::get<1>( t2 ) == 1 );
    REQUIRE( gsw::get<2>( t2 ) == 6.0 );
  }

  SECTION( "Tuple element types can be extracted using tuple_element class" ){
    gsw::tuple<int, char, bool> t;
    //compile check
    gsw::tuple_element<1, decltype( t )>::type c = 'c';
    gsw::tuple_element<2, decltype( t )>::type b = true;

    REQUIRE( c == 'c' );
    REQUIRE( b );
  }
}

