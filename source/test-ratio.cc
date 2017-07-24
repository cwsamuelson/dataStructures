#include<catch.hpp>

#include<ratio.hh>

TEST_CASE( "Ratio equivalence.", "[ratio]" ){
  typedef gsw::ratio<1, 2> R;
  typedef gsw::ratio<2, 4> S;
  R r;
  S s;

  REQUIRE( double( r ) == .5 );
  REQUIRE( double( s ) == .5 );
  REQUIRE( r == s );
  REQUIRE( R::value       == S::value );
  REQUIRE( R::numerator   == S::numerator );
  REQUIRE( R::denominator == S::denominator );
}

TEST_CASE( "Ratio arithmetic.", "[ratio]" ){
  typedef gsw::ratio<1, 2> R;
  typedef gsw::ratio<4, 1> S;

  R r;
  S s;

  REQUIRE( double( decltype( r * s )::value ) == 2 );
}

