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

  SECTION( "Assignment" ){
    arr[0] = 'd';
    REQUIRE( arr[0] == 'd' );
    REQUIRE( arr[1] == 'b' );
    REQUIRE( arr[2] == 'c' );

    arr[1] = 'e';
    REQUIRE( arr[0] == 'd' );
    REQUIRE( arr[1] == 'e' );
    REQUIRE( arr[2] == 'c' );

    arr[2] = 'f';
    REQUIRE( arr[0] == 'd' );
    REQUIRE( arr[1] == 'e' );
    REQUIRE( arr[2] == 'f' );
  }
}

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

    for( unsigned int i = 0; i <= 4; ++i ){
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

/*!
 * @todo change some of these to compile-time checks
 * REQUIRE( arr[0] == 1 );
 * may execute at run time since operator[] is not declared constexpr, and not
 * sure it can/should be.  the goal here is that it won't execute at run-time,
 * only compile-time
 */
TEST_CASE( "Brace initialization", "[array]" ){
  const gsw::array<int[5]> arr{ 1, 2, 3, 4, 5 };
  const int i = arr[0];

  REQUIRE( arr[0] == 1 );
  REQUIRE( i == 1 );
  REQUIRE( arr.size() == 5 );
}
