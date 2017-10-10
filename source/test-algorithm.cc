#include<random>

#include<catch.hpp>

#include<algorithm.hh>

using namespace gsw;

TEST_CASE( "Sort algorithm", "[algorithm]" ){
  int count = 1000;
  vector<int> vec;
  std::random_device rd;
  std::mt19937 rate( rd() );
  std::normal_distribution<> gene( 0, 10000000 );

  for( int i = 0; i < count; ++i ){
    vec.push_back( gene( rate ) );
  }

  sort( vec.begin(), vec.end() );

  REQUIRE( vec.size() == count );

  for( unsigned int i = 1; i < vec.size(); ++i ){
    REQUIRE( vec[i] >= vec[i - 1] );
  }

  SECTION( "Floating point comparison" ){
    float f = 0.1f;
    float sum = 0;

    for( int i = 0; i < 10; ++i ){
      sum += f;
    }
    float product = f * 10;

    REQUIRE( product != sum );
    REQUIRE( are_equal( product, sum ) );
    REQUIRE( are_equal( product, f * 10 ) );
    REQUIRE( are_equal( sum, f * 10 ) );
  }
}

