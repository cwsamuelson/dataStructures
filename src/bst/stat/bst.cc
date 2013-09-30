#include"bst.hh"

using namespace std;

bst::bst(){
    this->left = NULL;
    this->right = NULL;
    this->size = 0;
}

bst::bst(int key, int data){
    this->key = key;
    this->data = data;
    this->left = NULL;
    this->right = NULL;
    this->size = 1;
}

//    ~bst(){//looping infinitely
//        while(this->size > 0){
//            debug_print("\tcheck\n");
//            this->remove();
//        }
//    }

// Insert new element into list.
int bst::insert(int key, int data){
    int ret;
    // Critical failure, inconsistency detected.
    if((this->size < 0)
    || (this->size == 0 && (this->left != NULL || this->right != NULL))
    || (this->size != 0 && (this->left == NULL && this->right == NULL))){
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
        return 0;
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
        return 0;
    }

    // Execution should never reach this point, return failure when it does.
    debug_print("\tcritical failure\n");
    return -1;
}

// Returns value of element at <index>.
int bst::get(int index){
    if(index == this->key){
        return this->data;
    }
    else if(index < this->key){
        return this->left->get(index);
    }
    else if(index > this->key){
        return this->right->get(index);
    }
    // Failure, no item found...handle this properly...
}

int bst::remove(int index){
    if(index == this->key){
        if(this->left == NULL && this->right == NULL){
            // Clear for deletion.
            return -2;
        }
        else if(this->left != NULL && this->right == NULL){
            // Sub-tree needs to be moved up before deleting node.
            return (int)this->left;
        }
        else if(this->left == NULL && this->right != NULL){
            // Sub-tree needs to be moved up before deleting node.
            return (int)this->right;
        }
    }
    else if(index < this->key){
        int res = this->left->remove(index);
        if(res == -2){
            delete this->left;
            this->size--;
        }
        else{
            bst *temp = this->left;
            this->left = (bst *)res;
            delete temp;
            this->size--;
        }
    }
    else if(index > this->key){
        int res = this->right->remove(index);
        if(res == -2){
            delete this->right;
            this->size--;
        }
        else{
            bst *temp = this->right;
            this->right = (bst *)res;
            delete temp;
            this->size--;
        }
    }
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

