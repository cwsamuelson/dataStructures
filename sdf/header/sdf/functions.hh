#pragma once

#include <cmath>

namespace flp {

template<typename Func1, typename Func2>
constexpr
auto min(Func1&& f1, Func2&& f2) noexcept {
  return [f1 = std::forward<Func1>(f1), f2 = std::forward<Func2>(f2)](auto&& ...args){
    return std::min(f1(args...), f2(args...));
  };
}

template<typename Func1, typename Func2>
constexpr
auto max(Func1&& f1, Func2&& f2) noexcept {
  return [f1 = std::forward<Func1>(f1), f2 = std::forward<Func2>(f2)](auto&& ...args){
    return std::max(f1(args...), f2(args...));
  };
}

template<typename Func>
constexpr
fvec3 calcNormal(const fvec3 p, Func&& func) noexcept {
  const float eps = 0.0001; // or some other value
  const fvec2 h = vec2(eps, 0);

  return normalize(
    fvec3(func(p + h("xyy"_swz)) - func(p - h("xyy"_swz)),
          func(p + h("yxy"_swz)) - func(p - h("yxy"_swz)),
          func(p + h("yyx"_swz)) - func(p - h("yyx"_swz))));
}

// 'tetrahedron technique'?
template<typename Func>
constexpr
fvec3 calcNormal(const fvec3 p, Func&& func) noexcept {
  const float h = 0.0001f; // replace by an appropriate value
  const fvec2 k = fvec2(1, -1);
  return normalize(
    func("xyy"_swz) * func(p + k("xyy"_swz) * h) +
    func("yyx"_swz) * func(p + k("yyx"_swz) * h) +
    func("yxy"_swz) * func(p + k("yxy"_swz) * h) +
    func("xxx"_swz) * func(p + k("xxx"_swz) * h));
}

// for terrain g(p)
template<typename Func>
fvec3 getNormal(const fvec2 p, Func&& func) {
  const float eps = 0.0001; // or some other value
  const fvec2 h = fvec2(eps, 0);

  return normalize(
    fvec3(func(p - h("xy"_swz)) - func(p + h("xy"_swz)),
    2.0 * h.x,
    func(p - h("yx"_swz)) - func(p + h("yx"_swz))));
}

}
