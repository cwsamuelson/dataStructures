#ifndef __QUEUE_H__
#define __QUEUE_H__

#include"../list/list.hh"

namespace galaxy{

template<class T>
class Queue{
  typedef T                 value_type;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef list_iterator<T>  iterator;
  typedef list_node<T>      node;
  typedef unsigned long     size_t;

private:
  list<value_type> que;

public:
  void            push();
  void            pop();
  reference       front();
  const_reference front() const;
  reference       back();
  const_reference back() const;
  bool            isEmpty() const;
  size_t          size() const;
};

#include"Queue.cc"

}

#endif

