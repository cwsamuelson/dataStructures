#include <system.hh>
#include <units.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct TestSystem : System {};
struct TestBase : DimensionBase {};

//struct TestDimension : Dimension<TestBase>{};

TEST_CASE("Units") {
  Unit<double, Dimension<>, TestSystem> unit;
  Unit<double, Dimension<TestDimension{0}>, TestSystem> unit;
}

TEST_CASE("Test Units") {
  Unit<double, Dimension<TestDimension{1}>, TestSystem> unit;
}

TEST_CASE("From Boost") {
  /*const double s1 = 2;
  const long x1 = 3;
  const static_rational<4, 3> x2;

  force u1 = newton;
  energy u2 = joule;

  quantity<force> q1(1.0 * u1);
  quantity<energy> q2(2.0 * u2);*/
}

