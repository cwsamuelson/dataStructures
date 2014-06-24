#include<Jing/list>
#include<iostream>
#include"character.hh"

using std::cout;
using std::endl;

Jing::list::list(){
  this->sameType = true;
  this->first = 0;
  this->last = 0;
  this->count = 0;
  this->iter = new listIterator(*this);
}

Jing::list::list(Collection& c):list(){
  this->insertAll(c);
}

void Jing::list::insert(Jing::Object& obj){
  this->insert(obj, this->size());
}

//OPTIMIZE: Insert from back using negative indexes
void Jing::list::insert(Jing::Object& obj, Jing::index_t idx){
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

void Jing::list::insertAll(Collection& c){
  this->insertAll(c, this->size() - 1);
}

void Jing::list::insertAll(Collection& c, Jing::index_t idx){
  Iterator& iter = c.iterator();
  Jing::index_t n = idx;
  while(iter.hasNext()){
    this->insert(iter.next(), n);
    ++n;
  }
  return;
}

Jing::Object& Jing::list::remove(){
  return this->remove((Jing::index_t)0);
}

Jing::Object& Jing::list::remove(Jing::index_t idx){
  Object& ret = this->first->data;
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

void Jing::list::remove(Jing::Object& obj){
  Jing::index_t idx = this->indexOf(obj);
  if(idx != (Jing::index_t)-1){
    this->remove(idx);
    return;
  }
  return;
}

void Jing::list::removeAll(Collection& c){
  Iterator& iter = c.iterator();
  while(iter.hasNext()){
    this->remove(iter.next());
  }
}

void Jing::list::removeRange(Jing::index_t fromIndex, Jing::index_t toIndex){
  for(Jing::index_t i = fromIndex; i < toIndex; ++i){
    this->remove(fromIndex);
  }
}

Jing::Object& Jing::list::get(Jing::index_t idx) const{
  //just return last
  if(idx >= this->size()){
    return this->first->get(this->size() - 1);
    //throw listIndexOutOfBounds(*this, idx);
  }
  return this->first->get(idx);
}

Jing::AbstractList& Jing::list::get(Jing::index_t start, Jing::index_t end) const{
  list& ret = *new list();
  for(Jing::index_t i = start; i < end; ++i){
    ret.insert(this->get(i));
  }
  return (AbstractList&)ret;
}

void Jing::list::assign(Jing::index_t idx, Jing::Object& obj){
  if(idx > this->size()){
    this->assign(this->size() - 1, obj);
  } else {
    this->first->assign(idx, obj);
  }
}

void Jing::list::clear(){
  while(this->size() > 0){
    this->remove();
  }
}

bool Jing::list::contains(Jing::Object& obj) const{
  if(this->first->find(obj, 0) > this->size())
    return false;
  else
    return true;
}

bool Jing::list::containsAll(Collection& c) const{
  Iterator& iter = c.iterator();
  while(iter.hasNext()){
    if(!this->contains(iter.next())){
      return false;
    }
  }
  return true;
}

Jing::index_t Jing::list::indexOf(Jing::Object& obj) const{
  return this->first->find(obj, 0);
}

Jing::index_t Jing::list::lastIndexOf(Jing::Object& obj) const{
  return this->last->backFind(obj, this->size() - 1);
}

bool Jing::list::equals(Jing::Object& obj) const{
  return false;
}

Jing::Iterator& Jing::list::iterator() const{
  this->iter->reset();
  return *(this->iter);
}

int Jing::list::hash() const{
  return 0;
}

int Jing::list::classID() const{
  return 1;
}

Jing::Object* Jing::list::clone() const{
  Jing::list* temp = new list(*this);
  return temp;
}

//create a new array containing all elements in proper order.
Jing::Object* Jing::list::toArray() const{
  return 0;
}

//take argument pointer to create and return an array containing all elements in proper order
//assumes enough memory was allocated by user
void Jing::list::toArray(Jing::Object* arr) const{
  for(Jing::index_t i = 0; i < this->size(); ++i){
    arr[i] = this->get(i);
  }
}

bool Jing::list::isEmpty() const{
  if(this->size() == 0)
    return true;
  else
    return false;
}

Jing::size_t Jing::list::size() const{
  return this->count;
}


/********************************************************/
/* List Node                                            */
/********************************************************/


Jing::list::listNode::listNode(Jing::Object& obj):
  data(obj),
  prev(0),
  next(0){  }

Jing::list::listNode::listNode(Object& obj, listNode* prev, listNode* next):
  data(obj),
  prev(prev),
  next(next){ }

bool Jing::list::listNode::add(Jing::Object& obj){
  return this->add(obj, -1);
}

bool Jing::list::listNode::add(Jing::Object& obj, Jing::index_t idx){
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

Jing::Object& Jing::list::listNode::remove(Jing::index_t idx){
  Jing::Object& ret = this->data;
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

Jing::Object& Jing::list::listNode::get(Jing::index_t idx) const{
  Jing::Object* ret = &this->data;
  if(idx > 0){
    if(this->next != 0){
      ret = &this->next->get(idx - 1);
    } else {
      ret = &this->data;
    }
  } else if(idx == 0){
    ret = &this->data;
  }
  return *ret;
}

bool Jing::list::listNode::assign(Jing::index_t idx, Jing::Object& obj){
  bool ret = false;
  if(idx > 0){
    ret = this->next->assign(idx - 1, obj);
  } else if(idx == 0){
    this->data = obj;
    ret = true;
  }
  return ret;
}

Jing::index_t Jing::list::listNode::find(Jing::Object& obj, Jing::index_t idx){
  if(!this->data.equals(obj)){
    if(this->next != 0){
      return this->next->find(obj, idx + 1);
    }
  }
  else if(this->data.equals(obj))
    return idx;
  return -1;
}

Jing::index_t Jing::list::listNode::backFind(Jing::Object& obj, Jing::index_t idx){
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


Jing::listIterator::listIterator(Jing::list& thisList):listIterator(thisList, 0){
}

Jing::listIterator::listIterator(Jing::list& thisList, Jing::index_t idx):idx(idx), theList(thisList){
}

bool Jing::listIterator::hasNext(){
  if(this->idx < this->theList.size())
    return true;
  else
    return false;
}

Jing::Object& Jing::listIterator::next(){
  return this->theList.get(this->idx++);
}

void Jing::listIterator::remove(){
  this->theList.remove(idx);
}

void Jing::listIterator::reset(){
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
