#include<iostream>
#include<functional>
#include<sstream>
#include<vector>

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

bool testFunction(){
  function<int(int)> fn;
  
  fn = [](int x){ return 1+x; };
  
  return fn(3) == 4;
}

bool testArray(){
  array<char[3] > arr;
  
  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';
  
  return arr[0] == 'a' && arr[1] == 'b' && arr[2] == 'c';
}

bool testTuple(){
  tuple<int> t1;
  tuple<int, int> t2;
  tuple<char, int, char> t3;
  
  get<0>(t1) = 1;
  
  get<0>(t2) = 2;
  get<1>(t2) = 3;
  
  get<0>(t3) = 'a';
  get<1>(t3) = 4;
  get<2>(t3) = 'b';
  
  return get<0>(t1) == 1 && get<0>(t2) == 2 && get<1>(t2) == 3 &&
       get<0>(t3) == 'a' && get<1>(t3) == 4 && get<2>(t3) == 'b';
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
  uniquePtr<int> ptr1(new int);
  uniquePtr<int> ptr2(new int);
  uniquePtr<foo> ptr3(new foo(x, flag1));
  uniquePtr<foo> ptr4(new foo(y, flag2));
  
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

bool testShared(){
  bool change = true;
  int x = 1;
  int y = 2;
  bool flag;
  sharedPtr<int> ptr1(new int);
  sharedPtr<int> ptr2(new int);
  sharedPtr<foo> ptr3(new foo(x, flag));
  sharedPtr<foo> ptr4(new foo(y, flag));
  sharedPtr<int> ptr5(ptr1);

  *ptr1 = 1;
  *ptr2 = 2;

  ptr1 = ptr2;
  change &= ((*ptr1) == 2);
  ptr4 = ptr3;
  change &= (ptr4->value() == x);
  /* ptr4 just gave up it's access to flag.  flag should be true now */
  change &= flag;
  ptr4 = ptr4;
  change &= (ptr4->value() == x);
  ptr3 = ptr3;
  change &= (ptr3->value() == x);

  return change;
}

typedef struct{
  int x;
  int y;
} X;

typedef struct{
  int z;
  char c;
  char d;
} Y;

typedef struct{
  int e;
  union{
    int f;
    char g[4];
  };
} Z;

bool testStruct(){
  X x;
  
  x.x = 1;
  x.y = (35) + (36 << 8);
  
  void* ptr = &x;
  
  if((*((Y*)ptr)).z != x.x){
    return false;
  } else if((int)(*((Z*)ptr)).g[2] != 0){
    return false;
  } else if((*((Y*)ptr)).d != (*((Z*)ptr)).g[1]){
    return false;
  } else if((*((Y*)ptr)).c != (*((Z*)ptr)).g[0]){
    return false;
  } else {
    return true;
  }
}

string testString(){
  return "test";
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

bool testVector(){
  vector<int> vec;
  int x = 3;
  bool ret = true;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(x);
  vec.pop_back();
  vec.pop_back();
  vec.push_back(x++);
  vec.push_back(x);
  vec.push_back(5);

  auto it = vec.begin();
  for(unsigned int i = 0; i < vec.size(); ++i, ++it){
    ret &= (*it == vec[i]);
  }
  auto jt = vec.begin();

  // dtor test
  bool b;
  bool bb;
  wrapper w(&b);
  vector<wrapper> v;

  v.push_back(w);
  v.pop_back();
  v.emplace_back(&bb);
  v.pop_back();

  return ((vec[0] == 1) && (*jt == 1) && ret) && b && bb;
}

bool testUnit(){
  int X = 1;
  int Y = 2;
  int Z = 3;
  unit<1, 0, 0, 0, 0, 0> x;
  unit<1, 0, 0, 0, 0, 0> y;
  unit<2, 0, 0, 0, 0, 0> z;
  voltage V = 3;
  current I = 5;
  resistance R = 4;
  resistance r;
  std::stringstream ss1;
  std::stringstream ss2;
  std::stringstream ss3;
  std::string s1;
  std::string s2;
  
  V = I * R;
  ss1 << V;
  ss2 << (I * R);
  ss1 >> s1;
  ss2 >> s2;
  ss3 << R;
  ss3 >> r;
  
  x = X;
  y = Y;
  z = Z;
  
  return (((x + y).getValue() == X + Y) && (s1 == s2) && (r == R)) &&
          (((x * y) + z).getValue() == ((X * Y) + Z)) && (V == (I * R));
}

bool testRange(){
  bool ret = true;

  vector<int> vec;
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  vec.push_back(6);
  range<decltype(vec)> rng(vec,
    [](decltype(vec)::const_reference x){
      return x % 2 == 0;
    },
    [](decltype(vec)::const_reference x){
      return x + 1;
    }
  );

  vector<int> vec0;
  vec0.push_back(2);
  vec0.push_back(4);
  vec0.push_back(6);
  
  auto it = rng.begin();
  auto jt = vec0.begin();
  for(;it != rng.end(); ++it, ++jt){
    ret &= (*it == (*jt + 1));
  }
  return ret;
}

TEST_CASE("A range iterator can act as a standard iterator", "[range]"){
  std::vector<int> source{2, 3, 4, 5, 6 };
  range<decltype(source)> rng(source);

  REQUIRE(*rng.begin() == source[0]);
  REQUIRE(*++rng.begin() == source[1]);
  REQUIRE(*--rng.end() == source[source.size() - 1]);

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
  REQUIRE(testFunction() == true);
  REQUIRE(testArray() == true);
  REQUIRE(testTuple() == true);
  REQUIRE(testPool() == true);
  REQUIRE(testUnique() == true);
  REQUIRE(testShared() == true);
  REQUIRE(testStruct() == true);
  REQUIRE(testVector() == true);
  REQUIRE(testUnit() == true);
  REQUIRE(testRange() == true);
}

