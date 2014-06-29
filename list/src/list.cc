#include<Jing/list>
#include<iostream>

using std::cout;
using std::endl;

template<class T>
Jing::list<T>::list(){
  //This list can only contain objects that inherit from Jing::Object references
  can_copy<T, Jing::Object&>();
  this->sameType = true;
  this->first = 0;
  this->last = 0;
  this->count = 0;
  this->iter = new listIterator(*this);
}

template<class T>
Jing::list<T>::list(Collection<T>& c):list(){
  this->insertAll(c);
}

template<class T>
void Jing::list<T>::insert(T& obj){
  this->insert(obj, this->size());
}

//OPTIMIZE: Insert from back using negative indexes
template<class T>
void Jing::list<T>::insert(T& obj, Jing::index_t idx){
  //uninitialized list
  if(this->size() == 0){
  //  update first
    this->first = new listNode(obj, 0, this->first);
  //  update last
    this->last = this->first;
  //insert at beginning
  } else if(idx == 0){
  //  update first
    this->first->prev = new listNode(obj, 0, this->first);
    this->first = this->first->prev;
  //insert at end
  } else if(idx >= this->count){
  //  update last
    this->last->next = new listNode(obj, this->last, 0);
    this->last = this->last->next;
  //insert normally
  } else {
    this->first->add(obj, idx);
  }
  ++this->count;
  return;
}

template<class T>
void Jing::list<T>::insertAll(Collection<T>& c){
  this->insertAll(c, this->size() - 1);
}

template<class T>
void Jing::list<T>::insertAll(Collection<T>& c, Jing::index_t idx){
  Iterator<T>& iter = c.iterator();
  Jing::index_t n = idx;
  while(iter.hasNext()){
    this->insert(iter.next(), n);
    ++n;
  }
  return;
}

template<class T>
T& Jing::list<T>::remove(){
  return this->remove((Jing::index_t)0);
}

template<class T>
T& Jing::list<T>::remove(Jing::index_t idx){
  T& ret = this->first->data;
  //uninitialized list
//don't delete from uninit list yet
//  probably throwing exception...?
/*
  if(this->size() == 0){
    return;
  //delete only remaining
  } else */if(this->size() == 1){
    ret = this->first->data;
    delete this->first;
    this->first = this->last = 0;
  //delete at beginning
  } else if(idx == 0){
  //  update first
    ret = this->first->data;
    this->first = this->first->next;
    delete this->first->prev;
    this->first->prev = 0;
  //delete at end
  } else if(idx == this->size() - 1){
  //  update last
    ret = this->last->data;
    this->last = this->last->prev;
    delete this->last->next;
    this->last->next = 0;
  //delete normally
  } else {
    ret = this->first->remove(idx);
  }
  --this->count;
  return ret;
}

template<class T>
void Jing::list<T>::remove(T& obj){
  Jing::index_t idx = this->indexOf(obj);
  if(idx != (Jing::index_t)-1){
    this->remove(idx);
    return;
  }
  return;
}

template<class T>
void Jing::list<T>::removeAll(Collection<T>& c){
  Iterator<T>& iter = c.iterator();
  while(iter.hasNext()){
    this->remove(iter.next());
  }
}

template<class T>
void Jing::list<T>::removeRange(Jing::index_t fromIndex, Jing::index_t toIndex){
  for(Jing::index_t i = fromIndex; i < toIndex; ++i){
    this->remove(fromIndex);
  }
}

template<class T>
T& Jing::list<T>::get() const{
  return this->get(0);
}

template<class T>
T& Jing::list<T>::get(Jing::index_t idx) const{
  //just return last
  if(idx >= this->size()){
    return this->first->get(this->size() - 1);
    //throw listIndexOutOfBounds(*this, idx);
  }
  return this->first->get(idx);
}

template<class T>
Jing::AbstractList<T>& Jing::list<T>::get(Jing::index_t start, Jing::index_t end) const{
  list& ret = *new list();
  for(Jing::index_t i = start; i < end; ++i){
    ret.insert(this->get(i));
  }
  return (AbstractList<T>&)ret;
}

template<class T>
T& Jing::list<T>::assign(Jing::index_t idx, T& obj){
  T& ret = this->remove(idx);
  this->insert(obj, idx);
  return ret;
/*
  if(idx > this->size()){
    this->assign(this->size() - 1, obj);
  } else {
    this->first->assign(idx, obj);
  }
*/
}

template<class T>
void Jing::list<T>::clear(){
  while(this->size() > 0){
    this->remove();
  }
}

