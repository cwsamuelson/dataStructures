#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include"node.hh"

//Bidirectional, not random access
class iterator{
private:
  node* ptr;

public:
  iterator();
  iterator(const iterator& that);
  iterator(node* that);
  virtual ~iterator() = default;
  
  bool hasNext();
  char next();
  char remove();
  
  iterator& operator=(const iterator& rhs);
  
  iterator& operator++();
  iterator& operator++(int);
  iterator& operator--();
  iterator& operator--(int);
};

#endif
