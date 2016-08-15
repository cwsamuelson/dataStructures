#include<iostream>
#include<functional>
#include<sstream>
#include<vector>
#include<random>

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

bool testTuple(){
  tuple<int> t1;
  tuple<int, int> t2;
  tuple<char, int, char> t3;
  tuple<int, int> t4(1, 2);
  
  get<0>(t1) = 1;
  
  get<0>(t2) = 2;
  get<1>(t2) = 3;
  
  get<0>(t3) = 'a';
  get<1>(t3) = 4;
  get<2>(t3) = 'b';
  
  return get<0>(t1) == 1 && get<0>(t2) == 2 && get<1>(t2) == 3 &&
       get<0>(t3) == 'a' && get<1>(t3) == 4 && get<2>(t3) == 'b' &&
       get<0>(t4) == 1 && get<1>(t4) == 2;
}

bool testPool(){
  bool ret = true;
  memoryPool<int> test(10);
  
  int* foo = test.allocate(2);
  int* bar = test.allocate(1);
  int* baz = test.allocate(2);
  test.deallocate(bar);
  bar = test.allocate(2);
  int* quux = test.allocate(1);

  ret &= ((baz + 2) == bar);
  ret &= ((foo + 2) == quux);
  return ret;
}

class foo{
private:
  int& X;
  bool& flag;
  
public:
  foo(int& x, bool& f):
    X(x),
    flag(f){
    flag = false;
  }
  ~foo(){
    flag = true;
  }
  
  int& value(){
    return X;
  }
};

bool testUnique(){
  bool change = true;
  int x = 1;
  int y = 2;
  bool flag1;
  bool flag2;
  unique_ptr<int> ptr1(new int);
  unique_ptr<int> ptr2(new int);
  unique_ptr<foo> ptr3(new foo(x, flag1));
  unique_ptr<foo> ptr4(new foo(y, flag2));
  
  *ptr1 = 1;
  *ptr2 = 2;

  ptr1 = ptr2;
  ptr4 = ptr3;
  
  /* flag2 should be toggled now, and not flag1 */
  change &= !flag1;
  change &= flag2;
  change &= (ptr4->value() == x);
  ptr4 = ptr4;
  change &= (ptr4->value() == x);
  
  x = 2;
  return (*ptr1) == 2 && ptr4->value() == x && change;;
}

TEST_CASE("Unique_ptrs have a mostly similar interface to regular pointers", "[unique_ptr]"){
  int* iPtr0 = new int(3);
  unique_ptr<int> uPtr0;

  uPtr0 = iPtr0;

  REQUIRE(uPtr0 == iPtr0);
  REQUIRE(*uPtr0 == *iPtr0);
}

TEST_CASE("Shared_ptrs have a similar interface to regular pointers", "[shared_ptr]"){
  int* iPtr0 = new int(3);
  shared_ptr<int> sPtr0;

  sPtr0 = iPtr0;

  SECTION("Initial equality checks."){
    REQUIRE(sPtr0 == iPtr0);
    REQUIRE(*sPtr0 == *iPtr0);
  }

  SECTION("Dereferenced shared_ptrs can be assigned"){
    *sPtr0 = 4;

    REQUIRE(*sPtr0 == 4);
    REQUIRE(*iPtr0 == 4);
  }

  SECTION("There can be multiple valid instances of a shared_ptr"){
    shared_ptr<int> sPtr1 = sPtr0;

    REQUIRE(sPtr0 == sPtr1);
    REQUIRE(*sPtr0 == *sPtr1);
  }

  SECTION("Copies of a shared pointer are not invalidated when others go out of scope"){
    {
      shared_ptr<int> sPtr1 = sPtr0;
    }

    REQUIRE(*sPtr0 == 3);
  }
}

TEST_CASE("Strings can be accessed like an array", "[string]"){
  const char* cstr = "length 8";
  string str(cstr);

  REQUIRE(str.size() == 8);

  for(unsigned int i = 0; i < str.size(); ++i){
    REQUIRE(cstr[i] == str[i]);
  }

  int i = 0;
  for(auto it:str){
    REQUIRE(it == cstr[i++]);
  }
}

