#include"list.hh"

list::list():head(0), tail(0), size(0){  }

list::~list(){
  while(!this->isEmpty()){
    this->popFront();
  }
}

void list::pushFront(char c){
  //Empty list
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->head->previous = new node(c, 0, this->head);
    this->head = this->head->previous;
  }
  this->size++;
}

void list::pushBack(char c){
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->tail->next = new node(c, this->tail, 0);
    this->tail = this->tail->next;
  }
  this->size++;
}

char list::popFront(){
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

char list::popBack(){
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

char& list::get(unsigned int idx){
  return this->head->get(idx);
}

iterator list::begin(){
  return iterator(this->head);
}

iterator list::end(){
  return iterator(0);
}

unsigned int list::length(){
  return this->size;
}

bool list::isEmpty(){
  return this->size == 0;
}

char& list::operator[](unsigned int idx){
  return this->get(idx);
}

