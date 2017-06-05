#include<catch.hpp>

#include<equation.hh>

using namespace std;

TEST_CASE( "Equations can be used in basic arithmetic", "[equ]" ){
  vector<double> vec { 1, 1, 1 };
  vector<double> vec2 { 2, 2, 2 };
  gsw::equation eq( vec.begin(), vec.end() );
  gsw::equation eq2( vec2.begin(), vec2.end() );

  SECTION( "Addition" ){
    REQUIRE( ( eq + eq2 )( 2 ) == 21 );
  }

  SECTION( "Subtraction" ){
    REQUIRE( ( eq2 - eq )( 2 ) == 7 );
    REQUIRE( ( eq - eq2 )( 2 ) == -7 );
  }

  SECTION( "Multiplication" ){
    REQUIRE( ( eq * 2 )( 2 ) == 2 * eq( 2 ) );

    vector<double> vec3 { 1, 1 };
    gsw::equation eq3( vec3.begin(), vec3.end() );
    vec3[0] = 2;
    gsw::equation eq4( vec3.begin(), vec3.end() );
    REQUIRE( ( eq3 * eq4 )( 2 ) == 12 );

    vector<double> vec4 { 1, 1 };
    gsw::equation eq5( vec4.begin(), vec4.end() );
    vec4.push_back( 1 );
    gsw::equation eq6( vec4.begin(), vec4.end() );
    REQUIRE( ( eq5 * eq6 )( 2 ) == 21 );
  }

//TODO:test dividing equation by another equation
  SECTION( "Division" ){
    REQUIRE( ( eq2 / 2 )( 2 ) == eq2( 2 ) / 2 );
  }
}

TEST_CASE( "Equation", "[equ]" ){
  vector<double> vec { 1, 1, 1 };
  vector<double> vec2 { 2, 2, 2 };
  gsw::equation eq( vec.begin(), vec.end() );
  gsw::equation eq2( vec2.begin(), vec2.end() );

  SECTION( "Equations can be evaluated" ){
    REQUIRE( eq( 2 ) == 7 );
    REQUIRE( eq2( 2 ) == 14 );
  }

  SECTION( "Equations with different number of terms" ){
    vec.push_back( 1 );
    gsw::equation eq3( vec.begin(), vec.end() );

    REQUIRE( eq3( 2 ) == 15 );
    REQUIRE( ( eq3 + eq )( 2 ) == 22 );
    REQUIRE( ( eq3 - eq )( 2 ) == 8 );
  }

  SECTION( "Derivative" ){
    gsw::equation eq3 = derive( eq2 );

    REQUIRE( eq3( 2 ) == 10 );
  }

  SECTION( "Integral" ){
    REQUIRE( integrate( eq2, 3, 1 ) == ( 29.0 + ( 1.0 / 3.0 ) ) );
  }
}

