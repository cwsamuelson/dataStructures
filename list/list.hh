#ifndef __GALAXY_LIST_H__
#define __GALAXY_LIST_H__

namespace galaxy{

template<class T>
class list_iterator;

template<class T>
class list_node;

template<class T>
class list{
public:
  typedef T                 value_type;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef list_iterator<T>  iterator;
  typedef list_node<T>      node;
  typedef unsigned long     size_t;

private:
  node* head;
  node* tail;
  size_t size;
  
public:
  list();
  list(iterator first, iterator last);
  virtual ~list();
  
  void pushFront(value_type c);
  void pushBack(value_type c);
  value_type popFront();
  value_type popBack();
  iterator insert(iterator it, const_reference data);
  iterator insert(iterator it, size_t n, const_reference data);
  iterator insert(iterator it, iterator first, iterator last);
  iterator erase(iterator it);
  iterator erase(iterator first, iterator last);
  void clear();
  reference get(size_t idx);
  const_reference get(size_t idx) const;
  iterator begin();
  const iterator begin() const;
  iterator end();
  const iterator end() const;
  size_t length();
  size_t length() const;
  bool isEmpty();

  reference operator[](size_t idx);
};

#include"list.cc"

}

#endif

