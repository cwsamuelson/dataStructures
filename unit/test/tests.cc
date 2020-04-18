#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<unit.hh>

using namespace gsw;

TEST_CASE("Units participate in arithmetic", "[unit]") {
  using test_t = unit<length_msr>;

  SECTION("Units of same type can be added and subtracted") {
    using kilovolt = voltage<double, kilo>;
    double valX = 1;
    double valY = 2;

    test_t x = valX;
    test_t y = valY;

    test_t z = x + y;
    test_t w = y - x;

    CHECK(x == valX);
    CHECK(y == valY);
    CHECK(z == valX + valY);
    CHECK(w == valY - valX);
    CHECK((kilovolt(1) + kilovolt(1)) == 2);
    CHECK((kilovolt(1) - kilovolt(1)) == 0);
  }

  SECTION("Constants can interact with a type") {
    using kilovolt = voltage<double, metric, kilo>;
    kilovolt kv(12);

    CHECK(kv + 3 == kilovolt(15));
    CHECK(3 + kv == kilovolt(15));
    CHECK(kv - 3 == kilovolt(9));
    CHECK(3 - kv == kilovolt(-9));
    CHECK(kv * 3 == kilovolt(36));
    // currently this breaks the build
    // this is a desired feature, but since similar works with addition, why
    //   does it not work for multiplication?
    //! @todo fix multiplying constant by unit
    //CHECK( 3 * kv == kilovolt( 36 ) );
    CHECK(kv / 3 == kilovolt(4));
    //CHECK( 36 / kv == kilovolt( 3 ) );
  }

  SECTION("Units multiplication/division result in new unit types") {
    SECTION("Electricity example") {
      voltage<> V = 3.0;
      current<> I = 5.0;
      resistance<> R = 4.0;

      V = I * R;

      CHECK(V.getValue() == I.getValue() * R.getValue());
      I = 3.0;

      I = V / R;

      CHECK(I == 5.0);
      CHECK(I.getValue() == V.getValue() / R.getValue());

      test_t X = 2.0;
      test_t Y = 3.0;
      unit<measure<2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>> Z;

      Z = X * Y;

      CHECK(Z.getValue() == 6.0);
    }

    SECTION("Kinematics example") {
      CHECK(acceleration<>(5) * gsw::time<>(2) * gsw::time<>(4) == length<>(40));
    }

    using tick_rate = decltype(tick<double>() / gsw::time<double>());
    gsw::time<double> counter(0.0);
    tick_rate rate(3.0);

    counter += gsw::time<double>(5.0);

    CHECK((counter * rate) > 1);
    CHECK((counter - ((1.0 / rate) * tick<double>(3))) == 4);

    SECTION("Units of same type can be value compared") {
      test_t X = 1.0;
      test_t Y = 1.0;
      test_t Z = 3.0;

      CHECK(X == Y);
      CHECK(X < Z);
      CHECK(Z > Y);
      CHECK(X < 3.0);
    }

    SECTION("Units can use compound operators") {
      test_t X = 0.0;

      X += 3.0;
      CHECK(X == 3.0);

      X -= 1.0;
      CHECK(X == 2.0);
    }

    SECTION("Unit prefixes can be used") {
      using kiloVolt = voltage<double, metric, kilo>;
      resistance<> r(500);
      kiloVolt kv(3);

      current<> I;

      I = kv / r;

      CHECK(I == 6.0);
      CHECK(kv == 3.0);
      CHECK(kv.getRaw() == 3000.0);
      CHECK(kv.getValue() == 3.0);
      CHECK(kv == voltage<double>(3000));
    }

    SECTION("Compatible storage classes can be used together") {
      voltage<int> v1(3);
      voltage<> v2(3.9);

      v1 = v2;

      CHECK(v1 != v2);
      CHECK(v1 == 3);
    }
  }
}

TEST_CASE("Unit can be used as a constant expression.", "[unit]") {
  const voltage<> v1(3);
  const voltage<> v2(3);
  const voltage<> v3(5);
  const double d1 = v1.getValue();
  const double d2 = v1.getRaw();
  const double d3 = (v1 + 4).getValue();

  static_assert(voltage<>(3) == 3);
  static_assert(voltage<>(3).getValue() == 3);
  static_assert(voltage<>(3).getRaw() == 3);
  static_assert((voltage<>(3) + voltage<>(4)) == 7);
  static_assert((voltage<>(7) - voltage<>(4)) == 3);
  static_assert((voltage<>(3) * voltage<>(4)) == 12);
  static_assert((voltage<>(12) / voltage<>(4)) == 3);
  static_assert((voltage<>(3) += 5) == 8);
  static_assert((voltage<>(8) -= 5) == 3);
  static_assert((voltage<>(4) *= 3) == 12);
  static_assert((voltage<>(12) /= 3) == 4);
  static_assert(voltage<>(5)++ == 5);
  static_assert(++voltage<>(5) == 6);
  static_assert(voltage<>(5)-- == 5);
  static_assert(--voltage<>(5) == 4);
  static_assert(voltage<>(3) == voltage<>(3));
  static_assert(voltage<>(3) < voltage<>(4));
  static_assert(voltage<>(4) > voltage<>(3));
  static_assert(voltage<>(3) <= voltage<>(3));
  static_assert(voltage<>(3) >= voltage<>(3));
  static_assert((voltage<>(5) = 6.0) == 6);

  CHECK(d1 == 3);
  CHECK(d2 == 3);
  CHECK(d3 == 7);
  CHECK(v2 == v1);
  CHECK(v1 < v3);
  CHECK(v3 > v1);
  CHECK(v1 <= v2);
  CHECK(v1 >= v2);
}

