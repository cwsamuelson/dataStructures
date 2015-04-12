template<class T>
gxy::vector<T>::vector():arr(new T[16]), size(0), capacity(16){  }

template<class T>
gxy::vector<T>::vector(const vector<value_type>& other){
  this->insert(this->begin(), other.begin(), other.end());
}

template<class T>
gxy::vector<T>::~vector(){
  delete this->arr;
}

template<class T>
void gxy::vector<T>::pushBack(value_type vt){
  if(this->size < this->capacity){
    this->arr[this->size++] = vt;
  } else {
    T* tmp = new T[this->capacity + 16];
    //copy everything to the new array.
    delete this->arr;
    this->arr = tmp;
  }
}

template<class T>
gxy::vector<T>::value_type gxy::vector<T>::popBack(){
  return this->arr[this->size--];
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
gxy::vector<T>::size_t gxy::vector<T>::capacity(){
  return this->capacity;
}

template<class T>
gxy::vector<T>::size_t gxy::vector<T>::capacity() const{
  return this->capacity;
}

template<class T>
void gxy::vector<T>::reserve(size_t n){
  if(n > this->capacity){
    T* tmp = new T[n];
    //Copy shit over
    delete this->arr;
    this->arr = tmp;
  }
}

template<class T>
void gxy::vector<T>::shrink(){
  T* tmp = new T[this->size];
  //copy shit over
  delete this->arr;
  this->arr = tmp;
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
template<class T>
gxy::iterator():idx(0){  }

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

