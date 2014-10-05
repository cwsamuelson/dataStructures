#include"test.hh"

using std::cout;
using std::endl;
using std::ostream;

using namespace Jing;

//update collection addition as new collections are created
bool testConstructors(){
  List<character> foo;
  foo.insert(*new character('a'));
  foo.insert(*new character('b'));

  List<character> bar(foo);

  if(foo.size() != bar.size()){
    return false;
  } else {
    for(Jing::index_t i = 0; i < foo.size(); ++i){
      if(!((foo.get(i)).equals(bar.get(i))))
        return false;
    }
  }

  return true;
}

bool testEmptyInserts(){
  List<character> foo;
  Iterator<character>& iter = *foo.iterator();
  while(iter.hasNext()){
    cout << iter.next() << endl;
  }
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    cout << foo.get(i) << endl;
  }
  return true;
}

bool testBasicInserts(){
  char tester[] = {'a', 'b', 'c', 'd'};
  List<character> foo;
  foo.insert(*new character('a'));
  foo.insert(*new character('b'));
  foo.insert(*new character('c'));
  foo.insert(*new character('d'));

  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester[i]))
      return false;
  }
  return true;
}

bool testArbitraryInserts(){
  List<character> foo;
  foo.insert(*new character('a'));
  foo.insert(*new character('c'));
  foo.insert(*new character('b'), 1);

  char tester1[] = {'a', 'b', 'c'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester1[i]))
      return false;
  }

  foo.insert(*new character('f'), foo.size() + 2);
  char tester2[] = {'a', 'b', 'c', 'f'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester2[i]))
      return false;
  }

  foo.insert(*new character('g'), -1);
  char tester3[] = {'a', 'b', 'c', 'f', 'g'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester3[i]))
      return false;
  }

  foo.insert(*new character('d'), foo.size() - 2);
  foo.insert(*new character('e'), foo.size() - 2);
  char finalTester[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(finalTester[i]))
      return false;
  }
  return true;
}

bool testInserts(){
  bool ret = true;
  if(testEmptyInserts()){
  } else {
    cout << "\tEmpty Inserts DON'T check out" << endl;
    ret = false;
  }
  if(testBasicInserts()){
  } else {
    cout << "\tBasic Inserts DON'T check out" << endl;
    ret = false;
  }
  if(testArbitraryInserts()){
  } else {
    cout << "\tArbitrary Inserts DON'T check out" << endl;
    ret = false;
  }
  return ret;
}

bool testRemoves(){
  bool ret = true;
/*
  int siz = 5;
  character** values = new character*[siz];
*/
  character* values[5]{
    new character('a'),
    new character('b'),
    new character('c'),
    new character('d'),
    new character('e')
  };

  List<character> foo;
/*  for(int i = 0; i < siz; ++i){
    values[i] = new character((char)((int)'a' + i));
    foo.insert(*values[i]);
  }
*/
  foo.insert(*values[0]);
  foo.insert(*values[1]);
  foo.insert(*values[2]);
  foo.insert(*values[3]);
  foo.insert(*values[4]);

  char tester1[] = {'a', 'b', 'c', 'd', 'e'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester1[i]))
      ret = false;
  }

  foo.remove();
  char tester2[] = {'b', 'c', 'd', 'e'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester2[i])){
      ret = false;
    }
  }

  foo.remove(1);
  char tester3[] = {'b', 'd', 'e'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester3[i])){
      cout << "\tFailed test 2:" << endl;
      cout << "\tExpected: " << tester3[i] << " at " << i << endl;
      cout << "\tFound: " << foo.get(i) << " at " << i << endl;
      ret = false;
    }
  }

  character& temp = *new character('e');
  foo.remove(temp);
  char tester4[] = {'b', 'd'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester4[i])){
      ret = false;
    }
  }

  for(unsigned int i = 0; i < 5; ++i){
    delete values[i];
  }
  return ret;
}

