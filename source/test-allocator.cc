#include<catch.hpp>

#include<allocator.hh>
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

TEST_CASE( "", "[allocator]" ){
  using type = scoped;
  using traits = allocator_traits<allocator<type>>;

  allocator<type> alloc;
  type* vals = nullptr;
  bool bools[3];

  bools[0] = false;
  bools[1] = false;
  bools[2] = false;

  vals = traits::allocate( alloc, 3 );
  traits::construct( alloc, &vals[0], bools[0] );
  traits::construct( alloc, &vals[1], bools[1] );
  traits::construct( alloc, &vals[2], bools[2] );

  REQUIRE( vals != nullptr );

  REQUIRE( bools[0] );
  REQUIRE( bools[1] );
  REQUIRE( bools[2] );

  traits::destroy( alloc, &vals[0] );
  traits::destroy( alloc, &vals[1] );
  traits::destroy( alloc, &vals[2] );

  REQUIRE( !bools[0] );
  REQUIRE( !bools[1] );
  REQUIRE( !bools[2] );

  traits::deallocate( alloc, vals, 3 );

  SECTION( "" ){
  }
}

