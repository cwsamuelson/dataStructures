#ifndef __MAP_H__
#define __MAP_H__

#include<Object.hh>
#include<Set.hh>
#include<Collection.hh>

namespace Jing{

template<class K, class V>
class Map{
public:
  virtual void clear() = 0;
  virtual bool containsKey(Object key) = 0;
  virtual bool containsValue(Object value) = 0;
  virtual Set<Map.Entry<K,V>> entrySet() = 0;
  virtual bool equals(Object o) = 0;
  virtual V get(Object key) = 0;
  virtual int hashCode() = 0;
  virtual bool isEmpty() = 0;
  virtual Set<K> keySet() = 0;
  virtual V put(K key, V value) = 0;
  virtual void putAll(Map<K, V> m) = 0;
  virtual V remove(Object key) = 0;
  virtual int size() = 0;
  virtual Collection<V> values() = 0;

  template<class K, class V>
  class Entry{
    bool equals(Object o);
    K getKey();
    V getValue();
    int hashCode();
    V setValue(V value);
  };

};

}

#endif