bool testGetsBasic(){
  Jing::index_t siz = 10;
  //Test some random gets inside the list.
  List<character> foo;
  char* tester = new char[siz];
  for(unsigned int i = 0; i < siz; ++i){
    tester[i] = (char)(i+97);
    foo.insert(*new character((char)(i+97)));
  }

  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!(foo.get(i)).equals(tester[i]))
      return false;
  }

  Jing:: index_t i = siz + 20;
  if(!(foo.get(i)).equals(tester[siz - 1]))
    return false;
  i = -1;
  if(!(foo.get(i)).equals(tester[siz - 1]))
    return false;

  delete[] tester;
  //Test some gets that are beyond the bounds of the list, should grab nearest index instead.
  return true;
}

bool testGet(){
  List<character> foo;
  foo.insert(*new character('a'));
  if(!(foo.get()).equals('a')){
    return false;
  }

  foo.insert(*new character('b'), 0);
  if(!(foo.get()).equals('b')){
    return false;
  }

  foo.insert(*new character('c'), 0);
  if(!(foo.get()).equals('c')){
    return false;
  }

  return true;
}

bool testGetRange(){
  List<character> foo;
  char chs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  for(int i = 0; i < 9; ++i){
    foo.insert(*new character(chs[i]));
  }

  Collection<character>& coll = foo.get(3, 6);
  for(Jing::index_t i = 0; i < coll.size(); ++i){
    if(!(foo.get(i)).equals(chs[i]))
      return false;
  }
  
  return true;
}

bool testGets(){
  bool ret = true;

  if(testGetsBasic()){
  } else {
    cout << "\tBasic Gets DON'T check out" << endl;
    ret = false;
  }

  if(testGet()){
  } else {
    cout << "\tEmpty Get DOESN'T check out" << endl;
    ret = false;
  }

  if(testGetRange()){
  } else {
    cout << "\tRange Gets DON'T check out" << endl;
    ret = false;
  }

  return ret;
}

bool testAssigns(){
  //TODO:Probably need more test cases here.
  List<character> foo;
  foo.insert(*new character('a'));
  //possible memory problem
  delete &foo.assign(0, *new character('b'));
  if(!(foo.get()).equals('b')){
    return false;
  }
  return true;
}

bool testContain(){
  bool ret = true;
  List<character> foo;
  character** vals= new character*[3];
  vals[0] = new character('a');
  vals[1] = new character('b');
  vals[2] = new character('c');

  foo.insert(*vals[0]);
  foo.insert(*vals[1]);
  foo.insert(*vals[2]);

  //TODO:test all 3 values to be sure
  character* test = new character('a');
  if(!foo.contains(*test)){
    ret = false;
  }

  //TODO:test some other bad values
  character* fail = new character('z');
  if(foo.contains(*fail)){
    ret = false;
  }

  delete vals[0];
  delete vals[1];
  delete vals[2];
  delete[] vals;
  delete test;
  delete fail;

  return ret;
}

bool testAllContain(){
  bool ret = true;
  List<character> base;
  character** vals = new character*[15];
  for(int i = 0; i < 15; ++i){
    vals[i] = new character((char)((int)'a' + i));
    base.insert(*vals[i]);
  }

  List<character> foo;
  for(int i = 0; i < 5; ++i){
    foo.insert(*vals[i]);
  }
  
  if(!base.containsAll(foo)){
    ret = false;
    cout << "\tFailed test 1" << endl;
  }

  List<character> baz;
  for(int i = 5; i < 10; ++i){
    baz.insert(*vals[i]);
  }

  if(!base.containsAll(baz)){
    ret = false;
    cout << "\tFailed test 2" << endl;
  }
  
  List<character> bar;
  for(int i = 10; i < 15; ++i){
    bar.insert(*vals[i]);
  }

  if(!base.containsAll(bar)){
    ret = false;
    cout << "\tFailed test 3" << endl;
  }

  for(int i = 0; i < 15; ++i){
    delete vals[i];
  }

  delete[] vals;
  return ret;
}

