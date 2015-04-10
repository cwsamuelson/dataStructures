#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include"node.hpp"

//Bidirectional, not random access
class iterator{
public:
  node* ptr;
  
  iterator();
  iterator(const iterator& that);
  iterator(node* that);
  virtual ~iterator();
  
  bool hasNext();
  char next();
  char remove();
  
  iterator& operator=(const iterator& rhs);
  
  iterator operator++();
  iterator operator++(int);
  iterator operator--();
  iterator operator--(int);
};

#endif
