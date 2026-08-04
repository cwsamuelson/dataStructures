#pragma once

#include <any>
#include <map>
#include <string>

namespace flp {

struct State {
  using ObjectMap = std::map<std::string, std::any, std::less<>>;
  using ValueRef = ObjectMap::iterator;

  struct ValueProxy {
    ValueRef reference;
  };

  ValueProxy operator[](std::string_view identifier) {
    return objects.find(identifier);
  }

  template<typename Type>
  Type& get(const std::string_view identifier) {
    return objects.at(identifier);
  }

  ObjectMap objects;
};

} // namespace flp