bool testContains(){
  bool ret = true;

  if(testContain()){
  } else {
    cout << "\tBasic Contain DOESN'T check out" << endl;
    ret = false;
  }

  if(testAllContain()){
  } else {
    cout << "\tAll Contain DOESN'T check out" << endl;
    ret = false;
  }

  return ret;
}

bool testFwdReverseget(){
  bool ret = true;
  List<character> foo;
  character** vals= new character*[3];
  vals[0] = new character('a');
  vals[1] = new character('b');
  vals[2] = new character('c');

  character** test= new character*[3];
  test[0] = new character('a');
  test[1] = new character('b');
  test[2] = new character('c');

  foo.insert(*vals[0]);
  foo.insert(*vals[1]);
  foo.insert(*vals[2]);

  for(unsigned int i = 0; i < 3; ++i){
    if(foo.indexOf(*test[i]) != i){
      cout << "\tFailed test 1 at index:" << i << endl;
      ret = false;
    }
  }

  delete vals[0];
  delete vals[1];
  delete vals[2];
  delete[] vals;
  return ret;
}

bool testRvsReverseGet(){
  bool ret = true;
  List<character> foo;
  character** vals= new character*[3];
  vals[0] = new character('a');
  vals[1] = new character('b');
  vals[2] = new character('c');

  character** test= new character*[3];
  test[0] = new character('a');
  test[1] = new character('b');
  test[2] = new character('c');

  foo.insert(*vals[0]);
  foo.insert(*vals[1]);
  foo.insert(*vals[2]);

  for(unsigned int i = 0; i < 3; ++i){
    if(foo.lastIndexOf(*test[i]) != i){
      cout << "\tFailed test 2 at index:" << i << endl;
      ret = false;
    }
  }

  delete vals[0];
  delete vals[1];
  delete vals[2];
  delete[] vals;
  return ret;
}

bool testReversegets(){
  bool ret = true;

  if(testFwdReverseget()){
  } else {
    cout << "\tForward Reverse Get DOESN'T check out" << endl;
    ret = false;
  }

  if(testRvsReverseGet()){
  } else {
    cout << "\tReverse Reverse Get DOESN'T check out" << endl;
    ret = false;
  }

  return ret;
}

bool testEquality(){
  bool ret = true;
  List<character> foo;
  character** one = new character*[3];
  one[0] = new character('a');
  one[1] = new character('b');
  one[2] = new character('c');

  foo.insert(*one[0]);
  foo.insert(*one[1]);
  foo.insert(*one[2]);

  List<character> bar;
  character** two = new character*[3];
  two[0] = new character('a');
  two[1] = new character('b');
  two[2] = new character('c');

  bar.insert(*two[0]);
  bar.insert(*two[1]);
  bar.insert(*two[2]);

/*
  if(!foo.equals(bar)){
    ret = false;
    for(int i = 0; i < 3; ++i){
      cout << "one:" << *one[i] << endl;
      cout << "two:" << *two[i] << endl;
    }
  }
*/

  delete one[0];
  delete one[1];
  delete one[2];
  delete[] one;

  delete two[0];
  delete two[1];
  delete two[2];
  delete[] two;

  return ret;
}

bool testIterator(){
  bool ret = true;
  unsigned int numbah= 8;
  List<character> foo;
  character** vals = new character*[numbah];
  for(unsigned int i = 0; i < numbah; ++i){
    vals[i] = new character((char)(i + (int)'a'));
    foo.insert(*vals[i]);
  }
  Iterator<character>& iter = *foo.iterator();

  int lcv = 0;
  while(iter.hasNext()){
    if(!vals[lcv]->equals(iter.next())){
      ret = false;
    }
    ++lcv;
  }

  for(unsigned int i = 0; i < numbah; ++i){
    delete vals[i];
  }
  delete[] vals;

  return ret;
}

bool testHash(){
  bool ret = true;
  List<character> foo;
  character** vals = new character*[4];
  vals[0] = new character('a');
  vals[1] = new character('b');
  vals[2] = new character('c');
  vals[3] = new character('d');

  foo.insert(*vals[0]);
  foo.insert(*vals[1]);
  foo.insert(*vals[2]);

  cout << "hash:" << foo.hash() << endl;

  foo.insert(*vals[3]);
  
  cout << "hash:" << foo.hash() << endl;

  delete vals[0];
  delete vals[1];
  delete vals[2];
  delete[] vals;

  return ret;
}

