#include"test.hh"

int main(int argc, char** argv){
  memoryPool<int> test(10);

  int* foo = test.allocate(2);
  int* bar = test.allocate(1);
  int* baz = test.allocate(2);
  test.deallocate(bar);
  bar = test.allocate(2);
  int* quux = test.allocate(1);
 
  if(baz + 2 == bar){
    std::cout << "check" << std::endl;
  }else{
    std::cout << "fail" << std::endl;
  }
  if(foo + 2 == quux){
    std::cout << "check" << std::endl;
  }else{
    std::cout << "fail" << std::endl;
  }
 
  return 0;
}
