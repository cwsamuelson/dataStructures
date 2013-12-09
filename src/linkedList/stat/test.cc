#include"LinkedList.hh"
#include<iostream>

using namespace std;

void testNorm(int number);
void testRef(int number);
void testMallocFree(int number);
void testNewDel(int number);

int main(int argc, char **argv){
    cout << "start" << endl;
    int number = 5;

//    testNorm(number);
//    testRef(number);
//    testMallocFree(number);
//    testNewDel(number);

    cout << "end" << endl;
    return 0;
}

void testNewDel(int number){
    cout << "start testing new/del" << endl;
    LinkedList *foo1;
    foo1 = new LinkedList();

    cout << "\tfoo1->getSize():\t\t\t"       << foo1->getSize()    << endl;
    cout << endl;
    for(int i = 0; i <= number; ++i){
        cout << "\tfoo1->insert(" << i << "):\t\t\t"      << foo1->insert(i) << endl;
        cout << "\tfoo1->getSize():\t\t\t"       << foo1->getSize()    << endl;
        cout << "\tfoo1->get():\t\t\t"           << foo1->get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= foo1->getSize(); ++j){
            cout << "\tfoo1->get(" << j << "):\t\t\t"           << foo1->get(j)       << endl;
        }
        cout << "\tfoo1->get(foo1->getSize()):\t" << foo1->get(foo1->getSize()) << endl;
        cout << endl;
    }
    cout << endl;
    // Remove one more than exists
    for(int i = 0; i <= number; ++i){
        cout << "\tfoo1->remove():\t\t\t"        << foo1->remove()     << endl;
        cout << "\tfoo1->getSize():\t\t\t"       << foo1->getSize()    << endl;
        cout << "\tfoo1->get():\t\t\t"           << foo1->get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= foo1->getSize(); ++j){
            cout << "\tfoo1->get(" << j << "):\t\t\t"           << foo1->get(j)       << endl;
        }
        cout << "\tfoo1->get(foo1->getSize()):\t" << foo1->get(foo1->getSize()) << endl;
        cout << endl;
    }

    delete foo1;
    cout << "end testing new/del" << endl;
}

void testMallocFree(int number){
    cout << "start testing malloc/free" << endl;
    void *mem = malloc(sizeof(LinkedList));
    LinkedList *bar1 = new (mem)LinkedList();

    cout << "\tbar1->getSize():\t\t\t"       << bar1->getSize()    << endl;
    cout << endl;
    for(int i = 0; i <= number; ++i){
        cout << "\tbar1->insert(" << i << "):\t\t"      << bar1->insert(i) << endl;
        cout << "\tbar1->getSize():\t\t"       << bar1->getSize()    << endl;
        cout << "\tbar1->get():\t\t\t"           << bar1->get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= bar1->getSize(); ++j){
            cout << "\tbar1->get(" << j << "):\t\t\t"           << bar1->get(j)       << endl;
        }
        cout << "\tbar1->get(bar1->getSize()):\t" << bar1->get(bar1->getSize()) << endl;
        cout << endl;
    }
    cout << endl;
    // Remove one more than exists
    for(int i = 0; i <= number; ++i){
        cout << "\tbar1->remove():\t\t\t"        << bar1->remove()     << endl;
        cout << "\tbar1->getSize():\t\t"       << bar1->getSize()    << endl;
        cout << "\tbar1->get():\t\t\t"           << bar1->get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= bar1->getSize(); ++j){
            cout << "\tbar1->get(" << j << "):\t\t\t"           << bar1->get(j)       << endl;
        }
        cout << "\tbar1->get(bar1->getSize()):\t" << bar1->get(bar1->getSize()) << endl;
        cout << endl;
    }

    bar1->~LinkedList();
    free(bar1);
    cout << "end testing malloc/free" << endl;
}

void testRef(int number){
    cout << "start testing by reference" << endl;
    LinkedList temp;
    LinkedList &baz1 = temp;

    cout << "\tbaz1.getSize():\t\t\t"       << baz1.getSize()    << endl;
    cout << endl;
    for(int i = 0; i <= number; ++i){
        cout << "\tbaz1.insert(" << i << "):\t\t\t"      << baz1.insert(i) << endl;
        cout << "\tbaz1.getSize():\t\t\t"       << baz1.getSize()    << endl;
        cout << "\tbaz1.get():\t\t\t"           << baz1.get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= baz1.getSize(); ++j){
            cout << "\tbaz1.get(" << j << "):\t\t\t"           << baz1.get(j)       << endl;
        }
        cout << "\tbaz1.get(baz1.getSize()):\t" << baz1.get(baz1.getSize()) << endl;
        cout << endl;
    }
    cout << endl;
    // Remove one more than exists
    for(int i = 0; i <= number; ++i){
        cout << "\tbaz1.remove():\t\t\t"        << baz1.remove()     << endl;
        cout << "\tbaz1.getSize():\t\t\t"       << baz1.getSize()    << endl;
        cout << "\tbaz1.get():\t\t\t"           << baz1.get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= baz1.getSize(); ++j){
            cout << "\tbaz1.get(" << j << "):\t\t\t"           << baz1.get(j)       << endl;
        }
        cout << "\tbaz1.get(baz1.getSize()):\t" << baz1.get(baz1.getSize()) << endl;
        cout << endl;
    }
    //baz1.~LinkedList();
    cout << "end testing by reference" << endl;
}

void testNorm(int number){
    cout << "start testing normal" << endl;
    LinkedList test;
    cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
    cout << endl;
    for(int i = 0; i <= number; ++i){
        cout << "\ttest.insert(" << i << "):\t\t\t"      << test.insert(i) << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.get():\t\t\t"           << test.get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= test.getSize(); ++j){
            cout << "\ttest.get(" << j << "):\t\t\t"           << test.get(j)       << endl;
        }
        cout << "\ttest.get(test.getSize()):\t" << test.get(test.getSize()) << endl;
        cout << endl;
    }
    cout << endl;
    // Remove one more than exists
    for(int i = 0; i <= number; ++i){
        cout << "\ttest.remove():\t\t\t"        << test.remove()     << endl;
        cout << "\ttest.getSize():\t\t\t"       << test.getSize()    << endl;
        cout << "\ttest.get():\t\t\t"           << test.get()       << endl;
        // Get one more than exists
        for(int j = 0; j <= test.getSize(); ++j){
            cout << "\ttest.get(" << j << "):\t\t\t"           << test.get(j)       << endl;
        }
        cout << "\ttest.get(test.getSize()):\t" << test.get(test.getSize()) << endl;
        cout << endl;
    }
    cout << "end testing normal" << endl;
    cout << endl;
}

