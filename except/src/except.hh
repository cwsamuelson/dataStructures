#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include<Jing/string>

namespace Jing{

class exception{
private:
  string& msg = *(new string());
public:
  exception(const char* message);
  exception(const string& message);

  const string& what() const;
};

}

#endif

