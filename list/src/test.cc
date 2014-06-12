#include<Jing/list>
#include<iostream>

using std::cout;
using std::endl;
using std::ostream;

using namespace Jing;

class character:public Object{
protected:
  char letter;
public:
  character(char c){ this->letter = c; }

  bool equals(Object& c) const{
    return false;
  }

  int hash() const{
    return 0;
  }

  int classID() const{
    return 99;
  }

  Object* clone() const{
    return new character(this->letter);
  }

  friend ostream& operator<<(ostream&os, const character& let);
};

ostream& operator<<(ostream&os, const character& let){
  os << let.letter;
  return os;
}


//update collection addition as new collections are created
bool testConstructors(){
  list foo;
  foo.insert(*new character('a'));
  cout << (character&)foo.get(0) << endl;
  return true;
}

bool testInserts(){
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
  cout << "Testing list class" << endl;
  cout << endl;

  cout << "Testing constructors" << endl;
  testConstructors();
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