TEST_CASE("Strings can construct and assign with strings and string literals", "[string]"){
  const char* cstr = "cstring";
  string str("test string");

  SECTION("Strings can be compared with c-strings"){
    REQUIRE(str == "test string");
  }

  SECTION("Strings can be assigned c-strings"){
    str = cstr;

    REQUIRE(str == cstr);
  }

  SECTION("Strings can be constructed with c-strings"){
    string str2(cstr);

    REQUIRE(str2 == cstr);
  }

  SECTION("Strings can be constructed with other strings"){
    string str2(str);

    REQUIRE(str == str2);
  }
}

class wrapper{
private:
  bool* ref;

public:
  wrapper(const wrapper& w):
    wrapper(w.ref){
  }
  wrapper(bool* val):
    ref(val){
    *ref = false;
  }
  ~wrapper(){
    (*ref) = true;
  }

  wrapper& operator=(const wrapper& w){
    ref = w.ref;
    return *this;
  }
  
};

TEST_CASE("Vectors will run constructors/destructors when appropriate", "[vector]"){
  bool test;
  vector<wrapper> v;

  SECTION("Constructor is run on emplace_back call"){
    v.emplace_back(&test);

    REQUIRE(!test);
  }

  SECTION("Destructor is run on pop_back"){
    v.emplace_back(&test);
    v.pop_back();

    REQUIRE(test);
  }
}

TEST_CASE("Vectors can be resized", "[vector]"){
  vector<int> v(5);

  SECTION("Vector capacity can be initialized"){
    REQUIRE(v.capacity() >= 5);
  }

  for(int i = 0; i < 5; ++i){
    v.push_back(i);
  }

  SECTION("Vector size increases with additions"){
    REQUIRE(v.size() == 5);
    v.push_back(10);
    REQUIRE(v.size() == 6);
  }

  SECTION("Resizing bigger changes size and capacity"){
    v.resize(10);

    REQUIRE(v.size() == 10);
    REQUIRE(v.capacity() >= 10);
  }

  SECTION("Resizing smaller changes size but not capacity"){
    v.resize(0);

    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() >= 5);
  }

  SECTION("Reserving bigger changes capacity but not size"){
    v.reserve(10);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 10);
  }

  SECTION("Reserving smaller does not change size or capacity"){
    v.reserve(0);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);
  }
}

TEST_CASE("Vectors can be iterated across using standard mechanisms", "[vector]"){
  vector<int> vec;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);

  SECTION("Vectors can participate in range-based for loops"){
    int i = 0;

    for(auto it:vec){
      REQUIRE(it == vec[i]);
      ++i;
    }
    REQUIRE(i == vec.size());
  }
}

TEST_CASE("Units participate in arithmetic", "[unit]"){
  typedef unit<1, 0, 0, 0, 0, 0> test_t;

  SECTION("Units of same type can be added and subtracted"){
    int valX = 1;
    int valY = 2;

    test_t x = valX;
    test_t y = valY;

    test_t z = x + y;

    REQUIRE(x == valX);
    REQUIRE(y == valY);
    REQUIRE(z == valX + valY);
  }

  SECTION("Units multiplication/division result in new unit types"){
    voltage V = 3;
    current I = 5;
    resistance R = 4;

    V = I * R;

    REQUIRE(V.getValue() == I.getValue() * R.getValue());

    test_t X = 2;
    test_t Y = 3;
    unit<2, 0, 0, 0, 0, 0> Z;

    Z = X * Y;

    REQUIRE(Z.getValue() == 6);
  }

  SECTION("Units of same type can be value compared"){
    test_t X = 1;
    test_t Y = 1;

    REQUIRE(X == Y);
  }

  SECTION("Units can use compount operators"){
    test_t X = 0;
    X += 3;

    REQUIRE(X == 3);

    X -=1;
    REQUIRE(X == 2);
  }
}

