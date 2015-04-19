template<class T>
vector<T>::vector():
  vector(16){  }

template<class T>
vector<T>::vector(size_t size):
  arr_(new value_type[size]),
  size_(0),
  capacity_(size){
}

template<class T>
vector<T>::vector(iterator& first, iterator& last):vector(){
  for(auto it = first; it != last; ++it){
    pushBack(*it);
  }
}

template<class T>
vector<T>::~vector(){
  delete[] arr_;
}

template<class T>
void vector<T>::pushBack(value_type data){
  if(size_ == capacity_){
    increaseCapacity();
  }
  arr_[size_++] = data;
}

template<class T>
typename vector<T>::value_type vector<T>::popBack(){
  return arr_[--size_];
}

template<class T>
typename vector<T>::iterator vector<T>::insert(iterator it, const_reference data){
  vector<T> buffer;
  while(size_ > it.idx_){
    buffer.pushBack(popBack());
  }
  pushBack(data);
  while(!buffer.isEmpty()){
    pushBack(buffer.popBack());
  }
  return it;
}

template<class T>
typename vector<T>::iterator vector<T>::insert(iterator it, size_t n, const_reference data){
  vector<T> buffer;
  while(size_ > it.idx_){
    buffer.pushBack(popBack());
  }
  for(unsigned int i = 0; i < n; ++i){
    pushBack(data);
  }
  while(!buffer.isEmpty()){
    pushBack(buffer.popBack());
  }
  return it;
}

template<class T>
typename vector<T>::iterator vector<T>::insert(iterator it, iterator first, iterator last){
  vector<T> buffer;
  while(size_ > it.idx_){
    buffer.pushBack(popBack());
  }
  for(auto itr = first; itr != last; ++itr){
    pushBack(*itr);
  }
  while(!buffer.isEmpty()){
    pushBack(buffer.popBack());
  }
  return it;
}

template<class T>
typename vector<T>::iterator vector<T>::erase(iterator it){
  vector<T> buffer;
  while(size_ > it.idx_){
    buffer.pushBack(popBack());
  }
  popBack();
  while(!buffer.isEmpty()){
    pushBack(buffer.popBack());
  }
  return it;
}

template<class T>
typename vector<T>::iterator vector<T>::erase(iterator first, iterator last){
  vector<T> buffer;
  while(size_ > first.idx){
    buffer.pushBack(popBack());
  }
  for(auto it = first; first != last; ++it){
    buffer.popBack();
  }
  while(!buffer.isEmpty()){
    pushBack(buffer.popBack());
  }
}

template<class T>
void vector<T>::clear(){
  size_ = 0;
}

template<class T>
typename vector<T>::reference vector<T>::get(size_t idx){
  return arr_[idx];
}

template<class T>
typename vector<T>::const_reference vector<T>::get(size_t idx) const{
  return this->get(idx);
}

template<class T>
typename vector<T>::iterator vector<T>::begin(){
  return vector::iterator(arr_);
}

template<class T>
typename vector<T>::iterator vector<T>::end(){
  return vector::iterator(arr_, size_);
}

template<class T>
typename vector<T>::size_t vector<T>::length(){
  return size_;
}

template<class T>
typename vector<T>::size_t vector<T>::length() const{
  return length();
}

template<class T>
typename vector<T>::size_t vector<T>::size(){
  return length();
}

template<class T>
typename vector<T>::size_t vector<T>::size() const{
  return size();
}

template<class T>
typename vector<T>::size_t vector<T>::capacity(){
  return capacity_;
}

template<class T>
typename vector<T>::size_t vector<T>::capacity() const{
  return capacity();
}

template<class T>
void vector<T>::reserve(size_t size){
  if(size > capacity_){
    changeCapacity(size);
  }
}

template<class T>
void vector<T>::shrinkToFit(){
  changeCapacity(size_);
}

template<class T>
bool vector<T>::isEmpty(){
  return size_ == 0;
}

template<class T>
typename vector<T>::reference vector<T>::operator[](size_t idx){
  return get(idx);
}

template<class T>
void vector<T>::changeCapacity(size_t size){
  if(size < size_){
    changeCapacity(size_);
  }
  pointer arr = new value_type[size];
  for(size_t i = 0; i < size_; ++i){
    arr[i] = arr_[i];
  }
  pointer hold = arr_;
  arr_ = arr;
  delete[] hold;
}

template<class T>
void vector<T>::increaseCapacity(){
  changeCapacity(1.5 * size_);
}

template<class T>
void vector<T>::increaseCapacity(size_t size){
  changeCapacity(size_ + size);
}

