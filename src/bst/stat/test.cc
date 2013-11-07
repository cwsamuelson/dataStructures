#include"bst.hh"
#include<iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv){
    cout << "start" << endl;
    int number = 4;
    bst test;

    cout << "\ttest.getSize():\t\t\t"       << test.getSize()   << endl;
    cout << endl;
    for(int i = 0; i < number; i++){
        cout << "\ttest.insert(" << i << "):\t\t\t"   << test.insert(i, i)    << endl;
        cout << "\ttest.getSize():\t\t\t"   << test.getSize()               << endl;
        for(int j = 0; j < i; j++){
            cout << "\ttest.get(" << j << "):\t\t\t"       << test.get(j)   << endl;
        }
        cout << "\ttest.getMin():\t\t\t" << test.getMin() << endl;
        cout << "\ttest.getMax():\t\t\t" << test.getMax() << endl;
        cout << endl;
    }
    cout << endl;
    for(int i = number - 1; i > 0; i--){
        cout << "\ttest.remove(" << i << "):\t\t\t" << test.remove(i)       << endl;
        cout << "\ttest.getSize():\t\t\t"   << test.getSize()               << endl;
        cout << "\ttest.get(" << i << "):\t\t\t"       << test.get(i)       << endl;
        cout << endl;
    }
    cout << endl;
    cout << "end" << endl;

    return 0;
}
