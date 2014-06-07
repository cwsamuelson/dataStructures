#include<Jing/list>

void Jing::list::init(){
  this->sameType = false;
  this->storedID = 0;
  this->first = 0;
  this->last = 0;
  this->count = 0;
  this->iter = new listIterator(this);
}

Jing::list::list(){
  this->init();
}

Jing::list::list(Collection& c){
  this->init();
  this->insertAll(c);
}

void Jing::list::insert(Jing::Object& obj){
  return this->insert(obj, 0);
}

void Jing::list::insert(Jing::Object& obj, index_t idx){
  //invalid index
  if(idx < 0)
    return; 
  ++this->count;
  //insert beginning
  if(idx == 0){
    //uninitialized beginning
    if(this->first == 0){
      this->first = new listNode(obj);
      this->last = this->first;
      return;
    //already initialized beginning
    }else{
      this->first->add(obj);
      this->first = this->first->prev;
      return;
    }
  //index is too big, just add at the end
  }else if(idx >= this->size()){
    this->last->add(obj, 1);
    this->last = this->last->next;
    return;
  //normal index, just crawl list for insert
  }else{
    this->first->add(obj, idx);
    return;
  }
  return;
}

void Jing::list::insertAll(Collection& c){
  this->insertAll(c, 0);
}

void Jing::list::insertAll(Collection& c, index_t idx){
  Iterator& iter = c.iterator();
  index_t n = idx;
  while(iter.hasNext()){
    this->insert(iter.next(), n);
    ++n;
  }
  return;
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

bool Jing::list::equals(Collection& c) const{
  return false;
}

index_t Jing::list::indexOf(Jing::Object& obj) const{
  return this->first->find(t, 0);
}

index_t Jing::list::lastIndexOf(Jing::Object& obj) const{
  return this->last->backFind(t, this->size() - 1);
}

Jing::Object& Jing::list::get(index_t n) const{
  if(n >= this->size()){
    throw listIndexOutOfBounds(*this, n);
  }
  return this->first->get(n);
}

int Jing::list::hashCode() const{
  return 0;
}

bool Jing::list::isEmpty() const{
  if(this->size() == 0)
    return true;
  else
    return false;
}

Iterator& Jing::list::iterator() const{
  this->iter->reset();
  return this->iter;
}

Jing::Object& Jing::list::remove(){
  return this->remove((index_t)0);
}

Jing::Object& Jing::list::remove(index_t idx){
  listNode *temp = first;
  --this->count;
  //adjust first pointer
  if(idx == 0){
    this->first = this->first->next;
  //remove last value
  } else if( (idx >= this->size()) && (idx < -1) ){
    this->last = this->last->prev;
    return this->last->next->remove((unsigned int)0);
  }else if(idx == -1){
    //exception..?
    return -1;
  }
  //remove current first item
  return temp->remove(n);
}

void Jing::list::remove(Jing::Object& obj){
  index_t idx = this->indexOf(obj);
  if(idx != -1){
    this->remove(idx);
    return true;
  }
  return false;
}

void Jing::list::removeAll(Collection& c){
  Iterator& iter = c.iterator();
  while(iter.hasNext()){
    this->remove(iter.next());
  }
  return;
}

void Jing::list::removeRange(int fromIndex, int toIndex){
  for(index_t i = fromIndex; i < toIndex; ++i){
    this->remove(i);
  }
}

size_t Jing::list::size() const{
  return this->count;
}

//create a new array containing all elements in proper order.
Jing::Object* Jing::list::toArray(){
  return 0;
}

//take argument pointer to create and return an array containing all elements in proper order
void Jing::list::toArray(Jing::Object* arr){
  return 0;
}


/********************************************************/
/* List Node                                            */
/********************************************************/


Jing::list::listNode::listNode(Jing::Object& obj){
  this->init();
  this->data = t;
}

bool Jing::list::listNode::add(Jing::Object& obj){
  return this->add(t, 0);

}

bool Jing::list::listNode::add(Jing::Object& obj, index_t n){
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

Jing::Object& Jing::list::listNode::remove(index_t n){
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

    Jing::Object& temp = this->data;
    //be careful.  only if generated with 'new', and may not be thread safe.
    delete this;
    return temp;
  }
  //else
    //derp
  return 0;
}

Jing::Object& Jing::list::listNode::get(index_t n) const{
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

index_t Jing::list::listNode::find(Jing::Object& obj, index_t n){
  if(!this->data.equals(obj)){
    if(this->next != 0){
      return this->next->find(obj, n + 1);
    }
  }
  else if(this->data.equals(obj))
    return n;
  return -1;
}

index_t Jing::list::listNode::backFind(Jing::Object& obj, index_t n){
  if(this->data != t){
    if(this->prev != 0){
      return this->prev->backFind(t, n - 1);
    }
  }
  else if(this->data == t)
    return n;
  return -1;
}

void Jing::list::listNode::init(){
  this->next = 0;
  this->prev = 0;
}


/********************************************************
 * List Iterator                                        *
 ********************************************************/
//Try optimizing by pointing the iterator at the individual nodes


Jing::listIterator::listIterator(list& thisList){
  this->theList = thisList;
  this->idx = 0;
}

Jing::listIterator::listIterator(list& thisList, index_t n){
  this->theList = thisList;
  this->idx = n;
}

bool Jing::listIterator::hasNext(){
  if(this->idx < theList->size())
    return true;
  else
    return false;
}

Jing::Object& Jing::listIterator::next(){
  return theList->get(this->idx++);
}

void Jing::listIterator::remove(){
  theList->remove(idx);
}

void Jing::listIterator::reset(){
  this->idx = 0;
}

/**********************
 *  IndexOutOfBounds  *
 **********************/

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

Jing::list::listIndexOutOfBounds::listIndexOutOfBounds(const list& theList, int index){
  this->initWithList(theList);
  this->msg += "Given index: ";
  this->msg += (index);
  this->msg += "\n";
}

//const string& listIndexOutOfBounds::listIndexOutOfBounds::what() const{
//}
//

