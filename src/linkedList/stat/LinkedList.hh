#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<cstdlib>
#include<cstdio>

#ifdef  DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define debug_print(fmt)\
        do{if(DEBUG_TEST) fprintf(stderr, "%s:%d:%s() " fmt, __FILE__,\
                          __LINE__,__func__);} while(0)

class LinkedList{
private:
    int data;
    int size;
    bool inited;
    LinkedList *next;

    void init();

public:
    LinkedList();

    LinkedList(int data);

//    ~LinkedList();//looping infinitely

    // Insert new element into list, defaults at head.
    int insert(int data);

    // Insert new element into list, new element will be element number <index>.
    int insert(int data, int index);

    // Returns value of first element.
    // Requires protection by user.
    int get() const;

    // Returns value of element at <index>.
    // Requires protection by user.
    int get(int index) const;

    // Deletes and returns the value of head.
    int remove();

    // Deletes and returns the value of <index>.
    int remove(int index);

    void swap(int A,int B);
    void copy();

    // Returns the number of elements in the list.
    int getSize() const;
};

#endif

