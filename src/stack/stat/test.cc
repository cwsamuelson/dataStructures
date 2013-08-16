#include"stack.hh"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int foo = 1;
    int bar = 2;
    int fu = 3;
    stack test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << endl;
    cout << "\ttest.push(foo):\t\t"      << test.push(foo) << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << "\ttest.push(bar):\t\t"      << test.push(bar) << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << "\ttest.push(fu):\t\t"       << test.push(fu)  << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << endl;
    cout << "\ttest.pop():\t\t\t"        << test.pop()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << "\ttest.pop():\t\t\t"        << test.pop()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    //below should not seg fault
    //it does anyway
    cout << endl;
    cout << "\ttest.pop():\t\t\t"        << test.pop()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    if(test.peek() != -1){
        cout << "\ttest.peek():\t\t\t"       << test.peek()        << endl;
    }
    if(test.peek() != -1){
        cout << "fail" << endl;
        cout << "\ttest.peek(test.getSize()):\t" << test.peek() << endl;
    }
    cout << "end" << endl;
    return 0;
}
