#include"testing.hh"
#include<iostream>
using std::cout;
using std::endl;

void testing::thing(){
  throw testEx(string("damn"));
}

testEx::testEx(const char* message):exception(message){
}

testEx::testEx(const string& message):exception(message){
}

const string& testEx::what() const{
  cout << "in testex" << endl;
  cout << this->msg << endl;
}

