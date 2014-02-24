#include"except.hh"

using namespace Jing;

exception::exception(const char* message){
  msg = message;
}

exception::exception(const string& message){
  msg = message;
}

const string& exception::what() const{
  return this->msg;
}

