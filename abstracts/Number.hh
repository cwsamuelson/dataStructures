#ifndef __NUMBER_H__
#define __NUMBER_H__

#include<Jing/Comparable.hh>

namespace Jing{

class Number:public Comparable{
  //virtual byte asByte() const = 0;
  //virtual double asdouble() const = 0;
  //virtual long aslong() const = 0;
  virtual float asfloat() const = 0;
  virtual int asint() const = 0;
  virtual char aschar() const = 0;

//[inherited from Comparable]
//  virtual int compareTo() const = 0;
};

}

#endif

