#include<catch.hpp>

#include<unit.hh>

TEST_CASE( "Units participate in arithmetic", "[unit]" ){
  typedef gsw::unit<1, 0, 0, 0, 0, 0> test_t;

  SECTION( "Units of same type can be added and subtracted" ){
    double valX = 1;
    double valY = 2;

    test_t x = valX;
    test_t y = valY;

    test_t z = x + y;
    test_t w = y - x;

    REQUIRE( x == valX );
    REQUIRE( y == valY );
    REQUIRE( z == valX + valY );
    REQUIRE( w == valY - valX );
  }

  SECTION( "Units multiplication/division result in new unit types" ){
    gsw::voltage<> V = 3.0;
    gsw::current<> I = 5.0;
    gsw::resistance<> R = 4.0;

    V = I * R;

    REQUIRE( V.getValue() == I.getValue() * R.getValue() );
    I = 3.0;

    I = V / R;

    REQUIRE( I == 5.0 );
    REQUIRE( I.getValue() == V.getValue() / R.getValue() );

    test_t X = 2.0;
    test_t Y = 3.0;
    gsw::unit<2, 0, 0, 0, 0, 0> Z;

    Z = X * Y;

    REQUIRE( Z.getValue() == 6.0 );
  }

  SECTION( "Units of same type can be value compared" ){
    test_t X = 1.0;
    test_t Y = 1.0;
    test_t Z = 3.0;

    REQUIRE( X == Y );
    REQUIRE( X < Z );
    REQUIRE( Z > Y );
    REQUIRE( X < 3.0 );
  }

  SECTION( "Units can use compound operators" ){
    test_t X = 0.0;

    X += 3.0;
    REQUIRE( X == 3.0 );

    X -= 1.0;
    REQUIRE( X == 2.0 );
  }

  SECTION( "Unit prefixes can be used" ){
    typedef gsw::voltage<double, gsw::ratio<1000, 1> > kiloVolt;
    gsw::resistance<> r( 500 );
    kiloVolt kv( 3 );

    gsw::current<> I;

    I = kv / r;

    REQUIRE( I == 6.0 );
    REQUIRE( kv == 3.0 );
    REQUIRE( kv.getRaw() == 3000.0 );
  }

  SECTION( "Compatible storage classes can be used together" ){
    gsw::voltage<int> v1( 3 );
    gsw::voltage<> v2( 3.9 );

    v1 = v2;

    REQUIRE( v1 != v2 );
    REQUIRE( v1 == 3 );
  }
}

