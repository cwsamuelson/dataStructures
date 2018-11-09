#include<algorithm>

#include<catch.hpp>

#include<range.hh>

TEST_CASE( "A range iterator can act as a standard iterator", "[range]" ){
  std::vector<int> source{2, 3, 4, 5, 6 };
  gsw::range<decltype( source )> rng( source );

  SECTION( "Initial basic range iterators reference source." ){
    CHECK( *rng.begin() == source[0] );
    CHECK( *++rng.begin() == source[1] );
    CHECK( *--rng.end() == source[source.size() - 1] );
  }

  SECTION( "Ranges can participate in range-based for loops" ){
    int idx = 0;

    for( auto it:rng ){
      CHECK( it == source[idx++] );
    }
  }

  SECTION( "Range iterators can be equality compared" ){
    gsw::range<decltype( source )> test( source );

    CHECK( rng.begin() == test.begin() );
    CHECK( rng.end() == test.end() );
  }

  SECTION( "Range iterators can be equality compared with standard iterators" ){
    CHECK( rng.begin() == source.begin() );
    CHECK( rng.end() == source.end() );
  }
}

TEST_CASE( "Ranges can filter values from a container", "[range]" ){
  std::vector<int> source( 10 );
  std::vector<int> result( source.size() / 2 );
  gsw::range<decltype( source )> rng( source,
    []( decltype( source )::value_type x )->bool{
      return x % 2 == 0;
    }
  );

  std::generate( source.begin(), source.end(),
    []()->int{
      static int i = 0;
      return i++;
    }
  );
  std::generate( result.begin(), result.end(),
    []()->int{
      static int i = -2;

      i += 2;
      return i;
    }
  );

  int count = 0;
  for( auto it:rng ){
    CHECK( it == result[count++] );
  }

  CHECK( count == result.size() );
}

TEST_CASE( "Ranges can modify the values from a container before returning them", "[range]" ){
  int mod = 1;
  std::vector<int> source( 10 );
  std::vector<int> result( source.size() );
  gsw::range<decltype( source )> rng( source,
    []( decltype( source )::value_type ){
      return true;
    },
    [=]( decltype( source )::value_type x ){
      return x + mod;
    }
  );

  std::generate( source.begin(), source.end(),
    []()->int{
      static int i = 0;
      return i++;
    }
  );
  std::generate( result.begin(), result.end(),
    [=]()->int{
      static int i = mod;
      return i++;
    }
  );

  auto it = rng.begin();
  auto jt = result.begin();
  for( ;it != rng.end(); ++it, ++jt ){
    CHECK( *it == *jt );
  }
}
