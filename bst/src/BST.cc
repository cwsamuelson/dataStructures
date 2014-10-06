//Constructors
template<class X, class Y>
Jing::BST<X, Y>::BST():
  root(0), 
  count(0){
  //iter(0){
  can_copy<X, Jing::Comparable<X>>();
  can_copy<Y, Jing::Object&>();
}

template<class X, class Y>
Jing::BST<X, Y>::BST(AbstractTree<X, Y>& at): BST(){
  this->insertAll(at);
}

template<class X, class Y>
Jing::BST<X, Y>::BST(AbstractList<X>& alx, AbstractList<Y>& aly):BST(){
  this->insertAll(alx, aly);
}

//Inserts
//  [inherited from collection]
template<class X, class Y>
void Jing::BST<X, Y>::insert(Y& obj){
}

template<class X, class Y>
void Jing::BST<X, Y>::insertAll(Collection<Y>& c){
}

//  [inherited from abstractTree]
template<class X, class Y>
void Jing::BST<X, Y>::insert(X& x, Y& y){
  if(this->root == 0){
    this->root = new treeNode(x, y);
  } else {
    this->root->add(x, y);
  }
}

template<class X, class Y>
void Jing::BST<X, Y>::insertAll(AbstractTree<X,Y>& at){
}

template<class X, class Y>
void Jing::BST<X, Y>::insertAll(AbstractList<X>& alx, AbstractList<Y>& aly){
}

//Gets
template<class X, class Y>
X& Jing::BST<X, Y>::get(Y& y) const{
}

template<class X, class Y>
X& Jing::BST<X, Y>::getByKey(Y& y) const{
}

template<class X, class Y>
Y& Jing::BST<X, Y>::getByData(X& x) const{
}


//Removes
//  [inherited from collection]
//Remove by key
template<class X, class Y>
void Jing::BST<X, Y>::remove(Y& y){
}

template<class X, class Y>
void Jing::BST<X, Y>::removeAll(Collection<X>& c){
}

//  [inherited from abstractTree]
template<class X, class Y>
void Jing::BST<X, Y>::remove(X& x){
}

template<class X, class Y>
void Jing::BST<X, Y>::removeByKey(X& x){
}

template<class X, class Y>
void Jing::BST<X, Y>::removeByData(Y& y){
}

template<class X, class Y>
bool Jing::BST<X, Y>::removeAll(AbstractList<X>& al){
}

template<class X, class Y>
bool Jing::BST<X, Y>::removeAllByKey(AbstractList<X>& al){
}

template<class X, class Y>
bool Jing::BST<X, Y>::removeAllByData(AbstractList<Y>& al){
}

//Contains
template<class X, class Y>
bool Jing::BST<X, Y>::containsKey(X& x) const{
}

template<class X, class Y>
bool Jing::BST<X, Y>::containsValue(Y& y) const{
}

//  [inherited from colleciton]
template<class X, class Y>
bool Jing::BST<X, Y>::contains(Y& obj) const{
}

template<class X, class Y>
bool Jing::BST<X, Y>::containsAll(Collection<Y>& c) const{
}

//Equality
template<class X, class Y>
bool Jing::BST<X, Y>::equals(Jing::BST<X, Y>& obj) const{
}

//  [inherited from object]
template<class X, class Y>
bool Jing::BST<X, Y>::is_equal(const Object& obj)const{
  const Jing::BST<X, Y>& obj_derived = dynamic_cast<const Jing::BST<X, Y>&>(obj);
  return false;
}

template<class X, class Y>
bool Jing::BST<X, Y>::equals(Jing::Object& obj) const{
  return false;
}

//States
//  hash
//  [inherited from object]
template<class X, class Y>
unsigned long long Jing::BST<X, Y>::hash() const{
}

//  clone
template<class X, class Y>
Jing::Object* Jing::BST<X, Y>::clone() const{
}

//  empty
template<class X, class Y>
bool Jing::BST<X, Y>::isEmpty() const{
}

//  size
template<class X, class Y>
Jing::size_t Jing::BST<X, Y>::size() const{
}

// clear
template<class X, class Y>
void Jing::BST<X, Y>::clear(){
}

//  iterator
//  [inherited from iterable]
template<class X, class Y>
Jing::Iterator<Y>* Jing::BST<X, Y>::iterator() const{
}


/********************************************************/
/* Tree Node                                            */
/********************************************************/


template<class X, class Y>
Jing::BST<X, Y>::treeNode::treeNode(X& x, Y& y):
  treeNode(x, y, 0){  }

template<class X, class Y>
Jing::BST<X, Y>::treeNode::treeNode(X& x, Y& y, treeNode* parent):
  parent(parent), 
  left(0), 
  right(0), 
  key(x), 
  value(y){  }

template<class X, class Y>
bool Jing::BST<X, Y>::treeNode::add(X& x, Y& y){
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
Y& Jing::BST<X, Y>::treeNode::remove(X& x){
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
Y& Jing::BST<X, Y>::treeNode::get(X& x) const{
  if(this->key.compareTo(x) == 0){
    return this->value;
  } else if(this->key.compareTo(x) < 0){
    return this->left->get(x);
  } else if(this->key.compareTo(x) > 0){
    return this->right->get(x);
  }
}

template<class X, class Y>
X& Jing::BST<X, Y>::treeNode::find(Y& y) const{
}


/********************************************************/
/* Tree iterator                                        */
/********************************************************/
/*
template<class X, class Y>
Jing::BST<X, Y>::treeIterator::treeIterator(BST<X, Y> *thisTree):theTree(thisTree){
}

template<class X, class Y>
bool Jing::BST<X, Y>::treeIterator::hasNext(){
}

template<class X, class Y>
Y& Jing::BST<X, Y>::treeIterator::next(){
}

template<class X, class Y>
void Jing::BST<X, Y>::treeIterator::remove(){
}

template<class X, class Y>
void Jing::BST<X, Y>::treeIterator::reset(){
}
*/
