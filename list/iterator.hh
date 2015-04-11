#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include"node.hh"

namespace gxy{

//Bidirectional, not random access
class iterator{
public:
  node* ptr;

  iterator();
  iterator(const iterator& that);
  iterator(node* that);
  virtual ~iterator() = default;
  
  bool hasNext();
  char next();
  char remove();
  
  iterator& operator=(const iterator& rhs);
  
  iterator& operator++();
  iterator  operator++(int);
  iterator& operator--();
  iterator  operator--(int);

  char& operator*();
  char* operator->();

  friend bool operator==(const iterator& lhs, const iterator& rhs);
  friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !operator==(lhs, rhs); }

  node*& accessNode();

};

bool operator==(const iterator& lhs, const iterator& rhs);

}

#endif

