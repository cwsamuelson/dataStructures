#ifndef __CHARSEQUENCE_H__
#define __CHARSEQUENCE_H__

#include<String.hh>

namespace Jing{

class CharSequence{
public:
  virtual char charAt(int index) = 0;
  virtual int length() = 0;
  virtual CharSequence subSequence(int start, int end) = 0;
  virtual String toString() = 0;
};

}

#endif

