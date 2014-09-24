#ifndef __NUMBER_H__
#define __NUMBER_H__

#include<Jing/Object.hh>
#include<Jing/Comparable.hh>

namespace Jing{

class Number:public Object, public Comparable<Number>{
  //virtual byte asByte() const = 0;
  //virtual long asLong() const = 0;
  //virtual float asFloat() const = 0;
  virtual double asDouble() const = 0;
  virtual int asInt() const = 0;
  virtual char asChar() const = 0;

//[inherited from Comparable]
//  virtual int compareTo(Nmuber& num) const = 0;
};

}

#endif

