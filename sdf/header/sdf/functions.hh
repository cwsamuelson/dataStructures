#pragma once

#include <cmath>

namespace flp {

template<typename Func1, typename Func2>
auto min(Func1&& f1, Func2&& f2) {
  return [f1 = std::forward<Func1>(f1), f2 = std::forward<Func2>(f2)](auto&& ...args){
    return std::min(f1(args...), f2(args...));
  };
}

template<typename Func1, typename Func2>
auto max(Func1&& f1, Func2&& f2) {
  return [f1 = std::forward<Func1>(f1), f2 = std::forward<Func2>(f2)](auto&& ...args){
    return std::max(f1(args...), f2(args...));
  };
}

}
