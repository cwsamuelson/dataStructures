#include<catch.hpp>

#include<memory_pool.hh>

TEST_CASE( "Memory pool will allocate resources from its collection.", "[mempool]" ){
  gsw::memoryPool<int> test( 10 );
  REQUIRE( test.in_use_count() == 0 );
  REQUIRE( test.available_space() == 10 );

  int* foo = test.allocate( 2 );
  int* bar = test.allocate( 1 );
  int* baz = test.allocate( 2 );
  REQUIRE( test.in_use_count() == 5 );
  REQUIRE( test.available_space() == 5 );

  test.deallocate( bar );
  REQUIRE( test.in_use_count() == 4 );
  REQUIRE( test.available_space() == 6 );

  bar = test.allocate( 2 );
  REQUIRE( test.in_use_count() == 6 );
  REQUIRE( test.available_space() == 4 );

  int* quux = test.allocate( 1 );
  REQUIRE( test.in_use_count() == 7 );
  REQUIRE( test.available_space() == 3 );

  REQUIRE( ( baz + 2 ) == bar );
  REQUIRE( ( foo + 2 ) == quux );

  //test invalid allocation
  REQUIRE( test.allocate( 20 ) == nullptr );
  REQUIRE( test.in_use_count() == 7 );
  REQUIRE( test.available_space() == 3 );

  //test invalid deallocation
  test.deallocate( baz + 1 );
  REQUIRE( test.in_use_count() == 7 );
  REQUIRE( test.available_space() == 3 );
}

