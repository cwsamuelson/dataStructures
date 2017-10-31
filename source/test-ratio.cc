#include<catch.hpp>

#include<ratio.hh>

TEST_CASE( "Ratio equivalence.", "[ratio]" ){
  using R = gsw::ratio<1, 2>;
  using S = gsw::ratio<2, 4>;
  using T = gsw::ratio<3, 6>;

  R r;
  S s;
  T t;

  REQUIRE( r == .5 );
  REQUIRE( s == .5 );
  REQUIRE( t == .5 );
  REQUIRE( r == s );
  REQUIRE( r == t );
  REQUIRE( t == s );
  REQUIRE( R::value       == S::value );
  REQUIRE( T::value       == S::value );
  REQUIRE( R::value       == T::value );
  REQUIRE( R::numerator   == S::numerator );
  REQUIRE( T::numerator   == S::numerator );
  REQUIRE( R::numerator   == T::numerator );
  REQUIRE( R::denominator == S::denominator );
  REQUIRE( T::denominator == S::denominator );
  REQUIRE( R::denominator == T::denominator );
}

TEST_CASE( "Ratio arithmetic.", "[ratio]" ){
  using R = gsw::ratio<1, 2>;
  using S = gsw::ratio<4, 1>;
  using T = gsw::ratio<1, 4>;

  R r;
  S s;
  T t;

  REQUIRE( decltype( r * s )::value == 2 );
  REQUIRE( r * s == 2 );
  REQUIRE( ( r   * 4 ) == 2 );
  REQUIRE( ( R() * 4 ) == 2 );
  REQUIRE( ( r * s ) == ( R() * 4 ) );
  REQUIRE( r.invert() == 2 );
  REQUIRE( s.invert() == T() );
  REQUIRE( s.invert() == t );
}

