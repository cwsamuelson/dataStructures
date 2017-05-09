#include<catch.hpp>

#include<string.hh>

TEST_CASE( "Strings can be accessed like an array", "[string]" ){
  const char* cstr = "length 8";
  string str( cstr );

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
  string str( "test string" );

  SECTION( "Strings can be compared with c-strings" ){
    REQUIRE( str == "test string" );
  }

  SECTION( "Strings can be assigned c-strings" ){
    str = cstr;

    REQUIRE( str == cstr );
  }

  SECTION( "Strings can be constructed with c-strings" ){
    string str2( cstr );

    REQUIRE( str2 == cstr );
  }

  SECTION( "Strings can be constructed with other strings" ){
    string str2( str );

    REQUIRE( str == str2 );
  }
}

