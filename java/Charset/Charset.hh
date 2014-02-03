#ifndef __CHARSET_H__
#define __CHARSET_H__

namespace Jing{

class Charset:Object:Comparable<Charset{
protected:
  Charset(String canonicalName, String[] aliases);
public:
  Set<String> aliases();
  static SortedMap<String, Charset> availableCharsets();
};

}

#endif

