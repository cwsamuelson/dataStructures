#include<Jing/list>
#include<iostream>
#include"character.hh"

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
    for(int i = 0; i < foo.size(); ++i){
      if(!(((character&)foo.get(i)).equals((character&)bar.get(i))))
        return false;
    }
  }

  return true;
}

bool testInserts(){
  list foo;
  Iterator& iter = foo.iterator();
  foo.insert(*new character('a'));
  foo.insert(*new character('b'));
  foo.insert(*new character('c'));
  foo.insert(*new character('d'));

  iter.reset();
  while(iter.hasNext()){
    cout << (character&)iter.next() << endl;
  }

  cout << "Expected: dcba" << endl;

  foo.insert(*new character('e'), 0);
  foo.insert(*new character('f'), 1);

  iter.reset();
  while(iter.hasNext()){
    cout << (character&)iter.next() << endl;
  }

  cout << "Expected: efdcba" << endl;

  foo.insert(*new character('g'), foo.size() + 1);
  foo.insert(*new character('h'), foo.size());
  foo.insert(*new character('i'), foo.size() - 1);
  foo.insert(*new character('j'), foo.size() - 2);

  cout << "for loop" << endl;
  for(int i = 0; i < foo.size(); ++i){
    cout << (character&)foo.get(i) << endl;
  }
  cout << "Expected: efdcbaghji" << endl;

  cout << "iterator" << endl;
  iter.reset();
  while(iter.hasNext()){
    cout << (character&)iter.next() << endl;
  }

  cout << "Expected: efdcbaghji" << endl;
  return true;
}

bool testRemoves(){
  return true;
}

bool testGets(){
  return true;
}

bool testAssigns(){
  return true;
}

bool testContains(){
  return true;
}

bool testReversegets(){
  return true;
}

bool testEquality(){
  return true;
}

bool testIterator(){
  return true;
}

bool testStates(){
  return true;
}

int main(int argc, char **argv){
  cout << "Testing class list" << endl;
  cout << endl;

  if(testConstructors())
    cout << "Constructors check out" << endl;
  else
    cout << "Constructors DON'T check out" << endl;

  cout << "Testing inserts" << endl;
  testInserts();
  cout << "Testing removes" << endl;
  testRemoves();
  cout << "Testing gets" << endl;
  testGets();
  cout << "Testing assigns" << endl;
  testAssigns();
  cout << "Testing contains" << endl;
  testContains();
  cout << "Testing reverse gets" << endl;
  testReversegets();
  cout << "Testing equality" << endl;
  testEquality();
  cout << "Testing iterator" << endl;
  testIterator();
  cout << "Testing states" << endl;
  testStates();
}
