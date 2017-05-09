#include<catch.hpp>

#include<accessor.hh>

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
      [&](value_type t ){
        ( void )t;
        ++j;
        return true;
      });
  }

  int getj(){
    return j;
  }
};

TEST_CASE( "", "[accessor]" ){
  bar b;

  REQUIRE( b.getInternal() == 0 );
  b.getInternal() = 12;
  REQUIRE( b.getInternal() == 12 );
  REQUIRE( b.getj() == 1 );
}

