#include"list.hh"
#include<iostream>

using std::cout;
using std::endl;

using namespace Jing;

//add includes add, remove, get, and isempty
void addTests();
void clearTests();
void containsTests();
void indexTests();
void iteratorTests();
void equalsTests();

int main(int argc, char **argv){
  addTests();
  clearTests();
  containsTests();
  indexTests();
  iteratorTests();
  return 0;
}

void iteratorTests(){
  cout << "iteraterTests" << endl;
  ArrayList<char> foo;
  foo.add('a');
  foo.add('b');
  foo.add('c');

  Iterator<char> *temp = foo.iterator();

  while(temp->hasNext()){
    cout << temp->next();
  }

  cout << endl;
  cout << endl;
}

void equalsTests(){
  cout << "indexTests" << endl;

  cout << endl;
  cout << endl;
}

void indexTests(){
  cout << "indexTests" << endl;
  ArrayList<char> foo;
  foo.add('a');
  foo.add('a');
  foo.add('b');
  foo.add('c');
  foo.add('b');

  Iterator<char> *temp = foo.iterator();

  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;
  cout << "contains 'a', 'd', 'c'" << endl;
  cout << "first and last index of 'a'" << endl;
  cout << foo.indexOf('a') << endl;
  cout << foo.lastIndexOf('a') << endl;
  cout << "first and last index of 'b'" << endl;
  cout << foo.indexOf('b') << endl;
  cout << foo.lastIndexOf('b') << endl;

  cout << endl;

  cout << endl;
  cout << endl;
}

void containsTests(){
  cout << "containsTests" << endl;
  ArrayList<char> foo;

  cout << "starting list" << endl;
  foo.add('d');
  foo.add('c');
  foo.add('b');
  foo.add('a');

  Iterator<char> *temp = foo.iterator();

  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << "contains 'a', 'd', 'c'" << endl;
  bool test = true;
  if(!foo.contains('a')) test = false;
  if(!foo.contains('d')) test = false;
  if(!foo.contains('c')) test = false;
  cout << "all contains ";
  test ? cout << "succeeded" : cout << "failed";cout << endl;
  cout << endl;

  cout << "bad contains 'z'" << endl;
  cout << "contain ";
  foo.contains('z') ? cout << "succeeded" : cout << "failed";cout << endl;
  cout << endl;

  ArrayList<char> bar;
  bar.add('b');
  bar.add('c');

  cout << "contains all 'b,c'" << endl;
  foo.containsAll(&bar) ? cout << "succeeded" : cout << "failed";cout << endl;
  cout << endl;

  ArrayList<char> baz;
  baz.add('x');
  baz.add('y');
  baz.add('z');

  cout << "bad contains all 'x,y,z'" << endl;
  foo.containsAll(&baz) ? cout << "succeeded" : cout << "failed";cout << endl;
  cout << endl;

  ArrayList<char> bop;
  bop.add('b');
  bop.add('c');
  bop.add('x');
  bop.add('y');
  bop.add('z');

  cout << "bad mixed contains all 'b,c,x,y,z'" << endl;
  foo.containsAll(&bop) ? cout << "succeeded" : cout << "failed";cout << endl;
  cout << endl;

  bop.clear();
  bop.add('x');
  bop.add('y');
  bop.add('z');
  bop.add('b');
  bop.add('c');
  cout << "bad mixed contains all 'x,y,z,b,c'" << endl;
  foo.containsAll(&bop) ? cout << "succeeded" : cout << "failed";cout << endl;
  cout << endl;


  cout << endl;
  cout << endl;
}

void clearTests(){
  cout << "clearTests" << endl;
  ArrayList<char> foo;

  cout << "prelim clear" << endl;
  cout << "before size:" << foo.size() << endl;
  foo.clear();
  cout << "after size:" << foo.size() << endl;
  cout << endl;

  foo.add('a');
  foo.add('b');
  foo.add('c');
  foo.add('d');
  foo.add('e');
  cout << "print filled list" << endl;

  Iterator<char> *temp = foo.iterator();

  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << "full list clear" << endl;
  foo.clear();
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << endl;
  cout << endl;
}

void addTests(){
  cout << "addTests" << endl;
  ArrayList<char> foo;

  cout << "print empty list" << endl;

  Iterator<char> *temp = foo.iterator();

  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;
  cout << "add basic characters" << endl;
  foo.add('a');
  foo.add('c');
  foo.add('d');
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << "arbitrary good insert" << endl;
  foo.add('b', 1);
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  //inserting to wrong index
  cout << "arbitrary bad insert 1" << endl;
  foo.add('z', foo.size() + 2);
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  //seg faulting
  cout << "arbitrary bad insert 2" << endl;
  foo.add('x', -1);
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << "remove first value" << endl;
  foo.remove((unsigned int) 0);
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;
  cout << "remove last value" << endl;
  foo.remove(foo.size());
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << "remove good 'a' value" << endl;
  foo.remove('a');
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << "remove bad 'l' value" << endl;
  foo.remove('l');
  temp->reset();
  while(temp->hasNext()){
    cout << temp->next();
  }
  cout << endl;

  cout << endl;
  cout << endl;
}

