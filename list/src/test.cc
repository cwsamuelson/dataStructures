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
  list foo;
  foo.insert(*new character('a'));
  foo.insert(*new character('b'));

  list bar(foo);

  if(foo.size() != bar.size()){
    return false;
  } else {
    for(Jing::index_t i = 0; i < foo.size(); ++i){
      if(!(((character&)foo.get(i)).equals((character&)bar.get(i))))
        return false;
    }
  }

  return true;
}

bool testEmptyInserts(){
  list foo;
  Iterator& iter = foo.iterator();
  while(iter.hasNext()){
    cout << (character&)iter.next() << endl;
  }
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    cout << (character&)foo.get(i) << endl;
  }
  return true;
}

bool testBasicInserts(){
  char tester[] = {'a', 'b', 'c', 'd'};
  list foo;
  foo.insert(*new character('a'));
  foo.insert(*new character('b'));
  foo.insert(*new character('c'));
  foo.insert(*new character('d'));

  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester[i]))
      return false;
  }
  return true;
}

bool testArbitraryInserts(){
  list foo;
  foo.insert(*new character('a'));
  foo.insert(*new character('c'));
  foo.insert(*new character('b'), 1);

  char tester1[] = {'a', 'b', 'c'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester1[i]))
      return false;
  }

  foo.insert(*new character('f'), foo.size() + 2);
  char tester2[] = {'a', 'b', 'c', 'f'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester2[i]))
      return false;
  }

  foo.insert(*new character('g'), -1);
  char tester3[] = {'a', 'b', 'c', 'f', 'g'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester3[i]))
      return false;
  }

  foo.insert(*new character('d'), foo.size() - 2);
  foo.insert(*new character('e'), foo.size() - 2);
  char finalTester[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(finalTester[i]))
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
  list foo;
  Iterator& iter = foo.iterator();
  foo.insert(*new character('a'));
  foo.insert(*new character('b'));
  foo.insert(*new character('c'));
  foo.insert(*new character('d'));
  foo.insert(*new character('e'));
  char tester1[] = {'a', 'b', 'c', 'd', 'e'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester1[i]))
      return false;
  }

  foo.remove();
  iter.reset();
  char tester2[] = {'b', 'c', 'd', 'e'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester2[i]))
      return false;
  }

  foo.remove(1);
  iter.reset();
  char tester3[] = {'b', 'd', 'e'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester3[i]))
      return false;
  }
  return true;
//TODO:Find a way to implement equals methods in Object subclasses that allows them to take an Object parameter, and not a parameter of the same class type.
  foo.remove(*new character('e'));
  iter.reset();
  char tester4[] = {'b', 'd'};
  for(Jing::index_t i = 0; i < foo.size(); ++i){
    if(!((character&)foo.get(i)).equals(tester4[i]))
      return false;
  }
  return true;
}

bool testGets(){
  return false;
}

bool testAssigns(){
  return false;
}

bool testContains(){
  return false;
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

int main(int argc, char **argv){
  cout << "Testing class list" << endl;
  cout << endl;

  if(testConstructors())
    cout << "Constructors check out" << endl;
  else
    cout << "Constructors DON'T check out" << endl;

  if(testInserts())
    cout << "Inserts check out" << endl;
  else
    cout << "Inserts DON'T check out" << endl;
  
  if(testRemoves())
    cout << "Removes check out" << endl;
  else
    cout << "Removes DON'T check out" << endl;
  
  if(testGets())
    cout << "Gets check out" << endl;
  else
    cout << "Gets DON'T check out" << endl;
  
  if(testAssigns())
    cout << "Assigns check out" << endl;
  else
    cout << "Assigns DON'T check out" << endl;
  
  if(testContains())
    cout << "Contains check out" << endl;
  else
    cout << "Contains DON'T check out" << endl;
  
  if(testReversegets())
    cout << "Reversegets check out" << endl;
  else
    cout << "Reversegets DON'T check out" << endl;
  
  if(testEquality())
    cout << "Equality check out" << endl;
  else
    cout << "Equality DON'T check out" << endl;
  
  if(testIterator())
    cout << "Iterator check out" << endl;
  else
    cout << "Iterator DON'T check out" << endl;
  
  if(testStates())
    cout << "States check out" << endl;
  else
    cout << "States DON'T check out" << endl;
}

