#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<cstdlib>
#include<iostream>
using namespace std;

template <class T>
class LinkedList{
private:
    template <class X>
    struct NODE{
        X *data;
        struct NODE<X> *prev;
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
//            //cout << "check" << endl;
//            this->remove();
//        }
//    }
    // Insert new element into list, defaults to the end.
    bool insert(T *data){
        // Critical failure, inconsistency detected.
        if((this->head == NULL && this->tail != NULL) || (this->head != NULL && this->tail == NULL)){
            cout << "critical failure" << endl;//debug
            return false;
        }

        // List is empty, create first node with new data.
        if(this->head == NULL && this->tail == NULL){
            // Set up a new node and assign it to head and tail as the only existing node.
            this->cur = new struct NODE<T>;
            this->cur->data = data;
            this->cur->prev = NULL;
            this->cur->next = NULL;

            this->head = this->cur;
            this->tail = this->cur;
            this->cur = NULL;

            this->size = 1;
            // Success!
            return true;
        }

        // Normal list, insert at tail.
        if(this->tail){
            //cout << "test" << endl;
            this->cur = new struct NODE<T>;
            this->cur->data = data;
            this->cur->prev = this->tail;
            this->tail->next = this->cur;
            this->cur->next = NULL; 
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
                temp.prev = this.cur;
                temp.next = this.cur.next;
                temp.next.prev = temp;
                temp.prev.next = temp;
                this.cur = NULL;

                this.size++;
                // Success!
                return true;
            }
        }
    }

    // Returns value of first element.
    T get(){
        if(this->head != NULL){
            return *this->head->data;
        }
        else
            return 0;//replace with error testing
    }

    // Returns value of element at <index>.
    T get(int index){
        this->cur = this->head;
        for(int i = 0; i < index; i++){
            if(this->cur->next){
                this->cur = this->cur->next;
            }
        }
        T ret = *this->cur->data;
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
            cout << "critical failure" << endl;
            return 0;
        }
        // One item remaining.
        if((this->head == this->tail)&&(this->size == 1)){
            cout << "\tremove size == 1" << endl;//debug
            this->cur = this->head;
            T ret = *this->cur->data;
            this->head = NULL;
            this->tail = NULL;
            delete this->cur;
            this->cur = NULL;
            this->size--;
            return ret;
        }
        // List is empty.
        if(this->head == NULL && this->tail == NULL && this->size == 0){
            cout << "list is empty!" << endl;
            return 0;
        }
        // Normally populated.
        if(this->head != this->tail && this->size > 0){
            //cout << "normal remove" << endl;
            this->cur = this->head;
            T ret = *this->cur->data;
            this->cur->next->prev = NULL;
            this->head = this->cur->next;
            delete this->cur;
            this->size--;
            return ret;
        }
        // Catch error.
        cout << "\tfailure" << endl;
        if(this->head == this->tail){
            cout << "fuck" << endl;
        }
        return 0;//replace with error checking
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
            cout << "check 0" << endl;//debug
            return this->remove();
        }else
        // Index is tail.
        if(index == this->size - 1){
            cout << "tail" << endl;//debug
            this->cur = this->tail;
            T ret = *this->cur->data;
            this->cur->prev->next = NULL;
            this->tail = this->cur->prev;
            delete this->cur;
            this->size--;
            return ret;
        }else{// Index is normal.
            cout << "normal" << endl;//debug
            for(int i = 0; i < index; i++){
                if(this->cur->next){
                    this->cur = this->cur->next;
                }
            }
            T ret = *this->cur->data;
            this->cur->next->prev = this->cur->prev;
            this->cur->prev->next = this->cur->next;
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
