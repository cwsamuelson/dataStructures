#include<utility>

#include<catch.hpp>

#include<shared_ptr.hh>

using namespace gsw;

class deathcry{
private:
  bool* val;

public:
  deathcry( bool* b ):
    val( b ){
  }
  ~deathcry(){
    *val = false;
  }
};

TEST_CASE( "Shared_ptrs have a similar interface to regular pointers", "[shared_ptr]" ){
  int* iPtr0 = new int( 3 );
  shared_ptr<int> sPtr0;

  sPtr0 = iPtr0;

  SECTION( "Initial equality checks." ){
    CHECK( sPtr0 == iPtr0 );
    CHECK( *sPtr0 == *iPtr0 );

    *iPtr0 = 5;
    CHECK( *sPtr0 == 5 );
    *sPtr0 = 4;
    CHECK( *iPtr0 == 4 );
  }

  SECTION( "Dereferenced shared_ptrs can be assigned" ){
    *sPtr0 = 4;

    CHECK( *sPtr0 == 4 );
    CHECK( *iPtr0 == 4 );
  }

  SECTION( "There can be multiple valid instances of a shared_ptr" ){
    shared_ptr<int> sPtr1 = sPtr0;
    shared_ptr<int> sPtr2( sPtr0 );

    CHECK( sPtr0 == sPtr1 );
    CHECK( *sPtr0 == *sPtr1 );
    CHECK( sPtr0 == sPtr2 );
    CHECK( *sPtr0 == *sPtr2 );
  }

  SECTION( "Copies of a shared pointer are not invalidated when others go out of scope" ){
    {
      shared_ptr<int> sPtr1 = sPtr0;
    }

    CHECK( *sPtr0 == 3 );
  }

  SECTION( "Destructors run appropriately" ){
    bool b = true;
    auto sp = make_shared<deathcry>( &b );
    bool b1 = true;
    {
      auto dc = make_shared<deathcry>( &b1 );
      dc = sp;
    }
    CHECK( b1 == false );
  }
}

TEST_CASE( "Shared_ptrs obey move semantics", "[shared_ptr]" ){
  bool b = true;
  auto sp = make_shared<deathcry>( &b );

  SECTION( "Move semantics will not prevent cleanup" ){
    bool b1 = true;
    {
      auto dc = make_shared<deathcry>( &b1 );
      dc = std::move( sp );
    }
    CHECK( b1 == false );
  }
}
