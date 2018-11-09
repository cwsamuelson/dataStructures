#include<catch.hpp>

#include<high_polynomial.hh>

using namespace gsw;

TEST_CASE( "", "[high_poly]" ){
  SECTION( "linear equation" ){
    high_polynomial hp;

    //2x
    hp[{1.0, 0.0, 0.0}] = 2;

    for( int i = 0; i < 10; ++i ){
      CHECK( hp( {i, 0, 0} ) == 2 * i );
    }
  }

  SECTION( "Quadratic equation" ){
    high_polynomial hp;

    //3x2 + 2x
    hp[{2, 0, 0}] = 3;
    hp[{1, 0, 0}] = 2;

    CHECK( hp( {1, 0, 0} ) == 5 );
    CHECK( hp( {2, 0, 0} ) == 16 );

    hp[{0, 0, 0}] = 4;
    CHECK( hp( {1, 0, 0} ) == 9 );
    CHECK( hp( {2, 0, 0} ) == 20 );

    for( int i = 5; i < 15; ++i ){
      CHECK( hp( {i, 0, 0} ) == ( ( 3 * i * i ) + ( 2 * i ) + 4 )  );
    }

    for( int i = 0; i < 5; ++i ){
      for( int j = 0; j < 5; ++j ){
        CHECK( hp( {0, i, j} ) == 4 );
      }
    }
  }

  SECTION( "Multivariate equation" ){
    high_polynomial hp;

    //xy
    hp[{1, 1, 0}] = 1;

    CHECK( hp( {1, 0, 0} ) == 0 );
    CHECK( hp( {0, 1, 0} ) == 0 );

    CHECK( hp( {1, 1, 0} ) == 1 );
    CHECK( hp( {1, 2, 0} ) == 2 );
    CHECK( hp( {2, 1, 0} ) == 2 );
    CHECK( hp( {3, 2, 0} ) == 6 );
    CHECK( hp( {2, 3, 0} ) == 6 );

    //xy + 2xyz
    hp[{1, 1, 1}] = 2;
    for( int i = 0; i < 10; ++i ){
      for( int j = 0; j < 10; ++j ){
        for( int k = 0; k < 10; ++k ){
          CHECK( hp( {i, j, k} ) == ( i * j ) + ( 2 * i * j * k ) );
        }
      }
    }
  }
}
