//#include<Jing/List>

template<class T>
Jing::List<T>::List(){
  //This list can only contain objects that inherit from Jing::Object references
  can_copy<T, Jing::Object&>();
  this->first = 0;
  this->last = 0;
  this->count = 0;
  this->iter = new listIterator(*this);
}

template<class T>
Jing::List<T>::List(Collection<T>& c):List(){
  this->insertAll(c);
}

template<class T>
void Jing::List<T>::insert(T& obj){
  this->insert(obj, this->size());
}

//TODO:Optimize by inserting from back using negative indexes
template<class T>
void Jing::List<T>::insert(T& obj, Jing::index_t idx){
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
void Jing::List<T>::insertAll(Collection<T>& c){
  this->insertAll(c, this->size() - 1);
}

template<class T>
void Jing::List<T>::insertAll(Collection<T>& c, Jing::index_t idx){
  Iterator<T>& iter = c.iterator();
  Jing::index_t n = idx;
  while(iter.hasNext()){
    this->insert(iter.next(), n);
    ++n;
  }
  return;
}

template<class T>
T& Jing::List<T>::remove(){
  return this->remove((Jing::index_t)0);
}

template<class T>
T& Jing::List<T>::remove(Jing::index_t idx){
  T& ret = *this->first->data.clone();
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
  } else if(idx >= this->size()){
    return this->remove(this->size() - 1);
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
void Jing::List<T>::remove(T& obj){
  Jing::index_t idx = this->indexOf(obj);
  if(idx != (Jing::index_t)-1){
    this->remove(idx);
    return;
  }
  return;
}

template<class T>
void Jing::List<T>::removeAll(Collection<T>& c){
  Iterator<T>& iter = c.iterator();
  while(iter.hasNext()){
    this->remove(iter.next());
  }
}

template<class T>
void Jing::List<T>::removeRange(Jing::index_t fromIndex, Jing::index_t toIndex){
  for(Jing::index_t i = fromIndex; i < toIndex; ++i){
    this->remove(fromIndex);
  }
}

template<class T>
T& Jing::List<T>::get() const{
  return this->get(0);
}

template<class T>
T& Jing::List<T>::get(Jing::index_t idx) const{
  //just return last
  if(idx >= this->size()){
    return this->first->get(this->size() - 1);
    //throw listIndexOutOfBounds(*this, idx);
  }
  return this->first->get(idx);
}

template<class T>
Jing::AbstractList<T>& Jing::List<T>::get(Jing::index_t start, Jing::index_t end) const{
  List& ret = *new List();
  for(Jing::index_t i = start; i < end; ++i){
    ret.insert(this->get(i));
  }
  return (AbstractList<T>&)ret;
}

template<class T>
T& Jing::List<T>::assign(Jing::index_t idx, T& obj){
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
void Jing::List<T>::clear(){
  while(this->size() > 0){
    this->remove();
  }
}

template<class T>
bool Jing::List<T>::contains(T& obj) const{
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
bool Jing::List<T>::containsAll(Collection<T>& c) const{
  Iterator<T>& iter = c.iterator();
  while(iter.hasNext()){
    if(!this->contains(iter.next())){
      return false;
    }
  }
  return true;
}

template<class T>
Jing::index_t Jing::List<T>::indexOf(T& obj) const{
  return this->first->find(obj, 0);
}

template<class T>
Jing::index_t Jing::List<T>::lastIndexOf(T& obj) const{
  return this->last->backFind(obj, this->size() - 1);
}

//TODO:can't do a valid check against an object, needs to be abstractList or collection
template<class T>
bool Jing::List<T>::equals(Jing::Object& obj) const{
//  for(int i = 0; i < this->size(); ++i){
//  }
  return false;
}

template<class T>
Jing::Iterator<T>& Jing::List<T>::iterator() const{
  this->iter->reset();
  return *(this->iter);
}

//Hash based on murmur hash 3 found on wikipedia.
//  https://en.wikipedia.org/wiki/MurmurHash#Implementations
//Murmur hash requires 3 parameters.
//  1. key
//  2. length
//  3. seed
//For this implementation
//  the key is the stored letter
//  the length is one
//  the seed will be constant
//  need to make the seed to be random, and not constant are described:
//One reason is that attackers may use the properties of a hash function 
//  to construct a denial of service attack. They could do this by providing
//  strings to your hash function that all hash to the same value destroying
//  the performance of your hash table. But if you use a different seed for
//  each run of your program, the set of strings the attackers must use changes.
//This feature is not included for simplicity,
//  and for the sake of not including std libraries (keeping all code my own)
/*
       char:8   bits
       long:32  bits
  long long:64  bits
*/
template<class T>
unsigned long long Jing::List<T>::hash() const{
  unsigned long len = 1;
  unsigned long long key = 0;
  unsigned long seed = 5871;

  const unsigned long c1 = 0xcc9e2d51;
  const unsigned long c2 = 0x1b873593;
  const unsigned long r1 = 15;
  const unsigned long r2 = 13;
  const unsigned long m = 5;
  const unsigned long n = 0xe6546b64;

  unsigned long long hash = seed;
  unsigned int nblocks = 0;

  for(int j = 0; j < this->size(); ++j){
    key = this->get(j).hash();
    for(unsigned long long i = 0, mask = 0xf; i < 16; ++i, mask << 4){
      unsigned long long k = (key & mask) >> (4 * i);
      ++nblocks;

      k = k * c1;
      k = (k << r1) | (k >> (32 - r1));
      k = k * c2;

      hash = hash ^ k;
      hash = (hash << r2) | (hash >> (32 - r2));
      hash = hash * m + n;
    }
  }

  len = nblocks;
  hash = hash ^ len;

  hash = hash ^ (hash >> 16);
  hash = hash * 0x85ebca6b;
  hash = hash ^ (hash >> 13);
  hash = hash * 0xc2b2ae35;
  hash = hash ^ (hash >> 16);

  return hash;
}

template<class T>
Jing::Object* Jing::List<T>::clone() const{
  Jing::List<T>* temp = new List<T>(*this);
  return temp;
}

//create a new array containing all elements in proper order.
template<class T>
Jing::Object* Jing::List<T>::toArray() const{
  return 0;
}

//take argument pointer to create and return an array containing all elements in proper order
//assumes enough memory was allocated by user
template<class T>
void Jing::List<T>::toArray(Jing::Object* arr) const{
  for(Jing::index_t i = 0; i < this->size(); ++i){
    arr[i] = this->get(i);
  }
}

template<class T>
bool Jing::List<T>::isEmpty() const{
  if(this->size() == 0)
    return true;
  else
    return false;
}

template<class T>
Jing::size_t Jing::List<T>::size() const{
  return this->count;
}


/********************************************************/
/* List Node                                            */
/********************************************************/


template<class T>
Jing::List<T>::listNode::listNode(T& obj):
  data(obj),
  prev(0),
  next(0){  }

template<class T>
Jing::List<T>::listNode::listNode(T& obj, listNode* prev, listNode* next):
  data(obj),
  prev(prev),
  next(next){ }

template<class T>
bool Jing::List<T>::listNode::add(T& obj, Jing::index_t idx){
  if(idx > 0){
    //idx is too big.  o well!
    //can't continue, install in place
    if(this->next == 0){
      this->next = new listNode(obj, this, 0);
      return true;
    //install somewhere ahead
    } else {
      return this->next->add(obj, idx - 1);
    }
  //install in place
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
T& Jing::List<T>::listNode::remove(Jing::index_t idx){
  if(idx > 0){
    return this->next->remove(idx - 1);
  }else if(idx == 0){
    if(this->prev != 0 && this->next != 0){
      this->prev->next = this->next;
      this->next->prev = this->prev;
    } else if(this->prev != 0 && this->next == 0){
      this->prev->next = 0;
    } else if(this->prev == 0 && this->next != 0){
      this->next->prev = 0;
    }

    T& ret = this->data;
    //be careful.  only if generated with 'new', and may not be thread safe.
    delete this;
    return ret;
  }
}

template<class T>
T& Jing::List<T>::listNode::get(Jing::index_t idx) const{
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
bool Jing::List<T>::listNode::assign(Jing::index_t idx, T& obj){
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
Jing::index_t Jing::List<T>::listNode::find(T& obj, Jing::index_t idx){
  if(!this->data.equals(obj)){
    if(this->next != 0){
      return this->next->find(obj, idx + 1);
    } else {
      return -1;
    }
  } else if(this->data.equals(obj))
    return idx;
  return -1;
}

template<class T>
Jing::index_t Jing::List<T>::listNode::backFind(T& obj, Jing::index_t idx){
  if(!this->data.equals(obj)){
    if(this->prev != 0){
      return this->prev->backFind(obj, idx - 1);
    } else {
      return -1;
    }
  } else if(this->data.equals(obj))
    return idx;
  return -1;
}


/********************************************************
 * List Iterator                                        *
 ********************************************************/
//Try optimizing by pointing the iterator at the individual nodes


template<class T>
Jing::List<T>::listIterator::listIterator(Jing::List<T>& thisList):theList(thisList){
  this->curNode = this->theList.first;
}

template<class T>
bool Jing::List<T>::listIterator::hasNext(){
  if(this->curNode !=0 && this->curNode->next != 0)
    return true;
  else
    return false;
return false;
}

template<class T>
T& Jing::List<T>::listIterator::next(){
  if(this->curNode->next != 0){
    this->curNode = this->curNode->next;
    return this->curNode->prev->data;
  } else {
    return this->curNode->data;
  }
}

template<class T>
void Jing::List<T>::listIterator::remove(){
  this->curNode->remove(0);
}

template<class T>
void Jing::List<T>::listIterator::reset(){
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
