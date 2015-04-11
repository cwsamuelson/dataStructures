#include"node.hh"

gxy::node::node(const char& c):data(c), previous(0), next(0){
}

gxy::node::node(const char& c, gxy::node* p, gxy::node* n):data(c), previous(p), next(n){ 
}

char& gxy::node::get(unsigned int idx){
  char ret;
  if(idx == 0){
    ret = this->data;
  } else {
    ret = this->next->get(idx - 1);
  }
  char& tmp = ret;
  return tmp;
}

