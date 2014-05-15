
using namespace Jing;
//using Jing::exception;

template<class T>
void list<T>::init(){
  this->first = 0;
  this->last = 0;
  this->count = 0;
  this->iter = new listIterator(this);
}

template<class T>
list<T>::list(){
  this->init();
}

template<class T>
list<T>::list(AbstractList<T> *c){
  this->init();
  this->addAll(c);
}

template<class T>
bool list<T>::add(T t){
  return this->add(t, 0);
}

template<class T>
bool list<T>::add(T t, index_t n){
  if(n < 0)
    return false; 
  ++this->count;
  if(n == 0){
    if(this->first == 0){
      this->first = new listNode(t);
      this->last = this->first;
      return true;
    }else{
      bool ret = this->first->add(t);
      this->first = this->first->prev;
      return ret;
    }
  }else if(n >= this->size()){
    this->last->add(t, 1);
    this->last = this->last->next;
    return true;
  }else{
    return this->first->add(t, n);
  }
  return false;
}

template<class T>
bool list<T>::addAll(AbstractList<T> *c){
  listIterator *iter = (listIterator*)c->iterator();
  bool ret = true;
  while(iter->hasNext()){
    if( !this->add(iter->next()) )
      ret = false;
  }
  return ret;
}

template<class T>
void list<T>::clear(){
  while(this->size() > 0){
    this->remove();
  }
}

template<class T>
bool list<T>::contains(T t) const{
  if(this->first->find(t, 0) > this->size())
    return false;
  else return true;
}

template<class T>
bool list<T>::containsAll(Collection<T> *c) const{
  Iterator<T> *temp = c->iterator();
  while(temp->hasNext()){
    if(!this->contains(temp->next())){
      return false;
    }
  }
  return true;
}

template<class T>
bool list<T>::equals(Collection<T> *c) const{
  return false;
}

template<class T>
index_t list<T>::indexOf(T t) const{
  return this->first->find(t, 0);
}

template<class T>
index_t list<T>::lastIndexOf(T t) const{
  return this->last->backFind(t, this->size() - 1);
}

template<class T>
T list<T>::get(index_t n) const{
  if(n >= this->size()){
    throw listIndexOutOfBounds(*this, n);
  }
  return this->first->get(n);
}

template<class T>
int list<T>::hashCode() const{
  return 0;
}

template<class T>
bool list<T>::isEmpty() const{
  if(this->size() == 0)
    return true;
  else
    return false;
}

template<class T>
Iterator<T> *list<T>::iterator() const{
  this->iter->reset();
  return this->iter;
}

template<class T>
T list<T>::remove(){
  return this->remove((index_t)0);
}

template<class T>
T list<T>::remove(index_t n){
  listNode *temp = first;
  --this->count;
  if(n == 0){
    this->first = this->first->next;
  } else if( (n >= this->size()) && (n < -1) ){
    this->last = this->last->prev;
    return this->last->next->remove((unsigned int)0);
  }else if(n == -1){
    return -1;
  }
  return temp->remove(n);
}

template<class T>
bool list<T>::remove(T t){
  index_t idx = this->indexOf(t);
  if(idx != -1){
    this->remove(idx);
    return true;
  }
  return false;
}

template<class T>
bool list<T>::removeAll(AbstractList<T> *c){
  Iterator<T> *temp = c->iterator();
  while(temp->hasNext()){
    this->remove(temp->next());
  }
  return false;
}

template<class T>
void list<T>::removeRange(int fromIndex, int toIndex){
}

template<class T>
size_t list<T>::size() const{
  return this->count;
}

//create a new array containing all elements in proper order.
template<class T>
T* list<T>::toArray(){
  return 0;
}

//take argument pointer to create and return an array containing all elements in proper order
template<class T>
void list<T>::toArray(T* arr){
  return 0;
}


/********************************************************/
/* List Node                                            */
/********************************************************/


template<class T>
list<T>::listNode::listNode(T t){
  this->init();
  this->data = t;
}

