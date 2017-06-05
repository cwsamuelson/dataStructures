#include<catch.hpp>

#include<array.hh>

TEST_CASE( "Arrays can be used as builtin arrays.", "[array]" ){
  gsw::array<char[3]> arr;
  
  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';
  
  SECTION( "Array basics." ){
    REQUIRE( arr[0] == 'a' );
    REQUIRE( arr[1] == 'b' );
    REQUIRE( arr[2] == 'c' );
  }

  SECTION( "Array range-based for." ){
    unsigned int i = 0;
    for( auto it : arr ){
      REQUIRE( it == arr[i++] );
    }
  }
}

//TODO: performance testing on array splicing
TEST_CASE( "Arrays can be 'spliced'.", "[array]" ){
  gsw::array<char[10]> arr;

  for( unsigned int i = 0; i < arr.size(); ++i ){
    arr[i] = char( i + 'a' );
  }

  SECTION( "Basic splice indeces." ){
    arr[arr > 8] = 'z';
    arr[arr < 2] = 'y';

    for( unsigned int i = 0; i < 2; ++i ){
      REQUIRE( arr[i] == 'y' );
    }
    for( unsigned int i = 9; i < 10; ++i ){
      REQUIRE( arr[i] == 'z' );
    }

    arr[arr >= 6] = 'x';
    arr[arr <= 4] = 'w';

    for( unsigned int i = 0; i < 4; ++i ){
      REQUIRE( arr[i] == 'w' );
    }
    for( unsigned int i = 6; i < 10; ++i ){
      REQUIRE( arr[i] == 'x' );
    }
  }

  SECTION( "Spliced by another container" ){
    gsw::array<unsigned int[3]> ids;

    ids[0] = 1;
    ids[1] = 3;
    ids[2] = 5;

    arr[ids] = 'z';

    for( auto it : ids ){
      REQUIRE( arr[it] == 'z' );
    }

    for( unsigned int i = 6; i < 10; ++i ){
      REQUIRE( arr[i] == ( 'a' + i ) );
    }
  }
}