TEST_CASE("A range iterator can act as a standard iterator", "[range]"){
  std::vector<int> source{2, 3, 4, 5, 6 };
  range<decltype(source)> rng(source);

  SECTION("Initial basic range iterators reference source."){
    REQUIRE(*rng.begin() == source[0]);
    REQUIRE(*++rng.begin() == source[1]);
    REQUIRE(*--rng.end() == source[source.size() - 1]);
  }

  SECTION("Ranges can participate in range-based for loops"){
    int idx = 0;

    for(auto it:rng){
      REQUIRE(it == source[idx++]);
    }
  }

  SECTION("Range iterators can be equality compared"){
    range<decltype(source)> test(source);

    REQUIRE(rng.begin() == test.begin());
    REQUIRE(rng.end() == test.end());
  }

  SECTION("Range iterators can be equality compared with standard iterators"){
    REQUIRE(rng.begin() == source.begin());
    REQUIRE(rng.end() == source.end());
  }
}

TEST_CASE("Ranges can filter values from a container", "[range]"){
  std::vector<int> source(10);
  std::vector<int> result(source.size() / 2);
  range<decltype(source)> rng(source,
    [](decltype(source)::value_type x)->bool{
      return x % 2 == 0;
    }
  );

  std::generate(source.begin(), source.end(),
    []()->int{
      static int i = 0;
      return i++;
    }
  );
  std::generate(result.begin(), result.end(),
    []()->int{
      static int i = -2;

      i += 2;
      return i;
    }
  );

  int count = 0;
  for(auto it:rng){
    REQUIRE(it == result[count++]);
  }

  REQUIRE(count == result.size());
}

TEST_CASE("Ranges can modify the values from a container before returning them"){
  int mod = 1;
  std::vector<int> source(10);
  std::vector<int> result(source.size());
  range<decltype(source)> rng(source,
    [](decltype(source)::value_type){
      return true;
    },
    [=](decltype(source)::value_type x){
      return x + mod;
    }
  );

  std::generate(source.begin(), source.end(),
    []()->int{
      static int i = 0;
      return i++;
    }
  );
  std::generate(result.begin(), result.end(),
    [=]()->int{
      static int i = mod;
      return i++;
    }
  );

  auto it = rng.begin();
  auto jt = result.begin();
  for(;it != rng.end(); ++it, ++jt){
    REQUIRE(*it == *jt);
  }
}

TEST_CASE("Tests pass", "[tests]"){
  REQUIRE(testTuple() == true);
  REQUIRE(testPool() == true);
}

TEST_CASE("Maps are associative containers", "[map]"){
  const int nIters = 10;
  map<int, int> mp;

  SECTION("Maps initialize empty"){
    REQUIRE(mp.empty());
  }

  for(int i = 0; i < nIters; ++i){
    mp[i] = i + 1;
  }

  SECTION(""){
    for(int i = 0; i < nIters; ++i){
      REQUIRE(mp[i] == i + 1);
    }
  }
}

TEST_CASE("Sort algorithm", "[algorithm]"){
  int count = 1000;
  vector<int> vec;
  std::random_device rd;
  std::mt19937 rate(rd());
  std::normal_distribution<> gene(0, 10000000);

  for(int i = 0; i < count; ++i){
    vec.push_back(gene(rate));
  }

  sort(vec.begin(), vec.end());

  REQUIRE(vec.size() == count);

  for(unsigned int i = 1; i < vec.size(); ++i){
    REQUIRE(vec[i] >= vec[i - 1]);
  }
}

