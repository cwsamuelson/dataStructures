#ifndef __LIST_H__
#define __LIST_H__

#include"node.hh"
#include"iterator.hh"

namespace gxy{

class list{
private:
  node* head;
  node* tail;
  unsigned int size;
  
public:
  list();
  virtual ~list();
  
  void pushFront(char c);
  void pushBack(char c);
  char popFront();
  char popBack();
  iterator insert(iterator it, const char& val);
  iterator insert(iterator it, size_t n, const char& val);
  iterator insert(iterator it, iterator first, iterator last);
  char& get(unsigned int idx);
  const char& get(unsigned int idx) const;
  iterator begin();
  iterator end();
  unsigned int length();
  unsigned int length() const;
  bool isEmpty();

  char& operator[](unsigned int idx);
};

}

#endif

