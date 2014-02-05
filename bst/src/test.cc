#include<Jing/bst.hh>
#include<iostream>

using namespace Jing;
using std::cout;
using std::endl;

int main(int argc, char** argv){
  bst<char, int> foo;
  foo.add('a', 1);
  return 0;
}

