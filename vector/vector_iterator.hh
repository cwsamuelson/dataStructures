#ifndef __GALAXY_VECTOR_ITERATOR_H__
#define __GALAXY_VECTOR_ITERATOR_H__

class vector_iterator{
public:
  typedef char              value_type;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef unsigned long     size_t;

private:
  size_t idx_;
  pointer data_;

public:
  vector_iterator(const vector_iterator& other);
  vector_iterator(pointer ptr);
  vector_iterator(pointer ptr, size_t idx);
  virtual ~vector_iterator() = default;

  vector_iterator& operator=(const vector_iterator& rhs);

  vector_iterator& operator++();
  vector_iterator  operator++(int);
  vector_iterator& operator--();
  vector_iterator  operator--(int);

  reference operator*();
  pointer operator->();

  friend bool operator==(const vector_iterator& lhs, const vector_iterator& rhs);
  friend bool operator!=(const vector_iterator& lhs, const vector_iterator& rhs);
};

bool operator==(const vector_iterator& lhs, const vector_iterator& rhs);
bool operator!=(const vector_iterator& lhs, const vector_iterator& rhs);

#include"vector_iterator.cc"

#endif

