
#include<catch.hpp>

#include<algorithm.hh>
#include<equation.hh>

using namespace gsw;

TEST_CASE( "Mathematical operators behave as expected", "[poly]" ){
  SECTION( "Basic operation" ){
    REQUIRE( ( "X"_evar ).evaluate( {{"X", 1}} ) == 1 );
    //REQUIRE( ( "foo"_lvar ).solve( {"foo"} ) ==
    //         set<set<string> > {{"foo"}} );
  }

  SECTION( "Constants" ){
    REQUIRE( ( "1"_evar ).evaluate( {} ) == 1 );
    REQUIRE( ( "5"_evar ).evaluate( {{"X", 1}} ) == 5 );
    REQUIRE( ( "4.2"_evar ).evaluate( {{"X", 1}} ) == 4.2 );
  }

  SECTION( "Negation" ){
    REQUIRE( ( -"X"_evar ).evaluate( {{"X", 1}} ) == -1 );
    REQUIRE( ( - -"X"_evar ).evaluate( {{"X", 1}} ) == 1 );
    REQUIRE( ( -"5"_evar ).evaluate( {{"X", 1}} ) == -5 );
    //REQUIRE( ( !"foo"_lvar ).solve( {"foo"} ) == 
    //         set<set<string> > {{}} );
  }

  SECTION( "Multiplication (*)" ){
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 2}, {"Y", 3}} ) == 6 );
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == -9 );
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 4}, {"Y", 3}} ) == 12 );
    REQUIRE( ( "X"_evar * "X"_evar ).evaluate( {{"X", 3}} ) == 9 );
    REQUIRE( ( "4.2"_evar * "X"_evar ).evaluate( {{"X", 2}} ) == 8.4 );
    //REQUIRE( ( "foo"_lvar && "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}} ) );
  }

  SECTION( "Division (/)" ){
    REQUIRE( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", 4}} ) == 3 );
    REQUIRE( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", -2}} ) == -6 );
    REQUIRE( ( "X"_evar / "X"_evar ).evaluate( {{"X", 12}} ) == 1 );
    REQUIRE( ( "4.2"_evar / "X"_evar ).evaluate( {{"X", 2}} ) == 2.1 );
  }

  SECTION( "Addition (+)" ){
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 1}, {"Y", 2}} ) == 3 );
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 3}, {"Y", 2}} ) == 5 );
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == -2 );
    REQUIRE( ( "5"_evar + "3"_evar ).evaluate( {} ) == 8 );
    //REQUIRE( ( "foo"_lvar || "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Subtraction (-)" ){
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 4}} ) == 1 );
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 7}} ) == -2 );
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == 12 );
    REQUIRE( ( "5"_evar - "3"_evar ).evaluate( {} ) == 2 );
    //REQUIRE( ( "foo"_lvar || "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Exponentiation (^)" ){
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 10}} ) == 1024 );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", 3}} ) == 27 );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == ( 1.0 / 27.0 ) );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 1.5}} ) == std::pow( 2, 1.5 ) );
    REQUIRE( ( "2"_evar ).pow( "X"_evar ).evaluate( {{"X", 3}} ) == std::pow( 2, 3 ) );
    REQUIRE( ( "X"_evar ).pow( "3"_evar ).evaluate( {{"X", 3}} ) == 27 );
    REQUIRE( ( "X"_evar ).pow( 3 ).evaluate( {{"X", 3}} ) == 27 );
    REQUIRE( are_equal( gsw::log( "X"_evar, "8"_evar ).evaluate( {{"X", 2}} ), std::log2( 8 ) ) );
  }

  SECTION( "Derivation" ){
    REQUIRE( ( "2"_evar ).derive( "X" ).evaluate( {} ) == 0 );
    REQUIRE( ( "2"_evar ).derive( "X" ).evaluate( {{"X", 5}} ) == 0 );
    REQUIRE( ( "X"_evar ).derive( "X" ).evaluate( {} ) == 1 );
    REQUIRE( ( "5"_evar * "X"_evar.pow( "2"_cvar ) + ( "2"_evar * "X"_evar ) ).derive( "X" ).evaluate( {{"X", 3}} ) == 32 );
    REQUIRE( ( "2"_evar * "X"_evar ).derive( "X" ).evaluate( {{"X", 0}} ) == 2 );
    REQUIRE( e_evar.pow( "X"_evar ).evaluate( {{"X", 1}} ) == e_evar.evaluate( {} ) );
    REQUIRE( e_evar.pow( "X"_evar ).evaluate( {{"X", 0}} ) == 1 );
    REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X" ).evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X" ).evaluate( {{"X", 0}} ), 1.0 ) );
    REQUIRE( ( "X"_evar ).pow( "2"_cvar ).derive( "X" ).evaluate( {{"X", 3}} ) == 6 );

    REQUIRE( ( "2"_evar ).derive( "X", 2 ).evaluate( {} ) == 0 );
    REQUIRE( ( "2"_evar ).derive( "X", 2 ).evaluate( {{"X", 5}} ) == 0 );
    REQUIRE( ( "X"_evar ).derive( "X", 2 ).evaluate( {} ) == 0 );
    REQUIRE( ( "5"_evar * "X"_evar.pow( "2"_cvar ) + ( "2"_evar * "X"_evar ) ).derive( "X", 2 ).evaluate( {{"X", 3}} ) == 10 );
    REQUIRE( ( "2"_evar * "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 0}} ) == 0 );
    REQUIRE( ( "X"_evar ).pow( "2"_cvar ).derive( "X", 2 ).evaluate( {{"X", 3}} ) == 2 );
    REQUIRE( ( "X"_evar ).pow( "2"_cvar ).derive( "X", 2 ).evaluate( {{"X", 5}} ) == 2 );
    //REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    //REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 0}} ), 1 ) );

    equation temp = e_evar.pow( "X"_evar );
    REQUIRE( are_equal( temp.evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    /*for( int i = 0; i < 10; ++i ){
      temp = temp.derive( "X" );
      REQUIRE( are_equal( temp.evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    }*/
  }
}

