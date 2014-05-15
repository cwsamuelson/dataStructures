#include<Jing/string>
#include<iostream>

using std::cout;
using std::endl;
using namespace Jing;

int main(int argc, char** argv){
  string foo("test");
  string bar(foo);

  cout << "charat" << endl;
  cout << foo.charAt(1) << endl;
  cout << "<<foo<<" << endl;
  cout << foo << endl;
  cout << "charat" << endl;
  cout << foo.charAt(1) << endl;

  cout << "charat" << endl;
  cout << bar.charAt(1) << endl;
  cout << "<<bar<<" << endl;
  cout << bar << endl;

  return 0;
}
