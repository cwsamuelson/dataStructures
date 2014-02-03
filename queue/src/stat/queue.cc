#include"queue.hh"

void queue::init(){
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}
queue::queue(){
    this->init();
}

queue::queue(int data){
    this->init();
    this->enqueue(data);
}

//    ~queue(){//looping infinitely
//        while(this->size > 0){
//            debug_print("\tcheck\n");
//            this->remove();
//        }
//    }

int queue::enqueue(int data){
    // Critical failure, inconsistency detected.
    if((this->head == NULL && this->tail != NULL) || (this->head != NULL && this->tail == NULL)){
        debug_print("\tcritical failure\n");
        return -1;
    }

    // List is empty, create first node with new data.
    if(this->head == NULL && this->tail == NULL && this->size == 0){
        debug_print("\tempty list\n");
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

    // Normal list, insert at tail.
    if(this->tail != NULL){
        debug_print("\tnormal\n");
        this->cur = new struct NODE;
        this->cur->data = data;
        this->cur->next = NULL; 
        this->tail->next = this->cur;
        this->tail = this->cur;
        this->cur = NULL;

        this->size++;
        // Success!
        return data;
    }

    // Execution should never reach this point, return failure when it does.
    return -2;
}

int queue::dequeue(){
    // Inconsistent.
    if((this->head != this->tail) && (this->size==1)){
        debug_print("\tcritical failure\n");
        return -1;
    }

    // List is empty.
    if(this->head == NULL && this->tail == NULL && this->size == 0){
        debug_print("\tlist is empty, no remove\n");
        return -2;
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
    return -3;//replace with error checking
}

int queue::peek(){
// Returns value of first element.
// Requires protection by user.
    if(this->head == NULL){
        debug_print("\ttestnullhead\n");
        return -1;
    }else{
        debug_print("\ttestelse\n");
        return this->head->data;
    }
    if(this->size == 0){
        debug_print("\ttestsize0\n");
        return 0;
    }
    else
        return -2;
}

// Returns the number of elements in the list.
int queue::getSize(){
    return this->size;
}

