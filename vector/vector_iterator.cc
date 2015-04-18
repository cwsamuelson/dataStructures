template<class T>
vector_iterator<T>::vector_iterator(const vector_iterator& other):
  idx_(other.idx_),
  data_(other.data_){  }

template<class T>
vector_iterator<T>::vector_iterator(vector_iterator::pointer ptr):
  vector_iterator(ptr, 0){  }

template<class T>
vector_iterator<T>::vector_iterator(vector_iterator::pointer ptr, size_t idx):
  idx_(idx),
  data_(ptr){  }

template<class T>
vector_iterator<T>& vector_iterator<T>::operator=(const vector_iterator<T>& rhs){
  data_ = rhs.data_;
  idx_ = rhs.idx_;
  return *this;
}

template<class T>
vector_iterator<T>& vector_iterator<T>::operator++(){
  ++idx_;
  return *this;
}

template<class T>
vector_iterator<T> vector_iterator<T>::operator++(int){
  vector_iterator tmp(*this);
  ++(*this);
  return tmp;
}

template<class T>
vector_iterator<T>& vector_iterator<T>::operator--(){
  --idx_;
  return *this;
}

template<class T>
vector_iterator<T> vector_iterator<T>::operator--(int){
  vector_iterator tmp(*this);
  --(*this);
  return tmp;
}

template<class T>
typename vector_iterator<T>::reference vector_iterator<T>::operator*(){
  return data_[idx_];
}

template<class T>
typename vector_iterator<T>::pointer vector_iterator<T>::operator->(){
  return data_ + idx_;
}

template<class T>
bool operator==(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs){
  return (lhs.data_ == rhs.data_ && lhs.idx_ == rhs.idx_);
}

template<class T>
bool operator!=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs){
  return !(lhs == rhs);
}

