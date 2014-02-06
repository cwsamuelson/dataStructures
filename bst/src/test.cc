#include<Jing/bst.hh>
#include<iostream>

using namespace Jing;
using std::cout;
using std::endl;

int main(int argc, char** argv){
  bst<char, int> foo;
  cout << "add 'a', 1" << endl;
  foo.add('a', 1);
  cout << "add 'b', 2" << endl;
  foo.add('b', 2);

  cout << endl;

  cout << "get 'a'" << endl;
  cout << foo.get('a') << endl;
  cout << "get 'b'" << endl;
  cout << foo.get('b') << endl;

  cout << endl;

  cout << "remove 'b'" << endl;
  foo.remove('b');

  cout << endl;

  cout << "get 'a'" << endl;
  cout << foo.get('a') << endl;
  cout << "get 'b'" << endl;
  cout << foo.get('b') << endl;
  return 0;
}

