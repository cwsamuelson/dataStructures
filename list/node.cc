#include"node.hh"

node::node(const char& c):data(c), next(0), previous(0){
}

node::node(const char& c, node* p, node* n):data(c), next(n), previous(p){ 
}

char& node::get(unsigned int idx){
  char& ret = this->data;
  if(idx == 0){
    ret = this->data;
  } else {
    ret = this->next->get(idx - 1);
  }
  return ret;
}

