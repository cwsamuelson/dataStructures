#ifndef __OBJECT_H__
#define __OBJECT_H__

namespace Jing{

class Object{
protected:
//Unique ID that identifies a class.
  int IDNUM = 0;
public:
//Equality
  virtual bool equals(Object& obj) const = 0;
//State
//  hash
  virtual int hash() const = 0;
//  ID
  virtual int classID() const = 0;
//  clone
  virtual const Object* clone() const = 0;
};

}

#endif

