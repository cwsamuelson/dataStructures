#ifndef __MEM_EXCEPTIONS_HH__
#define __MEM_EXCEPTIONS_HH__

#include<exception>

namespace gsw{

class bad_alloc : public std::exception{
public:
  virtual const char* what() const noexcept{
    return "Bad allocation!";
  }
};

}

#endif

