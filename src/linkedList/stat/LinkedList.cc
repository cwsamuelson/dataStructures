#include"LinkedList.hh"

void LinkedList::init(){
    this->inited = false;
    this->data = 0;
    this->next = NULL;
    this->size = 0;
}

LinkedList::LinkedList(){
    this->init();
}

LinkedList::LinkedList(int data){
    this->init();
    this->insert(data);
}

//LinkedList::~LinkedList(){//looping infinitely
//    debug_print("\tRemoving\n");
//    while(this->size > 0){
//        printf("%d\n", this->size);
//        debug_print("\t\tNext\n");
//        this->remove();
//    }
//}

    // Insert new element into list, defaults to the end.
int LinkedList::insert(int data){
    return this->insert(data, 0);
}

    // Insert new element into list, new element will be element number <index>.
//should return resultant node
int LinkedList::insert(int data, int index){
    //insert order is being weird
    // Bad index value.
    if(index > this->size){
        printf("idx:%d, size:%d\n", index, this->size);
        debug_print("\tBad index\n");
        return -1;
    }

    if(this->inited == false){
        this->data = data;
        this->size++;
        this->inited = true;
        return data;
    }

    // List is empty, create first node with new data.
    if(index == 0){
        LinkedList *temp = new LinkedList(this->data);
        temp->next = this->next;
        temp->size = this->size;
        this->data = data;
        this->next = temp;
        this->size++;
        return data;
    }else if(this->next != NULL){
        this->next->insert(data, index - 1);
        this->size++;
        return data;
    }else{
        this->next = new LinkedList(data);
        return data;
    }
    // Execution should never reach this point, return failure when it does.
    return -3;
}

    // Returns value of first element.
    // Requires protection by user.
int LinkedList::get() const{
    return this->get(0);
}

    // Returns value of element at <index>.
    // Requires protection by user.
int LinkedList::get(int index) const{
    if(index == 0){
        return this->data;
    }else if(this->next != NULL){
        return this->next->get(index - 1);
    }
    return -3;
}

    // Deletes and returns the value of head.
int LinkedList::remove(){
    return this->remove(0);
}

    // Deletes and returns the value of <index>.
int LinkedList::remove(int index){
    //insert order is being weird
    // Bad index value.
    if(index > this->size){
        printf("idx:%d, size:%d\n", index, this->size);
        debug_print("\tBad index\n");
        return -1;
    }

    if(index == 0){
        int ret = this->data;
        if(this->next != NULL){
            LinkedList *temp = this->next;
            this->data = temp->data;
            this->size = temp->size;
            this->next = temp->next;
            this->size--;
            delete temp;
        }else{
            this->data = 0;
            this->size--;
            this->inited = false;
        }
        return ret;
    }else{
        return this->next->remove(index - 1);
    }
    // Execution should never reach this point, return failure when it does.
    return -3;
}

    // Returns the number of elements in the list.
int LinkedList::getSize() const{
    return this->size;
}

