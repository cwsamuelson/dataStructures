#ifndef __LIST_H__
#define __LIST_H__

template<class T>
class vector{
private:
  T* arr;
  size_t size;
  size_t capacity;

public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef unsigned long long size_t;

  vector();
  vector(const vector<value_type>& other);
  virtual ~vector();

  void pushBack(value_type c);
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
  size_t capacity();
  size_t capacity() const;
  void reserve(size_t n);
  void shrink();
  bool isEmpty();

  reference operator[](size_t idx);

};

template<class T>
class iterator{
public:
  typename list<T>::size_t idx;

  iterator();
  iterator(const iterator<T>& that);
  iterator(typename list<T>::node* that);
  virtual ~iterator() = default;
  
  iterator<T>& operator=(const iterator& rhs);
  
  iterator<T>& operator++();
  iterator<T>  operator++(int);
  iterator<T>& operator--();
  iterator<T>  operator--(int);

  typename vector<T>::reference operator*();
  typename vector<T>::pointer operator->();

  template<class U>
  friend bool operator==(const iterator<U>& lhs, const iterator<U>& rhs);
  template<class U>
  friend bool operator!=(const iterator<U>& lhs, const iterator<U>& rhs);
};

#include"vector.cc"

#endif

