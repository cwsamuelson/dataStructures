#include"list.hh"
#include<iostream>

using std::cout;
using std::endl;

using namespace Jing;

int main(int argc, char **argv){
  cout << "start test" << endl;
  cout << "test int" << endl;
  ArrayList<int> test1;
  cout << "int add 1" << endl;
  test1.add(1);
  cout << "int remove 1" << endl;
  test1.remove(1);

  cout << endl;

  cout << "test float" << endl;
  ArrayList<float> test2;
  cout << "float add 1.0" << endl;
  test2.add(1.0);
  cout << "end tests" << endl;
  return 0;
}

