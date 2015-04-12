#include"list.hh"

gxy::list::list():head(0), tail(0), size(0){  }

gxy::list::~list(){
  while(!this->isEmpty()){
    this->popFront();
  }
}

void gxy::list::pushFront(char c){
  //Empty list
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->head->previous = new node(c, 0, this->head);
    this->head = this->head->previous;
  }
  this->size++;
}

void gxy::list::pushBack(char c){
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->tail->next = new node(c, this->tail, 0);
    this->tail = this->tail->next;
  }
  this->size++;
}

char gxy::list::popFront(){
  char ret;
  if(this->head == 0){
    ret = 0;
  } else if(this->head == this->tail){
    ret = this->head->data;
    delete this->head;
    this->head = this->tail = 0;
  } else {
    ret = this->head->data;
    this->head = this->head->next;
    delete this->head->previous;
  }
  this->size--;
  return ret;
}

char gxy::list::popBack(){
  char ret;
  if(this->tail == 0){
    ret = 0;
  } else if(this->head == this->tail){
    ret = this->head->data;
    delete this->head;
    this->head = this->tail = 0;
  } else {
    ret = this->tail->data;
    this->tail = this->tail->previous;
    delete this->tail->next;
  }
  this->size--;
  return ret;
}

gxy::iterator gxy::list::insert(gxy::iterator it, const char& val){
  list::node* tmp = new list::node(val, it.accessNode()->previous, it.accessNode());
  it.accessNode()->previous->next = tmp;
  it.accessNode()->previous = tmp;
  ++this->size;
  return iterator(it.accessNode()->previous);
}

gxy::iterator gxy::list::insert(gxy::iterator it, gxy::size_t n, const char& val){
  gxy::iterator tmp(it.accessNode()->previous);
  for(unsigned int i = 0; i < n; ++i){
    this->insert(it, val);
  }
  return tmp;
}

gxy::iterator gxy::list::insert(gxy::iterator it, gxy::iterator first, gxy::iterator last){
  gxy::iterator tmp(it.accessNode()->previous);
  for(auto itr = first; itr != last; ++itr){
    this->insert(it, *itr);
  }
  return tmp;
}

gxy::iterator gxy::list::erase(gxy::iterator it){
  gxy::iterator tmp(it.accessNode()->next);
  it.accessNode()->previous = it.accessNode()->next;
  it.accessNode()->next = it.accessNode()->previous;
  delete it.accessNode();
  return tmp;
}

gxy::iterator gxy::list::erase(gxy::iterator first, gxy::iterator last){
  gxy::iterator tmp;
  for(auto it = first; it != last; ++it){
    tmp = this->erase(it);
  }
  return gxy::iterator(tmp);
}

char& gxy::list::get(unsigned int idx){
  return this->head->get(idx);
}

const char& gxy::list::get(unsigned int idx) const{
  return this->get(idx);
}

gxy::iterator gxy::list::begin(){
  return gxy::iterator(this->head);
}

gxy::iterator gxy::list::end(){
  return gxy::iterator(0);
}

unsigned int gxy::list::length(){
  return this->size;
}

unsigned int gxy::list::length() const{
  return this->length();
}

bool gxy::list::isEmpty(){
  return this->size == 0;
}

char& gxy::list::operator[](unsigned int idx){
  return this->get(idx);
}

//Iterator implementation
gxy::iterator::iterator():ptr(0){
}

gxy::iterator::iterator(const gxy::iterator& that):ptr(that.ptr){
}

gxy::iterator::iterator(gxy::list::node* that):ptr(that){
}

gxy::iterator& gxy::iterator::operator=(const gxy::iterator& rhs){
  this->ptr = rhs.ptr;
  return *this;
}

gxy::iterator& gxy::iterator::operator++(){
  if(this->ptr){
    this->ptr = this->ptr->next;
  }
  return *this;
}

gxy::iterator gxy::iterator::operator++(int){
  gxy::iterator tmp(*this);
  ++(*this);
  return tmp;
}

gxy::iterator& gxy::iterator::operator--(){
 if(this->ptr){
    this->ptr = this->ptr->previous;
  }
  return *this;
}

gxy::iterator gxy::iterator::operator--(int){
  gxy::iterator tmp(*this);
  --(*this);
  return tmp;
}

char& gxy::iterator::operator*(){
  return this->ptr->data;
}

char* gxy::iterator::operator->(){
  return &(this->ptr->data);
}

bool gxy::operator==(const gxy::iterator& lhs, const gxy::iterator& rhs){
  return lhs.ptr == rhs.ptr;
}

gxy::list::node*& gxy::iterator::accessNode(){
  return this->ptr;
}

//node implementation
gxy::list::node::node(const char& c):data(c), previous(0), next(0){
}

gxy::list::node::node(const char& c, list::node* p, list::node* n):data(c), previous(p), next(n){ 
}

char& gxy::list::node::get(unsigned int idx){
  char ret;
  if(idx == 0){
    ret = this->data;
  } else {
    ret = this->next->get(idx - 1);
  }
  char& tmp = ret;
  return tmp;
}

