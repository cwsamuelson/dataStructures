#include<catch.hpp>

#include<region_tree.hh>

using namespace gsw;

TEST_CASE( "Region trees (such as quad tree and octree)", "[region_tree]" ){
  SECTION( "mathematical vector" ){
    vec<2> vec2( 1, 2 );
    REQUIRE( std::get<0>( vec2 ) == 1 );
    REQUIRE( std::get<1>( vec2 ) == 2 );

    vec<3> vec3( 1, 2, 3 );
    REQUIRE( std::get<0>( vec3 ) == 1 );
    REQUIRE( std::get<1>( vec3 ) == 2 );
    REQUIRE( std::get<2>( vec3 ) == 3 );
  }

  quad_tree<double> qt( {0, 0}, {100, 100} );

  qt.insert( 12.0, {25, 25} );
  qt.insert( 15.0, {20, 20} );

  REQUIRE( qt.get_groups() == std::vector<std::vector<double> >{{12.0, 15.0}} );

  qt.insert( 18.0, {75, 75} );
  qt.insert( 21.0, {70, 70} );

  REQUIRE( qt.get_groups() == std::vector<std::vector<double> >{{12.0, 15.0}, {18.0, 21.0}} );

  SECTION( "too many objects in a region after a split splits again" ){
  }
}

