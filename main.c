#include"LinkedList.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    cout << "start" << endl;
    int foo = 3;
    int bar = 2;
    int fu = 1;
    LinkedList<int> test; //= new LinkedList<int>;
    cout << "\ttest.insert(&foo):\t\t"      << test.insert(&foo) << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.get():\t\t\t"           << test.get()        << endl;
    cout << "\ttest.get(this.getSize()):\t" << test.get(test.getSize()) << endl;
    cout << endl;
    cout << "\ttest.insert(&bar):\t\t"      << test.insert(&bar) << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.get():\t\t\t"           << test.get()        << endl;
    cout << "\ttest.get(this.getSize()):\t" << test.get(test.getSize()) << endl;
    cout << endl;
    cout << "\ttest.insert(&fu):\t\t"       << test.insert(&fu)  << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.get():\t\t\t"           << test.get()        << endl;
    cout << "\ttest.get(this.getSize()):\t" << test.get(test.getSize()) << endl;
    cout << endl;
    cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.get(this.getSize()):\t" << test.get(test.getSize()) << endl;
    cout << endl;
    cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << "\ttest.get(this.getSize()):\t" << test.get(test.getSize()) << endl;
    //below should not cause seg fault
    //it does anyway
    //cout << endl;
    //cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
    //cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    //cout << "\ttest.get(this.getSize()):\t" << test.get(test.getSize()) << endl;
    cout << "end" << endl;
    return 0;
}
