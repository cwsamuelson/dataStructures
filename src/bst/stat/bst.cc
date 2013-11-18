#include"bst.hh"

void bst::init(){
    this->left = NULL;
    this->right = NULL;
    this->size = 0;
}

bst::bst(){
    init();
}

bst::bst(int key, int data){
    init();
    this->insert(key, data);
}

//    ~bst(){//looping infinitely
//        while(this->size > 0){
//            debug_print("\tcheck\n");
//            this->remove();
//        }
//    }

// Insert new element into list.
int bst::insert(int key, int data){
    // Critical failure, inconsistency detected.
    if((this->size < 0)
    || (this->size == 0 && (this->left != NULL || this->right != NULL))
    || (this->size > 1 && (this->left == NULL && this->right == NULL))){
        debug_print("\tcritical failure\n");
        debug_print("\tinconsistency detected\n");
        return -1;
    }

    // Tree is empty, create first node with new data.
    if(this->size == 0){
        debug_print("\tempty list\n");
        // Set up a new node and assign it to root and tail as the only existing node.
        this->key = key;
        this->data = data;
        this->left = NULL;
        this->right = NULL;

        this->size = 1;
        // Success!
        return data;
    }

    // Normal list.
    if(this->size > 0){
        debug_print("\tnormal\n");
        if(key < this->key){
            if(this->left == NULL){
                this->left = new bst(key, data);
            }
            else{
                this->left->insert(key, data);
            }
        }
        else if(key > this->key){
            if(this->right == NULL)
                this->right = new bst(key, data);
            else
                this->right->insert(key, data);
        }
        // Account for tree balance on the way up.
        this->size++;

        // Success!
        return data;
    }

    // Execution should never reach this point, return failure when it does.
    debug_print("\tcritical failure\n");
    return -2;
}

// Returns value of element at <index>.
int bst::get(int index){
    if(index == this->key){
        return this->data;
    }
    else if(index < this->key && this->left != NULL){
        return this->left->get(index);
    }
    else if(index > this->key && this->right != NULL){
        return this->right->get(index);
    }
    // Failure, no item found...handle this properly...
    return -1;
}

int bst::remove(int index){
    if(index == this->key){
        // no children
        if(this->left == NULL && this->right == NULL){
            // Clear for deletion.
            return -1;
        }
        // One child
        else if((this->left == NULL && this->right != NULL) || (this->left != NULL && this->right == NULL)){
            int ret;
            if(this->left != NULL){
                ret = (int)this->left;
            }
            else if(this->right != NULL){
                ret = (int)this->right;
            }
            return ret;
        }
        // Two child
        else if(this->left != NULL && this->right != NULL){
            return -2;
        }
    }
    else if(index < this->key){
        int res = this->left->remove(index);
        if(res == -1){
            delete this->left;
        }
        else if(res >= 0){
            bst *temp = this->left;
            this->left = (bst *)res;
            delete temp;
        }
    }
    else if(index > this->key){
        int res = this->right->remove(index);
        if(res == -1){
            delete this->right;
        }
        else if(res >= 0){
            bst *temp = this->right;
            this->right = (bst *)res;
            delete temp;
        }
    }
    this->size--;
    return -3;
}

    // Returns the number of elements in the list.
int bst::getSize(){
    return this->size;
}

int bst::getMin(){
    if(this->left){
        return this->left->getMin();
    }
    else{
        return this->data;
    }
}

int bst::getMax(){
    if(this->right){
        return this->right->getMax();
    }
    else{
        return this->data;
    }
}

bstException::bstException(){
    this->msg = NULL;
}

bstException::bstException(const char* nMsg){
    int len = 0;
    while(nMsg[len]){
        len++;
    }
    this->msg = (char *)malloc(sizeof(char) * len);
    for(int i = 0; i < len; i++){
        this->msg[i] = nMsg[i];
    }
}

bstException::~bstException(){
    free(this->msg);
}

const char* bstException::what() const throw(){
    if(!this->msg){
        return "BST error has occured!";
    }
    else{
        return this->msg;
    }
}