TEST_CASE("Arithmetic doesn't confuse prefixes.", "[unit]") {
  using kilo_amp = current<long, metric, kilo>;

  voltage<long, metric, kilo> kv(12);
  current<long, metric, milli> a;
  resistance<long> o(3);
  a = kv / o;

  CHECK(a == 4000000);
  CHECK(a == kilo_amp(4));
  CHECK(a.getValue() == 4000000);
}

TEST_CASE("Scheduler test", "[unit]") {
  using int_time = gsw::time<unsigned long long, metric, milli>;
  using tick_rate = measure<0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0>;
  using sched_tick_rate = unit<tick_rate, metric, unsigned long long, milli>;
  const tick<unsigned long long, metric> t = int_time(50) / sched_tick_rate(5);

  CHECK(t == 10);
}

TEST_CASE("Some units provide literal suffixes", "[unit]") {
  CHECK((0.0_0 + none<long double>(3)) == 3);
  CHECK((0.0_len + length<long double>(3)) == 3);
  CHECK((0.0_mass + mass<long double>(3)) == 3);
  CHECK((0.0_temp + temperature<long double>(3)) == 3);
  CHECK((0.0_t + gsw::time<long double>(3)) == 3);
  CHECK(3.0_A * 4.0_R == 12.0_V);

  CHECK((0_0 + none<unsigned long long>(3)) == 3);
  CHECK((0_len + length<unsigned long long>(3)) == 3);
  CHECK((0_mass + mass<unsigned long long>(3)) == 3);
  CHECK((0_temp + temperature<unsigned long long>(3)) == 3);
  CHECK((0_t + gsw::time<unsigned long long>(3)) == 3);
  CHECK(3_A * 4_R == 12_V);
}

class custom_system1 {};

class custom_system2 {};

using custom_unit1 = unit<length_msr, custom_system1, double, unity>;
using custom_unit2 = unit<length_msr, custom_system2, double, unity>;

template<typename T, typename F>
class converter<length_msr, custom_system1, custom_system2, T, T, F, F> : public converter_base<length_msr,
                                                                                                custom_system1,
                                                                                                custom_system2,
                                                                                                T,
                                                                                                T,
                                                                                                F,
                                                                                                F> {
public:
  using base = converter_base<length_msr, custom_system1, custom_system2, T, T, F, F>;

  constexpr converter() = default;

  constexpr typename base::result operator()(const typename base::input& val) {
    return typename base::result(val.getRaw() / 5);
  }
};

template<typename T, typename F>
class converter<length_msr, custom_system2, custom_system1, T, T, F, F> : public converter_base<length_msr,
                                                                                                custom_system2,
                                                                                                custom_system1,
                                                                                                T,
                                                                                                T,
                                                                                                F,
                                                                                                F> {
public:
  using base = converter_base<length_msr, custom_system2, custom_system1, T, T, F, F>;

  constexpr converter() = default;

  constexpr typename base::result operator()(const typename base::input& val) {
    return typename base::result(val.getRaw() * 5);
  }
};

TEST_CASE("Handles different unit systems", "[unit]") {
  SECTION("Can convert between unit systems") {
    celsius<> c(0);
    fahrenheit<> f(c);

    CHECK(f.getRaw() == 32);
    f = -40;
    c = f;
    CHECK(c.getRaw() == -40);
  }

  SECTION("Handles custom unit systems") {
    custom_unit1 cu1(5);
    custom_unit2 cu2(1);

    CHECK(cu1 == cu2);
  }
}

TEST_CASE("Converts between systems, and types and factors", "[unit]") {
  feet<> f1(3);
  meters<> m1(3);

  feet<> f2(f1);
  meters<> m2(f1);

  feet<> f3(m1);
  meters<> m3(m1);

  feet<int> f4(f1);
  meters<int> m4(f1);

  feet<int> f5(m1);
  meters<int> m5(m1);

  feet<double, ratio<5280, 1>> f6(f1);
  meters<double, ratio<1000, 1>> m6(f1);

  feet<double, ratio<5280, 1>> f7(m1);
  meters<double, ratio<1000, 1>> m7(m1);

  feet<int, ratio<5280, 1>> f8(f1);
  meters<int, ratio<1000, 1>> m8(f1);

  feet<int, ratio<5280, 1>> f9(m1);
  meters<int, ratio<1000, 1>> m9(m1);

  CHECK(f1 == f2);
  CHECK(m1 == m3);

  CHECK(f1 == f4);
  CHECK(m1 == m5);

  CHECK((f1 - m2) < .1);
  CHECK((m1 - f3) < .1);

  CHECK(f8 == 0.0);
  CHECK(m8 == 0.0);

  CHECK(f9 == 0.0);
  CHECK(m9 == 0.0);
  //@todo add more tests for this
}
