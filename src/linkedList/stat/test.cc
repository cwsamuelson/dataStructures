#include"list.hh"
#include<iostream>

using std::cout;
using std::endl;

using namespace Jing;

int main(int argc, char **argv){
  int intGood = 1;
  int intBad = 0;
  float floatGood = 1.0;
  float floatBad = 0.0;
  ArrayList<int> test1;
  ArrayList<float> test2;

  cout << "start test" << endl;
  cout << "test int" << endl;
  cout << "int add " << intGood << endl;
  test1.add(intGood) ? cout << "success" : cout << "failure";cout << endl;
  cout << "int get 0" << endl;
  test1.get(0) ? cout << "success" : cout << "failure";cout << endl;
  cout << "int get 1" << endl;
  test1.get(1) ? cout << "success" : cout << "failure";cout << endl;
  cout << "int contains " << intGood << endl;
  test1.contains(intGood) ? cout << "success" : cout << "failure";cout << endl;
  cout << "int contains " << intBad << endl;
  test1.contains(intBad) ? cout << "success" : cout << "failure";cout << endl;
  cout << "int get indexof " << intGood << endl;
  test1.get(test1.indexOf(intGood)) ? cout << "success" : cout << "failure";cout << endl;
  cout << "int get indexof " << intBad << endl;
  test1.get(test1.indexOf(intBad)) ? cout << "success" : cout << "failure";cout << endl;
//check type resolution here.
//move index_t into Jing namespace for easier future access.
  cout << "int remove 1" << endl;
  test1.remove(1) ? cout << "success" : cout << "failure";cout << endl;
  //cout << "int remove 0" << endl;
  //test1.remove(0) ? cout << "success" : cout << "failure";cout << endl;

  cout << endl;

  cout << "start test" << endl;
  cout << "test float" << endl;
  cout << "float add " << floatGood << endl;
  test2.add(floatGood) ? cout << "success" : cout << "failure";cout << endl;
  cout << "float get 0" << endl;
  test2.get(0) ? cout << "success" : cout << "failure";cout << endl;
  cout << "float get 1" << endl;
  test2.get(1) ? cout << "success" : cout << "failure";cout << endl;
  cout << "float contains " << floatGood << endl;
  test2.contains(floatGood) ? cout << "success" : cout << "failure";cout << endl;
  cout << "float contains " << floatBad << endl;
  test2.contains(floatBad) ? cout << "success" : cout << "failure";cout << endl;
  cout << "float get indexof " << floatGood << endl;
  test2.get(test2.indexOf(floatGood)) ? cout << "success" : cout << "failure";cout << endl;
  cout << "float get indexof " << floatBad << endl;
  test2.get(test2.indexOf(floatBad)) ? cout << "success" : cout << "failure";cout << endl;
//check type resolution here.
//move index_t into Jing namespace for easier future access.
  cout << "float remove " << floatGood << endl;
  test2.remove(floatGood) ? cout << "success" : cout << "failure";cout << endl;
  //cout << "float remove 0" << endl;
  //test2.remove(0) ? cout << "success" : cout << "failure";cout << endl;

  cout << "end tests" << endl;
  return 0;
}

