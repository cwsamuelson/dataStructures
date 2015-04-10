#include"list.hpp"

list::list():length(0){  }

void list::pushFront(char c){
  //Empty list
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->head->previous = new node(c);
    this->head = this->head->previous;
  }
  this->length++;
}

void list::pushBack(char c){
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->tail->next = new node(c);
    this->tail = this->tail->next;
  }
  this->length++;
}

char list::popFront(){
  char ret;
  if(this->head == 0){
    ret = 0;
  } else {
    ret = this->head->data;
    this->head = this->head->next;
    delete this->head->previous;
  }
  this->length--;
  return ret;
}

char list::popBack(){
  char ret;
  if(this->tail == 0){
    ret = 0;
  } else {
    ret = this->tail->data;
    this->tail = this->tail->previous;
    delete this->tail->next;
  }
  this->length--;
  return ret;
}

char list::get(unsigned int idx){
  return this->head->get(idx);
}

iterator list::begin(){
  return iterator(this->head);
}

iterator list::end(){
  return iterator(0);
}

unsigned int list::length(){
  return this->length;
}

bool list::isEmpty(){
  return this->length == 0;
}

char& list::operator[](unsigned int idx){
  return this->get(idx);
}

