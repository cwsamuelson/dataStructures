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

template <class T>
class queue{
private:
    template <class X>
    struct NODE{
        X data;
        struct NODE<X> *next;
    };

    NODE<T> *head;
    NODE<T> *tail;
    NODE<T> *cur;
    int size;

public:
    queue(){
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }

    queue(T data){
        if(data){
            this->head = new struct NODE<T>;
            this->head->data = data;
            this->tail = this->head;
            this->size = 1;
        }
    }

//    ~queue(){//looping infinitely

    bool enqueue(T data){
        // Critical failure, inconsistency detected.
        if((this->head == NULL && this->tail != NULL) || (this->head != NULL && this->tail == NULL)){
            debug_print("\tcritical failure\n");
            return false;
        }

        // List is empty, create first node with new data.
        if(this->head == NULL && this->tail == NULL && this->size == 0){
            debug_print("\tempty list\n");
            // Set up a new node and assign it to head and tail as the only existing node.
            this->cur = new struct NODE<T>;
            this->cur->data = data;
            this->cur->next = NULL;

            this->head = this->cur;
            this->tail = this->cur;
            this->cur = NULL;

            this->size = 1;
            // Success!
            return true;
        }

        // Normal list, insert at tail.
        if(this->tail != NULL){
            debug_print("\tnormal\n");
            this->cur = new struct NODE<T>;
            this->cur->data = data;
            this->cur->next = NULL; 
            this->tail->next = this->cur;
            this->tail = this->cur;
            this->cur = NULL;

            this->size++;
            // Success!
            return true;
        }

        // Execution should never reach this point, return failure when it does.
        return false;
    }

    T dequeue(){
        // Inconsistent.
        if((this->head != this->tail) && (this->size==1)){
            debug_print("\tcritical failure\n");
            return -1;
        }

        // List is empty.
        if(this->head == NULL && this->tail == NULL && this->size == 0){
            debug_print("\tlist is empty, no remove\n");
            return -1;
        }

        // One item remaining.
        if((this->head == this->tail) && (this->size == 1)){
            debug_print("\tremove size == 1\n");
            this->cur = this->head;
            int ret = this->cur->data;
            this->head = NULL;
            this->tail = NULL;
            delete this->cur;
            this->cur = NULL;
            this->size--;
            return ret;
        }

        // Normally populated.
        if(this->head != this->tail && this->size > 0){
            debug_print("normal remove\n");
            this->cur = this->head;
            int ret = this->cur->data;
            this->head = this->cur->next;
            delete this->cur;
            this->size--;
            return ret;
        }

        // Catch error.
        debug_print("\tfailure\n");
        return -1;//replace with error checking
    }

    T peek(){
    // Returns value of first element.
    // Requires protection by user.
        if(this->head == NULL){
            debug_print("\ttestnullehad\n");
            return -1;
        }else{
            debug_print("\ttestelse\n");
            return this->head->data;
        }
        if(this->size == 0){
            debug_print("\ttestsize0\n");
            return -2;
        }
        else
            return -3;
    }

    // Returns the number of elements in the list.
    int getSize(){
        return this->size;
    }

};

#endif