template<class T>
bool list<T>::listNode::add(T t){
  return this->add(t, 0);

}

template<class T>
bool list<T>::listNode::add(T t, index_t n){
  if(n < 0)
    return false; 
  if(n > 0){
    if(this->next == 0){
      this->next = new listNode(t);
      this->next->prev = this;
      return true;
    }
    return this->next->add(t, n - 1);
  }
  else if(n == 0){
    if(this->prev == 0){
      this->prev = new listNode(t);
      this->prev->next = this;
    }else{
      this->prev->next = new listNode(t);
      this->prev->next->next = this;
      this->prev = this->prev->next;
    }
    return true;
  }
  return false;
}

template<class T>
T list<T>::listNode::remove(index_t n){
  if(n > 0)
    return this->next->remove(n - 1);
  else if(n == 0){
    if(this->prev != 0 && this->next != 0){
      this->prev->next = this->next;
      this->next->prev = this->prev;
    } else if(this->prev != 0 && this->next == 0){
      this->prev->next = 0;
    } else if(this->prev == 0 && this->next != 0){
      this->next->prev = 0;
    }

    T temp = this->data;
    //be careful.  only if generated with 'new', and may not be thread safe.
    delete this;
    return temp;
  }
  //else
    //derp
  return 0;
}

template<class T>
T list<T>::listNode::get(index_t n) const{
  if(n > 0){
    if(this->next != 0){
      return this->next->get(n - 1);
    } else {
      return 0;
    }
  }
  if(n == 0)
    return this->data;
  //else
    //wtf
  return 0;
}

template<class T>
index_t list<T>::listNode::find(T t, index_t n){
  if(this->data != t){
    if(this->next != 0){
      return this->next->find(t, n + 1);
    }
  }
  else if(this->data == t)
    return n;
  return -1;
}

template<class T>
index_t list<T>::listNode::backFind(T t, index_t n){
  if(this->data != t){
    if(this->prev != 0){
      return this->prev->backFind(t, n - 1);
    }
  }
  else if(this->data == t)
    return n;
  return -1;
}

template<class T>
void list<T>::listNode::init(){
  this->next = 0;
  this->prev = 0;
}


/********************************************************/
/* List Iterator                                        */
/********************************************************/


template<class T>
list<T>::listIterator::listIterator(list<T> *thisList){
  this->theList = thisList;
  this->idx = 0;
}

template<class T>
list<T>::listIterator::listIterator(list<T> *thisList, index_t n){
  this->theList = thisList;
  this->idx = n;
}

template<class T>
bool list<T>::listIterator::hasNext(){
  if(this->idx < theList->size())
    return true;
  else
    return false;
}

template<class T>
T list<T>::listIterator::next(){
  return theList->get(this->idx++);
}

template<class T>
void list<T>::listIterator::remove(){
  theList->remove(idx);
}

template<class T>
void list<T>::listIterator::reset(){
  this->idx = 0;
}

/**********************
 *  IndexOutOfBounds  *
 **********************/

template<class T>
void list<T>::listIndexOutOfBounds::initWithList(const list<T>& theList){
  this->msg = "\n";
  this->msg += "Index out of bounds.\n";
  this->msg += "List length: ";
  this->msg += theList.size();
  this->msg += "\n";
}

template<class T>
list<T>::listIndexOutOfBounds::listIndexOutOfBounds(const char * message):exception(message){
}

template<class T>
list<T>::listIndexOutOfBounds::listIndexOutOfBounds(const string& message):exception(message){
}

template<class T>
list<T>::listIndexOutOfBounds::listIndexOutOfBounds(const list<T>& theList){
  this->initWithList(theList);
}

template<class T>
list<T>::listIndexOutOfBounds::listIndexOutOfBounds(const list<T>& theList, int index){
  this->initWithList(theList);
  this->msg += "Given index: ";
  this->msg += (index);
  this->msg += "\n";
}

//const string& listIndexOutOfBounds::listIndexOutOfBounds::what() const{
//}
//

