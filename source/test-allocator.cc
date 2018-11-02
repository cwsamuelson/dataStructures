#include<catch.hpp>

#include<allocator.hh>
#include<pool_allocator.hh>
#include<block_allocator.hh>
#include<static_allocator.hh>
#include<tracking_allocator.hh>
#include<allocator_traits.hh>

class scoped{
private:
  bool& bl;

public:
  scoped( bool& b ):
    bl( b ){
    bl = true;
  }
  ~scoped(){
    bl = false;
  }
};

TEST_CASE( "Allocator allocates memory", "[base_allocator][allocator]" ){
  using type = scoped;
  using traits = gsw::allocator_traits<gsw::allocator<type> >;

  gsw::allocator<type> alloc;
  type* vals = nullptr;
  bool bools[3];

  bools[0] = false;
  bools[1] = false;
  bools[2] = false;

  vals = traits::allocate( alloc, 3 );
  REQUIRE( vals != nullptr );

  REQUIRE( !bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( !bools[2] );

  traits::construct( alloc, &vals[0], bools[0] );
  REQUIRE( bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( !bools[2] );

  traits::construct( alloc, &vals[1], bools[1] );
  REQUIRE( bools[0] );
  REQUIRE( bools[1] );
  REQUIRE( !bools[2] );

  traits::construct( alloc, &vals[2], bools[2] );
  REQUIRE( bools[0] );
  REQUIRE( bools[1] );
  REQUIRE( bools[2] );

  traits::destroy( alloc, &vals[0] );
  REQUIRE( !bools[0] );
  REQUIRE( bools[1] );
  REQUIRE( bools[2] );

  traits::destroy( alloc, &vals[1] );
  REQUIRE( !bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( bools[2] );

  traits::destroy( alloc, &vals[2] );
  REQUIRE( !bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( !bools[2] );

  traits::deallocate( alloc, vals, 3 );
}

TEST_CASE( "pool", "[pool_allocator][allocator]" ){
  using type = scoped;
  using traits = gsw::allocator_traits<gsw::pool_allocator<type> >;

  gsw::pool_allocator<type> alloc( 10 );
  type* vals = nullptr;
  bool bools[5];

  type* foo = traits::allocate( alloc, 2 );
  type* bar = traits::allocate( alloc, 1 );
  type* baz = traits::allocate( alloc, 2 );

  REQUIRE( foo != bar );
  REQUIRE( foo != baz );
  REQUIRE( bar != baz );

  type* last = bar;
  traits::deallocate( alloc, bar, 1 );
  bar = traits::allocate( alloc, 2 );

  REQUIRE( bar != last );
  REQUIRE( ( baz + 2 ) == bar );

  type* quux = traits::allocate( alloc, 2 );

  REQUIRE( ( bar + 2 ) == quux );

  traits::deallocate( alloc, foo, 2 );
  traits::deallocate( alloc, bar, 2 );
  traits::deallocate( alloc, baz, 2 );
}

TEST_CASE( "static", "[static_allocator][allocator]" ){
  using type = scoped;
  using traits = gsw::allocator_traits<gsw::static_allocator<type, 7> >;

  gsw::static_allocator<type, 7> alloc;

  type* foo = traits::allocate( alloc, 2 );
  type* bar = traits::allocate( alloc, 1 );
  type* baz = traits::allocate( alloc, 2 );

  REQUIRE( foo != bar );
  REQUIRE( bar != baz );
  REQUIRE( baz != foo );

  type* last = bar;
  traits::deallocate( alloc, bar, 1 );

  bar = traits::allocate( alloc, 1 );
  REQUIRE( bar == last );

  traits::deallocate( alloc, bar, 1 );
  bar = traits::allocate( alloc, 2 );

  REQUIRE( bar != last );

  traits::deallocate( alloc, foo, 2 );
  traits::deallocate( alloc, bar, 2 );
  traits::deallocate( alloc, baz, 2 );
}

TEST_CASE( "block", "[block_allocator][allocator]" ){
  using type = scoped;
  using traits = gsw::allocator_traits<gsw::block_allocator<type, 7> >;

  gsw::block_allocator<type, 7> alloc;

  type* foo = traits::allocate( alloc, 2 );
  type* bar = traits::allocate( alloc, 1 );
  type* baz = traits::allocate( alloc, 2 );

  REQUIRE( foo != bar );
  REQUIRE( bar != baz );
  REQUIRE( baz != foo );

  type* last = bar;
  traits::deallocate( alloc, bar, 1 );

  bar = traits::allocate( alloc, 1 );
  REQUIRE( bar == last );

  traits::deallocate( alloc, bar, 1 );
  bar = traits::allocate( alloc, 2 );

  REQUIRE( bar != last );
  REQUIRE( bar == ( baz + 2 ) );

  // create new block
  type* quux = traits::allocate( alloc, 2 );
  REQUIRE( quux != ( bar + 2 ) );

  traits::deallocate( alloc, foo, 2 );
  traits::deallocate( alloc, bar, 2 );
  traits::deallocate( alloc, baz, 2 );
  traits::deallocate( alloc, quux, 2 );
}

TEST_CASE( "tracking", "[tracking_allocator][allocator]" ){
  using type = scoped;
  using traits = gsw::allocator_traits<gsw::tracking_allocator<type> >;

  gsw::tracking_allocator<type> alloc;
  type* vals = nullptr;
  bool bools[3];

  bools[0] = false;
  bools[1] = false;
  bools[2] = false;

  vals = traits::allocate( alloc, 3 );
  REQUIRE( vals != nullptr );

  REQUIRE( alloc.usage() == 3 );
  REQUIRE( alloc.max_usage() == 3 );

  REQUIRE( !bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( !bools[2] );

  traits::construct( alloc, &vals[0], bools[0] );
  REQUIRE( bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( !bools[2] );

  traits::construct( alloc, &vals[1], bools[1] );
  REQUIRE( bools[0] );
  REQUIRE( bools[1] );
  REQUIRE( !bools[2] );

  traits::construct( alloc, &vals[2], bools[2] );
  REQUIRE( bools[0] );
  REQUIRE( bools[1] );
  REQUIRE( bools[2] );

  traits::destroy( alloc, &vals[0] );
  REQUIRE( !bools[0] );
  REQUIRE( bools[1] );
  REQUIRE( bools[2] );

  traits::destroy( alloc, &vals[1] );
  REQUIRE( !bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( bools[2] );

  traits::destroy( alloc, &vals[2] );
  REQUIRE( !bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( !bools[2] );

  traits::deallocate( alloc, vals, 3 );
  REQUIRE( alloc.usage() == 0 );
  REQUIRE( alloc.max_usage() == 3 );
}
