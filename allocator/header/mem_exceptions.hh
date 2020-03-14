#ifndef __MEM_EXCEPTIONS_HH__
#define __MEM_EXCEPTIONS_HH__

#include<exception>

namespace gsw {

class bad_alloc : public std::exception {
public:
  [[nodiscard]]
  virtual const char* what() const noexcept override {
    return "Bad allocation!";
  }
};

}

#endif
