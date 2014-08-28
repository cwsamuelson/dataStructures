#include<Jing/list>
#include<iostream>
#include"character.hh"
#include<Jing/Misc.hh>

using std::cout;
using std::endl;
using std::ostream;

using namespace Jing;

//update collection addition as new collections are created
bool testConstructors(){
  list<character&> foo;
  foo.insert(*new character('a'));
  foo.insert(*new character('b'));

  list<character&> bar(foo);

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
  list<character&> foo;
  Iterator<character&>& iter = foo.iterator();
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
  list<character&> foo;
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
  list<character&> foo;
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

  list<character&> foo;
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
  list<character&> foo;
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
  list<character&> foo;
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
  list<character&> foo;
  char chs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  for(int i = 0; i < 9; ++i){
    foo.insert(*new character(chs[i]));
  }

  Collection<character&>& coll = foo.get(3, 6);
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
  list<character&> foo;
  foo.insert(*new character('a'));
  //possible memory problem
  delete &foo.assign(0, *new character('b'));
  if(!(foo.get()).equals('b')){
    return false;
  }
  return true;
}

bool testContain(){
  list<character&> foo;
  if(foo.contains(*new character('a'))){
    cout << "check!" << endl;
  }
  return false;
}

bool testAllContain(){
  return false;
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

bool testReversegets(){
  return false;
}

bool testEquality(){
  return false;
}

bool testIterator(){
  return false;
}

bool testStates(){
  return false;
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
    cout << "Reversegets check out" << endl;
  } else {
    ret = false;
    cout << "Reversegets DON'T check out" << endl;
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
}

