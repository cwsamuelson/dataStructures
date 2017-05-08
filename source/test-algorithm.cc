#include<random>

#include<catch/catch.hpp>

#include<algorithm.hh>

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
}

