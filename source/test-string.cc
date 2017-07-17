#include<catch.hpp>

#include<string.hh>

TEST_CASE( "Strings can be accessed like an array", "[string]" ){
  const char* cstr = "length 8";
  gsw::string str( cstr );

  REQUIRE( str.size() == 8 );

  for( unsigned int i = 0; i < str.size(); ++i ){
    REQUIRE( cstr[i] == str[i] );
  }

  int i = 0;
  for( auto it:str ){
    REQUIRE( it == cstr[i++] );
  }
}

TEST_CASE( "Strings can construct and assign with strings and string literals", "[string]" ){
  const char* cstr = "cstring";
  gsw::string str( "test string" );

  SECTION( "Strings can be compared with c-strings" ){
    REQUIRE( str == "test string" );
  }

  SECTION( "Strings can be assigned c-strings" ){
    str = cstr;

    REQUIRE( str == cstr );
  }

  SECTION( "Strings can be constructed with c-strings" ){
    gsw::string str2( cstr );

    REQUIRE( str2 == cstr );
  }

  SECTION( "Strings can be constructed with other strings" ){
    gsw::string str2( str );

    REQUIRE( str == str2 );
  }
}

TEST_CASE( "Strings have compile time facility", "[string]" ){
  typedef gsw::ct_string<'a', 'b', 'c'> abc;
  typedef gsw::ct_string<'1', '2', '3'> nums;
  typedef typename gsw::concatenate<abc, nums>::result cat;

  REQUIRE( gsw::string( "abc123" ) == cat::string() );
}

