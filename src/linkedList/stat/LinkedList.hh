#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<cstdlib>
#include<cstdio>
#include<iostream>

#ifdef  DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define debug_print(fmt)\
        do{if(DEBUG_TEST) fprintf(stderr, "%s:%d:%s() " fmt, __FILE__,\
                          __LINE__,__func__);} while(0)

using std::cout;
using std::endl;

class LinkedList{
private:
    int data;
    int size;
    LinkedList *next;

    void init();
    bool inited;

public:
    LinkedList();

    LinkedList(int data);

    ~LinkedList();//looping infinitely

    // Insert new element into list, defaults at head.
    int insert(int data);

    // Insert new element into list, new element will be element number <index>.
    int insert(int data, int index);

    // Returns value of first element.
    // Requires protection by user.
    int get();

    // Returns value of element at <index>.
    // Requires protection by user.
    int get(int index);

    // Deletes and returns the value of head.
    int remove();

    // Deletes and returns the value of <index>.
    int remove(int index);

    // Returns the number of elements in the list.
    int getSize();
};

#endif

