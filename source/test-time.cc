#include<catch.hpp>

#include<date_time.hh>

TEST_CASE( "Regular operations can be performed on time units", "[time]" ){

  SECTION( "Time units convert nicely, and report expected amounts." ){
    gsw::minute m( 1 );
    gsw::second s( m );

    REQUIRE( s == 60 );
    REQUIRE( m == 1 );
  }

  SECTION( "Units interact with ostreams." ){
    gsw::minute m( 1 );
    std::stringstream ss;
    std::string str;

    ss << m;
    ss >> str;
    REQUIRE( str == "1" );
    ss >> str;
    REQUIRE( str == "minutes" );
  }

  SECTION( "A date is printed in a human readable format to an ostream." ){
    gsw::date dayt( gsw::day( 11 ), 8, gsw::year( 2016 ) );
    std::stringstream ss;
    std::string str;

    ss << dayt;
    ss >> str;
    REQUIRE( str == "11" );
    ss >> str;
    REQUIRE( str == "August" );
    ss >> str;
    REQUIRE( str == "2016" );
  }

  SECTION( "Mathematical operations can be performed on time units." ){
    gsw::minute m( 59 );

    m += 1;

    gsw::hour h( m );

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
    gsw::date_time dt( gsw::date( gsw::day( 11 ), 8, gsw::year( 2016 ) ), gsw::hour( 15 ), gsw::minute( 41 ), gsw::second( 14 ) );
    std::stringstream ss;
    std::string str;

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
    std::string str( "5 seconds" );
    gsw::time_type<5> tu;
    std::stringstream ss( str );

    ss >> tu;
    REQUIRE( tu == 1 );

    std::stringstream ss2;

    ss2 << gsw::second( 10 );
    ss2 >> tu;
    REQUIRE( tu == 2 );
  }
}

