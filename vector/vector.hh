#ifndef __GALAXY_VECTOR_H__
#define __GALAXY_VECTOR_H__

template<class T>
class vector_iterator;

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

  //changeCapacity changes to capacity of size
  void changeCapacity(size_t size);
  void increaseCapacity();
  //increaseCapacity increases by an amount size
  void increaseCapacity(size_t size);

public:
  vector();
  vector(size_t size);
  vector(iterator& first, iterator& last);
  virtual ~vector();

  void 	          pushBack(value_type data);
  value_type      popBack();
  iterator        insert(iterator it, const_reference data);
  iterator        insert(iterator it, size_t n, const_reference data);
  iterator        insert(iterator it, iterator first, iterator last);
  iterator        erase(iterator it);
  iterator        erase(iterator first, iterator last);
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

