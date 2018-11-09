#include<catch.hpp>

#include<function.hh>

int testfn(){
  return 5;
}

class functor{
public:
  int
  operator()( int i ){
    return i + 5;
  }
};

TEST_CASE( "Function objects are used as normal functions.", "[function]" ){
  gsw::function<int( int )> fn;
  gsw::function<int( int )> fn2;
  gsw::function<int( int, int )> nf;
  gsw::function<int()> tst;

  fn = []( int x ){ return 1 + x; };
  nf = []( int x, int y ){ return x + y; };
  tst = testfn;
  fn2 = functor();

  SECTION( "Calling functions produce expected results." ){
    CHECK( fn( 3 ) == 4 );
    CHECK( nf( 1, 2 ) == 3 );
    CHECK( tst() == 5 );
    CHECK( fn2( 5 ) == 10 );
  }
}
