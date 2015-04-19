//Constructors
template<class T>
Queue<T>::Queue(){
}

template<class T>
Queue<T>::Queue(Collection<T>& c){
  this->que.insertAll(c);
}

//Inserts
template<class T>
void Queue<T>::enqueue(T& obj){
  this->que.insert(obj, this->que.size());
}

//  [inherited from collection]
template<class T>
void Queue<T>::insert(T& obj){
  this->enqueue(obj);
}

template<class T>
void Queue<T>::insertAll(Collection<T>& c){
}

//Removes
template<class T>
T& Queue<T>::dequeue(){
  return this->que.remove(0);
}

template<class T>
T& Queue<T>::remove(){
  return this->dequeue();
}

//  [inherited from collection]
template<class T>
void Queue<T>::remove(T& obj){
}

template<class T>
void Queue<T>::removeAll(Collection<T>& c){
}

//Contains
//  [inherited from collection]
template<class T>
bool Queue<T>::contains(T& obj) const{
}

template<class T>
bool Queue<T>::containsAll(Collection<T>& c) const{
}

//Reverse gets
//Equality
//  [inherited from Object]
template<class T>
bool Queue<T>::equals(Object& obj) const{
}

//Iterator
//  [inherited from Iterable]
template<class T>
Iterator<T>& Queue<T>::iterator() const{
  return this->que.iterator();
}

//States
//  hash
//  [inherited from Object]
template<class T>
unsigned long long Queue<T>::hash() const{
  return 0;
}

//  clone
//  [inherited from Object]
//memory management may be up to the user.
//clean up with delete
template<class T>
Object* Queue<T>::clone() const{
  return 0;
}

//  isempty
//  [inherited from collection]
template<class T>
bool Queue<T>::isEmpty() const{
  return this->que.isEmpty();
}

//  size
//  [inherited from collection]
template<class T>
size_t Queue<T>::size() const{
  return this->que.size();
}

//  clear
//  [inherited from collection]
template<class T>
void Queue<T>::clear(){
  this->que.clear();
}

