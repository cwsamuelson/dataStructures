#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include<operators.hh>

class foo : public gsw::additive<foo, int>,
                   gsw::additive<int, foo>,
                   gsw::multiplicative<foo, int>,
                   gsw::multiplicative<int, foo>{
private:
  int x;

public:
  foo( int y ):
    x( y ){
  }
  foo( const foo& ) = default;

  friend
  foo&
  operator+=( foo& lhs, int rhs ){
    lhs.x += rhs;

    return lhs;
  }

  friend
  int&
  operator+=( int& lhs, const foo& rhs ){
    lhs += rhs.x;

    return lhs;
  }

  friend
  foo&
  operator*=( foo& lhs, int rhs ){
    lhs.x *= rhs;

    return lhs;
  }

  friend
  int&
  operator*=( int& lhs, const foo& rhs ){
    lhs *= rhs.x;

    return lhs;
  }

  int
  getVal(){
    return x;
  }
};

class bar : public gsw::additive<bar>,
                   gsw::multiplicative<bar>{
private:
  int x;

public:
  bar( int y ):
    x( y ){
  }
  bar( const bar& ) = default;

  friend
  bar&
  operator+=( bar& lhs, const bar& rhs ){
    lhs.x += rhs.x;

    return lhs;
  }

  friend
  bar&
  operator*=( bar& lhs, const bar& rhs ){
    lhs.x *= rhs.x;

    return lhs;
  }

  int
  getVal(){
    return x;
  }
};

TEST_CASE( "Operator usage", "[operators]" ){
  foo a( 3 );
  foo b( 3 );
  bar c( 3 );
  bar d( 3 );

  CHECK( ( c + d ).getVal() == 6 );
  CHECK( ( d + c ).getVal() == 6 );

  CHECK( ( a + 5 ).getVal() == 8 );
  CHECK( ( 5 + a ) == 8 );

  CHECK( ( b * 5 ).getVal() == 15 );
  CHECK( ( 5 * b ) == 15 );
}
