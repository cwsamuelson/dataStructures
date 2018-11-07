#include<catch.hpp>

#include<high_polynomial.hh>

using namespace gsw;

TEST_CASE( "", "[high_poly]" ){
  SECTION( "linear equation" ){
    high_polynomial hp;

    //2x
    hp[point3{1.0, 0.0, 0.0}] = 2;

    for( int i = 0; i < 10; ++i ){
      REQUIRE( hp( {i, 0, 0} ) == 2 * i );
    }
  }

  SECTION( "Quadratic equation" ){
    high_polynomial hp;

    //3x2 + 2x
    hp[point3{2, 0, 0}] = 3;
    hp[point3{1, 0, 0}] = 2;

    REQUIRE( hp( {1, 0, 0} ) == 5 );
    REQUIRE( hp( {2, 0, 0} ) == 16 );

    hp[point3{0, 0, 0}] = 4;
    REQUIRE( hp( {1, 0, 0} ) == 9 );
    REQUIRE( hp( {2, 0, 0} ) == 20 );

    for( int i = 5; i < 15; ++i ){
      REQUIRE( hp( {i, 0, 0} ) == ( ( 3 * i * i ) + ( 2 * i ) + 4 )  );
    }

    for( int i = 0; i < 5; ++i ){
      for( int j = 0; j < 5; ++j ){
        REQUIRE( hp( {0, i, j} ) == 4 );
      }
    }
  }

  SECTION( "Multivariate equation" ){
    high_polynomial hp;

    //xy
    hp[point3{1, 1, 0}] = 1;

    REQUIRE( hp( {1, 0, 0} ) == 0 );
    REQUIRE( hp( {0, 1, 0} ) == 0 );

    REQUIRE( hp( {1, 1, 0} ) == 1 );
    REQUIRE( hp( {1, 2, 0} ) == 2 );
    REQUIRE( hp( {2, 1, 0} ) == 2 );
    REQUIRE( hp( {3, 2, 0} ) == 6 );
    REQUIRE( hp( {2, 3, 0} ) == 6 );

    for( int i = 0; i < 10; ++i ){
      for( int j = 0; j < 10; ++j ){
        REQUIRE( hp( {i, j, 0} ) == i * j );
      }
    }
  }
}
