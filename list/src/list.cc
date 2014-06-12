#include<Jing/list>

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
  return this->insert(obj, 0);
}

void Jing::list::insert(Jing::Object& obj, Jing::index_t idx){
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
  listNode *temp = first;
  --this->count;
  //adjust first pointer
  if(idx == 0){
    this->first = this->first->next;
  //remove last value
  //might not need && (idx < -1)
  } else if( (idx >= this->size()) && (idx < -1) ){
    this->last = this->last->prev;
    return this->last->next->remove((index_t)0);
  }
  //idx is unsigned int
  //  will never be < 0

  //remove current first item
  return temp->remove(idx);
}

void Jing::list::removeAll(Collection& c, Jing::index_t idx){
  Iterator& iter = c.iterator();
  for(int i = 0; i < idx; ++i){
    iter.next();
  }
  while(iter.hasNext()){
    this->remove(iter.next());
  }
}

void Jing::list::remove(Jing::Object& obj){
  Jing::index_t idx = this->indexOf(obj);
  if(idx != -1){
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

bool Jing::list::equals(Jing::Object& c) const{
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
  for(int i = 0; i < this->size(); ++i){
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


Jing::list::listNode::listNode(Jing::Object& obj):data(obj),next(0),prev(0){
}

bool Jing::list::listNode::add(Jing::Object& obj){
  return this->add(obj, 0);
}

bool Jing::list::listNode::add(Jing::Object& obj, Jing::index_t idx){
  if(idx < 0)
    return false; 
  if(idx > 0){
    if(this->next == 0){
      this->next = new listNode(obj);
      this->next->prev = this;
      return true;
    }
    return this->next->add(obj, idx - 1);
  }
  else if(idx == 0){
    if(this->prev == 0){
      this->prev = new listNode(obj);
      this->prev->next = this;
    }else{
      this->prev->next = new listNode(obj);
      this->prev->next->next = this;
      this->prev = this->prev->next;
    }
    return true;
  }
  return false;
}

Jing::Object& Jing::list::listNode::remove(Jing::index_t idx){
  if(idx > 0)
    return this->next->remove(idx - 1);
  else if(idx == 0){
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
}

Jing::Object& Jing::list::listNode::get(Jing::index_t idx) const{
  if(idx > 0){
    if(this->next != 0){
      return this->next->get(idx - 1);
    }
    //inconsistent state, bigger problems, ignoring for now.
  /*
     else {
      return 0;
    }
  */
  } else if(idx == 0){
    return this->data;
  }
}

bool Jing::list::listNode::assign(Jing::index_t idx, Jing::Object& obj){
  if(idx > 0){
    return this->next->assign(idx - 1, obj);
  } else if(idx == 0){
    this->data = obj;
  }
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
