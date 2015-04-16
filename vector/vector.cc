template<class T>
void gxy::vector<T>::increaseCapacity(){
  this->increaseSize(1.5 * this->size_);
}

template<class T>
void gxy::vector<T>::increaseCapacity(size_t sz){
  T* tmp = new T[sz];
  for(unsigned int i = 0; i < this->size_; ++i){
    tmp[i] = this->arr[i];
  }

  T* dl = this->arr;
  this->arr = tmp;
  this->capacity_ = sz;
  delete[] dl;
}

template<class T>
void decreaseCapacity(){
  this->decreaseCapacity(this->size_);
}

template<class T>
void decreaseCapacity(size_t sz){
}

template<class T>
gxy::vector<T>::vector():
  vector((size_t)16){  }

template<class T>
vector(size_t sz):
  arr(new T[sz]),
  size_(0),
  capacity(sz){  }

template<class T>
gxy::vector<T>::vector(const vector<value_type>& other):
  vector(){
  this->insert(this->begin(), other.begin(), other.end());
}

template<class T>
gxy::vector<T>::~vector(){
  delete this->arr;
}

template<class T>
void gxy::vector<T>::pushBack(value_type vt){
  if(this->size_ >= this->capacity_){
    this->increaseCapacity();
  }
  this->arr[this->size_++] = vt;
}

template<class T>
gxy::vector<T>::value_type gxy::vector<T>::popBack(){
  return this->arr[--this->size];
}

template<class T>
gxy::vector<T>::iterator<value_type> gxy::vector<T>::insert(iterator<value_type> it, const_reference val){
}

template<class T>
gxy::vector<T>::iterator<value_type> gxy::vector<T>::insert(iterator<value_type> it, size_t n, const_reference val){
}

template<class T>
gxy::vector<T>::iterator<value_type> gxy::vector<T>::insert(iterator<value_type> it, iterator<value_type> first, iterator<value_type> last){
}

template<class T>
gxy::vector<T>::iterator<value_type> gxy::vector<T>::erase(iterator<value_type> it){
}

template<class T>
gxy::vector<T>::iterator<value_type> gxy::vector<T>::erase(iterator<value_type> first, iterator<value_type> last){
}

template<class T>
void gxy::vector<T>::clear(){
  this->size = 0;
}

template<class T>
gxy::vector<T>::reference gxy::vector<T>::get(size_t idx){
  if(idx >= this->size){
    return this->arr[this->size - 1];
  } else {
    return this->arr[idx];
  }
}

template<class T>
gxy::vector<T>::const_reference gxy::vector<T>::get(size_t idx) const{
  return this->get(idx);
}

template<class T>
gxy::vector<T>::iterator<value_type> gxy::vector<T>::begin(){
}

template<class T>
gxy::vector<T>::iterator<value_type> gxy::vector<T>::end(){
  return gxy::iterator<T>(0);
}

template<class T>
gxy::vector<T>::size_t gxy::vector<T>::length(){
  return this->size;
}

template<class T>
gxy::vector<T>::size_t gxy::vector<T>::length() const{
  return this->size;
}

template<class T>
size_t size(){
  return this->length();
}

template<class T>
size_t size() const{
  return this->length();
}

template<class T>
gxy::vector<T>::size_t gxy::vector<T>::capacity(){
  return this->capacity_;
}

template<class T>
gxy::vector<T>::size_t gxy::vector<T>::capacity() const{
  return this->capacity_;
}

template<class T>
void gxy::vector<T>::reserve(size_t n){
  if(n > this->sizeMax){
    this->increaseCapacity(n);
  }
}

template<class T>
void gxy::vector<T>::shrink(){
  this->decreaseCapacity();
}

template<class T>
bool gxy::vector<T>::isEmpty(){
  return this->size == 0;
}

template<class T>
gxy::vector<T>::reference gxy::vector<T>::operator[](size_t idx){
  return this->get(idx);
}

//iterator implementation
iterator(const gxy::vector<T>&, const iterator<T>& that);
template<class T>
gxy::iterator():idx(0){  }

gxy::iterator(const gxy::vector<T>&):idx(0){  }

template<class T>
gxy::iterator(const iterator<T>& that):idx(that.idx){  }

template<class T>
gxy::iterator(gxy::vector<T>::size_t sz):idx(sz){  }

template<class T>
gxy::iterator<T>& gxy::iterator<T>::operator=(const gxy::iterator<T>& rhs){
  this->idx = rhs.idx;
}

template<class T>
gxy::iterator<T>& gxy::iterator<T>::operator++(){
  ++this->idx;
  return *this;
}

template<class T>
gxy::iterator<T>  gxy::iterator<T>::operator++(int){
  gxy::iterator<T> tmp(*this);
  ++(*this);
  return tmp;
}

template<class T>
gxy::iterator<T>& gxy::iterator<T>::operator--(){
  --this->idx;
  return *this;
}

template<class T>
gxy::iterator<T>  gxy::iterator<T>::operator--(int){
  gxy::iterator<T> tmp(*this);
  --this->idx;
  return *this;
}

template<class T>
typename list<T>::reference gxy::iterator<T>::operator*(){
}

template<class T>
typename list<T>::pointer gxy::iterator<T>::operator->(){
}

template<class U>
bool gxy::iterator<U>::operator==(const gxy::iterator<U>& lhs, const gxy::iterator<U>& rhs){
}

template<class U>
bool gxy::iterator<U>::operator!=(const gxy::iterator<U>& lhs, const gxy::iterator<U>& rhs){
}

