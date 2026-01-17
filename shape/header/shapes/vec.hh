#pragma once

#include "shapes/vecn.hh"

namespace flp {

template<typename Type>
using vec2 = vecn<Type, 2>;
template<typename Type>
using vec3 = vecn<Type, 3>;
template<typename Type>
using vec4 = vecn<Type, 4>;

template<size_t Count>
using fvec = vecn<float, Count>;
template<size_t Count>
using dvec = vecn<double, Count>;
template<size_t Count>
using ivec = vecn<signed long long, Count>;
template<size_t Count>
using uvec = vecn<unsigned long long, Count>;
template<size_t Count>
using bvec = vecn<bool, Count>;

using fvec2 = vec2<float>;
using fvec3 = vec3<float>;
using fvec4 = vec4<float>;

using dvec2 = vec2<double>;
using dvec3 = vec3<double>;
using dvec4 = vec4<double>;

using ivec2 = vec2<signed long long>;
using ivec3 = vec3<signed long long>;
using ivec4 = vec4<signed long long>;

using svec2 = ivec2;
using svec3 = ivec3;
using svec4 = ivec4;

using uvec2 = vec2<unsigned long long>;
using uvec3 = vec3<unsigned long long>;
using uvec4 = vec4<unsigned long long>;

using bvec2 = vec2<bool>;
using bvec3 = vec3<bool>;
using bvec4 = vec4<bool>;

}
