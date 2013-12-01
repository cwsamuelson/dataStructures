#include"LinkedList.hh"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int number = 5;
    LinkedList test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << endl;
    for(int i = 0; i <= number; i++){
        cout << "\ttest.insert(" << i << "):\t\t\t"      << test.insert(i) << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.get():\t\t\t"           << test.get()       << endl;
        for(int j = 0; j <= i; j++){
            cout << "\ttest.get(" << j << "):\t\t\t"           << test.get(j)       << endl;
        }
        cout << "\ttest.get(test.getSize()):\t" << test.get(test.getSize()) << endl;
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.get():\t\t\t"           << test.get()       << endl;
        for(int j = 0; j < test.getSize(); j++){
            cout << "\ttest.get(" << j << "):\t\t\t"           << test.get(j)       << endl;
        }
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

