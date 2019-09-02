#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <polynomial.hh>
#include <high_polynomial.hh>
#include <algorithm.hh>

using namespace std;

TEST_CASE("polynomial can be intuitively copied", "[poly]")
{
// compile checks
  gsw::polynomial e;
  auto a = e;
  gsw::polynomial e0(a);
  gsw::polynomial e1(gsw::polynomial());
}

TEST_CASE("", "[hp]")
{
  gsw::high_polynomial hp;
  auto a = hp;
  gsw::high_polynomial hp0(a);
  gsw::high_polynomial hp1(gsw::high_polynomial());
}

TEST_CASE("polynomial can be used in basic arithmetic", "[poly]")
{
  vector<double> vec1 {1, 1, 1};
  vector<double> vec2 {2, 2, 2};
  gsw::polynomial eq1(vec1.begin(), vec1.end());
  gsw::polynomial eq2(vec2.begin(), vec2.end());

  CHECK(eq1(2) == 7);
  CHECK(eq2(2) == 14);

  SECTION("Addition")
  {
    CHECK((eq1 + eq2)(2) == 21);
  }

  SECTION("Subtraction")
  {
    CHECK((eq2 - eq1)(2) == 7);
    CHECK((eq1 - eq2)(2) == -7);
  }

  SECTION("Multiplication")
  {
    CHECK((eq1 * 2)(2) == 2 * eq1(2));

    vector<double> vec3 {1, 1};
    gsw::polynomial eq3(vec3.begin(), vec3.end());
    vec3[0] = 2;
    gsw::polynomial eq4(vec3.begin(), vec3.end());
    CHECK((eq3 * eq4)(2) == 12);

    vector<double> vec4 {1, 1};
    gsw::polynomial eq5(vec4.begin(), vec4.end());
    vec4.push_back(1);
    gsw::polynomial eq6(vec4.begin(), vec4.end());
    CHECK((eq5 * eq6)(2) == 21);
  }

  /*! @todo test dividing polynomial by another polynomial */
  SECTION("Division")
  {
    CHECK((eq2 / 2)(2) == eq2(2) / 2);

    vector<double> vec1{-5, 1};
    vector<double> vec2{-2, 1};
    vector<double> vec3{10, -7, 1};
    gsw::polynomial eq1(vec1.begin(), vec1.end());
    gsw::polynomial eq2(vec2.begin(), vec2.end());
    gsw::polynomial eq3(vec3.begin(), vec3.end());

    CHECK((eq1 * eq2) == eq3);
    CHECK((eq3 / eq2) == eq1);
  }
}

TEST_CASE("", "[hp]")
{
  using tup_type = tuple<gsw::high_polynomial::input_point, gsw::high_polynomial::value_type>;

  gsw::high_polynomial eq;
  gsw::high_polynomial::input_point p{0, 0, 0};
  eq[{0, 0, 1}] = 1.0;
  eq[p] = 2.0;
}

