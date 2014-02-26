#include"testing.hh"

void testing::thing(){
  throw testEx(string("damn"));
}

testEx::testEx(const char* message):exception(message){
}

testEx::testEx(const string& message):exception(message){
}

//const string& testEx::what() const{
//}
