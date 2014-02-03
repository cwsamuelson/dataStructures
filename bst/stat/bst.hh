#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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

class bst{
private:
    int data;
    int key;
    bst *left;
    bst *right;
    int size;
    void init();

public:
    bst();

    bst(int key, int data);

//    ~bst(){//looping infinitely

    // Insert new element into list, defaults to the end.
    int insert(int key, int data);

    // Returns value of element at <key>.
    // Requires protection by user.
    int get(int key);

    // Deletes and returns the value of <index>.
    int remove(int key);

    // Returns the number of elements in the list.
    int getSize();

    // Finds the minimum value in the tree.
    int getMin();

    // Finds the Maximum value in the tree.
    int getMax();

};

class bstException{
private:
    char* msg;

public:
    bstException();
    bstException(const char* nMsg);
    ~bstException();
    virtual const char* what() const throw();

};

#endif

