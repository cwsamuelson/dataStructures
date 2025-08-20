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

#define SwizMember(TYPE, NAME) \
  constexpr \
  TYPE NAME() noexcept { \
    return { *this }; \
  }

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember>
using XY = Swizzler<Vec, Type, XMember, YMember>;

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember, Type Vec::* ZMember>
using XYZ = Swizzler<Vec, Type, XMember, YMember, ZMember>;

template<typename Vec, typename Type, Type Vec::* XMember, Type Vec::* YMember, Type Vec::* ZMember, Type Vec::* WMember>
using XYZW = Swizzler<Vec, Type, XMember, YMember, ZMember, WMember>;

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

#define Swiz2(Vec, N) \
XXSwiz(Vec, N); \
XYSwiz(Vec, N); \
YYSwiz(Vec, N); \
YXSwiz(Vec, N); \
SwizMember(XX##N, xx) \
SwizMember(XY##N, xy) \
SwizMember(YX##N, yx) \
SwizMember(YY##N, yy)

#define Swiz3Help(Vec, name, x, y, z) \
using name = XYZ<Vec, decltype(std::declval<Vec>().x), &Vec::x, &Vec::y, &Vec::z>

#define XXXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXX##suffix, x, x, x)

#define XXYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXY##suffix, x, x, y)

#define XXZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXZ##suffix, x, x, z)

#define XYXSwiz(Vec, suffix) \
Swiz3Help(Vec, XYX##suffix, x, y, x)

#define XYYSwiz(Vec, suffix) \
Swiz3Help(Vec, XYY##suffix, x, y, y)

#define XYZSwiz(Vec, suffix) \
Swiz3Help(Vec, XYZ##suffix, x, y, z)

#define YXXSwiz(Vec, suffix) \
Swiz3Help(Vec, YXX##suffix, y, x, x)

#define YXYSwiz(Vec, suffix) \
Swiz3Help(Vec, YXY##suffix, y, x, y)

#define YXZSwiz(Vec, suffix) \
Swiz3Help(Vec, YXZ##suffix, y, x, z)

#define YYXSwiz(Vec, suffix) \
Swiz3Help(Vec, YYX##suffix, y, y, x)

#define YYYSwiz(Vec, suffix) \
Swiz3Help(Vec, YYY##suffix, y, y, y)

#define YYZSwiz(Vec, suffix) \
Swiz3Help(Vec, YYZ##suffix, y, y, z)

#define YXXSwiz(Vec, suffix) \
Swiz3Help(Vec, YXX##suffix, y, x, x)

#define ZXYSwiz(Vec, suffix) \
Swiz3Help(Vec, ZXY##suffix, z, x, y)

#define ZXZSwiz(Vec, suffix) \
Swiz3Help(Vec, ZXZ##suffix, z, x, z)

#define ZYXSwiz(Vec, suffix) \
Swiz3Help(Vec, ZYX##suffix, z, y, x)

#define ZYYSwiz(Vec, suffix) \
Swiz3Help(Vec, ZYY##suffix, z, y, y)

#define ZYZSwiz(Vec, suffix) \
Swiz3Help(Vec, ZYZ##suffix, z, y, z)

#define ZZXSwiz(Vec, suffix) \
Swiz3Help(Vec, ZZX##suffix, z, z, x)

#define ZZYSwiz(Vec, suffix) \
Swiz3Help(Vec, ZZY##suffix, z, z, y)

#define ZZZSwiz(Vec, suffix) \
Swiz3Help(Vec, ZZZ##suffix, z, z, z)

#define Swiz3(Vec, N) \
XXSwiz(Vec, N); \
XYSwiz(Vec, N); \
YYSwiz(Vec, N); \
YXSwiz(Vec, N); \
XXXSwiz(Vec, N) \
XXYSwiz(Vec, N) \
XXZSwiz(Vec, N) \
XYXSwiz(Vec, N) \
XYYSwiz(Vec, N) \
XYZSwiz(Vec, N) \
YXXSwiz(Vec, N) \
YXYSwiz(Vec, N) \
YXZSwiz(Vec, N) \
YYXSwiz(Vec, N) \
YYYSwiz(Vec, N) \
YYZSwiz(Vec, N) \
YXXSwiz(Vec, N) \
ZXYSwiz(Vec, N) \
ZXZSwiz(Vec, N) \
ZYXSwiz(Vec, N) \
ZYYSwiz(Vec, N) \
ZYZSwiz(Vec, N) \
ZZXSwiz(Vec, N) \
ZZYSwiz(Vec, N) \
ZZZSwiz(Vec, N)

#define Swiz4Help(Vec, name, x, y, z, w) \
using name = XYZW<Vec, decltype(std::declval<Vec>().x), &Vec::x, &Vec::y, &Vec::z, &Vec::w>

#define XXXXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXX##suffix, x, x, x, x)

#define XXXYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXY##suffix, x, x, x, y)

#define XXXZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXZ##suffix, x, x, x, z)

#define XXYXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXX##suffix, x, x, y, x)

#define XXYYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXY##suffix, x, x, y, y)

#define XXYZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXZ##suffix, x, x, y, z)

#define XXZXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXX##suffix, x, x, z, x)

#define XXZYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXY##suffix, x, x, z, y)

#define XXZZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXZ##suffix, x, x, z, z)

#define XYXXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXX##suffix, x, y, x, x)

#define XYXYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXY##suffix, x, y, x, y)

#define XYXZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXZ##suffix, x, y, x, z)

#define XYYXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXX##suffix, x, y, y, x)

#define XYYYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXY##suffix, x, y, y, y)

#define XYYZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXZ##suffix, x, y, y, z)

#define XYZXSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXX##suffix, x, y, z, x)

#define XYZYSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXY##suffix, x, y, z, y)

#define XYZZSwiz(Vec, suffix) \
Swiz3Help(Vec, XXXZ##suffix, x, y, z, z)

// ...

#define Swiz4(Vec, N) \
XXSwiz(Vec, N); \
XYSwiz(Vec, N); \
YYSwiz(Vec, N); \
YXSwiz(Vec, N); \
XXXSwiz(Vec, N) \
XXYSwiz(Vec, N) \
XXZSwiz(Vec, N) \
XYXSwiz(Vec, N) \
XYYSwiz(Vec, N) \
XYZSwiz(Vec, N) \
YXXSwiz(Vec, N) \
YXYSwiz(Vec, N) \
YXZSwiz(Vec, N) \
YYXSwiz(Vec, N) \
YYYSwiz(Vec, N) \
YYZSwiz(Vec, N) \
YXXSwiz(Vec, N) \
ZXYSwiz(Vec, N) \
ZXZSwiz(Vec, N) \
ZYXSwiz(Vec, N) \
ZYYSwiz(Vec, N) \
ZYZSwiz(Vec, N) \
XXXXSwiz(Vec, N) \
XXXYSwiz(Vec, N) \
XXXZSwiz(Vec, N) \
XXYXSwiz(Vec, N) \
XXYYSwiz(Vec, N) \
XXYZSwiz(Vec, N) \
XXZXSwiz(Vec, N) \
XXZYSwiz(Vec, N) \
XXZZSwiz(Vec, N) \
XYXXSwiz(Vec, N) \
XYXYSwiz(Vec, N) \
XYXZSwiz(Vec, N) \
XYYXSwiz(Vec, N) \
XYYYSwiz(Vec, N) \
XYYZSwiz(Vec, N) \
XYZXSwiz(Vec, N) \
XYZYSwiz(Vec, N) \
XYZZSwiz(Vec, N)

}