TEST_CASE("Regular operations can be performed on time units", "[time]"){

  SECTION("Time units convert nicely, and report expected amounts."){
    minute m(1);
    second s(m);

    REQUIRE(s == 60);
    REQUIRE(m == 1);
  }

  SECTION("Units interact with ostreams."){
    minute m(1);
    std::stringstream ss;
    std::string str;

    ss << m;
    ss >> str;
    REQUIRE(str == "1");
    ss >> str;
    REQUIRE(str == "minutes");
  }

  SECTION("A date is printed in a human readable format to an ostream."){
    date dayt(11, 8, 2016);
    std::stringstream ss;
    std::string str;

    ss << dayt;
    ss >> str;
    REQUIRE(str == "11");
    ss >> str;
    REQUIRE(str == "August");
    ss >> str;
    REQUIRE(str == "2016");
  }

  SECTION("Mathematical operations can be performed on time units."){
    minute m(59);

    m += 1;

    hour h(m);

    REQUIRE(h == 1);

    m -= 5;

    REQUIRE(m == 55);

    REQUIRE(++h == 2);
    REQUIRE(m++ == 55);
    REQUIRE(m == 56);
    REQUIRE(--h == 1);
    REQUIRE(m-- == 56);
    REQUIRE(m == 55);
  }

  SECTION("Date time interacts with streams."){
    date_time dt(date(11, 8, 2016), 15, 41, 14);
    std::stringstream ss;
    std::string str;

    ss << dt;
    ss >> str;
    REQUIRE(str == "11");
    ss >> str;
    REQUIRE(str == "August");
    ss >> str;
    REQUIRE(str == "2016");

    ss >> str;
    REQUIRE(str == "15:41:14");
  }

  SECTION("Units convert when using streams."){
    std::string str("5 seconds");
    time_unit<5> tu;
    std::stringstream ss(str);

    ss >> tu;
    REQUIRE(tu == 1);

    std::stringstream ss2;

    ss2 << second(10);
    ss2 >> tu;
    REQUIRE(tu == 2);
  }
}

int testfn(){
  return 5;
}

TEST_CASE("Function objects are used as normal functions.", "[function]"){
  function<int(int)> fn;
  function<int(int, int)> nf;
  function<int()> tst;
  
  fn = [](int x){ return 1+x; };
  nf = [](int x, int y){ return x + y; };
  tst = testfn;
  
  SECTION("Calling functions produce expected results."){
    REQUIRE(fn(3) == 4);
    REQUIRE(nf(1, 2) == 3);
    REQUIRE(tst() == 5);
  }
}

TEST_CASE("Arrays can be used as builtin arrays.", "[array]"){
  array<char[3]> arr;
  
  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';
  
  SECTION("Array basics."){
    REQUIRE(arr[0] == 'a');
    REQUIRE(arr[1] == 'b');
    REQUIRE(arr[2] == 'c');
  }
}

TEST_CASE("Equations can be used in basic arithmetic", "[equ]"){
  std::vector<double> vec { 1, 1, 1 };
  std::vector<double> vec2 { 2, 2, 2 };
  equation eq(vec.begin(), vec.end());
  equation eq2(vec2.begin(), vec2.end());

  SECTION("Addition"){
    REQUIRE((eq + eq2)(2) == 21);
  }

  SECTION("Subtraction"){
    REQUIRE((eq2 - eq)(2) == 7);
    REQUIRE((eq - eq2)(2) == -7);
  }

  SECTION("Multiplication"){
    REQUIRE((eq * 2)(2) == 2 * eq(2));

    std::vector<double> vec3 { 1, 1 };
    equation eq3(vec3.begin(), vec3.end());
    vec3[0] = 2;
    equation eq4(vec3.begin(), vec3.end());
    REQUIRE((eq3 * eq4)(2) == 12);

    std::vector<double> vec4 { 1, 1 };
    equation eq5(vec4.begin(), vec4.end());
    vec4.push_back(1);
    equation eq6(vec4.begin(), vec4.end());
    REQUIRE((eq5 * eq6)(2) == 21);
  }

//TODO:test equation division
  SECTION("Division"){
    REQUIRE((eq2 / 2)(2) == eq2(2) / 2);
  }
}

TEST_CASE("Equation", "[equ]"){
  std::vector<double> vec { 1, 1, 1 };
  std::vector<double> vec2 { 2, 2, 2 };
  equation eq(vec.begin(), vec.end());
  equation eq2(vec2.begin(), vec2.end());

  SECTION("Equations can be evaluated"){
    REQUIRE(eq(2) == 7);
    REQUIRE(eq2(2) == 14);
  }

  SECTION("Equations with different number of terms"){
    vec.push_back(1);
    equation eq3(vec.begin(), vec.end());

    REQUIRE(eq3(2) == 15);
    REQUIRE((eq3 + eq)(2) == 22);
    REQUIRE((eq3 - eq)(2) == 8);
  }
}

