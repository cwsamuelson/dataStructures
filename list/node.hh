#ifndef __NODE_H__
#define __NODE_H__

class node{
public:
  char data;
  node* next;
  node* previous;
  
  node(char* c);
  node(char* c, node* p, node* n);
  virtual ~node() = default;
  char get(unsigned int idx);
  
  node& operator=(const node& rhs) = default;
};
  
#endif

