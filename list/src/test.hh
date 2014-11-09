#include<Jing/Runnable.hh>
#include<Jing/List>
#include<Jing/character>
#include<Jing/Misc.hh>
#include<Jing/string>
#include<iostream>

template class Jing::List<Jing::character>;
/*
class Feature{
  Jing::List<Jing::Runnable>* tests;
  Jing::string* name;

  Feature():Feature(new Jing::string("feature")){
    
  }

  Feature(Jing::string* nam):tests(new Jing::List<Jing::Runnable>), name(nam){
  }

  ~Feature(){
    delete tests;
    delete name;
  }

  void addTest(Jing::Runnable& tst){
    this->tests->insert(tst);
  }

};
*/
