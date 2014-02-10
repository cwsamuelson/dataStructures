#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

namespace Jing{

class exception{
private:
public:
  exception(char* message);
  exception(string message);

  string what();
};

}

#endif

