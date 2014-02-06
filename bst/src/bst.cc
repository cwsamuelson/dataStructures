
using namespace Jing;

template<class X, class Y>
void bst<X, Y>::init(){
  this->root = 0;
  this->count = 0;
  this->iter = 0;
}

template<class X, class Y>
bst<X, Y>::bst(){
  this->init();
}

template<class X, class Y>
bst<X, Y>::bst(AbstractTree<X, Y> *at){
  this->init();
  this->add(at);
}

template<class X, class Y>
//bst<X, Y>::bst(Collection<X> *cx, Collection<Y> *cy){
bst<X, Y>::bst(AbstractList<X> *alx, AbstractList<Y> *aly){
  this->init();
  this->add(alx, aly);
}

template<class X, class Y>
bool bst<X, Y>::add(X x, Y y){
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
bool bst<X, Y>::addAll(AbstractTree<X, Y> *at){
  Iterator<Y> *it = at->iterator();
//  while(it->hasNext())
//    this->add();
}

template<class X, class Y>
bool bst<X, Y>::addAll(AbstractList<X> *alx, AbstractList<Y> *aly){
  Iterator<X> *xiter = alx->iterator();
  Iterator<Y> *yiter = aly->iterator();

  while(xiter->hasNext() && yiter->hasNext()){
    this->add(xiter->next(), yiter->next());
  }
}

template<class X, class Y>
Y bst<X, Y>::remove(X x){
  return this->root->remove(x);
}

template<class X, class Y>
bool bst<X, Y>::removeAll(AbstractList<X> *al){
  Iterator<X> *it = al->iterator();
  while(it->hasNext())
    this->remove(it->next());
}

template<class X, class Y>
bool bst<X, Y>::removeAll(AbstractTree<X, Y> *at){
}

template<class X, class Y>
Y bst<X, Y>::get(X x) const{
  this->root->get(x);
}

template<class X, class Y>
X bst<X, Y>::getKey(Y y) const{
}

template<class X, class Y>
void bst<X, Y>::clear(){
  Iterator<Y> *it = this->iterator();
  while(it->hasNext()){
    this->root->remove(it->next());
  }
}

template<class X, class Y>
bool bst<X, Y>::contains(Y y) const{
  return this->containsKey(y);
}

template<class X, class Y>
bool bst<X, Y>::containsKey(X x) const{
//  return this->root->get(x);
}

template<class X, class Y>
bool bst<X, Y>::containsValue(Y y) const{
}

template<class X, class Y>
bool bst<X, Y>::containsAll(Collection<Y> *cy) const{
}

template<class X, class Y>
bool bst<X, Y>::isEmpty() const{
  if(this->size() == 0)
    return true;
  else return false;
}

template<class X, class Y>
bool bst<X, Y>::equals(AbstractTree<X, Y> *at) const{
}

template<class X, class Y>
bool bst<X, Y>::equals(Collection<Y> *c) const{
}

template<class X, class Y>
int bst<X, Y>::hashCode() const{
  return 0;
}

template<class X, class Y>
void bst<X, Y>::toArray(X *x, Y *y) const{
}

template<class X, class Y>
Iterator<Y> *bst<X, Y>::iterator() const{
  this->iter->reset();
  return this->iter;
}

template<class X, class Y>
typename bst<X, Y>::size_t bst<X, Y>::size() const{
  return this->count;
}


/********************************************************/
/* Tree Node                                            */
/********************************************************/


template<class X, class Y>
void bst<X, Y>::treeNode::init(){
  this->left = 0;
  this->right = 0;
  this->parent = 0;
}

template<class X, class Y>
bst<X, Y>::treeNode::treeNode(X x, Y y){
  this->init();
  this->key = x;
  this->value = y;
}

template<class X, class Y>
bool bst<X, Y>::treeNode::add(X x, Y y){
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
Y bst<X, Y>::treeNode::remove(X x){
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
Y bst<X, Y>::treeNode::get(X x) const{
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
X bst<X, Y>::treeNode::find(Y y) const{
}


/********************************************************/
/* Tree Node                                            */
/********************************************************/

template<class X, class Y>
bst<X, Y>::treeIterator::treeIterator(bst *thisList){
}

template<class X, class Y>
bool bst<X, Y>::treeIterator::hasNext(){
}

template<class X, class Y>
Y bst<X, Y>::treeIterator::next(){
}

template<class X, class Y>
void bst<X, Y>::treeIterator::remove(){
}

template<class X, class Y>
void bst<X, Y>::treeIterator::reset(){
}

