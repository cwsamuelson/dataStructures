#include<iostream>
#include"vector.hh"

int main(int argc, char** argv){
  galaxy::vector<char> foo;
  foo.pushBack('a');
  foo.pushBack('b');
  foo.pushBack('c');
  foo.pushBack('d');
  for(auto it = foo.begin(); it != foo.end(); ++it){
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;
  while(foo.size() > 0){
    std::cout << foo.popBack() << std::endl;
  }
  return 0;
}

