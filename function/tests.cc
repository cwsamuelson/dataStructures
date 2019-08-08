#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include<function.hh>

int testfn(){
  return 5;
}

class functor{
<<<<<<< HEAD:source/test-functional.cc
public:
  int
  operator()( int i ){
    return i + 5;
=======
private:
  int y;

public:
  functor(int x)
    : y(x)
  {}

  int
  operator()(int x)
  {
    return x + y;
>>>>>>> master:function/tests.cc
  }
};

TEST_CASE( "Function objects are used as normal functions.", "[function]" ){
  gsw::function<int( int )> fn;
  gsw::function<int( int )> fn2;
  gsw::function<int( int, int )> nf;
  gsw::function<int()> tst;
<<<<<<< HEAD:source/test-functional.cc

=======
  gsw::function<int(int)> fnctr;
  
// TODO test with type erasure
  //fnctr = functor(5);
>>>>>>> master:function/tests.cc
  fn = []( int x ){ return 1 + x; };
  nf = []( int x, int y ){ return x + y; };
  tst = testfn;
  fn2 = functor();

  SECTION( "Calling functions produce expected results." ){
<<<<<<< HEAD:source/test-functional.cc
    CHECK( fn( 3 ) == 4 );
    CHECK( nf( 1, 2 ) == 3 );
    CHECK( tst() == 5 );
    CHECK( fn2( 5 ) == 10 );
=======
    CHECK(fn( 3 ) == 4);
    CHECK(nf( 1, 2 ) == 3);
    CHECK(tst() == 5);
// TODO test with type erasure
    //CHECK(fnctr(3) == 8)
>>>>>>> master:function/tests.cc
  }
}
