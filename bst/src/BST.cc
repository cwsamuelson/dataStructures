template<class X, class Y>
Jing::BST<X, Y>::BST():root(0), count(0), iter(0){
  can_copy<X, Jing::Object&>();
  can_copy<Y, Jing::Comparable<Y>&>();
}

template<class X, class Y>
Jing::BST<X, Y>::BST(AbstractTree<X, Y>& at):BST(){
  this->insert(at);
}

template<class X, class Y>
Jing::BST<X, Y>::BST(AbstractList<X>& alx, AbstractList<Y>& aly):BST(){
  this->insert(alx, aly);
}

template<class X, class Y>
bool Jing::BST<X, Y>::insert(X& x, Y& y){
  if(this->root == 0){
    ++this->count;
    this->root = new treeNode(x, y);
    return true;
  } else {
    bool ret = this->root->add(x, y);
    if(ret)
      ++this->count;
    return ret;
  }
}

template<class X, class Y>
bool Jing::BST<X, Y>::insertAll(AbstractTree<X, Y>& at){
  Iterator<Y> *it = at->iterator();
//  while(it->hasNext())
//    this->add();
}

template<class X, class Y>
bool Jing::BST<X, Y>::insertAll(AbstractList<X>& alx, AbstractList<Y>& aly){
  Iterator<X> *xiter = alx->iterator();
  Iterator<Y> *yiter = aly->iterator();

  while(xiter->hasNext() && yiter->hasNext()){
    this->add(xiter->next(), yiter->next());
  }
}

template<class X, class Y>
Y& Jing::BST<X, Y>::remove(X& x){
  return this->root->remove(x);
}

template<class X, class Y>
bool Jing::BST<X, Y>::removeAll(AbstractList<X>& al){
  Iterator<X> *it = al->iterator();
  while(it->hasNext())
    this->remove(it->next());
}

template<class X, class Y>
Y Jing::BST<X, Y>::get(X x) const{
  this->root->get(x);
}

template<class X, class Y>
X Jing::BST<X, Y>::getKey(Y y) const{
}

template<class X, class Y>
void Jing::BST<X, Y>::clear(){
  Iterator<Y> *it = this->iterator();
  while(it->hasNext()){
    this->root->remove(it->next());
  }
}

template<class X, class Y>
bool Jing::BST<X, Y>::contains(Y y) const{
  return this->containsKey(y);
}

template<class X, class Y>
bool Jing::BST<X, Y>::containsKey(X x) const{
//  return this->root->get(x);
}

template<class X, class Y>
bool Jing::BST<X, Y>::containsValue(Y y) const{
}

template<class X, class Y>
bool Jing::BST<X, Y>::containsAll(Collection<Y> *cy) const{
}

template<class X, class Y>
bool Jing::BST<X, Y>::isEmpty() const{
  if(this->size() == 0)
    return true;
  else return false;
}

template<class X, class Y>
bool Jing::BST<X, Y>::equals(AbstractTree<X, Y> *at) const{
}

template<class X, class Y>
bool Jing::BST<X, Y>::equals(Collection<Y> *c) const{
}

template<class X, class Y>
int Jing::BST<X, Y>::hashCode() const{
  return 0;
}

template<class X, class Y>
void Jing::BST<X, Y>::toArray(X *x, Y *y) const{
}

template<class X, class Y>
Iterator<Y> *Jing::BST<X, Y>::iterator() const{
  this->iter->reset();
  return this->iter;
}

template<class X, class Y>
size_t Jing::BST<X, Y>::size() const{
  return this->count;
}


/********************************************************/
/* Tree Node                                            */
/********************************************************/


template<class X, class Y>
void Jing::BST<X, Y>::treeNode::init(){
  this->left = 0;
  this->right = 0;
  this->parent = 0;
}

template<class X, class Y>
Jing::BST<X, Y>::treeNode::treeNode(X x, Y y){
  this->init();
  this->key = x;
  this->value = y;
}

template<class X, class Y>
bool Jing::BST<X, Y>::treeNode::add(X x, Y y){
  treeNode *temp;
  if(x == this->key){
    return false;
  } else if(x < this->key){
    if(this->left == 0){
      this->left = new treeNode(x, y);
      this->left->parent = this;
      return true;
    } else {
      return temp->add(x, y);
    }
  } else if(x > this->key){
    if(this->right == 0){
      this->right = new treeNode(x, y);
      this->right->parent = this;
      return true;
    } else {
      return temp->add(x, y);
    }
  }
}

template<class X, class Y>
Y Jing::BST<X, Y>::treeNode::remove(X x){
  if(x == this->key){
    if(this->left == 0 && this->right == 0){
      Y thing = this->value;
      delete this;
      return thing;
    } else if(!(this->left != 0 && this->right != 0)){
      treeNode *child;
      if(this->left != 0 && this->right == 0){
        child = this->left;
      } else if(this->left == 0 && this->right != 0){
        child = this->right;
      }
      if(child->key < parent->key){
        parent->left = child;
      } else if(child->key > parent->key){
        parent->right = child;
      }
      child->parent = this->parent;
    } else {
      //well shit, not sure how to handle this yet.
    }
  } else if(x < this->key){
    return this->left->remove(x);
  } else if(x > this->key){
    return this->right->remove(x);
  }
}

template<class X, class Y>
Y Jing::BST<X, Y>::treeNode::get(X x) const{
  if(x == this->key){
    return this->value;
  }
  else if(x < this->key){
    return this->left->get(x);
  }
  else if(x > this->key){
    return this->right->get(x);
  }
  else
    return 0;
}

template<class X, class Y>
X Jing::BST<X, Y>::treeNode::find(Y y) const{
}


/********************************************************/
/* Tree Node                                            */
/********************************************************/

template<class X, class Y>
Jing::BST<X, Y>::treeIterator::treeIterator(bst *thisList){
}

template<class X, class Y>
bool Jing::BST<X, Y>::treeIterator::hasNext(){
}

template<class X, class Y>
Y Jing::BST<X, Y>::treeIterator::next(){
}

template<class X, class Y>
void Jing::BST<X, Y>::treeIterator::remove(){
}

template<class X, class Y>
void Jing::BST<X, Y>::treeIterator::reset(){
}

