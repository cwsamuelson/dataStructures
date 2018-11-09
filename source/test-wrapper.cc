#include<vector>

#include<catch.hpp>

#include<reference_wrapper.hh>

TEST_CASE( "Reference wrappers can be used similar to regular references", "[reference_wrapper]" ){
  int i = 1;
  int j = 2;

  gsw::reference_wrapper<int> ref( i );
  gsw::reference_wrapper<int> refs[2]{ i, j };

  i = 3;
  CHECK( ref == 3 );
  CHECK( refs[0] == 3 );
  CHECK( refs[1] == 2 );
  CHECK( ref.get() == 3 );

  ref.get() = 5;
  CHECK( ref == 5 );
  CHECK( refs[0] == 5 );
  CHECK( refs[1] == 2 );
  CHECK( ref.get() == 5 );
}

TEST_CASE( "Reference wrappers can be stored in containers", "[reference_wrapper]" ){
  std::vector<gsw::reference_wrapper<int> > vec;
  int i = 0;

  vec.emplace_back( i );
  i = 5;
  CHECK( vec[0] == 5 );
}
