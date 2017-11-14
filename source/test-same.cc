#include<catch.hpp>

#include<is_same.hh>

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

  int getj(){
    return j;
  }
};

TEST_CASE( "Same-ness checks", "[is_same]"){
  typedef is_same<int, signed int> SIGNED;
  typedef is_same<int, volatile int> VOLATILE;
  typedef is_same<int, const int> CONST_SAME;
  typedef is_same<int, float> FLOAT;
  typedef is_same<int, bar> BAR;
  typedef is_same<bar, bar> BAR_BAR;

  REQUIRE( SIGNED::value );
  REQUIRE( BAR_BAR::value );
  REQUIRE( !VOLATILE::value );
  REQUIRE( !CONST_SAME::value );
  REQUIRE( !FLOAT::value );
  REQUIRE( !BAR::value );
}

