#include<Jing/string.hh>
#include<iostream>

using std::cout;
using std::endl;
using namespace Jing;

int main(int argc, char** argv){
  string foo("test");
  string bar(foo);

  cout << "check" << endl;
  cout << foo.charAt(1) << endl;
  cout << foo << endl;
  cout << foo.charAt(1) << endl;

  cout << bar.charAt(1) << endl;
  cout << bar << endl;

  return 0;
}
