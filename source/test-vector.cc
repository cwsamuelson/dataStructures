#include<catch/catch.hpp>

#include<vector.hh>

class wrapper{
private:
  bool* ref;

public:
  wrapper( const wrapper& w ):
    wrapper( w.ref ){
  }
  wrapper( bool* val ):
    ref( val ){
    *ref = false;
  }
  ~wrapper(){
    ( *ref ) = true;
  }

  wrapper& operator=( const wrapper& w ){
    ref = w.ref;
    return *this;
  }
  bool operator==( const wrapper& other ){
    return ref == other.ref;
  }
};

TEST_CASE( "Vectors will run constructors/destructors when appropriate", "[vector]" ){
  bool test;
  vector<wrapper> v;

  SECTION( "Constructor is run on emplace_back call" ){
    v.emplace_back( &test );

    REQUIRE( !test );
    REQUIRE( v.back() == wrapper( &test ) );
    REQUIRE( v.size() == 1 );
    REQUIRE( v.capacity() >= 1 );
  }

  SECTION( "Destructor is run on pop_back" ){
    v.emplace_back( &test );

    REQUIRE( v.size() == 1 );
    REQUIRE( v.capacity() >= 1 );

    v.pop_back();

    REQUIRE( v.size() == 0 );

    REQUIRE( test );
  }
}

TEST_CASE( "Vectors can be resized", "[vector]" ){
  vector<int> v( 5 );

  SECTION( "Vector capacity can be initialized" ){
    REQUIRE( v.capacity() >= 5 );
    REQUIRE( v.empty() );
    REQUIRE( v.size() == 0 );
  }

  for( int i = 0; i < 5; ++i ){
    REQUIRE( v.size() == i );

    v.push_back( i );

    REQUIRE( v.back() == i );
  }

  SECTION( "Vector size increases with additions" ){
    REQUIRE( v.size() == 5 );
    v.push_back( 10 );
    REQUIRE( v.size() == 6 );
  }

  SECTION( "Resizing bigger changes size and capacity" ){
    v.resize( 10 );

    REQUIRE( v.size() == 10 );
    REQUIRE( v.capacity() >= 10 );
  }

  SECTION( "Resizing smaller changes size but not capacity" ){
    v.resize( 0 );

    REQUIRE( v.size() == 0 );
    REQUIRE( v.capacity() >= 5 );
  }

  SECTION( "Reserving bigger changes capacity but not size" ){
    v.reserve( 10 );

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 10 );
  }

  SECTION( "Reserving smaller does not change size or capacity" ){
    v.reserve( 0 );

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );
  }

  SECTION( "Capacity increases immediately as size exceeds it" ){
    while( v.size() < v.capacity() ){
      v.push_back( 3 );
    }

    REQUIRE( v.size() == v.capacity() );

    v.push_back( 3 );

    REQUIRE( v.capacity() > v.size() );
  }
}

TEST_CASE( "Vectors can be iterated across using standard mechanisms", "[vector]" ){
  vector<int> vec;

  vec.push_back( 1 );
  vec.push_back( 2 );
  vec.push_back( 3 );
  vec.push_back( 4 );

  SECTION( "Vectors can participate in range-based for loops" ){
    int i = 0;

    for( auto it : vec ){
      REQUIRE( it == vec[i] );
      ++i;
    }
    REQUIRE( i == vec.size() );
  }

  SECTION( "Vectors can be iterated like arrays" ){
    for( unsigned int i = 0; i < vec.size(); ++i ){
      REQUIRE( vec[i] == i + 1 );
    }
  }

  SECTION( "Vectors can be iterated by iterators(begin, end)" ){
    int i = 1;

    for( auto it = vec.begin(); it != vec.end(); ++it ){
      REQUIRE( *it == i++ );
    }
  }
}


