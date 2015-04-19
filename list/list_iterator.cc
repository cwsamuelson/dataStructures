#include"list_iterator.hh"

template<class T>
list_iterator<T>::list_iterator():
  ptr(0){  }

template<class T>
list_iterator<T>::list_iterator(const list_iterator& that):
  ptr(that.ptr){  }

template<class T>
list_iterator<T>::list_iterator(node* that):
  ptr(that){  }

template<class T>
list_iterator<T>& list_iterator<T>::operator=(const list_iterator& rhs){
  ptr = rhs.ptr;
  return *this;
}

template<class T>
list_iterator<T>& list_iterator<T>::operator++(){
  if(this->ptr != 0){
    this->ptr = this->ptr->right;
  }
  return *this;
}

template<class T>
list_iterator<T>  list_iterator<T>::operator++(int){
  list_iterator ret(*this);
  ++(*this);
  return ret;
}

template<class T>
list_iterator<T>& list_iterator<T>::operator--(){
  if(this->ptr != 0){
    this->ptr = this->ptr->left;
  }
  return *this;
}

template<class T>
list_iterator<T>  list_iterator<T>::operator--(int){
  list_iterator ret(*this);
  --(*this);
  return ret;
}

template<class T>
typename list<T>::reference list_iterator<T>::operator*(){
  return ptr->data;
}

template<class T>
typename list<T>::pointer list_iterator<T>::operator->(){
  return &(ptr->data);
}

template<class T>
bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs){
  return lhs.ptr == rhs.ptr;
}

template<class T>
bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs){
  return !(lhs == rhs);
}

