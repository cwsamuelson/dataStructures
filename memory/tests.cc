#include<utility>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include<memory_pool.hh>
#include<shared_ptr.hh>
#include<unique_ptr.hh>

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

using namespace gsw;

class deathcry{
private:
  bool* val;

public:
  deathcry( bool* b ):
    val( b ){
  }
  ~deathcry(){
    *val = false;
  }
};

TEST_CASE( "Shared_ptrs have a similar interface to regular pointers", "[shared_ptr]" ){
  int* iPtr0 = new int( 3 );
  shared_ptr<int> sPtr0;

  sPtr0 = iPtr0;

  SECTION( "Initial equality checks." ){
    CHECK( sPtr0 == iPtr0 );
    CHECK( *sPtr0 == *iPtr0 );

    *iPtr0 = 5;
    CHECK( *sPtr0 == 5 );
    *sPtr0 = 4;
    CHECK( *iPtr0 == 4 );
  }

  SECTION( "Dereferenced shared_ptrs can be assigned" ){
    *sPtr0 = 4;

    CHECK( *sPtr0 == 4 );
    CHECK( *iPtr0 == 4 );
  }

  SECTION( "There can be multiple valid instances of a shared_ptr" ){
    shared_ptr<int> sPtr1 = sPtr0;
    shared_ptr<int> sPtr2( sPtr0 );

    CHECK( sPtr0 == sPtr1 );
    CHECK( *sPtr0 == *sPtr1 );
    CHECK( sPtr0 == sPtr2 );
    CHECK( *sPtr0 == *sPtr2 );
  }

  SECTION( "Copies of a shared pointer are not invalidated when others go out of scope" ){
    {
      shared_ptr<int> sPtr1 = sPtr0;
    }

    CHECK( *sPtr0 == 3 );
  }

  SECTION( "Destructors run appropriately" ){
    bool b = true;
    auto sp = make_shared<deathcry>( &b );
    bool b1 = true;
    {
      auto dc = make_shared<deathcry>( &b1 );
      dc = sp;
    }
    CHECK( b1 == false );
  }
}

TEST_CASE( "Shared_ptrs obey move semantics", "[shared_ptr]" ){
  bool b = true;
  auto sp = make_shared<deathcry>( &b );

  SECTION( "Move semantics will not prevent cleanup" ){
    bool b1 = true;
    {
      auto dc = make_shared<deathcry>( &b1 );
      dc = std::move( sp );
    }
    CHECK( b1 == false );
  }
}
<<<<<<< HEAD:source/test-shared.cc
=======

class foo{
private:
  int& X;
  bool& flag;
  
public:
  foo( int& x, bool& f ):
    X( x ),
    flag( f ){
    flag = false;
  }
  ~foo(){
    flag = true;
  }
  
  int& value(){
    return X;
  }
};

TEST_CASE( "Unique_ptrs have a mostly similar interface to regular pointers", "[unique_ptr]" ){
  int* iPtr0 = new int( 3 );
  unique_ptr<int> uPtr0;

  uPtr0 = iPtr0;

  REQUIRE( uPtr0 == iPtr0 );
  REQUIRE( *uPtr0 == *iPtr0 );

  unique_ptr<int> uPtr1( std::move( uPtr0 ) );
  REQUIRE( uPtr0 == nullptr );
  REQUIRE( uPtr1 == iPtr0 );

  auto uPtr2 = make_unique<int>( 5 );
  REQUIRE( *uPtr2 == 5 );
}

TEST_CASE( "Unique pointers behave mostly as regular pointers", "[unique_ptr]" ){
  int x = 1;
  int y = 2;
  bool flag1;
  bool flag2;
  unique_ptr<int> ptr1( new int );
  unique_ptr<int> ptr2( new int );
  unique_ptr<foo> ptr3( new foo( x, flag1 ) );
  unique_ptr<foo> ptr4( new foo( y, flag2 ) );
  
  *ptr1 = 1;
  *ptr2 = 2;

  ptr1 = std::move( ptr2 );
  ptr4 = std::move( ptr3 );
  
  /* flag2 should be toggled now, and not flag1 */
  REQUIRE( !flag1 );
  REQUIRE( flag2 );
  REQUIRE( ptr4->value() == x );
  ptr4 = std::move( ptr4 );
  REQUIRE( ptr4->value() == x );
  
  x = 2;
  REQUIRE( ( *ptr1 ) == 2 );
  REQUIRE( ptr4->value() == x );
}

>>>>>>> master:memory/tests.cc
