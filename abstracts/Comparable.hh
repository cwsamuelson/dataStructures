#ifndef __COMPARABLE_H__
#define __COMPARABLE_H__

#include<Jing/Object>

namespace Jing{

class Comparable:public Object{
//A subclass of Comparable is only comparable to itself, and between subclasses.
//Returns a negative integer, zero, or a positive integer as this object is less than, equal to, or greater than the specified object.
//Specifically Compares this object to another.
  virtual int compareTo() const = 0;
};

}

#endif

