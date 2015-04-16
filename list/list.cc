template<class T>
gxy::list<T>::list():head(0), tail(0), size(0){  }

template<class T>
gxy::list<T>::~list(){
  this->clear();
}

template<class T>
void gxy::list<T>::pushFront(gxy::list<T>::value_type c){
  //Empty list
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->head->previous = new node(c, 0, this->head);
    this->head = this->head->previous;
  }
  this->size++;
}

template<class T>
void gxy::list<T>::pushBack(gxy::list<T>::value_type c){
  if(this->head == 0 && this->tail == 0){
    this->head = this->tail = new node(c);
  } else {
    this->tail->next = new node(c, this->tail, 0);
    this->tail = this->tail->next;
  }
  this->size++;
}

template<class T>
typename gxy::list<T>::value_type gxy::list<T>::popFront(){
  gxy::list<T>::value_type ret;
  if(this->head == 0){
    ret = 0;
  } else if(this->head == this->tail){
    ret = this->head->data;
    delete this->head;
    this->head = this->tail = 0;
  } else {
    ret = this->head->data;
    this->head = this->head->next;
    delete this->head->previous;
  }
  this->size--;
  return ret;
}

template<class T>
typename gxy::list<T>::value_type gxy::list<T>::popBack(){
  gxy::list<T>::value_type ret;
  if(this->tail == 0){
    ret = 0;
  } else if(this->head == this->tail){
    ret = this->head->data;
    delete this->head;
    this->head = this->tail = 0;
  } else {
    ret = this->tail->data;
    this->tail = this->tail->previous;
    delete this->tail->next;
  }
  this->size--;
  return ret;
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::insert(gxy::list<T>::iterator it, gxy::list<T>::const_reference val){
  list<T>::node* tmp = new list<T>::node(val, it.accessNode()->previous, it.accessNode());
  it.accessNode()->previous->next = tmp;
  it.accessNode()->previous = tmp;
  ++this->size;
  return list<T>::iterator(it.accessNode()->previous);
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::insert(gxy::list<T>::iterator it, gxy::list<T>::size_t n, gxy::list<T>::const_reference val){
  gxy::list<T>::iterator tmp(it.accessNode()->previous);
  for(unsigned int i = 0; i < n; ++i){
    this->insert(it, val);
  }
  return tmp;
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::insert(gxy::list<T>::iterator it, gxy::list<T>::iterator first, gxy::list<T>::iterator last){
  gxy::list<T>::iterator tmp(it.accessNode()->previous);
  for(auto itr = first; itr != last; ++itr){
    this->insert(it, *itr);
  }
  return tmp;
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::erase(gxy::list<T>::iterator it){
  gxy::list<T>::iterator tmp(it.accessNode()->next);
  it.accessNode()->previous = it.accessNode()->next;
  it.accessNode()->next = it.accessNode()->previous;
  delete it.accessNode();
  return tmp;
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::erase(gxy::list<T>::iterator first, gxy::list<T>::iterator last){
  gxy::list<T>::iterator tmp;
  for(auto it = first; it != last; ++it){
    tmp = this->erase(it);
  }
  return gxy::list<T>::iterator(tmp);
}

template<class T>
void gxy::list<T>::clear(){
  while(!this->isEmpty()){
    this->popFront();
  }
}

template<class T>
typename gxy::list<T>::reference gxy::list<T>::get(list<T>::size_t idx){
  return this->head->get(idx);
}

template<class T>
typename gxy::list<T>::const_reference gxy::list<T>::get(list<T>::size_t idx) const{
  return this->get(idx);
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::begin(){
  return gxy::list<T>::iterator(this->head);
}

template<class T>
const typename gxy::list<T>::iterator gxy::list<T>::begin() const{
  return this->begin();
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::end(){
  return gxy::list<T>::iterator(0);
}

template<class T>
const typename gxy::list<T>::iterator gxy::list<T>::end() const{
  return this->end();
}

template<class T>
typename gxy::list<T>::size_t gxy::list<T>::length(){
  return this->size;
}

template<class T>
typename gxy::list<T>::size_t gxy::list<T>::length() const{
  return this->length();
}

template<class T>
bool gxy::list<T>::isEmpty(){
  return this->size == 0;
}

template<class T>
typename gxy::list<T>::reference gxy::list<T>::operator[](gxy::list<T>::size_t idx){
  return this->get(idx);
}

//Iterator implementation
template<class T>
gxy::list<T>::iterator::iterator():ptr(0){  }

template<class T>
gxy::list<T>::iterator::iterator(const gxy::list<T>::iterator& that):ptr(that.ptr){  }

template<class T>
gxy::list<T>::iterator::iterator(typename gxy::list<T>::node* that):ptr(that){  }

template<class T>
typename gxy::list<T>::iterator& gxy::list<T>::iterator::operator=(const gxy::list<T>::iterator& rhs){
  this->ptr = rhs.ptr;
  return *this;
}

template<class T>
typename gxy::list<T>::iterator& gxy::list<T>::iterator::operator++(){
  if(this->ptr){
    this->ptr = this->ptr->next;
  }
  return *this;
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::iterator::operator++(int){
  gxy::list<T>::iterator tmp(*this);
  ++(*this);
  return tmp;
}

template<class T>
typename gxy::list<T>::iterator& gxy::list<T>::iterator::operator--(){
 if(this->ptr){
    this->ptr = this->ptr->previous;
  }
  return *this;
}

template<class T>
typename gxy::list<T>::iterator gxy::list<T>::iterator::operator--(int){
  gxy::list<T>::iterator tmp(*this);
  --(*this);
  return tmp;
}

template<class T>
typename gxy::list<T>::reference gxy::list<T>::iterator::operator*(){
  return this->ptr->data;
}

template<class T>
typename gxy::list<T>::pointer gxy::list<T>::iterator::operator->(){
  return &(this->ptr->data);
}

template<class T>
bool gxy::operator==(const typename gxy::list<T>::iterator& lhs, const typename gxy::list<T>::iterator& rhs){
  return lhs.ptr == rhs.ptr;
}

template<class T>
bool gxy::operator!=(const typename gxy::list<T>::iterator& lhs, const typename gxy::list<T>::iterator& rhs){
  return !gxy::operator==(lhs, rhs);
}

template<class T>
typename gxy::list<T>::node*& gxy::list<T>::iterator::accessNode(){
  return this->ptr;
}

//node implementation
template<class T>
gxy::list<T>::node::node(gxy::list<T>::const_reference c):data(c), previous(0), next(0){
}

template<class T>
gxy::list<T>::node::node(gxy::list<T>::const_reference c, list<T>::node* p, list<T>::node* n):data(c), previous(p), next(n){ 
}

template<class T>
typename gxy::list<T>::reference gxy::list<T>::node::get(gxy::list<T>::size_t idx){
  gxy::list<T>::value_type ret;
  if(idx == 0){
    ret = this->data;
  } else {
    ret = this->next->get(idx - 1);
  }
  gxy::list<T>::reference tmp = ret;
  return tmp;
}

