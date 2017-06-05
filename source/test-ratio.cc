#include<catch.hpp>

#include<ratio.hh>

TEST_CASE( "", "[ratio]" ){
  typedef gsw::ratio<1, 2> R;
  typedef gsw::ratio<2, 4> S;
  R r;
  S s;

  REQUIRE( r == .5 );
  REQUIRE( s == .5 );
  REQUIRE( r == s );
  REQUIRE( R::value == S::value );
}

