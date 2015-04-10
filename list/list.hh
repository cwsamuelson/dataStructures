#ifndef __LIST_H__
#define __LIST_H__

#include"node.hpp"
#include"iterator.hpp"

class list{
private:
  node* head;
  node* tail;
  unsigned int length;
  
public:
  list();
  virtual ~list() = default;
  
  iterator pushFront(char c);
  iterator pushBack(char c);
  char popFront();
  char popBack();
  char get();
  iterator begin();
  iterator end();
  unsigned int length();
  bool isEmpty();

  char& operator[](unsigned int idx);
};

#endif
