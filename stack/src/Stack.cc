//#include<Jing/list>

//Constructors
template<class T>
Jing::Stack<T>::Stack():stk(){
}

template<class T>
Jing::Stack<T>::Stack(Collection<T>& c):stk(c){
}

//Inserts
template<class T>
void Jing::Stack<T>::push(T& obj){
  this->stk.insert(obj, 0);
}

//  [inherited from collection]
template<class T>
void Jing::Stack<T>::insert(T& obj){
  this->push(obj);
}

template<class T>
void Jing::Stack<T>::insertAll(Collection<T>& c){
}

//Removes
template<class T>
T& Jing::Stack<T>::pop(){
  return this->stk.remove(0);
}

template<class T>
T& Jing::Stack<T>::remove(){
  return this->pop();
}

//  [inherited from collection]
template<class T>
void Jing::Stack<T>::remove(T& obj){
}

template<class T>
void Jing::Stack<T>::removeAll(Collection<T>& c){
}

//Contains
//  [inherited from collection]
template<class T>
bool Jing::Stack<T>::contains(T& obj) const{
}

template<class T>
bool Jing::Stack<T>::containsAll(Collection<T>& c) const{
}

//Reverse gets
//Equality
//  [inherited from Object]
template<class T>
bool Jing::Stack<T>::equals(Object& obj) const{
}

//Iterator
//  [inherited from Iterable]
template<class T>
Jing::Iterator<T>& Jing::Stack<T>::iterator() const{
  return this->stk.iterator();
}

//States
//  hash
//  [inherited from Object]
template<class T>
unsigned long long Jing::Stack<T>::hash() const{
  return 0;
}

//  clone
//  [inherited from Object]
//memory management may be up to the user.
//clean up with delete
template<class T>
Jing::Object* Jing::Stack<T>::clone() const{
  return 0;
}

//  isempty
//  [inherited from collection]
template<class T>
bool Jing::Stack<T>::isEmpty() const{
  return this->stk.isEmpty();
}

//  size
//  [inherited from collection]
template<class T>
Jing::size_t Jing::Stack<T>::size() const{
  return this->stk.size();
}

//  clear
//  [inherited from collection]
template<class T>
void Jing::Stack<T>::clear(){
  this->stk.clear();
}

