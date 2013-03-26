#include"LinkedList.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int foo = 1;
    int bar = 2;
    int fu = 3;
    LinkedList<int> test; //= new LinkedList<int>;
    cout << "\ttest.insert(&foo):\t"    << test.insert(&foo) << endl;
    cout << "\ttest.get():\t\t"         << test.get()        << endl;
    cout << "\ttest.getSize():\t\t"     << test.getSize()    << endl;
    cout << "\ttest.insert(&bar):\t"    << test.insert(&bar) << endl;
    cout << "\ttest.get():\t\t"         << test.get()        << endl;
    cout << "\ttest.getSize():\t\t"     << test.getSize()    << endl;
    cout << "\ttest.insert(&fu):\t"     << test.insert(&fu)  << endl;
    cout << "\ttest.getSize():\t\t"     << test.getSize()    << endl;
    cout << "\ttest.get():\t\t"         << test.get()        << endl;
    cout << "\ttest.remove():\t\t"      << test.remove()     << endl;
    cout << "\ttest.getSize():\t\t"     << test.getSize()    << endl;
    cout << "\ttest.remove():\t\t"      << test.remove()     << endl;
    cout << "end" << endl;
    return 0;
}
