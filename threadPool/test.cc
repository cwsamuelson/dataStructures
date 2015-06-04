#include<iostream>
#include<mutex>
#include"threadPool.hh"

void func1(){
  static int i = 0;
  static std::mutex mtx;

  mtx.lock();
  std::cout << ++i << std::endl;
  mtx.unlock();
}

void func2(){
  static int i = 10;
  static std::mutex mtx;

  mtx.lock();
  std::cout << ++i << std::endl;
  mtx.unlock();
}

int main(int argc, char** argv){
  threadPool test(4);

  for(unsigned int i = 0; i < 10; ++i){
    if(i % 2 == 0)
      test.push(func1);
    else
      test.push(func2);
  }

  return 0;
}