template<class T>
bool Jing::list<T>::contains(T& obj) const{
  if(this->size() > 0){
    if(this->first->find(obj, 0) > this->size()){
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

template<class T>
bool Jing::list<T>::containsAll(Collection<T>& c) const{
  Iterator<T>& iter = c.iterator();
  while(iter.hasNext()){
    if(!this->contains(iter.next())){
      return false;
    }
  }
  return true;
}

template<class T>
Jing::index_t Jing::list<T>::indexOf(T& obj) const{
  return this->first->find(obj, 0);
}

template<class T>
Jing::index_t Jing::list<T>::lastIndexOf(T& obj) const{
  return this->last->backFind(obj, this->size() - 1);
}

template<class T>
bool Jing::list<T>::equals(Jing::Object& obj) const{
  return false;
}

template<class T>
Jing::Iterator<T>& Jing::list<T>::iterator() const{
  this->iter->reset();
  return *(this->iter);
}

template<class T>
int Jing::list<T>::hash() const{
  return 0;
}

template<class T>
int Jing::list<T>::classID() const{
  return 1;
}

template<class T>
Jing::Object* Jing::list<T>::clone() const{
  Jing::list<T>* temp = new list<T>(*this);
  return temp;
}

//create a new array containing all elements in proper order.
template<class T>
Jing::Object* Jing::list<T>::toArray() const{
  return 0;
}

//take argument pointer to create and return an array containing all elements in proper order
//assumes enough memory was allocated by user
template<class T>
void Jing::list<T>::toArray(Jing::Object* arr) const{
  for(Jing::index_t i = 0; i < this->size(); ++i){
    arr[i] = this->get(i);
  }
}

template<class T>
bool Jing::list<T>::isEmpty() const{
  if(this->size() == 0)
    return true;
  else
    return false;
}

template<class T>
Jing::size_t Jing::list<T>::size() const{
  return this->count;
}


/********************************************************/
/* List Node                                            */
/********************************************************/


template<class T>
Jing::list<T>::listNode::listNode(T& obj):
  data(obj),
  prev(0),
  next(0){  }

template<class T>
Jing::list<T>::listNode::listNode(T& obj, listNode* prev, listNode* next):
  data(obj),
  prev(prev),
  next(next){ }

template<class T>
bool Jing::list<T>::listNode::add(T& obj){
  return this->add(obj, -1);
}

template<class T>
bool Jing::list<T>::listNode::add(T& obj, Jing::index_t idx){
  if(idx > 0){
    //idx is too big.  o well!
    if(this->next == 0){
      this->next = new listNode(obj);
      this->next->prev = this;
      return true;
    } else {
      return this->next->add(obj, idx - 1);
    }
  } else if(idx == 0){
    if(this->prev != 0){
      this->prev = new listNode(obj, this->prev, this);
      this->prev->prev->next = this->prev;
    } else {
      this->prev = new listNode(obj, 0, this);
    }
    return true;
  }
  return false;
}

template<class T>
T& Jing::list<T>::listNode::remove(Jing::index_t idx){
  T& ret = this->data;
  if(idx > 0){
    ret = this->next->remove(idx - 1);
  }else if(idx == 0){
    if(this->prev != 0 && this->next != 0){
      this->prev->next = this->next;
      this->next->prev = this->prev;
    } else if(this->prev != 0 && this->next == 0){
      this->prev->next = 0;
    } else if(this->prev == 0 && this->next != 0){
      this->next->prev = 0;
    }

    ret = this->data;
    //be careful.  only if generated with 'new', and may not be thread safe.
    delete this;
  }
  return ret;
}

template<class T>
T& Jing::list<T>::listNode::get(Jing::index_t idx) const{
  if(idx > 0){
    if(this->next != 0){
      return this->next->get(idx - 1);
    } else {
      return this->data;
    }
  } else if(idx == 0){
    return this->data;
  }
}

template<class T>
bool Jing::list<T>::listNode::assign(Jing::index_t idx, T& obj){
  bool ret = false;
  if(idx > 0){
    ret = this->next->assign(idx - 1, obj);
  } else if(idx == 0){
    this->data = obj;
    ret = true;
  }
  return ret;
}

template<class T>
Jing::index_t Jing::list<T>::listNode::find(T& obj, Jing::index_t idx){
  if(!this->data.equals(obj)){
    if(this->next != 0){
      return this->next->find(obj, idx + 1);
    }
  }
  else if(this->data.equals(obj))
    return idx;
  return -1;
}

template<class T>
Jing::index_t Jing::list<T>::listNode::backFind(T& obj, Jing::index_t idx){
  if(!this->data.equals(obj)){
    if(this->prev != 0){
      return this->prev->backFind(obj, idx - 1);
    }
  }
  else if(this->data.equals(obj))
    return idx;
  return -1;
}


/********************************************************
 * List Iterator                                        *
 ********************************************************/
//Try optimizing by pointing the iterator at the individual nodes


template<class T>
Jing::list<T>::listIterator::listIterator(Jing::list<T>& thisList):listIterator(thisList, 0){
}

template<class T>
Jing::list<T>::listIterator::listIterator(Jing::list<T>& thisList, Jing::index_t idx):idx(idx), theList(thisList){
}

template<class T>
bool Jing::list<T>::listIterator::hasNext(){
  if(this->idx < this->theList.size())
    return true;
  else
    return false;
}

template<class T>
T& Jing::list<T>::listIterator::next(){
  return this->theList.get(this->idx++);
}

template<class T>
void Jing::list<T>::listIterator::remove(){
  this->theList.remove(idx);
}

template<class T>
void Jing::list<T>::listIterator::reset(){
  this->idx = 0;
}

/**********************
 *  IndexOutOfBounds  *
 **********************/
/*
void Jing::listIndexOutOfBounds::initWithList(const list& theList){
  this->msg = "\n";
  this->msg += "Index out of bounds.\n";
  this->msg += "List length: ";
  this->msg += theList.size();
  this->msg += "\n";
}

Jing::listIndexOutOfBounds::listIndexOutOfBounds(const char * message):exception(message){
}

Jing::listIndexOutOfBounds::listIndexOutOfBounds(const string& message):exception(message){
}

Jing::listIndexOutOfBounds::listIndexOutOfBounds(const list& theList){
  this->initWithList(theList);
}

Jing::listIndexOutOfBounds::listIndexOutOfBounds(const list& theList, int index){
  this->initWithList(theList);
  this->msg += "Given index: ";
  this->msg += (index);
  this->msg += "\n";
}


//const string& listIndexOutOfBounds::listIndexOutOfBounds::what() const{
//}
//
*/
