#include<catch.hpp>

#include<list.hh>

using namespace gsw;

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

TEST_CASE( "Runs constructors/destructors when appropriate", "[list]" ){
  bool test = true;
  gsw::list<wrapper> l;

  SECTION( "Constructor is run on emplace calls" ){
    l.emplace_back( &test );

    REQUIRE( !test );
    REQUIRE( l.back() == wrapper( &test ) );
    REQUIRE( l.size() == 1 );

    l.emplace_front( &test );

    REQUIRE( !test );
    REQUIRE( l.front() == wrapper( &test ) );
    REQUIRE( l.size() == 2 );
  }

  SECTION( "Destructor is run on pop calls )" ){
    test = false;
    l.emplace_back( &test );
    l.emplace_front( &test );

    l.pop_back();
    REQUIRE( test );

    test = false;
    l.pop_front();
    REQUIRE( test );
  }
}

