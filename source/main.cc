#include<iostream>
#include<functional>
#include<sstream>
#include<vector>
#include<random>
#include<memory>

#define CATCH_CONFIG_MAIN
#include<catch/catch.hpp>

#include<function.hh>
#include<array.hh>
#include<tuple.hh>
#include<memory_pool.hh>
#include<shared_ptr.hh>
#include<unique_ptr.hh>
#include<string.hh>
#include<vector.hh>
#include<unit.hh>
#include<range.hh>
#include<map.hh>
#include<algorithm.hh>
#include<date_time.hh>
#include<equation.hh>
#include<menu.hh>
#include<accessor.hh>
#include<reference_wrapper.hh>
#include<is_same.hh>

class foo{
private:
  int& X;
  bool& flag;
  
public:
  foo( int& x, bool& f ):
    X( x ),
    flag( f ){
    flag = false;
  }
  ~foo(){
    flag = true;
  }
  
  int& value(){
    return X;
  }
};

TEST_CASE( "Unique_ptrs have a mostly similar interface to regular pointers", "[unique_ptr]" ){
  int* iPtr0 = new int( 3 );
  unique_ptr<int> uPtr0;

  uPtr0 = iPtr0;

  REQUIRE( uPtr0 == iPtr0 );
  REQUIRE( *uPtr0 == *iPtr0 );

  unique_ptr<int> uPtr1( uPtr0 );
  REQUIRE( uPtr0 == nullptr );
  REQUIRE( uPtr1 == iPtr0 );
}

TEST_CASE( "Shared_ptrs have a similar interface to regular pointers", "[shared_ptr]" ){
  int* iPtr0 = new int( 3 );
  shared_ptr<int> sPtr0;

  sPtr0 = iPtr0;

  SECTION( "Initial equality checks." ){
    REQUIRE( sPtr0 == iPtr0 );
    REQUIRE( *sPtr0 == *iPtr0 );

    *iPtr0 = 5;
    REQUIRE( *sPtr0 == 5 );
    *sPtr0 = 4;
    REQUIRE( *iPtr0 == 4 );
  }

  SECTION( "Dereferenced shared_ptrs can be assigned" ){
    *sPtr0 = 4;

    REQUIRE( *sPtr0 == 4 );
    REQUIRE( *iPtr0 == 4 );
  }

  SECTION( "There can be multiple valid instances of a shared_ptr" ){
    shared_ptr<int> sPtr1 = sPtr0;
    shared_ptr<int> sPtr2( sPtr0 );

    REQUIRE( sPtr0 == sPtr1 );
    REQUIRE( *sPtr0 == *sPtr1 );
    REQUIRE( sPtr0 == sPtr2 );
    REQUIRE( *sPtr0 == *sPtr2 );
  }

  SECTION( "Copies of a shared pointer are not invalidated when others go out of scope" ){
    {
      shared_ptr<int> sPtr1 = sPtr0;
    }

    REQUIRE( *sPtr0 == 3 );
  }
}

TEST_CASE( "Strings can be accessed like an array", "[string]" ){
  const char* cstr = "length 8";
  string str( cstr );

  REQUIRE( str.size() == 8 );

  for( unsigned int i = 0; i < str.size(); ++i ){
    REQUIRE( cstr[i] == str[i] );
  }

  int i = 0;
  for( auto it:str ){
    REQUIRE( it == cstr[i++] );
  }
}

TEST_CASE( "Strings can construct and assign with strings and string literals", "[string]" ){
  const char* cstr = "cstring";
  string str( "test string" );

  SECTION( "Strings can be compared with c-strings" ){
    REQUIRE( str == "test string" );
  }

  SECTION( "Strings can be assigned c-strings" ){
    str = cstr;

    REQUIRE( str == cstr );
  }

  SECTION( "Strings can be constructed with c-strings" ){
    string str2( cstr );

    REQUIRE( str2 == cstr );
  }

  SECTION( "Strings can be constructed with other strings" ){
    string str2( str );

    REQUIRE( str == str2 );
  }
}

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

