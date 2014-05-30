
using namespace Jing;
//using Jing::exception;

void list::init(){
  this->first = 0;
  this->last = 0;
  this->count = 0;
  this->iter = new listIterator(this);
}

list::list(){
  this->init();
}

list::list(AbstractList *c){
  this->init();
  this->addAll(c);
}

bool list::add(Object obj){
  return this->add(t, 0);
}

bool list::add(Object obj, index_t n){
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

bool list::addAll(AbstractList *c){
  listIterator *iter = (listIterator*)c->iterator();
  bool ret = true;
  while(iter->hasNext()){
    if( !this->add(iter->next()) )
      ret = false;
  }
  return ret;
}

void list::clear(){
  while(this->size() > 0){
    this->remove();
  }
}

bool list::contains(Object obj) const{
  if(this->first->find(t, 0) > this->size())
    return false;
  else return true;
}

bool list::containsAll(Collection *c) const{
  Iterator *temp = c->iterator();
  while(temp->hasNext()){
    if(!this->contains(temp->next())){
      return false;
    }
  }
  return true;
}

bool list::equals(Collection *c) const{
  return false;
}

index_t list::indexOf(Object obj) const{
  return this->first->find(t, 0);
}

index_t list::lastIndexOf(Object obj) const{
  return this->last->backFind(t, this->size() - 1);
}

Object list::get(index_t n) const{
  if(n >= this->size()){
    throw listIndexOutOfBounds(*this, n);
  }
  return this->first->get(n);
}

int list::hashCode() const{
  return 0;
}

bool list::isEmpty() const{
  if(this->size() == 0)
    return true;
  else
    return false;
}

Iterator *list::iterator() const{
  this->iter->reset();
  return this->iter;
}

Object list::remove(){
  return this->remove((index_t)0);
}

Object list::remove(index_t n){
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

bool list::remove(Object obj){
  index_t idx = this->indexOf(t);
  if(idx != -1){
    this->remove(idx);
    return true;
  }
  return false;
}

bool list::removeAll(AbstractList *c){
  Iterator *temp = c->iterator();
  while(temp->hasNext()){
    this->remove(temp->next());
  }
  return false;
}

void list::removeRange(int fromIndex, int toIndex){
}

size_t list::size() const{
  return this->count;
}

//create a new array containing all elements in proper order.
Object* list::toArray(){
  return 0;
}

//take argument pointer to create and return an array containing all elements in proper order
void list::toArray(Object* arr){
  return 0;
}


/********************************************************/
/* List Node                                            */
/********************************************************/


list::listNode::listNode(Object obj){
  this->init();
  this->data = t;
}

bool list::listNode::add(Object obj){
  return this->add(t, 0);

}

bool list::listNode::add(Object obj, index_t n){
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

Object list::listNode::remove(index_t n){
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

    Object temp = this->data;
    //be careful.  only if generated with 'new', and may not be thread safe.
    delete this;
    return temp;
  }
  //else
    //derp
  return 0;
}

Object list::listNode::get(index_t n) const{
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

index_t list::listNode::find(Object obj, index_t n){
  if(this->data != t){
    if(this->next != 0){
      return this->next->find(t, n + 1);
    }
  }
  else if(this->data == t)
    return n;
  return -1;
}

index_t list::listNode::backFind(Object obj, index_t n){
  if(this->data != t){
    if(this->prev != 0){
      return this->prev->backFind(t, n - 1);
    }
  }
  else if(this->data == t)
    return n;
  return -1;
}

void list::listNode::init(){
  this->next = 0;
  this->prev = 0;
}


/********************************************************/
/* List Iterator                                        */
/********************************************************/


list::listIterator::listIterator(list *thisList){
  this->theList = thisList;
  this->idx = 0;
}

list::listIterator::listIterator(list *thisList, index_t n){
  this->theList = thisList;
  this->idx = n;
}

bool list::listIterator::hasNext(){
  if(this->idx < theList->size())
    return true;
  else
    return false;
}

Object list::listIterator::next(){
  return theList->get(this->idx++);
}

void list::listIterator::remove(){
  theList->remove(idx);
}

void list::listIterator::reset(){
  this->idx = 0;
}

/**********************
 *  IndexOutOfBounds  *
 **********************/

void list::listIndexOutOfBounds::initWithList(const list& theList){
  this->msg = "\n";
  this->msg += "Index out of bounds.\n";
  this->msg += "List length: ";
  this->msg += theList.size();
  this->msg += "\n";
}

list::listIndexOutOfBounds::listIndexOutOfBounds(const char * message):exception(message){
}

list::listIndexOutOfBounds::listIndexOutOfBounds(const string& message):exception(message){
}

list::listIndexOutOfBounds::listIndexOutOfBounds(const list& theList){
  this->initWithList(theList);
}

list::listIndexOutOfBounds::listIndexOutOfBounds(const list& theList, int index){
  this->initWithList(theList);
  this->msg += "Given index: ";
  this->msg += (index);
  this->msg += "\n";
}

//const string& listIndexOutOfBounds::listIndexOutOfBounds::what() const{
//}
//

