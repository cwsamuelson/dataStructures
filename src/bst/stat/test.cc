#include"bst.hh"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int foo1 = 1;// key
    int foo2 = 1;// data
    int bar1 = 2;// key
    int bar2 = 2;// data
    int fu1  = 3;// key
    int fu2  = 3;// data
    int baz1 = 4;// key
    int baz2 = 2;// data
    bst test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << endl;
    cout << "\ttest.insert(foo):\t\t"       << test.insert(foo1, foo2)      << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get(foo1)               << endl;
    cout << endl;
    cout << "\ttest.insert(bar):\t\t"       << test.insert(bar1, bar2)      << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get(foo1)               << endl;
    cout << endl;
    cout << "\ttest.insert(fu):\t\t"        << test.insert(fu1, fu2)        << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get(foo1)               << endl;
    cout << endl;
    cout << "\ttest.insert(baz):\t\t"       << test.insert(baz1, baz2)      << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get(foo1)               << endl;
    cout << endl;
    cout << "\ttest.insert(bar):\t\t"       << test.insert(bar1, bar2)      << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << *test.get(foo1)              << endl;
    cout << endl;
    cout << "\ttest.remove(baz):\t\t\t"     << test.remove(baz)             << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get()                   << endl;
    cout << endl;
    cout << "\ttest.remove(fu):\t\t\t"      << test.remove(fu)              << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get()                   << endl;
    cout << endl;
    cout << "\ttest.remove(bar):\t\t\t"     << test.remove(bar)             << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get()                   << endl;
    cout << endl;
    cout << "\ttest.remove(foo):\t\t\t"     << test.remove(foo)             << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()               << endl;
    cout << "\ttest.get():\t\t\t"           << test.get()                   << endl;
    //below should not seg fault
    //below should not seg fault
    //below should not seg fault
    //below should not seg fault
    //it does anyway
    cout << endl;
    cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    if(test.get() != NULL){
        cout << "\ttest.get():\t\t\t"       << test.get()       << endl;
    }
    if(test.get(test.getSize()) != NULL){
        cout << "fail" << endl;
        cout << "\ttest.get(test.getSize()):\t" << *test.get(test.getSize()) << endl;
    }
    cout << "end" << endl;
    return 0;
}