TEST_CASE("", "[hp]")
{
  using tup_type = tuple<gsw::high_polynomial::input_point, gsw::high_polynomial::value_type>;

  vector<tup_type> vec1{{{{0, 0, 0}}, 1.0},
                        {{{1, 0, 0}}, 1.0},
                        {{{2, 0, 0}}, 1.0}};
  vector<tup_type> vec2{{{{0, 0, 0}}, 2.0},
                        {{{1, 0, 0}}, 2.0},
                        {{{2, 0, 0}}, 2.0}};
  gsw::high_polynomial eq1(vec1.begin(), vec1.end());
  gsw::high_polynomial eq2(vec2.begin(), vec2.end());

  CHECK(eq1({{2, 0, 0}}) == 7);
  CHECK(eq2({{2, 0, 0}}) == 14);

  SECTION("Addition")
  {
    CHECK((eq1 + eq2)({{2, 0, 0}}) == 21);
  }

  SECTION("Subtraction")
  {
    CHECK((eq2 - eq1)({{2, 0, 0}}) == 7);
    CHECK((eq1 - eq2)({{2, 0, 0}}) == -7);
  }

  SECTION("Multiplication")
  {
    CHECK((eq1 * 2)({{2, 0, 0}}) == 2 * eq1({{2, 0, 0}}));
    CHECK((eq1 * 2)({{2, 0, 0}}) == eq2({{2, 0, 0}}));

    vector<gsw::high_polynomial::storage_type::value_type> vec3 {{{1, 0, 0}, 1}};
    gsw::high_polynomial eq3(vec3.begin(), vec3.end());
    vector<gsw::high_polynomial::storage_type::value_type> vec4 {{{1, 0, 0}, 2}};
    gsw::high_polynomial eq4(vec4.begin(), vec4.end());
    CHECK((eq3 * eq4)({5, 0, 0}) == 50);
    CHECK((eq3 * eq4)({5, 0, 0}) == eq3({5, 0, 0}) * eq4({5, 0, 0}));
  }

  /*! @todo test dividing high_polynomial by another high_polynomial */
  SECTION("Division")
  {
    CHECK((eq2 / 2)({{2, 0, 0}}) == eq2({{2, 0, 0}}) / 2);

    vector<gsw::high_polynomial::storage_type::value_type> vec1{{{0, 0, 0}, -5}, {{1, 0, 0}, 1}};
    vector<gsw::high_polynomial::storage_type::value_type> vec2{{{0, 0, 0}, -2}, {{1, 0, 0}, 1}};
    vector<gsw::high_polynomial::storage_type::value_type> vec3{{{0, 0, 0} ,10}, {{1, 0, 0}, -7}, {{2, 0, 0}, 1}};
    gsw::high_polynomial eq1(vec1.begin(), vec1.end());
    gsw::high_polynomial eq2(vec2.begin(), vec2.end());
    gsw::high_polynomial eq3(vec3.begin(), vec3.end());

    CHECK((eq1 * eq2) == eq3);
    CHECK((eq3 / eq2) == eq1);
  }
}

TEST_CASE("polynomial", "[poly]")
{
  vector<double> vec1{1, 1, 1};
  vector<double> vec2{2, 2, 2};
  gsw::polynomial eq1(vec1.begin(), vec1.end());
  gsw::polynomial eq2(vec2.begin(), vec2.end());

  SECTION("polynomial can be evaluated")
  {
    CHECK(eq1(2) == 7);
    CHECK(eq2(2) == 14);
  }

  SECTION("convenient poly creation")
  {
    gsw::polynomial p;

    p[0] = 1;
    p[1] = 2;
    p[2] = 3;

    CHECK(p(2) == 17);
  }

  SECTION("Inline poly creation")
  {
    gsw::polynomial p({1, 2, 3});

    CHECK(p(2) == 17);

    p[0] = 2;

    CHECK(p(2) == 18);
  }

  SECTION("polynomial with different number of terms")
  {
    vec1.push_back(1);
    gsw::polynomial eq3(vec1.begin(), vec1.end());

    CHECK(eq3(2) == 15);
    CHECK((eq3 + eq1)(2) == 22);
    CHECK((eq3 - eq1)(2) == 8);
  }

  SECTION("Derivative")
  {
    gsw::polynomial eq3 = derive(eq2);

    CHECK(eq3(2) == 10);
  }

  SECTION("Integral")
  {
    CHECK(integrate(eq2, 3, 1) == (29.0 + (1.0 / 3.0)));

    vector<double> v1 {1};
    gsw::polynomial e1(v1.begin(), v1.end());

    CHECK(integrate(e1, 3, 0) == 3);

    vector<double> v2 {1, 2, 3};
    gsw::polynomial e2(v2.begin(), v2.end());

    CHECK(integrate(e2, 3, 0) == 39);

    vector<double> v3 {3, 2, 1};
    gsw::polynomial e3(v3.begin(), v3.end());

    CHECK(integrate(e3, 3, 0) == 27);
  }
}

