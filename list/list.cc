#include"list_iterator.hh"
#include"list_node.hh"

template<class T>
list<T>::list():
  head(0),
  tail(0),
  size(0){  }

template<class T>
list<T>::~list(){
  clear();
}

template<class T>
void list<T>::pushFront(value_type data){
  if(head == 0){
    head = tail = new node(data);
  } else {
    head = new node(data, 0, head->right);
  }
  ++size;
}

template<class T>
void list<T>::pushBack(value_type data){
  if(tail == 0){
    head = tail = new node(data);
  } else {
    tail = new node(data, tail->left, 0);
  }
  ++size;
}

template<class T>
typename list<T>::value_type list<T>::popFront(){
  if(head != 0){
    head = head->right;
    delete head->left;
    head->left = 0;
    --size;
  }
}

template<class T>
typename list<T>::value_type list<T>::popBack(){
  if(tail != 0){
    tail = tail->left;
    delete tail->right;
    tail->right = 0;
    --size;
  }
}

template<class T>
typename list<T>::iterator list<T>::insert(iterator it, const_reference val){
}

template<class T>
typename list<T>::iterator list<T>::insert(iterator it, size_t n, const_reference val){
  return it;
}

template<class T>
typename list<T>::iterator list<T>::insert(iterator it, iterator first, iterator last){
  return it;
}

template<class T>
typename list<T>::iterator list<T>::erase(iterator it){
  return it;
}

template<class T>
typename list<T>::iterator list<T>::erase(iterator first, iterator last){
  return first;
}

template<class T>
void list<T>::clear(){
  while(size > 0){
    popBack();
  }
}

template<class T>
typename list<T>::reference list<T>::get(size_t idx){
  return head->get(idx);
}

template<class T>
typename list<T>::const_reference list<T>::get(size_t idx) const{
  return head->get(idx);
}

template<class T>
typename list<T>::iterator list<T>::begin(){
  return iterator(head);
}

template<class T>
typename list<T>::iterator list<T>::end(){
  return iterator((node*)0);
}

template<class T>
size_t list<T>::length(){
  return size;
}

template<class T>
bool list<T>::isEmpty(){
  return size == 0;
}

template<class T>
typename list<T>::reference list<T>::operator[](size_t idx){
  return get(idx);
}

