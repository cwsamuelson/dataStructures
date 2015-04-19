#ifndef __STACK_H__
#define __STACK_H__

#include"../vector/vector.hh"

namespace galaxy{

template<class T>
class stack{
public:
  typedef T                 value_type;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef unsigned long     size_t;

private:
  vector<value_type> stk;

public:
  void            push(value_type data);
  void            pop();
  reference       top();
  const_reference top() const;
  bool            isEmpty() const;
  size_t          size() const;
};

}

#include"Stack.cc"

#endif

