#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include<ratio.hh>

TEST_CASE( "Ratio equivalence.", "[ratio]" ){
  using R = gsw::ratio<1, 2>;
  using S = gsw::ratio<2, 4>;
  using T = gsw::ratio<3, 6>;

  R r;
  S s;
  T t;

  CHECK( r == .5 );
  CHECK( s == .5 );
  CHECK( t == .5 );
  CHECK( r == s );
  CHECK( r == t );
  CHECK( t == s );
  CHECK( R::value       == S::value );
  CHECK( T::value       == S::value );
  CHECK( R::value       == T::value );
  CHECK( R::numerator   == S::numerator );
  CHECK( T::numerator   == S::numerator );
  CHECK( R::numerator   == T::numerator );
  CHECK( R::denominator == S::denominator );
  CHECK( T::denominator == S::denominator );
  CHECK( R::denominator == T::denominator );
}

TEST_CASE( "Ratio arithmetic.", "[ratio]" ){
  using R = gsw::ratio<1, 2>;
  using S = gsw::ratio<4, 1>;
  using T = gsw::ratio<1, 4>;

  R r;
  S s;
  T t;

  CHECK( decltype( r * s )::value == 2 );
  CHECK( r * s == 2 );
  CHECK( ( r   * 4 ) == 2 );
  CHECK( ( R() * 4 ) == 2 );
  CHECK( ( r * s ) == ( R() * 4 ) );
  CHECK( r.invert() == 2 );
  CHECK( s.invert() == T() );
  CHECK( s.invert() == t );
}
