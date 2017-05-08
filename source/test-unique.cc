#include<catch/catch.hpp>

#include<unique_ptr.hh>

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

  unique_ptr<int> uPtr1( uPtr0 );
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

  ptr1 = ptr2;
  ptr4 = ptr3;
  
  /* flag2 should be toggled now, and not flag1 */
  REQUIRE( !flag1 );
  REQUIRE( flag2 );
  REQUIRE( ptr4->value() == x );
  ptr4 = ptr4;
  REQUIRE( ptr4->value() == x );
  
  x = 2;
  REQUIRE( ( *ptr1 ) == 2 );
  REQUIRE( ptr4->value() == x );
}

