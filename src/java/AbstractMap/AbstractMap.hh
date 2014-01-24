#ifndef __ABSTRACTMAP_H__
#define __ABSTRACTMAP_H__

#include<Object.hh>
#include<Serializable.hh>
#include<Map.hh>
#include<String.hh>

namespace Jing{

template<class K, class V>
class AbstractMap{
  template<class K, class V>
  class SimpleEntry:Object:Map::Entry<K,V>:Serializable{
  public:
    SimpleEntry(K key, V value);
    SimpleEntry(Map::Entry<K, V> entry);

    bool equals(Object o);
    K getKey();
    V getValue();
    V setValue(V value);
    String toString();
  };

};

}

#endif

