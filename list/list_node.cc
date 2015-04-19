template<class T>
list_node<T>::list_node(const_reference c):
  data(c),
  left(0),
  right(0){  }

template<class T>
list_node<T>::list_node(const_reference c, list_node<T>* l, list_node<T>* r):
  data(c),
  left(l),
  right(r){  }

template<class T>
typename list_node<T>::reference list_node<T>::get(size_t idx){
  if(idx == 0){
    return data;
  } else {
    return get(idx - 1);
  }
}

