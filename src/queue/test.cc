#include"queue.hh"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int foo = 1;
    int bar = 2;
    int fu = 3;
    queue test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << endl;
    cout << "\ttest.enqueue(foo):\t\t"      << test.enqueue(foo) << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << "\ttest.enqueue(bar):\t\t"      << test.enqueue(bar) << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << "\ttest.enqueue(fu):\t\t"       << test.enqueue(fu)  << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << endl;
    cout << "\ttest.dequeue():\t\t\t"        << test.dequeue()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    cout << endl;
    cout << "\ttest.dequeue():\t\t\t"        << test.dequeue()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
    //below should not seg fault
    //it does anyway
    cout << endl;
    cout << "\ttest.dequeue():\t\t\t"        << test.dequeue()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    if(test.peek() != NULL){
        cout << "\ttest.peek():\t\t\t"       << test.peek()        << endl;
    }
    if(test.peek() != NULL){
        cout << "fail" << endl;
        cout << "\ttest.peek(test.getSize()):\t" << test.peek() << endl;
    }
    cout << "end" << endl;
    return 0;
}
