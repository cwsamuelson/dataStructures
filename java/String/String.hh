#ifndef __STRING_H__
#define __STRING_H__

#include<Object.hh>
#include<Comparator.hh>
#include<CharSequence.hh>
#include<Comparable.hh>

namespace Jing{

class String:Object:Serializeable:CharSequence,Comparable<String>{
public:
//  static Comparator<String> 
  String();
  String(char[] chars);
  String(char[] chars, Charset charset);
};

}

#endif

