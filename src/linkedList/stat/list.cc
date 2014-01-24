
using namespace Jing;

template<class T>
void ArrayList<T>::init(){
  this->first = 0;
  this->last = 0;
  this->count = 0;
  this->iter = new listIterator(this);
}

template<class T>
ArrayList<T>::ArrayList(){
  this->init();
}

template<class T>
ArrayList<T>::ArrayList(Collection<T> *c){
  this->init();
  this->addAll(c);
}

template<class T>
bool ArrayList<T>::add(T t){
  return this->add(t, 0);
}

template<class T>
bool ArrayList<T>::add(T t, index_t n){
  if(n > this->size()){
    this->last->add(t);
  }else if(this->first == 0){
    ++this->count;
    this->first = new listNode(t);
    return true;
  }else
    return this->first->add(t, n);
  return false;
}

template<class T>
bool ArrayList<T>::addAll(Collection<T> *c){
  listIterator *iter = (listIterator*)c->iterator();
  bool ret = true;
  while(iter->hasNext()){
    if( !this->add(iter->next()) )
      ret = false;
  }
  return ret;
}

template<class T>
void ArrayList<T>::clear(){
  while(this->size() > 0){
    this->remove();
  }
}

template<class T>
bool ArrayList<T>::contains(T t){
  if(this->first->find(t, 0) > this->size())
    return false;
  else return true;
}

template<class T>
bool ArrayList<T>::containsAll(Collection<T> *c){
  Iterator<T> *temp = c->iterator();
  while(temp->hasNext())
    if(!this->contains(temp->next()))
      return false;
  return true;
}

template<class T>
bool ArrayList<T>::equals(T t){
  return false;
}

template<class T>
typename ArrayList<T>::index_t ArrayList<T>::indexOf(T t) const{
  return this->first->find(t, 0);
}

template<class T>
typename ArrayList<T>::index_t ArrayList<T>::lastIndexOf(T t) const{
  return this->last->backFind(this->size());
}

template<class T>
T ArrayList<T>::get(index_t n) const{
  return this->first->get(n);
}

template<class T>
int ArrayList<T>::hashCode(){
  return 0;
}

template<class T>
bool ArrayList<T>::isEmpty(){
  if(this->size() == 0)
    return true;
  else
    return false;
}

template<class T>
Iterator<T> *ArrayList<T>::iterator(){
  this->iter->reset();
  return this->iter;
}

template<class T>
T ArrayList<T>::remove(){
  return this->remove((index_t)0);
}

template<class T>
T ArrayList<T>::remove(index_t n){
  --this->count;
  listNode *temp = first;
  if(n == 0)
    this->first = this->first->next;
  return temp->remove(n);
}

template<class T>
bool ArrayList<T>::remove(T t){
  this->remove(this->indexOf(t));
  return true;
}

template<class T>
bool ArrayList<T>::removeAll(Collection<T> *c){
  Iterator<T> *temp = c->iterator();
  while(temp->hasNext()){
    this->remove(temp->next());
  }
  return false;
}

template<class T>
bool ArrayList<T>::retainAll(Collection<T> *c){
  return false;
}

template<class T>
typename ArrayList<T>::size_t ArrayList<T>::size(){
  return this->count;
}

//create a new array containing all elements in proper order.
template<class T>
T* ArrayList<T>::toArray(){
  return 0;
}

//take argument pointer to create and return an array containing all elements in proper order
template<class T>
T* ArrayList<T>::toArray(T* arr){
  return 0;
}


/********************************************************/
/* List Node                                            */
/********************************************************/


template<class T>
ArrayList<T>::listNode::listNode(T t){
  this->init();
  this->data = t;
}

template<class T>
bool ArrayList<T>::listNode::add(T t){
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

template<class X>
bool ArrayList<X>::listNode::add(X x, index_t n){
  if(n > 0)
    return this->next->add(x, n - 1);
  else if(n == 0)
    return this->next->add(x);
  return false;
}

template<class T>
T ArrayList<T>::listNode::remove(index_t n){
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
T ArrayList<T>::listNode::get(index_t n) const{
  if(n > 0)
    return this->next->get(n - 1);
  if(n == 0)
    return this->data;
  //else
    //wtf
  return 0;
}

template<class T>
typename ArrayList<T>::index_t ArrayList<T>::listNode::find(T t, index_t n){
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
typename ArrayList<T>::index_t ArrayList<T>::listNode::backFind(T t, index_t n){
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
void ArrayList<T>::listNode::init(){
  this->next = 0;
  this->prev = 0;
}


/********************************************************/
/* List Iterator                                        */
/********************************************************/


template<class T>
ArrayList<T>::listIterator::listIterator(ArrayList<T> *thisList){
  this->theList = thisList;
  this->idx = 0;
}

template<class T>
ArrayList<T>::listIterator::listIterator(ArrayList<T> *thisList, index_t n){
  this->theList = thisList;
  this->idx = n;
}

template<class T>
bool ArrayList<T>::listIterator::hasNext(){
  if(this->idx < theList->size())
    return true;
  else
    return false;
}

template<class T>
T ArrayList<T>::listIterator::next(){
  return theList->get(this->idx++);
}

template<class T>
void ArrayList<T>::listIterator::remove(){
  theList->remove(idx);
}

template<class T>
void ArrayList<T>::listIterator::reset(){
  this->idx = 0;
}

