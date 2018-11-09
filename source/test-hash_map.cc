#include<string>

#include<catch.hpp>

#include<hash_map.hh>

using namespace gsw;
using namespace std;

TEST_CASE( "hash_Maps are associative containers", "[hash_map]" ){
  const int nIters = 10;
  gsw::hash_map<int, int> mp;

  SECTION( "hash_Maps initialize empty" ){
    CHECK( mp.empty() );
  }

  for( int i = 0; i < nIters; ++i ){
    mp[i] = i + 1;
  }

  CHECK( mp.size() == 10 );

  SECTION( "Basic value hash_mapping" ){
    for( int i = 0; i < nIters; ++i ){
      CHECK( mp[i] == i + 1 );
    }
  }

  SECTION( "More detailed value hash_mapping, and value changing" ){
    gsw::hash_map<string, string> m;

    m["test"] = "foo";

    CHECK( m.size() == 1 );
    CHECK( m["test"] == "foo" );

    m["test"] = "bar";

    CHECK( m.size() == 1 );
    CHECK( m["test"] == "bar" );

    m["test2"] = "foo";

    CHECK( m.size() == 2 );
    CHECK( m["test2"] == "foo" );
    CHECK( m["test"] == "bar" );

    auto it = m.begin();
    CHECK( std::get<0>( *it ) == "test" );
    CHECK( std::get<1>( *it ) == "bar" );
    ++it;
    CHECK( std::get<0>( *it ) == "test2" );
    CHECK( std::get<1>( *it ) == "foo" );
  }
}
