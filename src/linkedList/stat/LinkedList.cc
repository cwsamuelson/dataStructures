#include"LinkedList.hh"

void LinkedList::init(){
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

LinkedList::LinkedList(){
    this->init();
}

LinkedList::LinkedList(int data){
    this->init();
    this->insert(data);
}

//    ~LinkedList(){//looping infinitely
//        while(this->size > 0){
//            debug_print("\tcheck\n");
//            this->remove();
//        }
//    }

    // Insert new element into list, defaults to the end.
int LinkedList::insert(int data){
    return this->insert(data, 0);
}

    // Insert new element into list, new element will be element number <index>.
int LinkedList::insert(int data, int index){
    //insert order is being weird
    // Bad index value.
    if(index > this->size){
        debug_print("\tbad index\n");
        return -1;
    }

    // Critical failure, inconsistency.
    if((this->head == NULL && this->tail != NULL) || (this->head != NULL && this->tail == NULL)){
        debug_print("\tcritical failure\n");
        return -2;
    }

    // List is empty, create first node with new data.
    if(this->head == NULL && this->tail == NULL && this->size == 0){
        debug_print("\tempty insert\n");
        // Set up a new node and assign it to head and tail as the only existing node.
        this->cur = new struct NODE;
        this->cur->data = data;
        this->cur->next = NULL;

        this->head = this->cur;
        this->tail = this->cur;
        this->cur = NULL;

        this->size = 1;
        // Success!
        return data;
    }

    if(this->head != NULL){
        struct NODE *back = NULL;
        debug_print("\tnormal insert\n");
        // Start at head.
        // Find insert point.
        this->cur = this->head;
        for(int i = 0; i < index; i++){
            if(this->cur->next){
                back = this->cur;
                this->cur = this->cur->next;
            }
        }
        // Insert new node.
        struct NODE *temp = new struct NODE;
        if(back != NULL){
            back->next = temp;
        }
        temp->data = data;
        temp->next = this->cur;
        this->cur = NULL;

        this->size++;
        // Success!
        return data;
    }
    // Execution should never reach this point, return failure when it does.
    return -3;
}

    // Returns value of first element.
    // Requires protection by user.
int LinkedList::get(){
    return this->get(0);
}

    // Returns value of element at <index>.
    // Requires protection by user.
int LinkedList::get(int index){
    if(this->head == NULL){
        debug_print("\ttestnullhead\n");
        return -1;
    }
    if(this->size == 0){
        debug_print("\ttestsize0\n");
        return -2;
    }
    if(index == 0){
        return this->head->data;
    }

    this->cur = this->head;
    for(int i = 0; i < index; i++){
        if(this->cur->next){
            this->cur = this->cur->next;
        }
    }
    int ret = this->cur->data;
    this->cur = NULL;
    return ret;
}

    // Deletes and returns the value of head.
int LinkedList::remove(){
    return this->remove(0);
}

    // Deletes and returns the value of <index>.
int LinkedList::remove(int index){
    if(this->head == NULL && this->tail != NULL){
        debug_print("\tcritical failure\n");
        return -1;
    }
    // Inconsistent.
    if((this->head != this->tail)&&(this->size==1)){
        debug_print("\tcritical failure\n");
        return -1;
    }

    // List is empty.
    if(this->head == NULL && this->tail == NULL && this->size == 0){
        debug_print("\tlist is empty, no remove\n");
        return -2;
    }

    // One item remaining.
    if((this->head == this->tail)&&(this->size == 1)){
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

    // Index is head.
    if(index == 0){
        debug_print("\tindex head\n");
        this->cur = this->head;
        int ret = this->cur->data;
        this->head = this->cur->next;
        delete this->cur;
        this->cur = NULL;
        this->size--;
        return ret;
    }else// Index is tail.
    if(index == this->size - 1){
        debug_print("\tindex tail\n");
        this->cur = this->tail;
        int ret = this->cur->data;
        delete this->cur;
        this->size--;
        return ret;
    }else{// Index is normal.
        debug_print("\tindex normal\n");
        this->cur = this->head;
        for(int i = 0; i < index; i++){
            if(this->cur->next){
                this->cur = this->cur->next;
            }
        }
        int ret = this->cur->data;
        delete this->cur;
        this->size--;
        return ret;
    }
    // Catch error.
    debug_print("\tfailure\n");
    return -3;//replace with error checking
}

    // Returns the number of elements in the list.
int LinkedList::getSize(){
    return this->size;
}

