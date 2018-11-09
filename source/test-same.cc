#include<catch.hpp>

#include<is_same.hh>

using namespace gsw;

class bar{
public:
  using value_type = int;

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
  CHECK( is_same<int, signed int>::value );
  CHECK( is_same<bar, bar>::value );
  CHECK( !is_same<int, volatile int>::value );
  CHECK( !is_same<int, const int>::value );
  CHECK( !is_same<int, float>::value );
  CHECK( !is_same<int, bar>::value );
}