TEST_CASE( "Units participate in arithmetic", "[unit]" ){
  typedef unit<1, 0, 0, 0, 0, 0> test_t;

  SECTION( "Units of same type can be added and subtracted" ){
    double valX = 1;
    double valY = 2;

    test_t x = valX;
    test_t y = valY;

    test_t z = x + y;
    test_t w = y - x;

    REQUIRE( x == valX );
    REQUIRE( y == valY );
    REQUIRE( z == valX + valY );
    REQUIRE( w == valY - valX );
  }

  SECTION( "Units multiplication/division result in new unit types" ){
    voltage<> V = 3.0;
    current<> I = 5.0;
    resistance<> R = 4.0;

    V = I * R;

    REQUIRE( V.getValue() == I.getValue() * R.getValue() );
    I = 3.0;

    I = V / R;

    REQUIRE( I == 5.0 );
    REQUIRE( I.getValue() == V.getValue() / R.getValue() );

    test_t X = 2.0;
    test_t Y = 3.0;
    unit<2, 0, 0, 0, 0, 0> Z;

    Z = X * Y;

    REQUIRE( Z.getValue() == 6.0 );
  }

  SECTION( "Units of same type can be value compared" ){
    test_t X = 1.0;
    test_t Y = 1.0;
    test_t Z = 3.0;

    REQUIRE( X == Y );
    REQUIRE( X < Z );
    REQUIRE( Z > Y );
    REQUIRE( X < 3.0 );
  }

  SECTION( "Units can use compound operators" ){
    test_t X = 0.0;

    X += 3.0;
    REQUIRE( X == 3.0 );

    X -= 1.0;
    REQUIRE( X == 2.0 );
  }
}

TEST_CASE( "A range iterator can act as a standard iterator", "[range]" ){
  std::vector<int> source{2, 3, 4, 5, 6 };
  range<decltype( source )> rng( source );

  SECTION( "Initial basic range iterators reference source." ){
    REQUIRE( *rng.begin() == source[0] );
    REQUIRE( *++rng.begin() == source[1] );
    REQUIRE( *--rng.end() == source[source.size() - 1] );
  }

  SECTION( "Ranges can participate in range-based for loops" ){
    int idx = 0;

    for( auto it:rng ){
      REQUIRE( it == source[idx++] );
    }
  }

  SECTION( "Range iterators can be equality compared" ){
    range<decltype( source )> test( source );

    REQUIRE( rng.begin() == test.begin() );
    REQUIRE( rng.end() == test.end() );
  }

  SECTION( "Range iterators can be equality compared with standard iterators" ){
    REQUIRE( rng.begin() == source.begin() );
    REQUIRE( rng.end() == source.end() );
  }
}

TEST_CASE( "Ranges can filter values from a container", "[range]" ){
  std::vector<int> source( 10 );
  std::vector<int> result( source.size() / 2 );
  range<decltype( source )> rng( source,
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
    REQUIRE( it == result[count++] );
  }

  REQUIRE( count == result.size() );
}

TEST_CASE( "Ranges can modify the values from a container before returning them", "[range]" ){
  int mod = 1;
  std::vector<int> source( 10 );
  std::vector<int> result( source.size() );
  range<decltype( source )> rng( source,
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
    REQUIRE( *it == *jt );
  }
}

TEST_CASE( "Unique pointers behave mostly as regular pointers", "[unique_ptr]" ){
  int x = 1;
  int y = 2;
  bool flag1;
  bool flag2;
  unique_ptr<int> ptr1( new int );
  unique_ptr<int> ptr2( new int );
  unique_ptr<foo> ptr3( new foo( x, flag1 ) );
  unique_ptr<foo> ptr4( new foo( y, flag2 ) );
  
  *ptr1 = 1;
  *ptr2 = 2;

  ptr1 = ptr2;
  ptr4 = ptr3;
  
  /* flag2 should be toggled now, and not flag1 */
  REQUIRE( !flag1 );
  REQUIRE( flag2 );
  REQUIRE( ptr4->value() == x );
  ptr4 = ptr4;
  REQUIRE( ptr4->value() == x );
  
  x = 2;
  REQUIRE( ( *ptr1 ) == 2 );
  REQUIRE( ptr4->value() == x );
}

TEST_CASE( "Tuple elements can be set and checked", "[tuple]" ){
  tuple<int> t1;
  tuple<int, int> t2;
  tuple<char, int, char> t3;
  tuple<int, int> t4( 1, 2 );
  
  get<0>( t1 ) = 1;
  
  get<0>( t2 ) = 2;
  get<1>( t2 ) = 3;
  
  get<0>( t3 ) = 'a';
  get<1>( t3 ) = 4;
  get<2>( t3 ) = 'b';
  
  REQUIRE( get<0>( t1 ) == 1 );
  REQUIRE( get<0>( t2 ) == 2 );
  REQUIRE( get<1>( t2 ) == 3 );
  REQUIRE( get<0>( t3 ) == 'a' );
  REQUIRE( get<1>( t3 ) == 4 );
  REQUIRE( get<2>( t3 ) == 'b' );
  REQUIRE( get<0>( t4 ) == 1 );
  REQUIRE( get<1>( t4 ) == 2 );
}

