#ifndef __OBJECT_H__
#define __OBJECT_H__

#include<typeinfo>

namespace Jing{

class Object{
protected:
public:
//Equality
  bool equals(const Object& obj) const{
    if(typeid(this) != typeid(obj)){
      return false;
    }
    return this->is_equal(obj);
  }

  virtual bool is_equal(const Object& obj)const = 0;
//State
//  hash
  virtual unsigned long long hash() const = 0;
//  clone
//memory management may be up to the user.
//clean up with delete
//TODO:find better solution than above
  virtual Object* clone() const = 0;
};

}

#endif

