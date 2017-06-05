#include<catch.hpp>

#include<operators.hh>

class foo : public gsw::additive<foo, int>,
                   gsw::multiplicative<foo, int>{
private:
  int x;

public:
  foo( int y ):
    x( y ){
  }
  foo( const foo& ) = default;

  friend foo& operator+=( foo& lhs, int rhs ){
    lhs.x += rhs;

    return lhs;
  }

  friend foo& operator*=( foo& lhs, int rhs ){
    lhs.x *= rhs;

    return lhs;
  }

  int getVal(){
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

  friend bar& operator+=( bar& lhs, const bar& rhs ){
    lhs.x += rhs.x;

    return lhs;
  }

  friend bar& operator*=( bar& lhs, const bar& rhs ){
    lhs.x *= rhs.x;

    return lhs;
  }

  int getVal(){
    return x;
  }
};

TEST_CASE( "", "[]" ){
  foo a( 3 );
  foo b( 3 );
  bar c( 3 );
  bar d( 3 );

  REQUIRE( ( c + d ).getVal() == 6 );
  REQUIRE( ( a + 5 ).getVal() == 8 );
  REQUIRE( ( b * 5 ).getVal() == 15 );
}