TEST_CASE( "Memory pool will allocate resources from its collection.", "[mempool]" ){
  memoryPool<int> test( 10 );
  REQUIRE( test.in_use_count() == 0 );
  REQUIRE( test.available_space() == 10 );

  int* foo = test.allocate( 2 );
  int* bar = test.allocate( 1 );
  int* baz = test.allocate( 2 );
  REQUIRE( test.in_use_count() == 5 );
  REQUIRE( test.available_space() == 5 );

  test.deallocate( bar );
  REQUIRE( test.in_use_count() == 4 );
  REQUIRE( test.available_space() == 6 );

  bar = test.allocate( 2 );
  REQUIRE( test.in_use_count() == 6 );
  REQUIRE( test.available_space() == 4 );

  int* quux = test.allocate( 1 );
  REQUIRE( test.in_use_count() == 7 );
  REQUIRE( test.available_space() == 3 );

  REQUIRE( ( baz + 2 ) == bar );
  REQUIRE( ( foo + 2 ) == quux );

  //test invalid allocation
  REQUIRE( test.allocate( 20 ) == nullptr );
  REQUIRE( test.in_use_count() == 7 );
  REQUIRE( test.available_space() == 3 );

  //test invalid deallocation
  test.deallocate( baz + 1 );
  REQUIRE( test.in_use_count() == 7 );
  REQUIRE( test.available_space() == 3 );
}

TEST_CASE( "Maps are associative containers", "[map]" ){
  const int nIters = 10;
  map<int, int> mp;

  SECTION( "Maps initialize empty" ){
    REQUIRE( mp.empty() );
  }

  for( int i = 0; i < nIters; ++i ){
    mp[i] = i + 1;
  }

  SECTION( "" ){
    for( int i = 0; i < nIters; ++i ){
      REQUIRE( mp[i] == i + 1 );
    }
  }
}

TEST_CASE( "Sort algorithm", "[algorithm]" ){
  int count = 1000;
  vector<int> vec;
  std::random_device rd;
  std::mt19937 rate( rd() );
  std::normal_distribution<> gene( 0, 10000000 );

  for( int i = 0; i < count; ++i ){
    vec.push_back( gene( rate ) );
  }

  sort( vec.begin(), vec.end() );

  REQUIRE( vec.size() == count );

  for( unsigned int i = 1; i < vec.size(); ++i ){
    REQUIRE( vec[i] >= vec[i - 1] );
  }
}

TEST_CASE( "Regular operations can be performed on time units", "[time]" ){

  SECTION( "Time units convert nicely, and report expected amounts." ){
    minute m( 1 );
    second s( m );

    REQUIRE( s == 60 );
    REQUIRE( m == 1 );
  }

  SECTION( "Units interact with ostreams." ){
    minute m( 1 );
    std::stringstream ss;
    std::string str;

    ss << m;
    ss >> str;
    REQUIRE( str == "1" );
    ss >> str;
    REQUIRE( str == "minutes" );
  }

  SECTION( "A date is printed in a human readable format to an ostream." ){
    date dayt( 11, 8, 2016 );
    std::stringstream ss;
    std::string str;

    ss << dayt;
    ss >> str;
    REQUIRE( str == "11" );
    ss >> str;
    REQUIRE( str == "August" );
    ss >> str;
    REQUIRE( str == "2016" );
  }

  SECTION( "Mathematical operations can be performed on time units." ){
    minute m( 59 );

    m += 1;

    hour h( m );

    REQUIRE( h == 1 );

    m -= 5;

    REQUIRE( m == 55 );

    REQUIRE( ++h == 2 );
    REQUIRE( m++ == 55 );
    REQUIRE( m == 56 );
    REQUIRE( --h == 1 );
    REQUIRE( m-- == 56 );
    REQUIRE( m == 55 );
  }

  SECTION( "Date time interacts with streams." ){
    date_time dt( date( 11, 8, 2016 ), 15, 41, 14 );
    std::stringstream ss;
    std::string str;

    ss << dt;
    ss >> str;
    REQUIRE( str == "11" );
    ss >> str;
    REQUIRE( str == "August" );
    ss >> str;
    REQUIRE( str == "2016" );

    ss >> str;
    REQUIRE( str == "15:41:14" );
  }

  SECTION( "Units convert when using streams." ){
    std::string str( "5 seconds" );
    time_unit<5> tu;
    std::stringstream ss( str );

    ss >> tu;
    REQUIRE( tu == 1 );

    std::stringstream ss2;

    ss2 << second( 10 );
    ss2 >> tu;
    REQUIRE( tu == 2 );
  }
}

