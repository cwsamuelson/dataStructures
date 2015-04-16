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

  class iterator{
  public:
    typename list<T>::node* ptr;

    iterator();
    iterator(const iterator& that);
    iterator(typename list<T>::node* that);
    virtual ~iterator() = default;
    
    iterator& operator=(const iterator& rhs);
    
    iterator& operator++();
    iterator  operator++(int);
    iterator& operator--();
    iterator  operator--(int);

    typename list<T>::reference operator*();
    typename list<T>::pointer operator->();

    template<class U>
    friend bool operator==(const iterator& lhs, const iterator& rhs);
    template<class U>
    friend bool operator!=(const iterator& lhs, const iterator& rhs);

    typename list<T>::node*& accessNode();
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
  iterator insert(iterator it, const_reference val);
  iterator insert(iterator it, size_t n, const_reference val);
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

template<class T>
bool operator==(const typename list<T>::iterator& lhs, const typename list<T>::iterator& rhs);

template<class T>
bool operator!=(const typename list<T>::iterator& lhs, const typename list<T>::iterator& rhs);

}

#include"list.cc"

#endif

