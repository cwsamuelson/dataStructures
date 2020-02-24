#include<cmath>
#include<random>
#include<vector>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include <algorithm.hh>

using namespace gsw;

TEST_CASE( "Sort algorithm", "[algorithm]" ){
  int count = 1000;
  std::vector<int> vec;
  std::random_device rd;
  std::mt19937 rate( rd() );
  std::normal_distribution<> gene( 0, 10000000 );

  for( int i = 0; i < count; ++i ){
    vec.push_back( gene( rate ) );
  }

  //sort( vec.begin(), vec.end() );

  CHECK( vec.size() == count );

  for( unsigned int i = 1; i < vec.size(); ++i ){
    CHECK( vec[i] >= vec[i - 1] );
  }
}

TEST_CASE( "Floating point comparison", "[algorithm]" ){
  float f = 0.1f;
  float sum = 0;

  for( int i = 0; i < 100; ++i ){
    sum += f;
  }
  float product = f * 100;

  SECTION( "Negative testing" ){
    CHECK( !are_equal( 1, 5 ) );
    CHECK( !are_equal( 1, 2 ) );
    CHECK( !are_equal( 1, 100 ) );
  }

  CHECK(            1.0 * ( 0.5 - 0.4 - 0.1 ) != 0.0 );
  CHECK( are_equal( 1.0 * ( 0.5 - 0.4 - 0.1 ),   0.0 ) );

  CHECK(            1.0 / 3.0 != 0.333333333333333333333 );
  CHECK( are_equal( 1.0 / 3.0,   0.333333333333333333333 ) );

  CHECK(            3.0 * ( 1.0 / 3.0 ) != 1.0 );
  CHECK( are_equal( 3.0 * ( 1.0 / 3.0 ),   1.0 ) );

  CHECK(            product != sum );
  CHECK( are_equal( product, sum ) );

  CHECK(            product != f * 100 );
  CHECK( are_equal( product,   f * 100 ) );

  CHECK(            sum != f * 100 );
  CHECK( are_equal( sum,   f * 100 ) );

  CHECK(            sum != 10.0f );
  CHECK( are_equal( sum,   10.0f ) );

  CHECK(            product != 10.0f );
  CHECK( are_equal( product,   10.0f ) );

  // atan(1)*4 == pi
  CHECK(            std::sin( std::atan( 1 ) * 4 ) != 0.0 );
  CHECK( are_equal( std::sin( std::atan( 1 ) * 4 ),   0.0 ) );
}
