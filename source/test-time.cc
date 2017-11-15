#include<sstream>

#include<catch.hpp>

#include<date_time.hh>

using namespace std;
using namespace gsw;

TEST_CASE( "Regular operations can be performed on time units", "[time]" ){

  SECTION( "Time units convert nicely, and report expected amounts." ){
    minute m( 1 );
    second s( m );

    REQUIRE( s == 60 );
    REQUIRE( m == 1 );
  }

  SECTION( "Units interact with ostreams." ){
    minute m( 1 );
    stringstream ss;
    string str;

    ss << m;
    ss >> str;
    REQUIRE( str == "1" );
    ss >> str;
    REQUIRE( str == "minutes" );
  }

  SECTION( "A date is printed in a human readable format to an ostream." ){
    date dayt( 11, 8, 2016 );
    stringstream ss;
    string str;

    ss << dayt;
    ss >> str;
    REQUIRE( str == "11" );
    ss >> str;
    REQUIRE( str == "August" );
    ss >> str;
    REQUIRE( str == "2016" );
  }

  SECTION( "Mathematical operations can be performed on time units." ){
    minute m( 59 );

    m += 1;

    REQUIRE( m == 60 );

    hour h( m );

    REQUIRE( h == 1 );

    m -= 5;

    REQUIRE( ++h == 2 );
    REQUIRE( m == 55 );
    REQUIRE( m++ == 55 );
    REQUIRE( m == 56 );
    REQUIRE( --h == 1 );
    REQUIRE( m-- == 56 );
    REQUIRE( m == 55 );
  }

  SECTION( "Date time interacts with streams." ){
    date_time dt( date( 11, 8, 2016 ), 15, 41, 14 );
    stringstream ss;
    string str;

    ss << dt;
    ss >> str;
    REQUIRE( str == "11" );
    ss >> str;
    REQUIRE( str == "August" );
    ss >> str;
    REQUIRE( str == "2016" );

    ss >> str;
    REQUIRE( str == "15:41:14" );
  }

  SECTION( "Units convert when using streams." ){
    string str( "5 seconds" );
    time_type<5> tu;
    stringstream ss( str );

    ss >> tu;
    REQUIRE( tu == 1 );

    stringstream ss2;

    ss2 << second( 10 );
    ss2 >> tu;
    REQUIRE( tu == 2 );
  }
}

TEST_CASE( "Some units of time provide literal suffixes", "[time]" ){
  REQUIRE( 1_s == second( 1 ) );
  REQUIRE( 1_m == minute( 1 ) );
  REQUIRE( 1_m == second( 60 ) );
  REQUIRE( 2_m == second( 120 ) );

  REQUIRE( ( second( 1 ) + second( 1 ) ) == 2 );
  REQUIRE( ( second( 1 ) + 1_s )         == 2 );
  REQUIRE( ( 1_s         + 1_s )         == 2 );
  REQUIRE( ( 1_s         + second( 1 ) ) == 2 );

  REQUIRE( ( second( 1 ) + second( 1 ) ) == second( 2 ) );
  REQUIRE( ( second( 1 ) + 1_s )         == second( 2 ) );
  REQUIRE( ( 1_s         + 1_s )         == second( 2 ) );
  REQUIRE( ( 1_s         + second( 1 ) ) == second( 2 ) );

  REQUIRE( ( second( 1 ) + second( 1 ) ) == 2_s );
  REQUIRE( ( second( 1 ) + 1_s )         == 2_s );
  REQUIRE( ( 1_s         + 1_s )         == 2_s );
  REQUIRE( ( 1_s         + second( 1 ) ) == 2_s );

  REQUIRE( ( 0_s + second( 3 ) ) == 3 );
  REQUIRE( ( 2_s + second( 3 ) ) == 5 );
  REQUIRE( ( 0_m + minute( 3 ) ) == 3 );
  REQUIRE( ( 2_m + minute( 3 ) ) == 5 );
  REQUIRE( ( 0_h +   hour( 3 ) ) == 3 );
  REQUIRE( ( 2_h +   hour( 3 ) ) == 5 );
  REQUIRE( ( 0_d +    day( 3 ) ) == 3 );
  REQUIRE( ( 2_d +    day( 3 ) ) == 5 );
  REQUIRE( ( 0_w +   week( 3 ) ) == 3 );
  REQUIRE( ( 2_w +   week( 3 ) ) == 5 );
  REQUIRE( ( 0_M +  month( 3 ) ) == 3 );
  REQUIRE( ( 2_M +  month( 3 ) ) == 5 );
  REQUIRE( ( 0_y +   year( 3 ) ) == 3 );
  REQUIRE( ( 2_y +   year( 3 ) ) == 5 );

  REQUIRE( ( 1_w + day( 7 ) ) == 2_w );
  REQUIRE( ( 1_w - day( 7 ) ) == 0_w );
}

