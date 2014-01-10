#include"list.hh"

using namespace Jing;

void list::init(){
    this->inited = false;
    this->data = 0;
    this->next = NULL;
    this->last = NULL;
    this->size = 0;
    this->max_size = -1;
}

list::list(){
    this->init();
}

explicit list::list(size_t n){
    this->init();
    this->max_size = n;
}

// Copy x
list::list(const list& x){
    this->init();
}

// Move x
list::list(const list&& x){
    this->init();
}

list::~list(){
}

list& list::operator=(const list& x){
}

list& list::operator=(list&& x){
}

bool list::empty() const noexcept{
    if(this->size == 0)
        return true;
    else
        return false;
}

size_t list::size() const noexcept{
    return this->size;
}

void list::assign(size_t n, const T& val){
}

void list::push_front(const T& val){
    this->insert(0, val);
}

void list::push_front(T&& val){
    //may want to reference the other overload
    this->insert(0, val);
}

void list::pop_front(){
    this->erase(0);
}

void list::push_back(const T& val){
    this->insert(this->size(), val);
}

void list::push_front(T&& val){
    this->insert(this->size(), val);
}

void list::pop_back(){
    this->erase(this->size()-1);
}

list& list::erase(size_t n){
}

list& list::erase(size_t first, size_t last){
}

void list::swap(list& x){
}

void list::swap(size_t a, size_t b){
}

void list::clear() noexcept{
}

void list::splice(size_t n, list& x){
}

void list::splice(size_t n, list&& x){
}

void list::splice(size_t n, list& x, size_t i){
}

void list::splice(size_t n, list&& x, size_t i){
}

void list::splice(size_t n, list& x, size_t i, size_t first, size_t last){
}

void list::splice(size_t n, list&& x, size_t i, size_t first, size_t last){
}

void list::remove(const T& val){
}

void list::unique(){
}

void list::sort(){
}

void list::reverse() noexcept{
}

list::~list(){
    while(this->size > 0){
        printf("%d\n", this->size);
        this->remove();
    }
}

bool list::empty() const{
    if(this->size == 0)
        return true;
    else
        return false;
}

size_t list::size() const{
    return this->size;
}

size_t list::max_size() const{
    return this->maxSize;
}

    // Insert new element into list, defaults to the end.
int list::insert(int data){
    return this->insert(data, 0);
}

    // Insert new element into list, new element will be element number <index>.
//should return resultant node
int list::insert(int data, int index){
    //insert order is being weird
    // Bad index value.
    if(index > this->size){
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
        list *temp = new list(this->data);
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
        this->next = new list(data);
        return data;
    }
    // Execution should never reach this point, return failure when it does.
    return -3;
}

    // Returns value of first element.
    // Requires protection by user.
int list::get(int *data) const{
    return this->get(data, 0);
}

int list::get(int *data, int index) const{
    if(index == 0){
        *data = this->data;
        return 0;
    }else if(this->next != NULL){
        this->next->get(data, index - 1);
        return 0;
    }
    return -3;
}

int list::remove(){
    return this->remove(0);
}

int list::remove(int index){
    // Bad index value.
    if(index > this->size){
        debug_print("\tBad index\n");
        return -1;
    }

    if(index == 0){
        int ret = this->data;
        if(this->next != NULL){
            list *temp = this->next;
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


