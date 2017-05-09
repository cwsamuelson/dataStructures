#include<catch.hpp>

#include<date_time.hh>

TEST_CASE( "Regular operations can be performed on time units", "[time]" ){

  SECTION( "Time units convert nicely, and report expected amounts." ){
    minute m( 1 );
    second s( m );

    REQUIRE( s == 60 );
    REQUIRE( m == 1 );
  }

  SECTION( "Units interact with ostreams." ){
    minute m( 1 );
    std::stringstream ss;
    std::string str;

    ss << m;
    ss >> str;
    REQUIRE( str == "1" );
    ss >> str;
    REQUIRE( str == "minutes" );
  }

  SECTION( "A date is printed in a human readable format to an ostream." ){
    date dayt( 11, 8, 2016 );
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
    minute m( 59 );

    m += 1;

    hour h( m );

    REQUIRE( h == 1 );

    m -= 5;

    REQUIRE( m == 55 );

    REQUIRE( ++h == 2 );
    REQUIRE( m++ == 55 );
    REQUIRE( m == 56 );
    REQUIRE( --h == 1 );
    REQUIRE( m-- == 56 );
    REQUIRE( m == 55 );
  }

  SECTION( "Date time interacts with streams." ){
    date_time dt( date( 11, 8, 2016 ), 15, 41, 14 );
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
    time_unit<5> tu;
    std::stringstream ss( str );

    ss >> tu;
    REQUIRE( tu == 1 );

    std::stringstream ss2;

    ss2 << second( 10 );
    ss2 >> tu;
    REQUIRE( tu == 2 );
  }
}


