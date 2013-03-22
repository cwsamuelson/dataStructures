#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<cstdlib>

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
        this.head = NULL;
        this.tail = NULL;
        this.size = 0;
    }
    LinkedList(T *data){
        if(data){
            this.head = new struct NODE<T>;
            this.head.data = data;
            this.tail = this.head;
            this.size = 1;
        }
    }
    ~LinkedList(){
        
    }
    // Insert new element into list, defaults to the end.
    bool insert(T *data){
        // Critical failure, inconsistency detected.
        if((this.head = NULL && this.tail) || (this.head && this.tail == NULL)){
            return false;
        }

        // List is empty, create first node with new data.
        if(this.head = NULL && this.tail = NULL){
            // Set up a new node and assign it to head and tail as the only existing node.
            this.cur = new struct NODE<T>;
            this.cur.data = data;
            this.cur.prev = NULL;
            this.cur.next = NULL;

            this.head = this.cur;
            this.tail = this.cur;
            this.cur = NULL;

            this.size = 1;
            // Success!
            return true;
        }

        // Normal list, insert at tail.
        if(this.tail){
            this.cur = new struct NODE<T>;
            this.cur.data = data;
            this.cur.prev = this.cur.tail;
            this.tail.next = this.cur;
            this.cur.next = NULL; 
            this.cur = NULL;

            this.size = 1;
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

        if(this.head){
            this.cur = this.head;
            // Set cur determined by insertion point.
            for(int i = 0; i < index; i++){
                if(this.cur.next)
                    this.cur = this.cur.next;
            }
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
        return *this.head.data;
    }

    // Returns value of element at <index>.
    T get(int index){
        for(int i = 0; i < index; i++){
            if(this.cur.next)
                this.cur = this.cur.next;
        }
        return *this.cur.data;
    }

    // Deletes and returns the value of head.
    T remove(){
        
    }

    // Deletes and returns the value of <index>.
    T remove(int index){
        if(index == 0){
            return this.remove();
        }
    }

    // Returns the number of elements in the list.
    int getSize(){
        return size;
    }

};

#endif
