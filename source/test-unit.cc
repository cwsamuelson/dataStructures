#include<catch.hpp>

#include<unit.hh>

using namespace gsw;

TEST_CASE( "Units participate in arithmetic", "[unit]" ){
  using test_t = unit<length_msr>;

  SECTION( "Units of same type can be added and subtracted" ){
    using kilovolt = voltage<double, kilo>;
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
    REQUIRE( ( kilovolt( 1 ) + kilovolt( 1 ) ) == 2 );
    REQUIRE( ( kilovolt( 1 ) - kilovolt( 1 ) ) == 0 );
  }

  SECTION( "Constants can interact with a type" ){
    using kilovolt = voltage<double, kilo>;
    kilovolt kv( 12 );

    REQUIRE( kv + 3 == kilovolt( 15 ) );
    REQUIRE( 3 + kv == kilovolt( 15 ) );
    REQUIRE( kv - 3 == kilovolt( 9 ) );
    REQUIRE( 3 - kv == kilovolt( -9 ) );
    REQUIRE( kv * 3 == kilovolt( 36 ) );
    // currently this breaks the build
    // this is a desired feature, but since similar works with addition, why
    //   does it not work for multiplication?
    //! @todo fix multiplying constant by unit
    //REQUIRE( 3 * kv == kilovolt( 36 ) );
    REQUIRE( kv / 3 == kilovolt( 4 ) );
    //REQUIRE( 36 / kv == kilovolt( 3 ) );
  }

  SECTION( "Units multiplication/division result in new unit types" ){
    SECTION( "Electricity example" ){
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
      unit<meas<2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0> > Z;

      Z = X * Y;

      REQUIRE( Z.getValue() == 6.0 );
    }

    SECTION( "Kinematics example" ){
      REQUIRE( acceleration<>( 5 ) * gsw::time<>( 2 ) * gsw::time<>( 4 ) == length<>( 40 ) );
    }
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
    using kiloVolt = voltage<double, metric, kilo>;
    resistance<> r( 500 );
    kiloVolt kv( 3 );

    current<> I;

    I = kv / r;

    REQUIRE( I == 6.0 );
    REQUIRE( kv == 3.0 );
    REQUIRE( kv.getRaw() == 3000.0 );
    REQUIRE( kv == voltage<double>( 3000 ) );
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

  static_assert( voltage<>( 3 ) == 3 );
  static_assert( voltage<>( 3 ).getValue() == 3 );
  static_assert( voltage<>( 3 ).getRaw() == 3 );
  static_assert( ( voltage<>( 3 ) + voltage<>( 4 ) ) == 7 );
  static_assert( ( voltage<>( 7 ) - voltage<>( 4 ) ) == 3 );
  static_assert( ( voltage<>( 3 ) * voltage<>( 4 ) ) == 12 );
  static_assert( ( voltage<>( 12 ) / voltage<>( 4 ) ) == 3 );
  static_assert( ( voltage<>( 3 ) += 5 ) == 8 );
  static_assert( ( voltage<>( 8 ) -= 5 ) == 3 );
  static_assert( ( voltage<>( 4 ) *= 3 ) == 12 );
  static_assert( ( voltage<>( 12 ) /= 3 ) == 4 );
  static_assert( voltage<>( 5 )++ == 5 );
  static_assert( ++voltage<>( 5 ) == 6 );
  static_assert( voltage<>( 5 )-- == 5 );
  static_assert( --voltage<>( 5 ) == 4 );
  static_assert( voltage<>( 3 ) == voltage<>( 3 ) );
  static_assert( voltage<>( 3 ) < voltage<>( 4 ) );
  static_assert( voltage<>( 4 ) > voltage<>( 3 ) );
  static_assert( voltage<>( 3 ) <= voltage<>( 3 ) );
  static_assert( voltage<>( 3 ) >= voltage<>( 3 ) );
  static_assert( ( voltage<>( 5 ) = 6.0 ) == 6 );

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
  using kilo_amp = current<long, metric, kilo>;

  voltage<long, metric, kilo> kv( 12 );
  current<long, metric, milli> a;
  resistance<long> o( 3 );
  a = kv / o;

  REQUIRE( a == 4000000 );
  REQUIRE( a == kilo_amp( 4 ) );
  REQUIRE( a.getValue() == 4000000 );
}

TEST_CASE( "Scheduler test", "[unit]" ){
  using int_time = gsw::time<unsigned long long, metric, milli>;
  using tick_rate = meas<0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0>;
  using sched_tick_rate = unit<tick_rate, metric, unsigned long long, milli>;
  const tick<unsigned long long, metric> t = int_time( 50 ) / sched_tick_rate( 5 );

  REQUIRE( t == 10 );
}

TEST_CASE( "Some units provide literal suffixes", "[unit]" ){
  REQUIRE( ( 0.0_0    + none<long double>( 3 ) )        == 3 );
  REQUIRE( ( 0.0_len  + length<long double>( 3 ) )      == 3 );
  REQUIRE( ( 0.0_mass + mass<long double>( 3 ) )        == 3 );
  REQUIRE( ( 0.0_temp + temperature<long double>( 3 ) ) == 3 );
  REQUIRE( ( 0.0_t    + gsw::time<long double>( 3 ) )   == 3 );
  REQUIRE( 3.0_A * 4.0_R == 12.0_V );

  REQUIRE( ( 0_0    + none<unsigned long long>( 3 ) )        == 3 );
  REQUIRE( ( 0_len  + length<unsigned long long>( 3 ) )      == 3 );
  REQUIRE( ( 0_mass + mass<unsigned long long>( 3 ) )        == 3 );
  REQUIRE( ( 0_temp + temperature<unsigned long long>( 3 ) ) == 3 );
  REQUIRE( ( 0_t    + gsw::time<unsigned long long>( 3 ) )   == 3 );
  REQUIRE( 3_A * 4_R == 12_V );
}
