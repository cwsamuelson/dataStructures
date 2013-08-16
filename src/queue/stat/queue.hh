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

class queue{
private:
    struct NODE{
        int data;
        struct NODE *next;
    };

    NODE *head;
    NODE *tail;
    NODE *cur;
    int size;

public:
    queue();

    queue(int data);

//    ~queue(){//looping infinitely

    bool enqueue(int data);
    int dequeue();
    int peek();

    // Returns the number of elements in the list.
    int getSize();

};

#endif
