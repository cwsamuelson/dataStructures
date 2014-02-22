#include"except.hh"
using namespace Jing;

exception::exception(const char* message){
}

exception::exception(const string& message){
}

const string& exception::what() const{
  return this->msg;
}

