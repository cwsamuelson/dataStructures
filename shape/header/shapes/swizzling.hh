#pragma once

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

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember>
using XY = Swizzler<Vec, Type, XMember, YMember>;

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember, Type Vec::* ZMember>
using XYZ = Swizzler<Vec, Type, XMember, YMember, ZMember>;

#define Swiz2Help(Vec, name, x, y) \
using name = XY<Vec, decltype(std::declval<Vec>().x), &Vec::x, &Vec::y>

#define XXSwiz(Vec, suffix) \
Swiz2Help(Vec, XX##suffix, x, x)

#define XYSwiz(Vec, suffix) \
Swiz2Help(Vec, XY##suffix, x, y)

#define YYSwiz(Vec, suffix) \
Swiz2Help(Vec, YY##suffix, y, y)

#define YXSwiz(Vec, suffix) \
Swiz2Help(Vec, YX##suffix, y, x)

#define Swiz3Help(Vec, name, x, y, z) \
using name = XYZ<Vec, decltype(std::declval<Vec>().x), &Vec::x, &Vec::y, &Vec::z>

#define XXXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, x, x, x)

#define XXYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, x, x, y)

#define XXZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, x, x, z)

#define XYXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, x, y, x)

#define XYYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, x, y, y)

#define XYZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, x, y, z)

#define YXXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, y, x, x)

#define YXYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, y, x, y)

#define YXZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, y, x, z)

#define YYXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, y, y, x)

#define YYYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, y, y, y)

#define YYZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, y, y, z)

#define YXXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, y, x, x)

#define ZXYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, z, x, y)

#define ZXZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, z, x, z)

#define ZYXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, z, y, x)

#define ZYYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, z, y, y)

#define ZYZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, z, y, z)

#define Swiz2(Vec, N) \
XXSwiz(Vec, N); \
XYSwiz(Vec, N); \
YYSwiz(Vec, N); \
YXSwiz(Vec, N);

#define Swiz3(Vec, N) \
XXSwiz(Vec, N); \
XYSwiz(Vec, N); \
YYSwiz(Vec, N); \
YXSwiz(Vec, N);

}
