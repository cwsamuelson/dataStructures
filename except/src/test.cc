#include<Jing/except.hh>
#include<Jing/string>
#include<iostream>
#include"testing.hh"

using std::cout;
using std::endl;
using Jing::string;

int main(int argc, char** argv){
  testing foobar;
  try{
    foobar.thing();
  } catch (testEx te) {
    cout << "testEx caught: " << te.what() << endl;
  }
  return 0;
}

