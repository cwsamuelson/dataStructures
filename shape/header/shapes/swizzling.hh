#pragma once

#include "shapes/swizzle_macros.hh"

namespace flp {

template<typename Vec, typename Type, Type Vec::* ...Members>
struct Swizzler;

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember>
struct Swizzler<Vec, Type, XMember, YMember> {
  constexpr
  Swizzler(Vec& v) noexcept
    : vec(v)
  {}

  template<typename OVec, typename OType, Type Vec::* OXMember, Type Vec::* OYMember>
  constexpr
  Swizzler& operator=(const Swizzler<OVec, OType, OXMember, OYMember>& other) noexcept {
    vec.*XMember = other.*OXMember;
    vec.*YMember = other.*OYMember;
    return *this;
  }

  constexpr
  Swizzler& operator=(const Vec& other) noexcept {
    vec.*XMember = other.x;
    vec.*YMember = other.y;
    return *this;
  }

  constexpr
  operator Vec() const noexcept {
    return { vec.*XMember, vec.*YMember };
  }

  Vec& vec;
};

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember, Type Vec::* ZMember>
struct Swizzler<Vec, Type, XMember, YMember, ZMember> {
  constexpr
  Swizzler(Vec& v) noexcept
    : vec(v)
  {}

  template<typename OVec, typename OType, Type Vec::* OXMember, Type Vec::* OYMember, Type Vec::* OZMember>
  constexpr
  Swizzler& operator=(const Swizzler<OVec, OType, OXMember, OYMember, OZMember>& other) noexcept {
    vec.*XMember = other.*OXMember;
    vec.*YMember = other.*OYMember;
    vec.*ZMember = other.*OZMember;
    return *this;
  }

  constexpr
  Swizzler& operator=(const Vec& other) noexcept {
    vec.*XMember = other.x;
    vec.*YMember = other.y;
    vec.*ZMember = other.z;
    return *this;
  }

  constexpr
  operator Vec() const noexcept {
    return { vec.*XMember, vec.*YMember, vec.*ZMember };
  }

  Vec& vec;
};

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember, Type Vec::* ZMember, Type Vec::* WMember>
struct Swizzler<Vec, Type, XMember, YMember, ZMember, WMember> {
  constexpr
  Swizzler(Vec& v) noexcept
    : vec(v)
  {}

  template<typename OVec, typename OType, Type Vec::* OXMember, Type Vec::* OYMember, Type Vec::* OZMember, Type Vec::*OWMember>
  constexpr
  Swizzler& operator=(const Swizzler<OVec, OType, OXMember, OYMember, OZMember, OWMember>& other) noexcept {
    vec.*XMember = other.*OXMember;
    vec.*YMember = other.*OYMember;
    vec.*ZMember = other.*OZMember;
    vec.*WMember = other.*OWMember;
    return *this;
  }

  constexpr
  Swizzler& operator=(const Vec& other) noexcept {
    vec.*XMember = other.x;
    vec.*YMember = other.y;
    vec.*ZMember = other.z;
    vec.*WMember = other.w;
    return *this;
  }

  constexpr
  operator Vec() const noexcept {
    return { vec.*XMember, vec.*YMember, vec.*ZMember, vec.*WMember };
  }

  Vec& vec;
};

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember>
using XY = Swizzler<Vec, Type, XMember, YMember>;

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember, Type Vec::* ZMember>
using XYZ = Swizzler<Vec, Type, XMember, YMember, ZMember>;

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember, Type Vec::* ZMember, Type Vec::* WMember>
using XYZW = Swizzler<Vec, Type, XMember, YMember, ZMember, WMember>;

}
