#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include<Jing/string>

namespace Jing{

class exception{
private:
  void init();
protected:
  Jing::string& msg;
public:
  exception();
  exception(const char* message);
  exception(const string& message);

  virtual const Jing::string& what() const;
};

}

#endif

