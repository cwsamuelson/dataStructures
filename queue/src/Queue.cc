//#include<Jing/list>

//Constructors
Jing::Queue<T>::Queue():que(){
}

Jing::Queue<T>::Queue(Collection<T>& c):que(c){
}

//Inserts
void Jing::Queue<T>::enqueue(T& obj){
  this->que.insert(obj, this->que.size());
}

//  [inherited from collection]
void Jing::Queue<T>::insert(T& obj){
  this->enqueue(obj);
}

void Jing::Queue<T>::insertAll(Collection<T>& c){
}

//Removes
T& Jing::Queue<T>::dequeue(){
  return this->que.remove(0);
}

T& Jing::Queue<T>::remove(){
  return this->dequeue();
}

//  [inherited from collection]
void Jing::Queue<T>::remove(T& obj){
}

void Jing::Queue<T>::removeAll(Collection<T>& c){
}

//Contains
//  [inherited from collection]
bool Jing::Queue<T>::contains(T& obj) const{
}

bool Jing::Queue<T>::containsAll(Collection<T>& c) const{
}

//Reverse gets
//Equality
//  [inherited from Object]
bool Jing::Queue<T>::equals(Object& obj) const{
}

//Iterator
//  [inherited from Iterable]
Iterator<T>& Jing::Queue<T>::iterator() const{
}

//States
//  hash
//  [inherited from Object]
unsigned long long Jing::Queue<T>::hash() const{
  return 0;
}

//  clone
//  [inherited from Object]
//memory management may be up to the user.
//clean up with delete
Object* Jing::Queue<T>::clone() const{
  return 0;
}

//  isempty
//  [inherited from collection]
bool Jing::Queue<T>::isEmpty() const{
  return this->que.isEmpty();
}

//  size
//  [inherited from collection]
size_t Jing::Queue<T>::size() const{
  return this->que.size();
}

//  clear
//  [inherited from collection]
void Jing::Queue<T>::clear(){
  this->que.clear();
}

