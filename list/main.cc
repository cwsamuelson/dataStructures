#include<iostream>
#include"list.hh"

int main(){
  list foo;
  foo.pushBack('H');
  foo.pushBack('e');
  foo.pushBack('l');
  foo.pushBack('l');
  foo.pushBack('o');
  foo.pushFront('\n');
  for(unsigned int i = 0; i < foo.length(); ++i){
    std::cout << foo.get(i) << std::endl;
  }
   
  return 0;
}

