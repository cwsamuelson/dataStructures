vector::vector():
  vector(16){  }

vector::vector(size_t size):
  arr_(new value_type[size]),
  size_(0),
  capacity_(size){
}

vector::vector(iterator& first, iterator& last):vector(){
  for(auto it = first; it != last; ++it){
    pushBack(*it);
  }
}

vector::~vector(){
  delete[] arr_;
}

void vector::pushBack(value_type data){
  if(size_ == capacity_){
    increaseCapacity();
  }
  arr_[size_++] = data;
}

vector::value_type vector::popBack(){
  return arr_[--size_];
}

void vector::clear(){
  size_ = 0;
}

vector::reference vector::get(size_t idx){
  return arr_[idx];
}

vector::const_reference vector::get(size_t idx) const{
  return this->get(idx);
}

vector::iterator vector::begin(){
  return vector::iterator(arr_);
}

vector::iterator vector::end(){
  return vector::iterator(arr_, size_);
}

vector::size_t vector::length(){
  return size_;
}

vector::size_t vector::length() const{
  return length();
}

vector::size_t vector::size(){
  return length();
}

vector::size_t vector::size() const{
  return size();
}

vector::size_t vector::capacity(){
  return capacity_;
}

vector::size_t vector::capacity() const{
  return capacity();
}

void vector::reserve(size_t size){
  if(size > capacity_){
    changeCapacity(size);
  }
}

void vector::shrinkToFit(){
  changeCapacity(size_);
}

bool vector::isEmpty(){
  return size_ == 0;
}

vector::reference vector::operator[](size_t idx){
  return get(idx);
}

void vector::changeCapacity(size_t size){
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

void vector::increaseCapacity(){
  changeCapacity(1.5 * size_);
}

