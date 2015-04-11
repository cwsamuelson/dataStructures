#ifndef __LIST_H__
#define __LIST_H__

#include"node.hh"
#include"iterator.hh"

class list{
private:
  node* head;
  node* tail;
  unsigned int size;
  
public:
  list();
  virtual ~list() = default;
  
  void pushFront(char c);
  void pushBack(char c);
  char popFront();
  char popBack();
  char& get(unsigned int idx);
  iterator begin();
  iterator end();
  unsigned int length();
  bool isEmpty();

  char& operator[](unsigned int idx);
};

#endif
