#ifndef __GALAXY_VECTOR_ITERATOR_H__
#define __GALAXY_VECTOR_ITERATOR_H__

template<class T>
class vector;

template<class T>
class vector_iterator{
public:
  typedef T                 value_type;
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

  friend vector<T>;

  template<class U>
  friend bool operator==(const vector_iterator<U>& lhs, const vector_iterator<U>& rhs);
  template<class U>
  friend bool operator!=(const vector_iterator<U>& lhs, const vector_iterator<U>& rhs);
};

template<class T>
bool operator==(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs);
template<class T>
bool operator!=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs);

#include"vector_iterator.cc"

#endif

