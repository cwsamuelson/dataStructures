#include"node.hh"

node::node(const char& c):data(c), previous(0), next(0){
}

node::node(const char& c, node* p, node* n):data(c), previous(p), next(n){ 
}

char& node::get(unsigned int idx){
  char ret;
  if(idx == 0){
    ret = this->data;
  } else {
    ret = this->next->get(idx - 1);
  }
  char& tmp = ret;
  return tmp;
}

