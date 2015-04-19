#include"test.hh"

using std::cout;
using std::endl;
using std::ostream;

using namespace Jing;

bool test(){
  bool ret = true;
  return ret;
}
//Use exceptions to pass errors
int main(int argc, char **argv){
  bool ret = true;
  cout << "Testing class list" << endl;
  cout << endl;

  //Uncomment any below to confirm inheritance checks.
  //list<int> foo;
  //list<int>* bar = new list<int>;
  //list<int>& baz = *new list<int>;
  //list<Object&> foo;
  //list<Object&>* bar = new list<Object&>;
  //list<Object&>& baz = *new list<Object&>;

  if(test()){
    cout << "Stuff checks out" << endl;
  } else {
    ret = false;
    cout << "Stuff DOESN'T check out" << endl;
  }

  return !ret;
}

