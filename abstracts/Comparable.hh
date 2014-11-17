#ifndef __COMPARABLE_H__
#define __COMPARABLE_H__

//#include<Jing/Misc.hh>

namespace Jing{

template<class T>
class Comparable{
//A subclass of Comparable is only comparable to itself, and between subclasses.
//Returns a negative integer, zero, or a positive integer as this object is less than, equal to, or greater than the specified object.
//Specifically Compares this object to another.
public:
  virtual int compareTo(const T& obj) const{
    //can_copy<T, Jing::Object&>();
  }

  bool operator==(const T& rhs) const{
    if(this->compareTo(rhs) == 0){
      return true;
    } else {
      return false;
    }
  }

  bool operator!=(const T& rhs) const{
    return !(*this == rhs);
  }

  bool operator<(const T& rhs) const{
    if(this->compareTo(rhs) < 0){
      return true;
    } else {
      return false;
    }
  }

  bool operator>(const T& rhs) const{
    if(this->compareTo(rhs) > 0){
      return true;
    } else {
      return false;
    }
  }

  bool operator<=(const T& rhs) const{
    if(*this < rhs || *this == rhs){
      return true;
    } else {
      return false;
    }
  }

  bool operator>=(const T& rhs) const{
    if(*this > rhs || *this == rhs){
      return true;
    } else {
      return false;
    }
  }

};

}

#endif

