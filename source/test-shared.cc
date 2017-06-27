#include<catch.hpp>

#include<shared_ptr.hh>

using namespace gsw;

TEST_CASE( "Shared_ptrs have a similar interface to regular pointers", "[shared_ptr]" ){
  int* iPtr0 = new int( 3 );
  shared_ptr<int> sPtr0;

  sPtr0 = iPtr0;

  SECTION( "Initial equality checks." ){
    REQUIRE( sPtr0 == iPtr0 );
    REQUIRE( *sPtr0 == *iPtr0 );

    *iPtr0 = 5;
    REQUIRE( *sPtr0 == 5 );
    *sPtr0 = 4;
    REQUIRE( *iPtr0 == 4 );
  }

  SECTION( "Dereferenced shared_ptrs can be assigned" ){
    *sPtr0 = 4;

    REQUIRE( *sPtr0 == 4 );
    REQUIRE( *iPtr0 == 4 );
  }

  SECTION( "There can be multiple valid instances of a shared_ptr" ){
    shared_ptr<int> sPtr1 = sPtr0;
    shared_ptr<int> sPtr2( sPtr0 );

    REQUIRE( sPtr0 == sPtr1 );
    REQUIRE( *sPtr0 == *sPtr1 );
    REQUIRE( sPtr0 == sPtr2 );
    REQUIRE( *sPtr0 == *sPtr2 );
  }

  SECTION( "Copies of a shared pointer are not invalidated when others go out of scope" ){
    {
      shared_ptr<int> sPtr1 = sPtr0;
    }

    REQUIRE( *sPtr0 == 3 );
  }
}

