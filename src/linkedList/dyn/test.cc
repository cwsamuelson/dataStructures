#include"LinkedList.hh"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int number = 4;
    LinkedList<int> test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.insert(" << i << "):\t\t\t"      << test.insert(i) << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.get():\t\t\t"           << test.get()       << endl;
        cout << "\ttest.get(test.getSize()):\t" << test.get(test.getSize()) << endl;
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.get():\t\t\t"           << test.get()       << endl;
        cout << "\ttest.get(test.getSize()):\t" << test.get(test.getSize()) << endl;
        cout << endl;
    }
    //below should not seg fault
    //it does anyway
    cout << endl;
    cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.get():\t\t\t"       << test.get()        << endl;
    cout << "end" << endl;
    return 0;
}
