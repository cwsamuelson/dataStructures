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

using namespace std;

template <class T>
class LinkedList{
private:
    template <class X>
    struct NODE{
        X *data;
        struct NODE<X> *next;
    };

    NODE<T> *head;
    NODE<T> *tail;
    NODE<T> *cur;
    int size;

public:
    LinkedList(){
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }

    LinkedList(T *data){
        if(data){
            this->head = new struct NODE<T>;
            this->head->data = data;
            this->tail = this->head;
            this->size = 1;
        }
    }
//    ~LinkedList(){//looping infinitely
//        while(this->size > 0){
//            debug_print("\tcheck\n");
//            this->remove();
//        }
//    }
    // Insert new element into list, defaults to the end.
    bool insert(T *data){
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
    // Insert new element into list, new element will be element number <index>.
    bool insert(T *data, int index){
        // Bad index value.
        if(index > this.size){
            return false;
        }

        // Critical failure, inconsistency detected.
        if((this.head = NULL && this.tail) || (this.head && this.tail == NULL)){
            return false;
        }

        // Normal list.
        if(this.head){
            this.cur = this.head;
            // Find insert point.
            for(int i = 0; i < index; i++){
                if(this.cur.next)
                    this.cur = this.cur.next;
            }
            // Insert new node.
            if(this.tail){
                struct NODE<T> temp = new struct NODE<T>;
                temp.data = data;
                temp.next = this.cur.next;
                this.cur = NULL;

                this.size++;
                // Success!
                return true;
            }
        }
    }

    // Returns value of first element.
    T* get(){
        if(this->head == NULL){
            debug_print("\ttestnullehad\n");
            return NULL;
        }else{
            debug_print("\ttestelse\n");
            return this->head->data;
        }
        if(this->size == 0){
            debug_print("\ttestsize0\n");
            return NULL;
        }
        else
            return NULL;
    }

    // Returns value of element at <index>.
    T* get(int index){
        if(index == 0){
            debug_print("\tindex is 0! \n");
            return NULL;
        }
        this->cur = this->head;
        for(int i = 0; i < index; i++){
            if(this->cur->next){
                this->cur = this->cur->next;
            }
        }
        T *ret = this->cur->data;
        this->cur = NULL;
        return ret;
    }

    // Deletes and returns the value of head.
    // Cases necessary:
    //   1. Inconsistencies.
    //   2. One item in list.
    //   3. No items remaining.
    //   4. Normally populated list.
    T remove(){
        // Inconsistent.
        if((this->head != this->tail)&&(this->size==1)){
            debug_print("\tcritical failure\n");
            return -1;
        }

        // List is empty.
        if(this->head == NULL && this->tail == NULL && this->size == 0){
            debug_print("\tlist is empty, no remove\n");
            return -1;
        }

        // One item remaining.
        if((this->head == this->tail)&&(this->size == 1)){
            debug_print("\tremove size == 1\n");
            this->cur = this->head;
            T ret = *this->cur->data;
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
            T ret = *this->cur->data;
            this->head = this->cur->next;
            delete this->cur;
            this->size--;
            return ret;
        }

        // Catch error.
        debug_print("\tfailure\n");
        return -1;//replace with error checking
    }

    // Deletes and returns the value of <index>.
    // Cases to check:
    // 1.Check valid index
    // 2.Index is head
    // 3.Index is tail
    // 4.Normal index
    // 4a.Find correct node
    // 4b.Isolate node
    // 4c.Connect sibling nodes
    // 4d.Delete isolated node
    T remove(int index){
        // Index is head.
        if(index == 0){
            debug_print("\tcheck 0\n");
            return this->remove();
        }else
        // Index is tail.
        if(index == this->size - 1){
            debug_print("\ttail\n");
            this->cur = this->tail;
            T ret = *this->cur->data;
            delete this->cur;
            this->size--;
            return ret;
        }else{// Index is normal.
            debug_print("\tnormal\n");
            for(int i = 0; i < index; i++){
                if(this->cur->next){
                    this->cur = this->cur->next;
                }
            }
            T ret = *this->cur->data;
            delete this->cur;
            this->size--;
            return ret;
        }
    }

    // Returns the number of elements in the list.
    int getSize(){
        return this->size;
    }

};

#endif
