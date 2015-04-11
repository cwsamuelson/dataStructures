#include"iterator.hh"

iterator::iterator():ptr(0){
}

iterator::iterator(const iterator& that):ptr(that.ptr){
}

iterator::iterator(node* that):ptr(that){
}

bool iterator::hasNext(){
  if(ptr == 0){
    return false;
  } else {
    return this->ptr->next != 0;
  }
}

char iterator::next(){
  if(this->ptr != 0){
    if(this->ptr->next != 0){
      this->ptr = this->ptr->next;
    }
    return this->ptr->data;
  } else {
    return 0;
  }
}

char iterator::remove(){
    
}
  
iterator& iterator::operator++(){
  if(this->ptr){
    this->ptr = this->ptr->next;
  }
  return *this;
}

iterator& iterator::operator++(int){
  iterator tmp(*this);
  ++(*this);
  return tmp;
}

iterator& iterator::operator--(){
 if(this->ptr){
    this->ptr = this->ptr->previous;
  }
  return *this;
}

iterator& iterator::operator--(int){
  iterator tmp(*this);
  --(*this);
  return tmp;
}
