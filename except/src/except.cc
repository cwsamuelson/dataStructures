#include<Jing/except>
#include<iostream>
using std::cout;
using std::endl;

Jing::exception::exception():msg(*(new Jing::string())){
}

Jing::exception::exception(const char* message):msg(*(new Jing::string(message))){
}

Jing::exception::exception(const Jing::string& message):msg(*(new Jing::string(message))){
}

const Jing::string& Jing::exception::what() const{
  cout << "in exception::what(), outputting message letter by letter: " << this->msg.length() << " letters" << endl;

  cout << "beep" << endl;
  cout << this->msg << endl;
  cout << "boop" << endl;

  for(int i = 0; i < this->msg.length(); ++i){
    cout << ":" << i << endl << this->msg.charAt(i) << endl;
  }
  return this->msg;
}

