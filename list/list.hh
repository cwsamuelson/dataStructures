#ifndef __LIST_H__
#define __LIST_H__

namespace gxy{

typedef unsigned long long size_t;

class iterator;

class list{
//private:
public:
  class node{
  public:
    char data;
    node* previous;
    node* next;
    
    node(const char& c);
    node(const char& c, node* p, node* n);
    virtual ~node() = default;
    char& get(unsigned int idx);
    
    node& operator=(const node& rhs) = default;
  };

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
  iterator erase(iterator it);
  iterator erase(iterator first, iterator last);
  void clear();
  char& get(unsigned int idx);
  const char& get(unsigned int idx) const;
  iterator begin();
  iterator end();
  unsigned int length();
  unsigned int length() const;
  bool isEmpty();

  char& operator[](unsigned int idx);
};

class iterator{
public:
  list::node* ptr;

  iterator();
  iterator(const iterator& that);
  iterator(list::node* that);
  virtual ~iterator() = default;
  
  iterator& operator=(const iterator& rhs);
  
  iterator& operator++();
  iterator  operator++(int);
  iterator& operator--();
  iterator  operator--(int);

  char& operator*();
  char* operator->();

  friend bool operator==(const iterator& lhs, const iterator& rhs);
  friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !operator==(lhs, rhs); }

  list::node*& accessNode();

};

bool operator==(const iterator& lhs, const iterator& rhs);

}

#endif

