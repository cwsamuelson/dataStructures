#include"stack.hh"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int number = 4;
    stack<int> test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.push(" << i << "):\t\t\t"      << test.push(i) << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.pop():\t\t\t"        << test.pop()     << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
        cout << endl;
    }
    //test extra pops
    cout << endl;
    cout << "\ttest.pop():\t\t\t"        << test.pop()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"       << test.peek()        << endl;
    cout << "end" << endl;
    return 0;
}
