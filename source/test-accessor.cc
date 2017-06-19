#include<catch.hpp>

#include<accessor.hh>

using namespace gsw;

class bar{
public:
  typedef int value_type;

private:
  value_type i;
  int j;

public:
  bar():
    i(0),
    j(0){
  }

  accessor<value_type> getInternal(){
    return accessor<value_type>( i,
      [&]( value_type t ){
        if( t == 12 ){
          ++j;
          return true;
        } else {
          return false;
        }
      });
  }

  int getj(){
    return j;
  }
};

TEST_CASE( "Accessor can be assigned to, but only if permitted by callback", "[accessor]" ){
  bar b;

  REQUIRE( b.getInternal() == 0 );
  b.getInternal() = 12;
  REQUIRE( b.getInternal() == 12 );
  REQUIRE( b.getj() == 1 );
  b.getInternal() = 11;
  REQUIRE( b.getInternal() == 12 );
  REQUIRE( b.getj() == 1 );
}

TEST_CASE( "Accessor can be used as ", "[accessor]" ){
  bar b;
  auto a = b.getInternal();

  REQUIRE( a == 0 );
  a = 12;
  REQUIRE( a == 12 );
}

