#include"queue.hh"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int number = 4;
    queue<int> test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.enqueue(" << i << "):\t\t"      << test.enqueue(i) << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.dequeue():\t\t\t"        << test.dequeue()     << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.peek():\t\t\t"           << test.peek()       << endl;
        cout << endl;
    }
    //below should not seg fault
    //it does anyway
    cout << endl;
    cout << "\ttest.dequeue():\t\t\t"        << test.dequeue()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.peek():\t\t\t"       << test.peek()        << endl;
    cout << "end" << endl;
    return 0;
}