TEST_CASE("polynomial can be compared to points", "[poly]")
{

  SECTION("Degree 0 polynomial")
  {
    vector<double> v1 {1};
    gsw::polynomial e1(v1.begin(), v1.end());
    gsw::point p1;
    gsw::point p2;
    gsw::point p3;

    p1.y() = 0;
    p2.y() = 2;
    p3.y() = 1;

    for(int i = -5; i < 5; ++i){
      p1.x() = i;
      p2.x() = i;
      p3.x() = i;

      CHECK(p1 <  e1);
      CHECK(e1 >  p1);
      CHECK(p1 <= e1);
      CHECK(e1 >= p1);

      CHECK(p2 >  e1);
      CHECK(e1 <  p2);
      CHECK(p2 >= e1);
      CHECK(e1 <= p2);

      CHECK(e1 == p3);
      CHECK(p3 == e1);
      CHECK(e1 >= p3);
      CHECK(p3 >= e1);
      CHECK(e1 <= p3);
      CHECK(p3 <= e1);
    }
  }

  SECTION("Degree 1 polynomial")
  {
    vector<double> v1 {0, 2};
    gsw::polynomial e1(v1.begin(), v1.end());
    gsw::point p1;
    gsw::point p2;
    gsw::point p3;

    for(int i = -5; i < 5; ++i){
      p1.x() = i;
      p2.x() = i;
      p3.x() = i;
      p1.y() = 2 * i - 1;
      p2.y() = 2 * i + 1;
      p3.y() = 2 * i;

      CHECK(p1 <  e1);
      CHECK(e1 >  p1);
      CHECK(p1 <= e1);
      CHECK(e1 >= p1);

      CHECK(p2 >  e1);
      CHECK(e1 <  p2);
      CHECK(p2 >= e1);
      CHECK(e1 <= p2);

      CHECK(e1 == p3);
      CHECK(p3 == e1);
      CHECK(e1 >= p3);
      CHECK(p3 >= e1);
      CHECK(e1 <= p3);
      CHECK(p3 <= e1);
    }
  }
}

TEST_CASE("Polynomial can find its roots", "[poly]")
{
  SECTION("Linear equation")
  {
    vector<double> v1{-5, 3};
    gsw::polynomial e1(v1.begin(), v1.end());
    auto answers = e1.solve();

    CHECK(answers.size() == 1);
    for(auto solution : answers){
      CHECK(gsw::are_equal(solution, 5.0 / 3.0));
    }
  }

  SECTION("Quadratic equation(with integral roots)")
  {
    vector<double> v1{10, -7, 1};
    gsw::polynomial e1(v1.begin(), v1.end());
    auto answers = e1.solve();

    CHECK(answers.size() == 2);
    CHECK(answers == set<double>({5, 2}));
  }
}

TEST_CASE( "", "[high_poly]" ){
  SECTION( "linear equation" ){
    gsw::high_polynomial hp;

    //2x
    hp[{1, 0, 0}] = 2;

    for( int i = 0; i < 10; ++i ){
      CHECK( hp( {i, 0, 0} ) == 2 * i );
    }
  }

SECTION( "Quadratic equation" ){
  gsw::high_polynomial hp;

  //3x2 + 2x
  hp[{2, 0, 0}] = 3;
  hp[{1, 0, 0}] = 2;

  CHECK( hp( {1, 0, 0} ) == 5 );
  CHECK( hp( {2, 0, 0} ) == 16 );

  hp[{0, 0, 0}] = 4;
  CHECK( hp( {1, 0, 0} ) == 9 );
  CHECK( hp( {2, 0, 0} ) == 20 );

  for( int i = 5; i < 15; ++i ){
    CHECK( hp( {i, 0, 0} ) == ( ( 3 * i * i ) + ( 2 * i ) + 4 )  );
  }

  for( int i = 0; i < 5; ++i ){
    for( int j = 0; j < 5; ++j ){
      CHECK( hp( {0, i, j} ) == 4 );
    }
  }
}

  SECTION( "Multivariate equation" ){
    gsw::high_polynomial hp;

    //xy
    hp[{1, 1, 0}] = 1;

    CHECK( hp( {1, 0, 0} ) == 0 );
    CHECK( hp( {0, 1, 0} ) == 0 );

    CHECK( hp( {1, 1, 0} ) == 1 );
    CHECK( hp( {1, 2, 0} ) == 2 );
    CHECK( hp( {2, 1, 0} ) == 2 );
    CHECK( hp( {3, 2, 0} ) == 6 );
    CHECK( hp( {2, 3, 0} ) == 6 );

    //xy + 2xyz
    hp[{1, 1, 1}] = 2;
    for( int i = 0; i < 10; ++i ){
      for( int j = 0; j < 10; ++j ){
        for( int k = 0; k < 10; ++k ){
          CHECK( hp( {i, j, k} ) == ( i * j ) + ( 2 * i * j * k ) );
        }
      }
    }
  }
}