int testfn(){
  return 5;
}

TEST_CASE( "Function objects are used as normal functions.", "[function]" ){
  function<int( int )> fn;
  function<int( int, int )> nf;
  function<int()> tst;
  
  fn = []( int x ){ return 1 + x; };
  nf = []( int x, int y ){ return x + y; };
  tst = testfn;
  
  SECTION( "Calling functions produce expected results." ){
    REQUIRE( fn( 3 ) == 4 );
    REQUIRE( nf( 1, 2 ) == 3 );
    REQUIRE( tst() == 5 );
  }
}

TEST_CASE( "Arrays can be used as builtin arrays.", "[array]" ){
  array<char[3]> arr;
  
  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';
  
  SECTION( "Array basics." ){
    REQUIRE( arr[0] == 'a' );
    REQUIRE( arr[1] == 'b' );
    REQUIRE( arr[2] == 'c' );
  }

  SECTION( "Array range-based for." ){
    unsigned int i = 0;
    for( auto it : arr ){
      REQUIRE( it == arr[i++] );
    }
  }
}

//TODO: performance testing on array splicing
TEST_CASE( "Arrays can be 'spliced'.", "[array]" ){
  array<char[10]> arr;

  for( unsigned int i = 0; i < arr.size(); ++i ){
    arr[i] = char( i + 'a' );
  }

  SECTION( "Basic splice indeces." ){
    arr[arr > 8] = 'z';
    arr[arr < 2] = 'y';

    for( unsigned int i = 0; i < 2; ++i ){
      REQUIRE( arr[i] == 'y' );
    }
    for( unsigned int i = 9; i < 10; ++i ){
      REQUIRE( arr[i] == 'z' );
    }

    arr[arr >= 6] = 'x';
    arr[arr <= 4] = 'w';

    for( unsigned int i = 0; i < 4; ++i ){
      REQUIRE( arr[i] == 'w' );
    }
    for( unsigned int i = 6; i < 10; ++i ){
      REQUIRE( arr[i] == 'x' );
    }
  }

  SECTION( "Spliced by another container" ){
    array<unsigned int[3]> ids;

    ids[0] = 1;
    ids[1] = 3;
    ids[2] = 5;

    arr[ids] = 'z';

    for( auto it : ids ){
      REQUIRE( arr[it] == 'z' );
    }

    for( unsigned int i = 6; i < 10; ++i ){
      REQUIRE( arr[i] == ( 'a' + i ) );
    }
  }
}

TEST_CASE( "Equations can be used in basic arithmetic", "[equ]" ){
  std::vector<double> vec { 1, 1, 1 };
  std::vector<double> vec2 { 2, 2, 2 };
  equation eq( vec.begin(), vec.end() );
  equation eq2( vec2.begin(), vec2.end() );

  SECTION( "Addition" ){
    REQUIRE( ( eq + eq2 )( 2 ) == 21 );
  }

  SECTION( "Subtraction" ){
    REQUIRE( ( eq2 - eq )( 2 ) == 7 );
    REQUIRE( ( eq - eq2 )( 2 ) == -7 );
  }

  SECTION( "Multiplication" ){
    REQUIRE( ( eq * 2 )( 2 ) == 2 * eq( 2 ) );

    std::vector<double> vec3 { 1, 1 };
    equation eq3( vec3.begin(), vec3.end() );
    vec3[0] = 2;
    equation eq4( vec3.begin(), vec3.end() );
    REQUIRE( ( eq3 * eq4 )( 2 ) == 12 );

    std::vector<double> vec4 { 1, 1 };
    equation eq5( vec4.begin(), vec4.end() );
    vec4.push_back( 1 );
    equation eq6( vec4.begin(), vec4.end() );
    REQUIRE( ( eq5 * eq6 )( 2 ) == 21 );
  }

//TODO:test dividing equation by another equation
  SECTION( "Division" ){
    REQUIRE( ( eq2 / 2 )( 2 ) == eq2( 2 ) / 2 );
  }
}

