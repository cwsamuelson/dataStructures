#include<catch.hpp>

#include<algorithm.hh>
#include<equation.hh>

using namespace gsw;

TEST_CASE( "Mathematical operators behave as expected", "[equ]" ){
  SECTION( "Basic operation" ){
    CHECK( ( "X"_evar ).evaluate( {{"X", 1}} ) == 1 );
    CHECK( ( "X"_evar ).evaluate( {{"X", 5}} ) == 5 );
    auto X = "X"_evar;
    auto Y = "Y"_evar;
    CHECK( ( X * Y ).evaluate( {{"X", 3}, {"Y", 2}} ) == 6 );
    //CHECK( ( "x"_evar ).solve( {"x"} ) ==
    //         set<set<string> > {{"foo"}} );
  }

  SECTION( "Constants" ){
    CHECK( ( "1"_evar ).evaluate( {} ) == 1 );
    CHECK( ( "5"_evar ).evaluate( {{"X", 1}} ) == 5 );
    CHECK( ( "4.2"_evar ).evaluate( {{"X", 1}} ) == 4.2 );
    CHECK( ( 1.0_evar ).evaluate( {} ) == 1 );
    CHECK( ( 5.0_evar ).evaluate( {{"X", 1}} ) == 5 );
    CHECK( ( 4.2_evar ).evaluate( {{"X", 1}} ) == 4.2 );
  }

  SECTION( "Negation" ){
    CHECK( ( -"X"_evar ).evaluate( {{"X", 1}} ) == -1 );
    CHECK( ( - -"X"_evar ).evaluate( {{"X", 1}} ) == 1 );

    CHECK( ( -"5"_evar ).evaluate( {{"X", 1}} ) == -5 );
    CHECK( ( - -"5"_evar ).evaluate( {{"X", 1}} ) == 5 );
    CHECK( ( "-5"_evar ).evaluate( {{"X", 1}} ) == -5 );
    CHECK( ( - "-5"_evar ).evaluate( {{"X", 1}} ) == 5 );

    CHECK( ( - 5.0_evar ).evaluate( {{"X", 1}} ) == -5 );
    CHECK( ( - - 5.0_evar ).evaluate( {{"X", 1}} ) == 5 );
    CHECK( ( -5.0_evar ).evaluate( {{"X", 1}} ) == -5 );
    CHECK( ( - -5.0_evar ).evaluate( {{"X", 1}} ) == 5 );

    //CHECK( ( !"foo"_lvar ).solve( {"foo"} ) ==
    //         set<set<string> > {{}} );
  }

  SECTION( "Multiplication (*)" ){
    CHECK( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 2}, {"Y", 3}} ) == 6 );
    CHECK( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == -9 );
    CHECK( ( "X"_evar * "Y"_evar ).evaluate( {{"X", -4}, {"Y", -3}} ) == 12 );
    CHECK( ( "X"_evar * "X"_evar ).evaluate( {{"X", 3}} ) == 9 );
    CHECK( ( "X"_evar * "5"_evar ).evaluate( {{"X", 3}} ) == 15 );
    CHECK( ( "4.2"_evar * "X"_evar ).evaluate( {{"X", 2}} ) == 8.4 );
    CHECK( ( "X"_evar * "4.2"_evar ).evaluate( {{"X", 2}} ) == 8.4 );
    //CHECK( ( 4.2 * "X"_evar ).evaluate( {{"X", 2}} ) == 8.4 );
    CHECK( ( "X"_evar * 4.2 ).evaluate( {{"X", 2}} ) == 8.4 );
    CHECK( ( "3"_evar * "5"_evar ).evaluate({}) == 15 );

    CHECK( ( "X"_evar * 5.0_evar ).evaluate( {{"X", 3}} ) == 15 );
    CHECK( ( 4.2_evar * "X"_evar ).evaluate( {{"X", 2}} ) == 8.4 );
    CHECK( ( 3.0_evar * 5.0_evar ).evaluate({}) == 15 );

    //CHECK( ( "foo"_lvar && "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}} ) );
  }

  SECTION( "Division (/)" ){
    CHECK( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", 4}} ) == 3 );
    CHECK( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", -2}} ) == -6 );
    CHECK( ( "X"_evar / "X"_evar ).evaluate( {{"X", 12}} ) == 1 );
    CHECK( ( "X"_evar / "3"_evar ).evaluate( {{"X", 12}} ) == 4 );
    CHECK( ( "X"_evar / 3 ).evaluate( {{"X", 12}} ) == 4 );
    //CHECK( ( 12 / "X"_evar ).evaluate( {{"X", 3}} ) == 4 );
    CHECK( ( "4.2"_evar / "X"_evar ).evaluate( {{"X", 2}} ) == 2.1 );
    CHECK( ( "15"_evar / "3"_evar ).evaluate( {} ) == 5 );

    CHECK( ( "X"_evar / 3.0_evar ).evaluate( {{"X", 12}} ) == 4 );
    CHECK( ( 4.2_evar / "X"_evar ).evaluate( {{"X", 2}} ) == 2.1 );
    CHECK( ( 15.0_evar / 3.0_evar ).evaluate( {} ) == 5 );
  }

  SECTION( "Addition (+)" ){
    CHECK( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 1}, {"Y", 2}} ) == 3 );
    CHECK( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 3}, {"Y", 2}} ) == 5 );
    CHECK( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == -2 );
    CHECK( ( "X"_evar + "3"_evar ).evaluate( {{"X", 3}} ) == 6 );
    CHECK( ( "3"_evar + "X"_evar ).evaluate( {{"X", 3}} ) == 6 );
    CHECK( ( "X"_evar + 3 ).evaluate( {{"X", 3}} ) == 6 );
    //CHECK( ( 3 + "X"_evar ).evaluate( {{"X", 3}} ) == 6 );
    CHECK( ( "5"_evar + "3"_evar ).evaluate( {} ) == 8 );

    CHECK( ( "X"_evar + 3.0_evar ).evaluate( {{"X", 3}} ) == 6 );
    CHECK( ( 5.0_evar + 3.0_evar ).evaluate( {} ) == 8 );

    //CHECK( ( "x"_evar || "y"_evar ).solve( {"x", "y"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Subtraction (-)" ){
    CHECK( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 4}} ) == 1 );
    CHECK( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 7}} ) == -2 );
    CHECK( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == 12 );

    CHECK( ( "X"_evar - "3"_evar ).evaluate( {{"X", 5}} ) == 2 );
    CHECK( ( "3"_evar - "X"_evar ).evaluate( {{"X", 5}} ) == -2 );

    CHECK( ( "X"_evar - 3 ).evaluate( {{"X", 5}} ) == 2 );
    //CHECK( ( 3 - "X"_evar ).evaluate( {{"X", 5}} ) == 2 );

    CHECK( ( "5"_evar - "3"_evar ).evaluate( {} ) == 2 );

    CHECK( ( "X"_evar - 3.0_evar ).evaluate( {{"X", 5}} ) == 2 );
    CHECK( ( 5.0_evar - 3.0_evar ).evaluate( {} ) == 2 );

    //CHECK( ( "x"_evar || "y"_lvar ).solve( {"x", "y"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Exponentiation (^)" ){
    CHECK( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 10}} ) == 1024 );
    CHECK( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", 3}} ) == 27 );
    CHECK( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == ( 1.0 / 27.0 ) );
    CHECK( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 1.5}} ) == std::pow( 2, 1.5 ) );
    CHECK( ( "2"_evar ).pow( "X"_evar ).evaluate( {{"X", 3}} ) == std::pow( 2, 3 ) );
    CHECK( ( "X"_evar ).pow( "3"_evar ).evaluate( {{"X", 3}} ) == 27 );
    CHECK( ( "X"_evar ).pow( 3 ).evaluate( {{"X", 3}} ) == 27 );
    CHECK( are_equal( gsw::log( "X"_evar, "8"_evar ).evaluate( {{"X", 2}} ), std::log2( 8 ) ) );

    CHECK( ( 2.0_evar ).pow( "X"_evar ).evaluate( {{"X", 3}} ) == std::pow( 2, 3 ) );
    CHECK( ( "X"_evar ).pow( 3.0_evar ).evaluate( {{"X", 3}} ) == 27 );
  }

  SECTION( "Derivation" ){
    CHECK( ( "2"_evar ).derive( "X" ).evaluate( {} ) == 0 );
    CHECK( ( "2"_evar ).derive( "X" ).evaluate( {{"X", 5}} ) == 0 );
    CHECK( ( "X"_evar ).derive( "X" ).evaluate( {} ) == 1 );
    CHECK( ( "5"_evar * "X"_evar.pow( 2.0_cvar ) + ( "2"_evar * "X"_evar ) ).derive( "X" ).evaluate( {{"X", 3}} ) == 32 );
    CHECK( ( "2"_evar * "X"_evar ).derive( "X" ).evaluate( {{"X", 0}} ) == 2 );
    CHECK( e_evar.pow( "X"_evar ).evaluate( {{"X", 1}} ) == e_evar.evaluate( {} ) );
    CHECK( e_evar.pow( "X"_evar ).evaluate( {{"X", 0}} ) == 1 );
    CHECK( are_equal( e_evar.pow( "X"_evar ).derive( "X" ).evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    CHECK( are_equal( e_evar.pow( "X"_evar ).derive( "X" ).evaluate( {{"X", 0}} ), 1.0 ) );
    CHECK( ( "X"_evar ).pow( 2.0_cvar ).derive( "X" ).evaluate( {{"X", 3}} ) == 6 );

    CHECK( ( "2"_evar ).derive( "X", 2 ).evaluate( {} ) == 0 );
    CHECK( ( "2"_evar ).derive( "X", 2 ).evaluate( {{"X", 5}} ) == 0 );
    CHECK( ( "X"_evar ).derive( "X", 2 ).evaluate( {} ) == 0 );
    CHECK( ( "5"_evar * "X"_evar.pow( 2.0_cvar ) + ( "2"_evar * "X"_evar ) ).derive( "X", 2 ).evaluate( {{"X", 3}} ) == 10 );
    CHECK( ( "2"_evar * "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 0}} ) == 0 );
    CHECK( ( "X"_evar ).pow( 2.0_cvar ).derive( "X", 2 ).evaluate( {{"X", 3}} ) == 2 );
    CHECK( ( "X"_evar ).pow( 2.0_cvar ).derive( "X", 2 ).evaluate( {{"X", 5}} ) == 2 );
    //CHECK( are_equal( e_evar.pow( "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    //CHECK( are_equal( e_evar.pow( "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 0}} ), 1 ) );

    equation temp = e_evar.pow( "X"_evar );
    CHECK( are_equal( temp.evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    /*for( int i = 0; i < 10; ++i ){
      temp = temp.derive( "X" );
      CHECK( are_equal( temp.evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    }*/
  }
}