bool testClone(){
  bool ret = false;
  List<character> foo;
  character** vals = new character*[4];
  vals[0] = new character('a');
  vals[1] = new character('b');
  vals[2] = new character('c');
  vals[3] = new character('d');

  foo.insert(*vals[0]);
  foo.insert(*vals[1]);
  foo.insert(*vals[2]);
  foo.insert(*vals[3]);

  delete vals[0];
  delete vals[1];
  delete vals[2];
  delete vals[3];
  delete[] vals;

  return ret;
}

bool testToArray(){
  bool ret = false;
  return ret;
}

bool testEmpty(){
  bool ret = false;
  return ret;
}

bool testSize(){
  bool ret = false;
  return ret;
}

bool testClear(){
  bool ret = false;
  return ret;
}

bool testStates(){
  bool ret = true;

  if(testHash()){
  } else {
    cout << "\tHash DOESN'T check out" << endl;
    ret = false;
  }

  if(testClone()){
  } else {
    cout << "\tClone DOESN'T check out" << endl;
    ret = false;
  }

  if(testToArray()){
  } else {
    cout << "\tTo Array DOESN'T check out" << endl;
    ret = false;
  }

  if(testEmpty()){
  } else {
    cout << "\tEmpty check DOESN'T check out" << endl;
    ret = false;
  }

  if(testSize()){
  } else {
    cout << "\tSize check DOESN'T check out" << endl;
    ret = false;
  }

  if(testClear()){
  } else {
    cout << "\tClear DOESN'T check out" << endl;
    ret = false;
  }

  return ret;
}

//Use exceptions to pass errors
int main(int argc, char **argv){
  bool ret = true;
  cout << "Testing class list" << endl;
  cout << endl;

  //Uncomment any below to confirm inheritance checks.
  //list<int> foo;
  //list<int>* bar = new list<int>;
  //list<int>& baz = *new list<int>;
  //list<Object&> foo;
  //list<Object&>* bar = new list<Object&>;
  //list<Object&>& baz = *new list<Object&>;

  if(testConstructors()){
    cout << "Constructors check out" << endl;
  } else {
    ret = false;
    cout << "Constructors DON'T check out" << endl;
  }

  if(testInserts()){
    cout << "Inserts check out" << endl;
  } else {
    ret = false;
    cout << "Inserts DON'T check out" << endl;
  }
  if(testRemoves()){
    cout << "Removes check out" << endl;
  } else {
    ret = false;
    cout << "Removes DON'T check out" << endl;
  }
  
  if(testGets()){
    cout << "Gets check out" << endl;
  } else {
    ret = false;
    cout << "Gets DON'T check out" << endl;
  }
  
  if(testAssigns()){
    cout << "Assigns check out" << endl;
  } else {
    ret = false;
    cout << "Assigns DON'T check out" << endl;
  }
  
  if(testContains()){
    cout << "Contains check out" << endl;
  } else {
    ret = false;
    cout << "Contains DON'T check out" << endl;
  }
  
  if(testReversegets()){
    cout << "Reverse gets check out" << endl;
  } else {
    ret = false;
    cout << "Reverse gets DON'T check out" << endl;
  }
  
  if(testEquality()){
    cout << "Equality check out" << endl;
  } else {
    ret = false;
    cout << "Equality DON'T check out" << endl;
  }
  
  if(testIterator()){
    cout << "Iterator check out" << endl;
  } else {
    ret = false;
    cout << "Iterator DON'T check out" << endl;
  }
  
  if(testStates()){
    cout << "State tests check out" << endl;
  } else {
    ret = false;
    cout << "State tests DON'T check out" << endl;
  }

  if(ret){
    cout << endl << "Overall list checks out" << endl;
  } else {
    cout << endl << "Overall list DOESN'T check out" << endl;
  }

  return !ret;
}

