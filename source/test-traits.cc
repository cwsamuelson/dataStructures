#include<catch.hpp>

#include<type_traits.hh>
#include<is_same.hh>

template<typename T>
typename gsw::enable_if<!gsw::is_void<T>::value, int>::type
fortyTwo(){
  return 0;
}

template<typename T>
typename gsw::enable_if<gsw::is_void<T>::value, int>::type
fortyTwo(){
  return 42;
}

TEST_CASE( "is_void", "[traits]" ){
  REQUIRE( fortyTwo<void>() == 42 );
  REQUIRE( fortyTwo<int>()  == 0 );
}

TEST_CASE( "remove_cv", "[traits]" ){
  gsw::remove_cv<const int>::type G = 5;

  REQUIRE( ( G += 5 ) == 10 );
  REQUIRE( gsw::is_same<gsw::remove_cv<const int>::type, int>::value );
}

