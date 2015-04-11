#include"iterator.hh"

gxy::iterator::iterator():ptr(0){
}

gxy::iterator::iterator(const gxy::iterator& that):ptr(that.ptr){
}

gxy::iterator::iterator(node* that):ptr(that){
}

bool gxy::iterator::hasNext(){
  if(ptr == 0){
    return false;
  } else {
    return this->ptr->next != 0;
  }
}

char gxy::iterator::next(){
  if(this->ptr != 0){
    if(this->ptr->next != 0){
      this->ptr = this->ptr->next;
    }
    return this->ptr->data;
  } else {
    return 0;
  }
}

char gxy::iterator::remove(){
  return 'a';
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

gxy::node*& gxy::iterator::accessNode(){
  return this->ptr;
}

