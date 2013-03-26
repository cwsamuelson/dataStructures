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
    ~LinkedList(){
        while(this->head){
            this->remove();
        }
    }
    // Insert new element into list, defaults to the end.
    bool insert(T *data){
        // Critical failure, inconsistency detected.
        if((this->head == NULL && this->tail != NULL) || (this->head != NULL && this->tail == NULL)){
            cout << "failure" << endl;//debug
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
            this->cur = new struct NODE<T>;
            this->cur->data = data;
            this->cur->prev = this->tail;
            this->tail->next = this->cur;
            this->cur->next = NULL; 
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
        this->cur = NULL;
        return *this->cur->data;
    }

    // Deletes and returns the value of head.
    T remove(){
        // If size == 1.
        if((this->head != this->tail)&&(this->size==1)){
            cout << "critical failure" << endl;
            return 0;
        }
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
        if(this->size > 0){
            cout<<"test"<<endl;//debug
            this->cur = this->head;
            T ret = *this->cur->data;
            this->cur->next->prev = NULL;//fails here, need to put this code in an if statement.
            this->head = this->cur->next;
            delete this->cur;
            this->size--;
            return ret;
        }
        //if(){
            
        //}
    // Catch error.
        return 0;//replace with error checking
    }

    // Deletes and returns the value of <index>.
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
        return size;
    }

};

#endif
