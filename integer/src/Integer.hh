#ifndef __INTEGER_H__
#define __INTEGER_H__

#include<Jing/Comparable.hh>
#include<Jing/Object.hh>
#include<ostream>

namespace Jing{

class Integer:public Object, public Comparable<Integer>{
protected:
  int value;
public:
  Integer(int c);
  virtual ~Integer();

  bool equals(Object& obj) const;
  bool equals(Integer& ch) const;
  bool equals(int ch) const;
  unsigned long long hash() const;
  Integer* clone() const;
//Comparison
//  [inherited from comparable]
  int compareTo(Integer& c) const;
//Conversion
//  [inherited from number]
  double asDouble() const;
  int asInt() const;
  char asChar() const;
  

  friend std::ostream& operator<<(std::ostream& os, const Integer& let);
};
std::ostream& operator<<(std::ostream& os, const Jing::Integer& let);

}

#endif
