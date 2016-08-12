#ifndef __FUNCTION_HH__
#define __FUNCTION_HH__

#include<tuple.hh>

template<class T>
class function;

template<class R, class ... Args>
class function<R(Args...)>{
public:
  typedef R(*func)(Args...);
  typedef R result;
  typedef tuple<Args...> args;

private:
  func f;

public:
  function():
    f(0){
  }

  function(func parm):
    f(parm){
  }
  
  R operator()(Args... args){
    return f(args...);
  }
  
  function& operator=(const function& rhs){
    f = rhs.f;
    return *this;
  }
  
  function& operator=(func F){
    f = F;
    return *this;
  }
};


#endif

