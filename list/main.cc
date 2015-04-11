#include<iostream>
#include"list.hh"

int main(){
  list foo;
  foo.pushFront(' ');
  foo.pushBack('W');
  foo.pushBack('o');
  foo.pushBack('r');
  foo.pushBack('l');
  foo.pushFront('o');
  foo.pushFront('l');
  foo.pushFront('l');
  foo.pushFront('e');
  foo.pushFront('H');
  foo.pushBack('d');
  for(auto it = foo.begin(); it != foo.end(); ++it){
    std::cout << *it;
  }
  std::cout << std::endl;
  for(unsigned int i = 0; i < foo.length(); ++i){
    std::cout << foo[i];
  }
  std::cout << std::endl;

  while(!foo.isEmpty()){
    std::cout << foo.popBack();
  }
  std::cout << std::endl;
   
  return 0;
}

