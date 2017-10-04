#include<cmath>

#include<catch.hpp>

#include<equation.hh>

using namespace gsw;

TEST_CASE( "Mathematical operators behave as expected", "[poly]" ){
  SECTION( "Basic operation" ){
    REQUIRE( ( "X"_evar ).evaluate( {{"X", 1}} ) == 1 );
    //REQUIRE( ( "foo"_lvar ).solve( {"foo"} ) ==
    //         set<set<string> > {{"foo"}} );
  }

  SECTION( "Negation" ){
    REQUIRE( ( -"X"_evar ).evaluate( {{"X", 1}} ) == -1 );
    REQUIRE( ( - -"X"_evar ).evaluate( {{"X", 1}} ) == 1 );
    //REQUIRE( ( !"foo"_lvar ).solve( {"foo"} ) == 
    //         set<set<string> > {{}} );
  }

  SECTION( "Multiplication (*)" ){
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 2}, {"Y", 3}} ) == 6 );
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == -9 );
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 4}, {"Y", 3}} ) == 12 );
    REQUIRE( ( "X"_evar * "X"_evar ).evaluate( {{"X", 3}} ) == 9 );
    //REQUIRE( ( "foo"_lvar && "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}} ) );
  }

  SECTION( "Division (/)" ){
    REQUIRE( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", 4}} ) == 3 );
    REQUIRE( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", -2}} ) == -6 );
    REQUIRE( ( "X"_evar / "X"_evar ).evaluate( {{"X", 12}} ) == 1 );
  }

  SECTION( "Addition (+)" ){
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 1}, {"Y", 2}} ) == 3 );
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 3}, {"Y", 2}} ) == 5 );
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == -2 );
    //REQUIRE( ( "foo"_lvar || "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Subtraction (-)" ){
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 4}} ) == 1 );
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 7}} ) == -2 );
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == 12 );
    //REQUIRE( ( "foo"_lvar || "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Exponentiation (^)" ){
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 10}} ) == 1024 );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", 3}} ) == 27 );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == ( 1.0 / 27.0 ) );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 1.5}} ) == std::pow( 2, 1.5 ) );
  }
}

