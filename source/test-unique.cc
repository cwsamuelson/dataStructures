#include<utility>

#include<catch.hpp>

#include<unique_ptr.hh>

using namespace gsw;

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

  CHECK( uPtr0 == iPtr0 );
  CHECK( *uPtr0 == *iPtr0 );

  unique_ptr<int> uPtr1( std::move( uPtr0 ) );
  CHECK( uPtr0 == nullptr );
  CHECK( uPtr1 == iPtr0 );

  auto uPtr2 = make_unique<int>( 5 );
  CHECK( *uPtr2 == 5 );
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
  CHECK( !flag1 );
  CHECK( flag2 );
  CHECK( ptr4->value() == x );
  ptr4 = std::move( ptr4 );
  CHECK( ptr4->value() == x );

  x = 2;
  CHECK( ( *ptr1 ) == 2 );
  CHECK( ptr4->value() == x );
}
