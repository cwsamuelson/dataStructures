#ifndef __GALAXY_LIST_ITERATOR_H__
#define __GALAXY_LIST_ITERATOR_H__

template<class T>
class list_node;

template<class T>
class list_iterator{
public:
  typedef T                 value_type;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef list_node<T>      node;
  typedef unsigned long     size_t;

private:
  node* ptr;

public:
  list_iterator();
  list_iterator(const list_iterator& that);
  list_iterator(node* that);
  virtual ~list_iterator() = default;
  
  list_iterator& operator=(const list_iterator& rhs);
  
  list_iterator& operator++();
  list_iterator  operator++(int);
  list_iterator& operator--();
  list_iterator  operator--(int);

  typename list<T>::reference operator*();
  typename list<T>::pointer operator->();

  template<class U>
  friend bool operator==(const list_iterator<U>& lhs, const list_iterator<U>& rhs);
  template<class U>
  friend bool operator!=(const list_iterator<U>& lhs, const list_iterator<U>& rhs);

  node*& accessNode();
};

template<class T>
bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs);

template<class T>
bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs);

#include"list_iterator.cc"

#endif

