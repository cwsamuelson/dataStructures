#include<catch.hpp>

#include<region_tree.hh>

using namespace gsw;

TEST_CASE( "Region trees (such as quad tree and octree)", "[region_tree]" ){
  SECTION( "mathematical vector" ){
    vec<2> test(1, 2);
    REQUIRE( std::get<0>( test ) == 1 );
    REQUIRE( std::get<1>( test ) == 2 );

    vec<3> vec3( 1, 2, 3 );
    REQUIRE( std::get<0>( test ) == 1 );
    REQUIRE( std::get<1>( test ) == 2 );
    REQUIRE( std::get<2>( test ) == 3 );
  }

  quad_tree<double> qt( {0, 0}, {100, 100} );

  qt.insert( 12.0, {12, 42} );
  qt.insert( 15.0, {52, 12} );
  qt.insert( 18.0, {12, 12} );


  SECTION( "too many objects in a region after a split splits again" ){
  }
}

