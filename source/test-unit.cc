#include<catch.hpp>

#include<unit.hh>

using namespace gsw;

TEST_CASE( "Units participate in arithmetic", "[unit]" ){
  typedef unit<1, 0, 0, 0, 0, 0, 0> test_t;

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
    voltage<> V = 3.0;
    current<> I = 5.0;
    resistance<> R = 4.0;

    V = I * R;

    REQUIRE( V.getValue() == I.getValue() * R.getValue() );
    I = 3.0;

    I = V / R;

    REQUIRE( I == 5.0 );
    REQUIRE( I.getValue() == V.getValue() / R.getValue() );

    test_t X = 2.0;
    test_t Y = 3.0;
    unit<2, 0, 0, 0, 0, 0, 0> Z;

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
    typedef voltage<double, kilo> kiloVolt;
    resistance<> r( 500 );
    kiloVolt kv( 3 );

    current<> I;

    I = kv / r;

    REQUIRE( I == 6.0 );
    REQUIRE( kv == 3.0 );
    REQUIRE( kv.getRaw() == 3000.0 );
  }

  SECTION( "Compatible storage classes can be used together" ){
    voltage<int> v1( 3 );
    voltage<> v2( 3.9 );

    v1 = v2;

    REQUIRE( v1 != v2 );
    REQUIRE( v1 == 3 );
  }
}

TEST_CASE( "Unit can be used as a constant expression.", "[unit]" ){
  const voltage<> v1( 3 );
  const voltage<> v2( 3 );
  const voltage<> v3( 5 );
  const double d1 = v1.getValue();
  const double d2 = v1.getRaw();
  const double d3 = ( v1 + 4 ).getValue();

  REQUIRE( d1 == 3 );
  REQUIRE( d2 == 3 );
  REQUIRE( d3 == 7 );
  REQUIRE( v2 == v1 );
  REQUIRE( v1 < v3 );
  REQUIRE( v3 > v1 );
  REQUIRE( v1 <= v2 );
  REQUIRE( v1 >= v2 );
}

TEST_CASE( "Arithmetic doesn't confuse prefixes.", "[unit]" ){
  voltage<double, kilo> kv( 12 );
  current<double, milli> a;
  resistance<> o( 3 );
  a = kv / o;

  REQUIRE( a.getValue() == 4000000 );
}

TEST_CASE( "Upholstery Heater test", "[unit]" ){
  using int_time = gsw::time<unsigned long long, milli>;
  using sched_tick_rate = unit<0, 1, 0, 0, 0, 0, 0, 0, -1, unsigned long long, milli>;
  const tick<> t = int_time( 50 ) / sched_tick_rate( 5 );

  REQUIRE( t == 10 );
}

