#include"node.hpp"

node::node(char* c):data(c), next(0), previous(0){
    
}

node(char* c, node* p, node* n):data(c), previous(p), next(n){
    
}

char get(unsigned int idx){
  char ret;
  if(idx == 0){
    ret = this->data;
  } else {
    ret = this->next->get(idx - 1);
  }
  return ret;
}

