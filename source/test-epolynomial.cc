#include<catch.hpp>

#include<polynomial.hh>
#include<algorithm.hh>

using namespace std;

TEST_CASE( "polynomial can be intuitively copied", "[equ]" ){
// compile checks
  gsw::polynomial e;
  auto a = e;
  gsw::polynomial e0( a );
  gsw::polynomial e1( gsw::polynomial() );
}

TEST_CASE( "polynomial can be used in basic arithmetic", "[equ]" ){
  vector<double> vec { 1, 1, 1 };
  vector<double> vec2 { 2, 2, 2 };
  gsw::polynomial eq( vec.begin(), vec.end() );
  gsw::polynomial eq2( vec2.begin(), vec2.end() );

  REQUIRE( eq( 2 ) == 7 );
  REQUIRE( eq2( 2 ) == 14 );

  SECTION( "Addition" ){
    REQUIRE( ( eq + eq2 )( 2 ) == 21 );
  }

  SECTION( "Subtraction" ){
    REQUIRE( ( eq2 - eq )( 2 ) == 7 );
    REQUIRE( ( eq - eq2 )( 2 ) == -7 );
  }

  SECTION( "Multiplication" ){
    REQUIRE( ( eq * 2 )( 2 ) == 2 * eq( 2 ) );

    vector<double> vec3 { 1, 1 };
    gsw::polynomial eq3( vec3.begin(), vec3.end() );
    vec3[0] = 2;
    gsw::polynomial eq4( vec3.begin(), vec3.end() );
    REQUIRE( ( eq3 * eq4 )( 2 ) == 12 );

    vector<double> vec4 { 1, 1 };
    gsw::polynomial eq5( vec4.begin(), vec4.end() );
    vec4.push_back( 1 );
    gsw::polynomial eq6( vec4.begin(), vec4.end() );
    REQUIRE( ( eq5 * eq6 )( 2 ) == 21 );
  }

  /*! @todo test dividing polynomial by another polynomial */
  SECTION( "Division" ){
    REQUIRE( ( eq2 / 2 )( 2 ) == eq2( 2 ) / 2 );

    vector<double> vec1{-5, 1};
    vector<double> vec2{-2, 1};
    vector<double> vec3{10, -7, 1};
    gsw::polynomial eq1( vec1.begin(), vec1.end() );
    gsw::polynomial eq2( vec2.begin(), vec2.end() );
    gsw::polynomial eq3( vec3.begin(), vec3.end() );

    REQUIRE( ( eq1 * eq2 ) == eq3 );
    REQUIRE( ( eq3 / eq2 ) == eq1 );
  }
}

TEST_CASE( "polynomial", "[equ]" ){
  vector<double> vec { 1, 1, 1 };
  vector<double> vec2 { 2, 2, 2 };
  gsw::polynomial eq( vec.begin(), vec.end() );
  gsw::polynomial eq2( vec2.begin(), vec2.end() );

  SECTION( "polynomial can be evaluated" ){
    REQUIRE( eq( 2 ) == 7 );
    REQUIRE( eq2( 2 ) == 14 );
  }

  SECTION( "polynomial with different number of terms" ){
    vec.push_back( 1 );
    gsw::polynomial eq3( vec.begin(), vec.end() );

    REQUIRE( eq3( 2 ) == 15 );
    REQUIRE( ( eq3 + eq )( 2 ) == 22 );
    REQUIRE( ( eq3 - eq )( 2 ) == 8 );
  }

  SECTION( "Derivative" ){
    gsw::polynomial eq3 = derive( eq2 );

    REQUIRE( eq3( 2 ) == 10 );
  }

  SECTION( "Integral" ){
    REQUIRE( integrate( eq2, 3, 1 ) == ( 29.0 + ( 1.0 / 3.0 ) ) );

    vector<double> v1 { 1 };
    gsw::polynomial e1( v1.begin(), v1.end() );

    REQUIRE( integrate( e1, 3, 0 ) == 3 );

    vector<double> v2 { 1, 2, 3 };
    gsw::polynomial e2( v2.begin(), v2.end() );

    REQUIRE( integrate( e2, 3, 0 ) == 39 );

    vector<double> v3 { 3, 2, 1 };
    gsw::polynomial e3( v3.begin(), v3.end() );

    REQUIRE( integrate( e3, 3, 0 ) == 27 );
  }
}

TEST_CASE( "polynomial can be compared to points", "[equ]" ){
  SECTION( "Degree 0 polynomial" ){
    vector<double> v1 {1};
    gsw::polynomial e1( v1.begin(), v1.end() );
    gsw::point p1;
    gsw::point p2;
    gsw::point p3;

    p1.y = 0;
    p2.y = 2;
    p3.y = 1;

    for( int i = -5; i < 5; ++i ){
      p1.x = i;
      p2.x = i;
      p3.x = i;

      REQUIRE( p1 <  e1 );
      REQUIRE( e1 >  p1 );
      REQUIRE( p1 <= e1 );
      REQUIRE( e1 >= p1 );

      REQUIRE( p2 >  e1 );
      REQUIRE( e1 <  p2 );
      REQUIRE( p2 >= e1 );
      REQUIRE( e1 <= p2 );

      REQUIRE( e1 == p3 );
      REQUIRE( p3 == e1 );
      REQUIRE( e1 >= p3 );
      REQUIRE( p3 >= e1 );
      REQUIRE( e1 <= p3 );
      REQUIRE( p3 <= e1 );
    }
  }

  SECTION( "Degree 1 polynomial" ){
    vector<double> v1 {0, 2};
    gsw::polynomial e1( v1.begin(), v1.end() );
    gsw::point p1;
    gsw::point p2;
    gsw::point p3;

    for( int i = -5; i < 5; ++i ){
      p1.x = i;
      p2.x = i;
      p3.x = i;
      p1.y = 2 * i - 1;
      p2.y = 2 * i + 1;
      p3.y = 2 * i;

      REQUIRE( p1 <  e1 );
      REQUIRE( e1 >  p1 );
      REQUIRE( p1 <= e1 );
      REQUIRE( e1 >= p1 );

      REQUIRE( p2 >  e1 );
      REQUIRE( e1 <  p2 );
      REQUIRE( p2 >= e1 );
      REQUIRE( e1 <= p2 );

      REQUIRE( e1 == p3 );
      REQUIRE( p3 == e1 );
      REQUIRE( e1 >= p3 );
      REQUIRE( p3 >= e1 );
      REQUIRE( e1 <= p3 );
      REQUIRE( p3 <= e1 );
    }
  }
}

TEST_CASE( "", "[equ]" ){
  SECTION( "" ){
    vector<double> v1{-5, 3};
    gsw::polynomial e1( v1.begin(), v1.end() );
    auto answers = e1.solve();

    REQUIRE( answers.size() == 1 );
    for( auto solution : answers ){
      REQUIRE( gsw::are_equal( solution, 5.0 / 3.0 ) );
    }
  }

  SECTION( "" ){
    vector<double> v1{10, -7, 1};
    gsw::polynomial e1( v1.begin(), v1.end() );
    auto answers = e1.solve();

    CHECK( answers.size() == 2 );
    CHECK( answers == set<double>( {5, 2} ) );
  }
}

