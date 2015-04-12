#ifndef __LIST_H__
#define __LIST_H__

namespace gxy{

template<class T>
class iterator;

template<class T>
class list{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef unsigned long long size_t;

//private:
public:
  class node{
  public:
    value_type data;
    node* previous;
    node* next;
    
    node(const_reference c);
    node(const_reference c, node* p, node* n);
    virtual ~node() = default;
    reference get(size_t idx);
    
    node& operator=(const node& rhs) = default;
  };

  node* head;
  node* tail;
  size_t size;
  
public:
  list();
  virtual ~list();
  
  void pushFront(value_type c);
  void pushBack(value_type c);
  value_type popFront();
  value_type popBack();
  iterator<value_type> insert(iterator<value_type> it, const_reference val);
  iterator<value_type> insert(iterator<value_type> it, size_t n, const_reference val);
  iterator<value_type> insert(iterator<value_type> it, iterator<value_type> first, iterator<value_type> last);
  iterator<value_type> erase(iterator<value_type> it);
  iterator<value_type> erase(iterator<value_type> first, iterator<value_type> last);
  void clear();
  reference get(size_t idx);
  const_reference get(size_t idx) const;
  iterator<value_type> begin();
  iterator<value_type> end();
  size_t length();
  size_t length() const;
  bool isEmpty();

  reference operator[](size_t idx);
};

template<class T>
class iterator{
public:
  typename list<T>::node* ptr;

  iterator();
  iterator(const iterator<T>& that);
  iterator(typename list<T>::node* that);
  virtual ~iterator() = default;
  
  iterator<T>& operator=(const iterator& rhs);
  
  iterator<T>& operator++();
  iterator<T>  operator++(int);
  iterator<T>& operator--();
  iterator<T>  operator--(int);

  typename list<T>::reference operator*();
  typename list<T>::pointer operator->();

  template<class U>
  friend bool operator==(const iterator<U>& lhs, const iterator<U>& rhs);
  template<class U>
  friend bool operator!=(const iterator<U>& lhs, const iterator<U>& rhs);

  typename list<T>::node*& accessNode();

};

template<class T>
bool operator==(const iterator<T>& lhs, const iterator<T>& rhs);

template<class T>
bool operator!=(const iterator<T>& lhs, const iterator<T>& rhs);

}

#include"list.cc"

#endif

