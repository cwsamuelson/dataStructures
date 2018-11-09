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
  bool operator==( const wrapper& other ) const{
    return ref == other.ref;
  }
};

TEST_CASE( "Runs constructors/destructors when appropriate", "[list]" ){
  bool test = true;
  gsw::list<wrapper> l;

  SECTION( "Constructor is run on emplace calls" ){
    l.emplace_back( &test );

    CHECK( !test );
    CHECK( l.back() == wrapper( &test ) );
    CHECK( l.size() == 1 );

    l.emplace_front( &test );

    CHECK( !test );
    CHECK( l.front() == wrapper( &test ) );
    CHECK( l.size() == 2 );
  }

  SECTION( "Destructor is run on pop calls )" ){
    test = false;
    l.emplace_back( &test );
    l.emplace_front( &test );

    l.pop_back();
    CHECK( test );

    test = false;
    l.pop_front();
    CHECK( test );
  }
}

TEST_CASE( "Lists can be iterated across using standard mechanisms", "[list]" ){
  gsw::list<int> lst;

  lst.push_back( 1 );
  lst.push_back( 2 );
  lst.push_back( 3 );
  lst.push_back( 4 );

  SECTION( "Lists can participate in range-based for loops" ){
    int i = 0;

    for( auto it : lst ){
      CHECK( it == lst[i] );
      ++i;
    }
    CHECK( i == lst.size() );
  }

  SECTION( "Lists can be iterated like arrays" ){
    for( unsigned int i = 0; i < lst.size(); ++i ){
      CHECK( lst[i] == i + 1 );
    }
  }

  SECTION( "Lists can be iterated by iterators(begin, end)" ){
    int i = 1;

    for( auto it = lst.begin(); it != lst.end(); ++it ){
      CHECK( *it == i++ );
    }
  }
}
