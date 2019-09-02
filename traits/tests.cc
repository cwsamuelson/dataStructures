#include<type_traits>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

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

class bar{
public:
  using value_type = int;

private:
  value_type i;
  int j;

public:
  bar():
    i(0),
    j(0){
  }

  int getj(){
    return j;
  }
};

TEST_CASE( "is_void", "[traits]" ){
  CHECK( fortyTwo<void>() == 42 );
  CHECK( fortyTwo<int>()  == 0 );
}

TEST_CASE( "remove_cv", "[traits]" ){
  gsw::remove_cv<const int>::type G = 5;

  CHECK( ( G += 5 ) == 10 );

  CHECK( gsw::is_same<gsw::remove_cv<const int>::type, int>::value );
  CHECK( gsw::is_same<gsw::remove_cv<int>::type,       int>::value );

  CHECK( gsw::is_same<gsw::remove_reference<int&&>::type, int>::value );
  CHECK( gsw::is_same<gsw::remove_reference<int&>::type,  int>::value );
  CHECK( gsw::is_same<gsw::remove_reference<int>::type,   int>::value );

  CHECK( gsw::is_same<gsw::remove_extent<int[12]>::type, int*>::value );
  CHECK( gsw::is_same<gsw::remove_extent<int>::type,     int>::value );

  CHECK( gsw::is_same<gsw::remove_pointer<int*>::type, int>::value );
  CHECK( gsw::is_same<gsw::remove_pointer<int>::type,  int>::value );

  CHECK( gsw::is_same<gsw::remove_pointer<int*[12]>::type, int*[12]>::value );
  CHECK( gsw::is_same<gsw::remove_extent<int*[12]>::type, int**>::value );
  CHECK( gsw::is_same<gsw::remove_pointer<
                          gsw::remove_pointer<
                            gsw::remove_extent<
                              int*[12]>::type>
                            ::type>
                          ::type,
                        int>::value );
}

class base{
};
class d1 : public base{
};
class d2 : public base{
};
class d3 : public base{
};

TEST_CASE( "common_type", "[traits]" ){
  SECTION( "Built-in types" ){
    CHECK( gsw::is_same<gsw::common_type<double, int     >::type, double>::value );
    CHECK( gsw::is_same<gsw::common_type<double, int, int>::type, double>::value );
    CHECK( gsw::is_same<gsw::common_type<long,      short>::type, long>::value );
  }

  SECTION( "Class and it's base" ){
    CHECK( gsw::is_same<gsw::common_type<base, base>::type, base>::value );
    CHECK( gsw::is_same<gsw::common_type<base,   d1>::type, base>::value );
    CHECK( gsw::is_same<gsw::common_type<d1,     d1>::type,   d1>::value );
    CHECK( gsw::is_same<gsw::common_type<d1,   base>::type, base>::value );
  }

  SECTION( "More than 2 types" ){
    CHECK( gsw::is_same<gsw::common_type<base, d2, d1    >::type, base>::value );
    CHECK( gsw::is_same<gsw::common_type<base, d3, d2, d1>::type, base>::value );
    //CHECK( gsw::is_same<gsw::common_type<d1, d2, base    >::type, base>::value );
    //CHECK( gsw::is_same<gsw::common_type<d1, d3, d2, base>::type, base>::value );
    //CHECK( gsw::is_same<gsw::common_type<d1, d2          >::type, base>::value );
  }
}

TEST_CASE( "Same-ness checks", "[is_same]"){
  REQUIRE( gsw::is_same<int, signed int>::value );
  REQUIRE( gsw::is_same<bar, bar>::value );
  REQUIRE( !gsw::is_same<int, volatile int>::value );
  REQUIRE( !gsw::is_same<int, const int>::value );
  REQUIRE( !gsw::is_same<int, float>::value );
  REQUIRE( !gsw::is_same<int, bar>::value );
}

