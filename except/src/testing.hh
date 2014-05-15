#ifndef __TISTING_H__
#define __TISTING_H__

#include<Jing/except>

using namespace Jing;

class testEx : public exception{
public:
  testEx(const char * message);
  testEx(const string& message);

  const string& what() const;
};

class testing{
public:
  void thing();
};

#endif

