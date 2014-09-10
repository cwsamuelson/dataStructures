#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include<Jing/Comparable.hh>
#include<Jing/Object.hh>
#include<ostream>

namespace Jing{

class character:public Object, public Comparable<character&>{
protected:
  char letter;
public:
  character(char c);
  virtual ~character();

  bool equals(Object& obj) const;
  bool equals(character& ch) const;
  bool equals(char ch) const;
  unsigned long long hash() const;
  character* clone() const;

  friend std::ostream& operator<<(std::ostream& os, const character& let);
};
std::ostream& operator<<(std::ostream& os, const Jing::character& let);

}

#endif

