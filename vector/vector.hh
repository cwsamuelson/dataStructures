#ifndef __GALAXY_VECTOR_H__
#define __GALAXY_VECTOR_H__

#include"vector_iterator.hh"

template<class T>
class vector{
public:
  typedef char               value_type;
  typedef value_type&        reference;
  typedef const value_type&  const_reference;
  typedef value_type*        pointer;
  typedef const value_type*  const_pointer;
  typedef vector_iterator<T> iterator;
  typedef unsigned long      size_t;

private:
  pointer arr_;
  size_t  size_;
  size_t  capacity_;

  void changeCapacity(size_t size);
  void increaseCapacity();

public:
  vector();
  vector(size_t size);
  vector(iterator& first, iterator& last);
  virtual ~vector();

  void 	          pushBack(value_type data);
  value_type      popBack();
  void            clear();
  reference       get(size_t idx);
  const_reference get(size_t idx) const;
  iterator        begin();
  iterator        end();
  size_t          length();
  size_t          length() const;
  size_t          size();
  size_t          size() const;
  size_t          capacity();
  size_t          capacity() const;
  void	          reserve(size_t sz);
  void            shrinkToFit();
  bool            isEmpty();

  reference       operator[](size_t idx);
};

#include"vector.cc"

#endif

