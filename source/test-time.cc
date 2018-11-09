#include<sstream>

#include<catch.hpp>

#include<date_time.hh>

using namespace std;
using namespace gsw;

TEST_CASE( "Regular operations can be performed on time units", "[time]" ){

  SECTION( "Time units convert nicely, and report expected amounts." ){
    minute m( 1 );
    second s( m );

    CHECK( s == 60 );
    CHECK( m == 1 );
  }

  SECTION( "Units interact with ostreams." ){
    minute m( 1 );
    stringstream ss;
    string str;

    ss << m;
    ss >> str;
    CHECK( str == "1" );
    ss >> str;
    CHECK( str == "minutes" );
  }

  SECTION( "A date is printed in a human readable format to an ostream." ){
    date dayt( 11, 8, 2016 );
    stringstream ss;
    string str;

    ss << dayt;
    ss >> str;
    CHECK( str == "11" );
    ss >> str;
    CHECK( str == "August" );
    ss >> str;
    CHECK( str == "2016" );
  }

  SECTION( "Mathematical operations can be performed on time units." ){
    minute m( 59 );

    m += 1;

    CHECK( m == 60 );

    hour h( m );

    CHECK( h == 1 );

    m -= 5;

    CHECK( ++h == 2 );
    CHECK( m == 55 );
    CHECK( m++ == 55 );
    CHECK( m == 56 );
    CHECK( --h == 1 );
    CHECK( m-- == 56 );
    CHECK( m == 55 );
  }

  SECTION( "Date time interacts with streams." ){
    date_time dt( date( 11, 8, 2016 ), 15, 41, 14 );
    stringstream ss;
    string str;

    ss << dt;
    ss >> str;
    CHECK( str == "11" );
    ss >> str;
    CHECK( str == "August" );
    ss >> str;
    CHECK( str == "2016" );

    ss >> str;
    CHECK( str == "15:41:14" );
  }

  SECTION( "Units convert when using streams." ){
    string str( "5 seconds" );
    time_type<5> tu;
    stringstream ss( str );

    ss >> tu;
    CHECK( tu == 1 );

    stringstream ss2;

    ss2 << second( 10 );
    ss2 >> tu;
    CHECK( tu == 2 );
  }
}

TEST_CASE( "Some units of time provide literal suffixes", "[time]" ){
  CHECK( 1_s == second( 1 ) );
  CHECK( 1_m == minute( 1 ) );
  CHECK( 1_m == second( 60 ) );
  CHECK( 2_m == second( 120 ) );

  CHECK( ( second( 1 ) + second( 1 ) ) == 2 );
  CHECK( ( second( 1 ) + 1_s )         == 2 );
  CHECK( ( 1_s         + 1_s )         == 2 );
  CHECK( ( 1_s         + second( 1 ) ) == 2 );

  CHECK( ( second( 1 ) + second( 1 ) ) == second( 2 ) );
  CHECK( ( second( 1 ) + 1_s )         == second( 2 ) );
  CHECK( ( 1_s         + 1_s )         == second( 2 ) );
  CHECK( ( 1_s         + second( 1 ) ) == second( 2 ) );

  CHECK( ( second( 1 ) + second( 1 ) ) == 2_s );
  CHECK( ( second( 1 ) + 1_s )         == 2_s );
  CHECK( ( 1_s         + 1_s )         == 2_s );
  CHECK( ( 1_s         + second( 1 ) ) == 2_s );

  CHECK( ( 0_s + second( 3 ) ) == 3 );
  CHECK( ( 2_s + second( 3 ) ) == 5 );
  CHECK( ( 0_m + minute( 3 ) ) == 3 );
  CHECK( ( 2_m + minute( 3 ) ) == 5 );
  CHECK( ( 0_h +   hour( 3 ) ) == 3 );
  CHECK( ( 2_h +   hour( 3 ) ) == 5 );
  CHECK( ( 0_d +    day( 3 ) ) == 3 );
  CHECK( ( 2_d +    day( 3 ) ) == 5 );
  CHECK( ( 0_w +   week( 3 ) ) == 3 );
  CHECK( ( 2_w +   week( 3 ) ) == 5 );
  CHECK( ( 0_M +  month( 3 ) ) == 3 );
  CHECK( ( 2_M +  month( 3 ) ) == 5 );
  CHECK( ( 0_y +   year( 3 ) ) == 3 );
  CHECK( ( 2_y +   year( 3 ) ) == 5 );

  CHECK( ( 1_w + day( 7 ) ) == 2_w );
  CHECK( ( 1_w - day( 7 ) ) == 0_w );
}
