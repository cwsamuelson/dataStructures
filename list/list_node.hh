#ifndef __GALAXY_LIST_NODE_H__
#define __GALAXY_LIST_NODE_H__

template<class T>
class list_node{
public:
  typedef T                 value_type;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef unsigned long     size_t;

  value_type data;
  list_node* left;
  list_node* right;
  
  list_node(const_reference c);
  list_node(const_reference c, list_node* l, list_node* r);
  virtual ~list_node() = default;

  reference get(size_t idx);
  
  list_node& operator=(const list_node& rhs) = default;
};

#include"list_node.cc"

#endif