TEST_CASE( "Equation", "[equ]" ){
  std::vector<double> vec { 1, 1, 1 };
  std::vector<double> vec2 { 2, 2, 2 };
  equation eq( vec.begin(), vec.end() );
  equation eq2( vec2.begin(), vec2.end() );

  SECTION( "Equations can be evaluated" ){
    REQUIRE( eq( 2 ) == 7 );
    REQUIRE( eq2( 2 ) == 14 );
  }

  SECTION( "Equations with different number of terms" ){
    vec.push_back( 1 );
    equation eq3( vec.begin(), vec.end() );

    REQUIRE( eq3( 2 ) == 15 );
    REQUIRE( ( eq3 + eq )( 2 ) == 22 );
    REQUIRE( ( eq3 - eq )( 2 ) == 8 );
  }

  SECTION( "Derivative" ){
    equation eq3 = derive( eq2 );

    REQUIRE( eq3( 2 ) == 10 );
  }

  SECTION( "Integral" ){
    REQUIRE( integrate( eq2, 3, 1 ) == ( 29.0 + ( 1.0 / 3.0 ) ) );
  }
}

TEST_CASE( "Menu allows option selection and provides callbacks on selection.", "[menu]" ){
  std::stringstream ss;
  auto pm = std::make_shared<menu<int>>();
  auto pm0 = std::make_shared<menu<int>>();
  std::shared_ptr<menu<int> > current( pm );

  pm->addOption( 0, "electric", pm0, [&](){ ss << "beep" << '\n'; } );
  pm->addOption( 1, "boogaloo", pm0, [&](){ ss << "boop" << '\n'; } );
  pm0->addOption( 0, "foo", pm, [&](){ ss << "buup" << '\n'; } );
  pm0->addOption( 1, "baz", pm, [&](){ ss << "biip" << '\n'; } );
  pm0->addOption( 1, "bar", pm, [&](){ ss << "byyp" << '\n'; } );

  //ctor compile check
  menu<int> one;
  menu<int> two( one );
  menu<int> three( menu<int>() );
  one.print( ss );
  one.print( ss );
  one.print( ss );

  SECTION( "Prints menus when requested." ){
    for( unsigned int i = 0; i < 2; ++i ){
      current->print( ss );
      current = current->select( i );
    }
    int i;
    std::string str;

    ss >> i;
    ss >> str;

    REQUIRE( i == 0 );
    REQUIRE( str == "electric" );

    ss >> i;
    ss >> str;

    REQUIRE( i == 1 );
    REQUIRE( str == "boogaloo" );

    ss >> str;

    REQUIRE( str == "beep" );

    ss >> i;
    ss >> str;

    REQUIRE( i == 0 );
    REQUIRE( str == "foo" );

    ss >> i;
    ss >> str;

    REQUIRE( i == 1 );
    REQUIRE( str == "bar" );

    ss >> str;

    REQUIRE( str == "byyp" );
  }

  SECTION( "Forwards out of range exception when accessing an invalid menu option." ){
    bool exceptionSanity = false;

    try{
      pm->select( 3 );
    }catch( std::out_of_range& ){
      exceptionSanity = true;
    }

    REQUIRE( exceptionSanity );
  }
}

class bar{
public:
  typedef int value_type;

private:
  value_type i;
  int j;

public:
  bar():
    i(0),
    j(0){
  }

  accessor<value_type> getInternal(){
    return accessor<value_type>( i,
      [&](value_type t ){
        ( void )t;
        ++j;
        return true;
      });
  }

  int getj(){
    return j;
  }
};

TEST_CASE( "", "[accessor]" ){
  bar b;

  REQUIRE( b.getInternal() == 0 );
  b.getInternal() = 12;
  REQUIRE( b.getInternal() == 12 );
  REQUIRE( b.getj() == 1 );
}

TEST_CASE( "", "[reference_wrapper]"){
  int i = 1;
  int j = 2;

  reference_wrapper<int> ref( i );
  reference_wrapper<int> refs[2]{ i, j };

  i = 3;
  REQUIRE( ref == 3 );
  REQUIRE( refs[0] == 3 );
}

TEST_CASE( "", "[is_same]"){
  typedef is_same<int, signed int> SIGNED;
  typedef is_same<int, volatile int> VOLATILE;
  typedef is_same<int, const int> CONST_SAME;
  typedef is_same<int, float> FLOAT;
  typedef is_same<int, bar> BAR;
  typedef is_same<bar, bar> BAR_BAR;

  REQUIRE( SIGNED::value );
  REQUIRE( BAR_BAR::value );
  REQUIRE( !VOLATILE::value );
  REQUIRE( !CONST_SAME::value );
  REQUIRE( !FLOAT::value );
  REQUIRE( !BAR::value );
}

