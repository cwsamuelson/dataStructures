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
  bool test;

  REQUIRE( ( G += 5 ) == 10 );

  test = gsw::is_same<gsw::remove_cv<const int>::type, int>::value;
  REQUIRE( test );
  test = gsw::is_same<gsw::remove_cv<int>::type,       int>::value;
  REQUIRE( test );

  test = gsw::is_same<gsw::remove_reference<int&&>::type, int>::value;
  REQUIRE( test );
  test = gsw::is_same<gsw::remove_reference<int&>::type,  int>::value;
  REQUIRE( test );
  test = gsw::is_same<gsw::remove_reference<int>::type,   int>::value;
  REQUIRE( test );

  test = gsw::is_same<gsw::remove_extent<int[12]>::type, int*>::value;
  REQUIRE( test );
  test = gsw::is_same<gsw::remove_extent<int>::type,     int>::value;
  REQUIRE( test );

  test = gsw::is_same<gsw::remove_pointer<int*>::type, int>::value;
  REQUIRE( test );
  test = gsw::is_same<gsw::remove_pointer<int>::type,  int>::value;
  REQUIRE( test );

  test = gsw::is_same<gsw::remove_pointer<int*[12]>::type, int*[12]>::value;
  REQUIRE( test );
  test = gsw::is_same<gsw::remove_extent<int*[12]>::type, int**>::value;
  REQUIRE( test );
  test = gsw::is_same<gsw::remove_pointer<
                        gsw::remove_pointer<
                          gsw::remove_extent<
                            int*[12]>::type>
                          ::type>
                        ::type,
                      int>::value;
  REQUIRE( test );
}

