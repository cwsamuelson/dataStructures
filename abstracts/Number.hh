#ifndef __NUMBER_H__
#define __NUMBER_H__

#include<Jing/Object.hh>
#include<Jing/Comparable.hh>
#include<ostream>

namespace Jing{

class Number:public Object, public Comparable<Number>{
public:
  void* value;
  //virtual byte asByte() const = 0;
  //virtual long asLong() const = 0;
  //virtual float asFloat() const = 0;
  virtual double asDouble() const = 0;
  virtual int asInt() const = 0;
  virtual char asChar() const = 0;

  Number& operator=(const Number& rhs);
  friend std::ostream& operator<<(std::ostream& os, const Number& let);

//[inherited from Object]
//  virtual bool is_equal(const Object& obj)const = 0;
//[inherited from Comparable]
//  virtual int compareTo(Nmuber& num) const = 0;
};
std::ostream& operator<<(std::ostream& os, const Jing::Number& let);

}

#endif

