#pragma once

#include "shapes/vec2.hh"
#include "shapes/vec3.hh"

namespace flp {

// 3D
namespace DDD {

// Sphere - exact (https://www.shadertoy.com/view/Xds3zN)
constexpr
float sdSphere(const vec3 p, const float s) noexcept {
  return length(p) - s;
}

// Box - exact (derivation: https://www.youtube.com/watch?v=62-pRVZuS5c)
constexpr
float sdBox(const vec3 p, const vec3 b) noexcept {
  vec3 const q = abs(p) - b;
  return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
}

// Round Box - exact
constexpr
float sdRoundBox(const vec3 p, const vec3 b, const float r) noexcept {
  const vec3 q = abs(p) - b + r;
  return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0) - r;
}

// Box Frame - exact (https://www.shadertoy.com/view/3ljcRh)
constexpr
float sdBoxFrame(vec3 p, const vec3 b, const float e) noexcept {
       p = abs(p) - b;
  const vec3 q = abs(p + e) - e;
  return min(
    min(
      length(max(vec3(p.x, q.y, q.z), 0.0)) + min(max(p.x, max(q.y, q.z)), 0.0),
      length(max(vec3(q.x, p.y, q.z), 0.0)) + min(max(q.x, max(p.y, q.z)), 0.0)
    ),
    length(max(vec3(q.x, q.y, p.z), 0.0)) + min(max(q.x, max(q.y, p.z)), 0.0)
 );
}

// Torus - exact
constexpr
float sdTorus(const vec3 p, const vec2 t) noexcept {
  const vec2 q = vec2(length(p.xz) - t.x, p.y);
  return length(q) - t.y;
}

// Capped Torus - exact (https://www.shadertoy.com/view/tl23RK)
constexpr
float sdCappedTorus(vec3 p, const vec2 sc, const float ra, const float rb) noexcept {
  p.x = abs(p.x);
  const float k = (sc.y * p.x > sc.x * p.y) ? dot(p.xy, sc) : length(p.xy);
  return sqrt(dot(p, p) + ra * ra - 2.0 * ra * k) - rb;
}

// Link - exact (https://www.shadertoy.com/view/wlXSD7)
constexpr
float sdLink(const vec3 p, const float le, const float r1, const float r2) noexcept {
  const vec3 q = vec3(p.x, max(abs(p.y) - le, 0.0), p.z);
  return length(vec2(length(q.xy) - r1, q.z)) - r2;
}

// Infinite Cylinder - exact
constexpr
float sdCylinder(const vec3 p, const vec3 c) noexcept {
  return length(p.xz - c.xy) - c.z;
}

// vertical
constexpr
float sdCylinder(const vec3 p, const vec2 h) noexcept {
  vec2 d = abs(vec2(length(p.xz), p.y)) - h;
  return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));
}

// arbitrary orientation
constexpr
float sdCylinder(const vec3 p, const vec3 a, const vec3 b, const float r) noexcept {
  const vec3 pa = p - a;
  const vec3 ba = b - a;
  const float baba = dot(ba, ba);
  const float paba = dot(pa, ba);

  const float x = length(pa * baba - ba * paba) - r * baba;
  const float y = abs(paba - baba * 0.5) - baba * 0.5;
  const float x2 = x * x;
  const float y2 = y * y * baba;
  const float d = (max(x, y) < 0.0) ? -min(x2, y2) : (((x > 0.0) ? x2 : 0.0) + ((y > 0.0) ? y2 : 0.0));
  return sign(d) * sqrt(abs(d)) / baba;
}

// Cone - exact
constexpr
float sdCone(const vec3 p, const vec2 c, const float h) noexcept {
  // c is the sin/cos of the angle, h is height
  // Alternatively pass q instead of (c, h),
  // which is the point at the base in 2D
  const vec2 q = h * vec2(c.x / c.y, -1.0);

  const vec2 w = vec2(length(p.xz), p.y);
  const vec2 a = w - q * clamp(dot(w, q) / dot(q, q), 0.0, 1.0);
  const vec2 b = w - q * vec2(clamp(w.x / q.x, 0.0, 1.0), 1.0);
  const float k = sign(q.y);
  const float d = min(dot(a, a), dot(b, b));
  const float s = max(k * (w.x * q.y - w.y * q.x), k * (w.y - q.y) );
  return sqrt(d) * sign(s);
}

// Cone - bound
constexpr
float sdCone(const vec3 p, const vec2 c, const float h) noexcept {
  const float q = length(p.xz);
  return max(dot(c.xy, vec2(q, p.y)), -h - p.y);
}

// Infinite Cone - exact
constexpr
float sdCone(const vec3 p, const vec2 c) noexcept {
  // c is the sin/cos of the angle
  const vec2 q = vec2(length(p.xz), -p.y);
  const float d = length(q - c * max(dot(q, c), 0.0));
  return d * ((q.x * c.y - q.y * c.x < 0.0) ? - 1.0 : 1.0);
}

// Plane - exact
constexpr
float sdPlane(const vec3 p, const vec3 n, const float h) noexcept {
  // n must be normalized
  return dot(p, n) + h;
}

// Hexagonal Prism - exact
constexpr
float sdHexPrism(vec3 p, const vec2 h) noexcept {
  const vec3 k = vec3(-0.8660254, 0.5, 0.57735);
  p = abs(p);
  p.xy -= 2.0 * min(dot(k.xy, p.xy), 0.0) * k.xy;
  const vec2 d = vec2(
    length(p.xy - vec2(clamp(p.x, -k.z * h.x, k.z * h.x), h.x)) * sign(p.y - h.x),
    p.z - h.y);
  return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));
}

// Triangular Prism - bound
constexpr
float sdTriPrism(const vec3 p, const vec2 h) noexcept {
  const vec3 q = abs(p);
  return max(q.z - h.y, max(q.x * 0.866025 + p.y * 0.5, -p.y) - h.x * 0.5);
}

// Capsule/Line - exact
constexpr
float sdCapsule(const vec3 p, const vec3 a, const vec3 b, float r) noexcept {
  const vec3 pa = p - a, ba = b - a;
  const float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
  return length(pa - ba * h) - r;
}

// Capsule/Line - exact
constexpr
float sdVerticalCapsule(vec3 p, const float h, const float r) noexcept {
  p.y -= clamp(p.y, 0.0, h);
  return length(p) - r;
}

// Vertical Capped Cylinder - exact (https://www.shadertoy.com/view/wdXGDr)
constexpr
float sdCappedCylinder(const vec3 p, const float h, const float r) noexcept {
  const vec2 d = abs(vec2(length(p.xz), p.y)) - vec2(r, h);
  return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));
}

// Arbitrary Capped Cylinder - exact (https://www.shadertoy.com/view/wdXGDr)
constexpr
float sdCappedCylinder(const vec3 p, const vec3 a, const vec3 b, const float r) noexcept {
  const vec3  ba = b - a;
  const vec3  pa = p - a;
  const float baba = dot(ba, ba);
  const float paba = dot(pa, ba);
  const float x = length(pa * baba - ba * paba) - r * baba;
  const float y = abs(paba - baba * 0.5) - baba * 0.5;
  const float x2 = x * x;
  const float y2 = y * y * baba;
  const float d = (max(x, y) < 0.0) ? -min(x2, y2) : (((x > 0.0) ? x2 : 0.0) + ((y > 0.0) ? y2 : 0.0));
  return sign(d) * sqrt(abs(d)) / baba;
}

// Rounded Cylinder - exact
constexpr
float sdRoundedCylinder(const vec3 p, const float ra, const float rb, const float h) noexcept {
  const vec2 d = vec2(length(p.xz) - 2.0 * ra + rb, abs(p.y) - h);
  return min(max(d.x, d.y), 0.0) + length(max(d, 0.0)) - rb;
}

// Capped Cone - exact
constexpr
float sdCappedCone(const vec3 p, const float h, const float r1, const float r2) noexcept {
  const vec2 q = vec2(length(p.xz), p.y);
  const vec2 k1 = vec2(r2, h);
  const vec2 k2 = vec2(r2 - r1, 2.0 * h);
  const vec2 ca = vec2(q.x - min(q.x, (q.y < 0.0) ? r1 : r2), abs(q.y) - h);
  const vec2 cb = q - k1 + k2 * clamp(dot(k1 - q, k2) / dot2(k2), 0.0, 1.0);
  const float s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
  return s * sqrt(min(dot2(ca), dot2(cb)));
}

// Capped Cone - exact (https://www.shadertoy.com/view/tsSXzK)
constexpr
float sdCappedCone(const vec3 p, const vec3 a, const vec3 b, const float ra, const float rb) noexcept {
  const float rba  = rb - ra;
  const float baba = dot(b - a, b - a);
  const float papa = dot(p - a, p - a);
  const float paba = dot(p - a, b - a) / baba;
  const float x = sqrt(papa - paba * paba * baba);
  const float cax = max(0.0, x - ((paba < 0.5) ? ra : rb));
  const float cay = abs(paba - 0.5) - 0.5;
  const float k = rba * rba + baba;
  const float f = clamp((rba * (x - ra) + paba * baba) / k, 0.0, 1.0);
  const float cbx = x - ra - f * rba;
  const float cby = paba - f;
  const float s = (cbx < 0.0 && cay < 0.0) ? -1.0 : 1.0;
  return s * sqrt(min(cax * cax + cay * cay * baba,
                      cbx * cbx + cby * cby * baba));
}

// Solid Angle - exact (https://www.shadertoy.com/view/wtjSDW)
constexpr
float sdSolidAngle(const vec3 p, const vec2 c, const float ra) noexcept {
  // c is the sin/cos of the angle
  const vec2 q = vec2(length(p.xz), p.y);
  const float l = length(q) - ra;
  const float m = length(q - c * clamp(dot(q, c), 0.0, ra));
  return max(l, m * sign(c.y * q.x - c.x * q.y));
}

// Cut Sphere - exact (https://www.shadertoy.com/view/stKSzc)
constexpr
float sdCutSphere(const vec3 p, const float r, const float h) noexcept {
  // sampling independent computations (only depend on shape)
  const float w = sqrt(r * r - h * h);

  // sampling dependant computations
  const vec2 q = vec2(length(p.xz), p.y);
  const float s = max((h - r) * q.x * q.x + w * w * (h + r - 2.0 * q.y), h * q.x - w * q.y);
  return (s < 0.0) ? length(q) - r :
         (q.x < w) ? h - q.y     :
                   length(q - vec2(w, h));
}

// Cut Hollow Sphere - exact (https://www.shadertoy.com/view/7tVXRt)
constexpr
float sdCutHollowSphere(const vec3 p, const float r, const float h, const float t) noexcept {
  // sampling independent computations (only depend on shape)
  const float w = sqrt(r * r - h * h);

  // sampling dependant computations
  const vec2 q = vec2(length(p.xz), p.y);
  return ((h * q.x < w * q.y) ? length(q - vec2(w, h)) :
                          abs(length(q) - r)) - t;
}

// Death Star - exact (https://www.shadertoy.com/view/7lVXRt)
constexpr
float sdDeathStar(const vec3 p2, const float ra, const float rb, const float d) noexcept {
  // sampling independent computations (only depend on shape)
  const float a = (ra * ra - rb * rb + d * d) / (2.0 * d);
  const float b = sqrt(max(ra * ra - a * a, 0.0));

  // sampling dependant computations
  const vec2 p = vec2(p2.x, length(p2.yz));
  if (p.x * b - p.y * a > d * max(b - p.y, 0.0)) {
    return length(p - vec2(a, b));
  } else {
    return max((length(p           ) - ra),
               -(length(p - vec2(d, 0.0)) - rb));
  }
}

// Round cone - exact
constexpr
float sdRoundCone(const vec3 p, const float r1, const float r2, const float h) noexcept {
  // sampling independent computations (only depend on shape)
  const float b = (r1 - r2) / h;
  const float a = sqrt(1.0 - b * b);

  // sampling dependant computations
  const vec2 q = vec2(length(p.xz), p.y);
  const float k = dot(q, vec2(-b, a));
  if (k < 0.0) {
    return length(q) - r1;
  }

  if (k > a * h) {
    return length(q - vec2(0.0, h)) - r2;
  }

  return dot(q, vec2(a, b)) - r1;
}

// Round Cone - exact (https://www.shadertoy.com/view/tdXGWr)
constexpr
float sdRoundCone(const vec3 p, const vec3 a, const vec3 b, const float r1, const float r2) noexcept {
  // sampling independent computations (only depend on shape)
  const vec3  ba = b - a;
  const float l2 = dot(ba, ba);
  const float rr = r1 - r2;
  const float a2 = l2 - rr * rr;
  const float il2 = 1.0 / l2;

  // sampling dependant computations
  const vec3 pa = p - a;
  const float y = dot(pa, ba);
  const float z = y - l2;
  const float x2 = dot2(pa * l2 - ba * y);
  const float y2 = y * y * l2;
  const float z2 = z * z * l2;

  // single square root!
  const float k = sign(rr) * rr * rr * x2;
  if (sign(z) * a2 * z2 > k) {
    return  sqrt(x2 + z2) * il2 - r2;
  } else if (sign(y) * a2 * y2 < k) {
    return  sqrt(x2 + y2) * il2 - r1;
  } else {
    return (sqrt(x2 * a2 * il2) + y * rr) * il2 - r1;
  }
}

// Ellipsoid - bound (https://www.shadertoy.com/view/tdS3DG)
constexpr
float sdEllipsoid(const vec3 p, const vec3 r) noexcept {
  const float k0 = length(p / r);
  const float k1 = length(p / (r * r));
  return k0 * (k0 - 1.0) / k1;
}

// Revolved Vesica - exact) (https://www.shadertoy.com/view/Ds2czG)
constexpr
float sdVesicaSegment(const vec3 p, const vec3 a, const vec3 b, const float w) noexcept {
  const vec3  c = (a + b) * 0.5;
  const float l = length(b - a);
  const vec3  v = (b - a) / l;
  const float y = dot(p - c, v);
  const vec2  q = vec2(length(p - c - y * v), abs(y));

  const float r = 0.5 * l;
  const float d = 0.5 * (r * r - w * w) / w;
  const vec3  h = (r * q.x < d * (q.y - r)) ? vec3(0.0, r, 0.0) : vec3(-d, 0.0, d + w);

  return length(q - h.xy) - h.z;
}

// Rhombus - exact (https://www.shadertoy.com/view/tlVGDc)
constexpr
float sdRhombus(vec3 p, const float la, const float lb, const float h, const float ra) noexcept {
  p = abs(p);
  const vec2 b = vec2(la, lb);
  const float f = clamp((ndot(b, b - 2.0 * p.xz)) / dot(b, b), -1.0, 1.0);
  const vec2 q = vec2(length(p.xz - 0.5 * b * vec2(1.0 - f, 1.0 + f)) * sign(p.x * b.y + p.z * b.x - b.x * b.y) - ra, p.y - h);
  return min(max(q.x, q.y), 0.0) + length(max(q, 0.0));
}

// Octahedron - exact (https://www.shadertoy.com/view/wsSGDG)
constexpr
float sdOctahedron(vec3 p, const float s) noexcept {
  p = abs(p);
  const float m = p.x + p.y + p.z - s;
  vec3 q;

  if (3.0 * p.x < m) {
    q = p.xyz;
  } else if (3.0 * p.y < m) {
    q = p.yzx;
  } else if (3.0 * p.z < m) {
    q = p.zxy;
  } else {
    return m * 0.57735027;
  }

  const float k = clamp(0.5 * (q.z - q.y + s), 0.0, s);
  return length(vec3(q.x, q.y - s + k, q.z - k));
}

// Octahedron - bound (not exact)
constexpr
float sdOctahedron(vec3 p, const float s) noexcept {
  p = abs(p);
  return (p.x + p.y + p.z - s) * 0.57735027;
}

// Pyramid - exact (https://www.shadertoy.com/view/Ws3SDl)
constexpr
float sdPyramid(vec3 p, const float h) noexcept {
  const float m2 = h * h + 0.25;

  p.xz = abs(p.xz);
  p.xz = (p.z > p.x) ? p.zx : p.xz;
  p.xz -= 0.5;

  const vec3 q = vec3(p.z, h * p.y - 0.5 * p.x, h * p.x + 0.5 * p.y);

  const float s = max(-q.x, 0.0);
  const float t = clamp((q.y - 0.5 * p.z) / (m2 + 0.25), 0.0, 1.0);

  const float a = m2 * (q.x + s) * (q.x + s) + q.y * q.y;
  const float b = m2 * (q.x + 0.5 * t) * (q.x + 0.5 * t) + (q.y - m2 * t) * (q.y - m2 * t);

  const float d2 = min(q.y, -q.x * m2 - q.y * 0.5) > 0.0 ? 0.0 : min(a, b);

  return sqrt((d2 + q.z * q.z) / m2) * sign(max(q.z, -p.y));
}

// Triangle - exact (https://www.shadertoy.com/view/4sXXRN)
constexpr
float udTriangle(const vec3 p, const vec3 a, const vec3 b, const vec3 c) noexcept {
  const vec3 ba = b - a; vec3 pa = p - a;
  const vec3 cb = c - b; vec3 pb = p - b;
  const vec3 ac = a - c; vec3 pc = p - c;
  const vec3 nor = cross(ba, ac);

  return sqrt(
    (sign(dot(cross(ba, nor), pa)) +
     sign(dot(cross(cb, nor), pb)) +
     sign(dot(cross(ac, nor), pc)) < 2.0)
     ?
     min(min(
     dot2(ba * clamp(dot(ba, pa) / dot2(ba), 0.0, 1.0) - pa),
     dot2(cb * clamp(dot(cb, pb) / dot2(cb), 0.0, 1.0) - pb)),
     dot2(ac * clamp(dot(ac, pc) / dot2(ac), 0.0, 1.0) - pc))
     :
     dot(nor, pa) * dot(nor, pa) / dot2(nor));
}

// Quad - exact (https://www.shadertoy.com/view/Md2BWW)
constexpr
float udQuad(const vec3 p, const vec3 a, const vec3 b, const vec3 c, const vec3 d) noexcept {
  const vec3 ba = b - a; vec3 pa = p - a;
  const vec3 cb = c - b; vec3 pb = p - b;
  const vec3 dc = d - c; vec3 pc = p - c;
  const vec3 ad = a - d; vec3 pd = p - d;
  const vec3 nor = cross(ba, ad);

  return sqrt(
    (sign(dot(cross(ba, nor), pa)) +
     sign(dot(cross(cb, nor), pb)) +
     sign(dot(cross(dc, nor), pc)) +
     sign(dot(cross(ad, nor), pd)) < 3.0)
     ?
     min(min(min(
     dot2(ba * clamp(dot(ba, pa) / dot2(ba), 0.0, 1.0) - pa),
     dot2(cb * clamp(dot(cb, pb) / dot2(cb), 0.0, 1.0) - pb)),
     dot2(dc * clamp(dot(dc, pc) / dot2(dc), 0.0, 1.0) - pc)),
     dot2(ad * clamp(dot(ad, pd) / dot2(ad), 0.0, 1.0) - pd))
     :
     dot(nor, pa) * dot(nor, pa) / dot2(nor));
}

// You can find code to do extrussion and revolution below, and also here: https://www.shadertoy.com/view/4lyfzw

constexpr
float opRevolution(const vec3 p, const sdf2d primitive, const float o) noexcept {
  const vec2 q = vec2(length(p.xz) - o, p.y);
  return primitive(q);
}

constexpr
float opExtrusion(const vec3 p, const sdf2d primitive, const float h) noexcept {
  const float d = primitive(p.xy)
  const vec2 w = vec2(d, abs(p.z) - h);
  return min(max(w.x,w.y),0.0) + length(max(w,0.0));
}

//constexpr
//vec4 opElongate(const vec3 p, const vec3 h) noexcept {
//  return { p - clamp(p, -h, h), 0.F };
//}

constexpr
vec4 opElongate(const vec3 p, const vec3 h) noexcept {
  const vec3 q = abs(p) - h;
  return {max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0 };
}

// Rounding - exact
constexpr
float opRound(const float d, const float rad) noexcept {
  return d - rad;
}

// onion - exact
constexpr
float opOnion(const float sdf, const float thickness) noexcept {
  return abs(sdf) - thickness;
}

// Change of metric - bound
constexpr
float length2(vec3 p) noexcept {
  p = p * p;
  return sqrt(p.x + p.y + p.z);
}

constexpr
float length6(vec3 p) noexcept {
  p = p * p * p;
  p = p * p;
  return pow(p.x + p.y + p.z, 1.0 / 6.0);
}

constexpr
float length8(vec3 p) noexcept {
  p = p * p;
  p = p * p;
  p = p * p;
  return pow(p.x + p.y + p.z, 1.0 / 8.0);
}

// Union - exact/bound
constexpr
float opUnion(const float d1, const float d2) noexcept {
  return min(d1, d2);
}

// Subtraction - bound
constexpr
float opSubtraction(const float d1, const float d2) noexcept {
  return max(-d1, d2);
}

// Intersection - bound
constexpr
float opIntersection(const float d1, const float d2) noexcept {
  return max(d1, d2);
}

constexpr
float opXor(const float d1, const float d2) noexcept {
  return max(min(d1, d2), -max(d1, d2));
}

// Smooth Union - bound
constexpr
float opSmoothUnion(const float d1, const float d2, const float k) noexcept {
  const float h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
  return mix(d2, d1, h) - k * h * (1.0 - h);
}

// Smooth Subtraction - bound
constexpr
float opSmoothSubtraction(const float d1, const float d2, const float k) noexcept {
  const float h = clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0);
  return mix(d2, -d1, h) + k * h * (1.0 - h);
}

// Smooth Intersection - bound
constexpr
float opSmoothIntersection(const float d1, const float d2, const float k) noexcept {
  const float h = clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0);
  return mix(d2, d1, h) + k * h * (1.0 - h);
}

// Rotation/Translation - exact
constexpr
vec3 opTx(const vec3 p, const transform t, const sdf3d primitive) noexcept {
  return primitive(invert(t) * p);
}

// Scale - exact
constexpr
float opScale(const vec3 p, const float s, const sdf3d primitive) noexcept {
  return primitive(p / s) * s;
}

// Symmetry - bound and exact
constexpr
float opSymX(vec3 p, const sdf3d primitive) noexcept {
  p.x = abs(p.x);
  return primitive(p);
}

constexpr
float opSymXZ(vec3 p, const sdf3d primitive) noexcept {
  p.xz = abs(p.xz);
  return primitive(p);
}

constexpr
float opRepetition(const vec3 p, const vec3 s, const sdf3d primitive) noexcept {
  const vec3 q = p - s * round(p/s);
  return primitive(q);
}

constexpr
vec3 opLimitedRepetition(const vec3 p, const float s, const vec3 l, const sdf3d primitive) noexcept {
  const vec3 q = p - s * clamp(round(p / s), -l, l);
  return primitive(q);
}

// Displacement
// The displacement example below is using sin(20*p.x)*sin(20*p.y)*sin(20*p.z) as displacement pattern, but you can of course use anything you might imagine.

constexpr
float opDisplace(const sdf3d primitive, const vec3 p) noexcept {
  const float d1 = primitive(p);
  const float d2 = displacement(p);
  return d1 + d2;
}

// Twist
constexpr
float opTwist(const sdf3d primitive, const vec3 p) noexcept {
  const float k = 10.0; // or some other amount
  const float c = cos(k * p.y);
  const float s = sin(k * p.y);
  const mat2  m = mat2(c, -s, s, c);
  const vec3  q = vec3(m * p.xz, p.y);
  return primitive(q);
}

// Bend
constexpr
float opCheapBend(const sdf3d primitive, const vec3 p) noexcept {
  const float k = 10.0; // or some other amount
  const float c = cos(k * p.x);
  const float s = sin(k * p.x);
  const mat2  m = mat2(c, -s, s, c);
  const vec3  q = vec3(m * p.xy, p.z);
  return primitive(q);
}

float sdHelix(vec3 p, float fr, float r1, float r2) {
  const vec2  nline = vec2(fr, 6.283185 * r1);
  const vec2  pline = vec2(nline.y, -nline.x);
  const float repeat = nline.x * nline.y;

  const vec2  pc = vec2(p.x, r1 * atan(p.y, p.z));              // to cylindrical

  const vec2  pp = vec2(dot(pc,pline),                     // project to line
                   dot(pc, nline));

  pp.x = round(pp.x / repeat) * repeat;                   // repeat in x

  const vec2 qc = (nline * pp.y + pline * pp.x) / dot(nline, nline); // un project to cylindrical
  qc.y /= r1;

  const vec3 q = vec3(qc.x, sin(qc.y) * r1, cos(qc.y) * r1 );   // to cartesian

  return length(p - q) - r2;
}

}

namespace DD {

// Circle - exact (https://www.shadertoy.com/view/3ltSW2)
constexpr
float sdCircle(vec2 p, float r) noexcept {
  return length(p) - r;
}

// Rounded Box - exact   (https://www.shadertoy.com/view/4llXD7 and https://www.youtube.com/watch?v=s5NGeUV2EyU)
constexpr
float sdRoundedBox(vec2 p, vec2 b, vec4 r) noexcept {
  r.xy = (p.x > 0.0) ? r.xy : r.zw;
  r.x  = (p.y > 0.0) ? r.x  : r.y;
  vec2 q = abs(p) - b + r.x;
  return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

// Chamfer Box - exact (https://www.shadertoy.com/view/3fc3zs)
constexpr
float sdChamferBox(vec2 p, vec2 b, float chamfer) noexcept {
  p = abs(p) - b;

  p = (p.y > p.x) ? p.yx : p.xy;
  p.y += chamfer;

  const float k = 1.0 - sqrt(2.0);
  if (p.y<0.0 && p.y + p.x * k<0.0 ) {
    return p.x;
  }

  if (p.x<p.y ) {
    return (p.x + p.y) * sqrt(0.5);
  }

  return length(p);
}

// Box - exact (https://www.youtube.com/watch?v=62-pRVZuS5c)
constexpr
float sdBox(vec2 p, vec2 b) noexcept {
  vec2 d = abs(p) - b;
  return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
}

// Oriented Box - exact (https://www.shadertoy.com/view/stcfzn)
constexpr
float sdOrientedBox(vec2 p, vec2 a, vec2 b, float th) noexcept {
  float l = length(b - a);
  vec2  d = (b - a) / l;
  vec2  q = (p - (a + b) * 0.5);
        q = mat2(d.x, -d.y, d.y, d.x) * q;
        q = abs(q) - vec2(l, th) * 0.5;
  return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0);
}

// Segment - exact (https://www.shadertoy.com/view/3tdSDj and https://www.youtube.com/watch?v=PMltMdi1Wzg)
constexpr
float sdSegment(vec2 p, vec2 a, vec2 b) noexcept {
  vec2 pa = p - a, ba = b - a;
  float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0 );
  return length(pa - ba * h );
}

// Rhombus - exact   (https://www.shadertoy.com/view/XdXcRB)
constexpr
float ndot(vec2 a, vec2 b ) noexcept { return a.x * b.x - a.y * b.y; }

constexpr
float sdRhombus(vec2 p, vec2 b ) noexcept {
  p = abs(p);
  float h = clamp(ndot(b - 2.0 * p, b) / dot(b, b), -1.0, 1.0 );
  float d = length(p - 0.5 * b * vec2(1.0 - h, 1.0 + h) );
  return d * sign(p.x * b.y + p.y * b.x - b.x * b.y );
}

// Isosceles Trapezoid - exact   (https://www.shadertoy.com/view/MlycD3)
constexpr
float sdTrapezoid(vec2 p, float r1, float r2, float he ) noexcept {
  vec2 k1 = vec2(r2, he);
  vec2 k2 = vec2(r2 - r1, 2.0 * he);
  p.x = abs(p.x);
  vec2 ca = vec2(p.x - min(p.x, (p.y<0.0) ? r1 : r2), abs(p.y) - he);
  vec2 cb = p - k1 + k2 * clamp(dot(k1 - p, k2) / dot2(k2), 0.0, 1.0 );
  float s = (cb.x<0.0 && ca.y<0.0) ? -1.0 : 1.0;
  return s * sqrt(min(dot2(ca), dot2(cb)) );
}

// Parallelogram - exact   (https://www.shadertoy.com/view/7dlGRf)
constexpr
float sdParallelogram(vec2 p, float wi, float he, float sk ) noexcept {
  vec2 e = vec2(sk, he);
  p = (p.y<0.0) ? -p : p;
  vec2  w = p - e; w.x -= clamp(w.x, -wi, wi);
  vec2  d = vec2(dot(w, w), -w.y);
  float s = p.x * e.y - p.y * e.x;
  p = (s<0.0) ? -p : p;
  vec2  v = p - vec2(wi, 0); v -= e * clamp(dot(v, e) / dot(e, e), -1.0, 1.0);
  d = min(d, vec2(dot(v, v), wi * he - abs(s)));
  return sqrt(d.x) * sign(-d.y);
}

// Equilateral Triangle - exact   (https://www.shadertoy.com/view/Xl2yDW)
constexpr
float sdEquilateralTriangle(vec2 p, float r ) noexcept {
  const float k = sqrt(3.0);
  p.x = abs(p.x) - r;
  p.y = p.y + r / k;
  if (p.x + k * p.y > 0.0 ) {
    p = vec2(p.x - k * p.y, -k * p.x - p.y) / 2.0;
  }

  p.x -= clamp(p.x, -2.0 * r, 0.0 );
  return -length(p) * sign(p.y);
}

// Isosceles Triangle - exact   (https://www.shadertoy.com/view/MldcD7)
constexpr
float sdTriangleIsosceles(vec2 p, vec2 q ) noexcept {
  p.x = abs(p.x);
  vec2 a = p - q * clamp(dot(p, q) / dot(q, q), 0.0, 1.0 );
  vec2 b = p - q * vec2(clamp(p.x / q.x, 0.0, 1.0 ), 1.0 );
  float s = -sign(q.y );
  vec2 d = min(vec2(dot(a, a), s * (p.x * q.y - p.y * q.x) ),
                vec2(dot(b, b), s * (p.y - q.y)  ));
  return -sqrt(d.x) * sign(d.y);
}

// Triangle - exact   (https://www.shadertoy.com/view/XsXSz4)
constexpr
float sdTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2 ) noexcept {
  vec2 e0 = p1 - p0, e1 = p2 - p1, e2 = p0 - p2;
  vec2 v0 = p -p0, v1 = p -p1, v2 = p -p2;
  vec2 pq0 = v0 - e0 * clamp(dot(v0, e0) / dot(e0, e0), 0.0, 1.0 );
  vec2 pq1 = v1 - e1 * clamp(dot(v1, e1) / dot(e1, e1), 0.0, 1.0 );
  vec2 pq2 = v2 - e2 * clamp(dot(v2, e2) / dot(e2, e2), 0.0, 1.0 );
  float s = sign(e0.x * e2.y - e0.y * e2.x );
  vec2 d = min(min(vec2(dot(pq0, pq0), s * (v0.x * e0.y - v0.y * e0.x)),
                   vec2(dot(pq1, pq1), s * (v1.x * e1.y - v1.y * e1.x))),
                   vec2(dot(pq2, pq2), s * (v2.x * e2.y - v2.y * e2.x)));
  return -sqrt(d.x) * sign(d.y);
}

// Uneven Capsule - exact   (https://www.shadertoy.com/view/4lcBWn)
constexpr
float sdUnevenCapsule(vec2 p, float r1, float r2, float h ) noexcept {
  p.x = abs(p.x);
  float b = (r1 - r2) / h;
  float a = sqrt(1.0 - b * b);
  float k = dot(p, vec2(-b, a));
  if (k < 0.0 ) {
    return length(p) - r1;
  }
  if (k > a * h ) {
    return length(p - vec2(0.0, h)) - r2;
  }
  return dot(p, vec2(a, b) ) - r1;
}

// Regular Pentagon - exact   (https://www.shadertoy.com/view/llVyWW)
constexpr
float sdPentagon(vec2 p, float r ) noexcept {
  const vec3 k = vec3(0.809016994, 0.587785252, 0.726542528);
  p.x = abs(p.x);
  p -= 2.0 * min(dot(vec2(-k.x, k.y), p), 0.0) * vec2(-k.x, k.y);
  p -= 2.0 * min(dot(vec2(k.x, k.y), p), 0.0) * vec2(k.x, k.y);
  p -= vec2(clamp(p.x, -r * k.z, r * k.z), r);
  return length(p) * sign(p.y);
}

// Regular Hexagon - exact
constexpr
float sdHexagon(vec2 p, float r ) noexcept {
  const vec3 k = vec3(-0.866025404, 0.5, 0.577350269);
  p = abs(p);
  p -= 2.0 * min(dot(k.xy, p), 0.0) * k.xy;
  p -= vec2(clamp(p.x, -k.z * r, k.z * r), r);
  return length(p) * sign(p.y);
}

// Regular Octogon - exact   (https://www.shadertoy.com/view/llGfDG)
constexpr
float sdOctogon(vec2 p, float r ) noexcept {
  const vec3 k = vec3(-0.9238795325, 0.3826834323, 0.4142135623 );
  p = abs(p);
  p -= 2.0 * min(dot(vec2(k.x, k.y), p), 0.0) * vec2(k.x, k.y);
  p -= 2.0 * min(dot(vec2(-k.x, k.y), p), 0.0) * vec2(-k.x, k.y);
  p -= vec2(clamp(p.x, -k.z * r, k.z * r), r);
  return length(p) * sign(p.y);
}

// Hexagram - exact   (https://www.shadertoy.com/view/tt23RR)
constexpr
float sdHexagram(vec2 p, float r ) noexcept {
  const vec4 k = vec4(-0.5, 0.8660254038, 0.5773502692, 1.7320508076);
  p = abs(p);
  p -= 2.0 * min(dot(k.xy, p), 0.0) * k.xy;
  p -= 2.0 * min(dot(k.yx, p), 0.0) * k.yx;
  p -= vec2(clamp(p.x, r * k.z, r * k.w), r);
  return length(p) * sign(p.y);
}

// Pentagram - exact   (https://www.shadertoy.com/view/t3X3z4)
constexpr
float sdPentagram(vec2 p, float r ) noexcept {
  const float k1x = 0.809016994;// cos(π / 5) = ¼(√5 + 1)
  const float k2x = 0.309016994;// sin(π / 10) = ¼(√5 - 1)
  const float k1y = 0.587785252;// sin(π / 5) = ¼√(10 - 2√5)
  const float k2y = 0.951056516;// cos(π / 10) = ¼√(10 + 2√5)
  const float k1z = 0.726542528;// tan(π / 5) = √(5 - 2√5)
  const vec2  v1  = vec2(k1x, -k1y);
  const vec2  v2  = vec2(-k1x, -k1y);
  const vec2  v3  = vec2(k2x, -k2y);

  p.x = abs(p.x);
  p -= 2.0 * max(dot(v1, p), 0.0) * v1;
  p -= 2.0 * max(dot(v2, p), 0.0) * v2;
  p.x = abs(p.x);
  p.y -= r;
  return length(p - v3 * clamp(dot(p, v3), 0.0, k1z * r))
 * sign(p.y * v3.x - p.x * v3.y);
}

// Regular Star - exact   (https://www.shadertoy.com/view/3tSGDy)
constexpr
float sdStar(vec2 p, float r, int n, float m) noexcept {
// next 4 lines can be precomputed for a given shape
  float an = 3.141593 / float(n);
  float en = 3.141593 / m;// m is between 2 and n
  vec2  acs = vec2(cos(an), sin(an));
  vec2  ecs = vec2(cos(en), sin(en));// ecs=vec2(0, 1) for regular polygon

  float bn = mod(atan(p.x, p.y), 2.0 * an) - an;
  p = length(p) * vec2(cos(bn), abs(sin(bn)));
  p -= r * acs;
  p += ecs * clamp(-dot(p, ecs), 0.0, r * acs.y / ecs.y);
  return length(p) * sign(p.x);
}

// Pie - exact   (https://www.shadertoy.com/view/3l23RK)
constexpr
float sdPie(vec2 p, vec2 c, float r ) noexcept {
  p.x = abs(p.x);
  float l = length(p) - r;
  float m = length(p - c * clamp(dot(p, c), 0.0, r));// c=sin / cos of aperture
  return max(l, m * sign(c.y * p.x - c.x * p.y));
}

// Cut Disk - exact   (https://www.shadertoy.com/view/ftVXRc)
constexpr
float sdCutDisk(vec2 p, float r, float h ) noexcept {
  float w = sqrt(r * r - h * h);// constant for any given shape
  p.x = abs(p.x);
  float s = max((h - r) * p.x * p.x + w * w * (h + r - 2.0 * p.y), h * p.x - w * p.y );
  return (s<0.0) ? length(p) - r :
         (p.x<w) ? h - p.y     :
                   length(p - vec2(w, h));
}

// Arc - exact   (https://www.shadertoy.com/view/wl23RK)
constexpr
float sdArc(vec2 p, vec2 sc, float ra, float rb ) noexcept {
// sc is the sin/cos of the arc's aperture
  p.x = abs(p.x);
  return ((sc.y * p.x > sc.x * p.y) ? length(p - sc * ra) :
                                abs(length(p) - ra)) - rb;
}

// Ring - exact   (https://www.shadertoy.com/view/DsccDH)
constexpr
float sdRing(vec2 p, vec2 n, float r, float th ) noexcept {
  p.x = abs(p.x);
  p = mat2x2(n.x, n.y, -n.y, n.x) * p;
  return max(abs(length(p) - r) - th * 0.5,
              length(vec2(p.x, max(0.0, abs(r - p.y) - th * 0.5))) * sign(p.x) );
}

// Horseshoe - exact   (https://www.shadertoy.com/view/WlSGW1)
constexpr
float sdHorseshoe(vec2 p, vec2 c, float r, vec2 w ) noexcept {
  p.x = abs(p.x);
  float l = length(p);
  p = mat2(-c.x, c.y, c.y, c.x) * p;
  p = vec2((p.y > 0.0 || p.x > 0.0) ? p.x : l * sign(-c.x),
           (p.x > 0.0) ? p.y : l );
  p = vec2(p.x, abs(p.y - r)) - w;
  return length(max(p, 0.0)) + min(0.0, max(p.x, p.y));
}

// Vesica - exact   (https://www.shadertoy.com/view/XtVfRW)
constexpr
float sdVesica(vec2 p, float w, float h) noexcept {
  vec3 d = 0.5 * (w * w - h * h)/h;
  p = abs(p);
  vec3 c = (w * p.y<d * (p.x - w)) ? vec3(0.0, w, 0.0) : vec3(-d, 0.0, d + h);
  return length(p - c.yx) - c.z;
}

// Oriented Vesica - exact   (https://www.shadertoy.com/view/cs2yzG)
constexpr
float sdOrientedVesica(vec2 p, vec2 a, vec2 b, float w ) noexcept {
  float r = 0.5 * length(b - a);
  float d = 0.5 * (r * r - w * w) / w;
  vec2 v = (b - a) / r;
  vec2 c = (b + a) * 0.5;
  vec2 q = 0.5 * abs(mat2(v.y, v.x, -v.x, v.y) * (p - c));
  vec3 h = (r * q.x<d * (q.y - r)) ? vec3(0.0, r, 0.0) : vec3(-d, 0.0, d + w);
  return length(q - h.xy) - h.z;
}

// Moon - exact   (https://www.shadertoy.com/view/WtdBRS)
constexpr
float sdMoon(vec2 p, float d, float ra, float rb ) noexcept {
  p.y = abs(p.y);
  float a = (ra * ra - rb * rb + d * d) / (2.0 * d);
  float b = sqrt(max(ra * ra - a * a, 0.0));
  if (d * (p.x * b - p.y * a) > d * d * max(b - p.y, 0.0)) {
    return length(p - vec2(a, b));
  }

  return max((length(p          ) - ra),
             -(length(p - vec2(d, 0)) - rb));
}

// Circle Cross - exact   (https://www.shadertoy.com/view/NslXDM)
constexpr
float sdRoundedCross(vec2 p, float h ) noexcept {
  float k = 0.5 * (h + 1.0 / h);
  p = abs(p);
  return (p.x<1.0 && p.y<p.x * (k - h) + h ) ?
           k - sqrt(dot2(p - vec2(1, k)))  :
         sqrt(min(dot2(p - vec2(0, h)),
                  dot2(p - vec2(1, 0))));
}

// Simple Egg - exact   (https://www.shadertoy.com/view/XtVfRW)
constexpr
float sdEgg(vec2 p, float ra, float rb ) noexcept {
  const float k = sqrt(3.0);
  p.x = abs(p.x);
  float r = ra - rb;
  return ((p.y<0.0)       ? length(vec2(p.x,  p.y    )) - r :
          (k * (p.x + r)<p.y) ? length(vec2(p.x,  p.y - k * r)) :
                            length(vec2(p.x + r, p.y    )) - 2.0 * r) - rb;
}

// Heart - exact   (https://www.shadertoy.com/view/3tyBzV)
constexpr
float sdHeart(vec2 p ) noexcept {
  p.x = abs(p.x);

  if (p.y + p.x > 1.0 ) {
    return sqrt(dot2(p - vec2(0.25, 0.75))) - sqrt(2.0) / 4.0;
  }

  return sqrt(min(dot2(p - vec2(0.00, 1.00)),
                  dot2(p - 0.5 * max(p.x + p.y, 0.0)))) * sign(p.x - p.y);
}

// Cross - exact exterior, bound interior   (https://www.shadertoy.com/view/XtGfzw)
constexpr
float sdCross(vec2 p, vec2 b, float r ) noexcept  {
  p = abs(p); p = (p.y > p.x) ? p.yx : p.xy;
  vec2  q = p - b;
  float k = max(q.y, q.x);
  vec2  w = (k > 0.0) ? q : vec2(b.y - p.x, -k);
  return sign(k) * length(max(w, 0.0)) + r;
}

// Rounded X - exact   (https://www.shadertoy.com/view/3dKSDc)
constexpr
float sdRoundedX(vec2 p, float w, float r ) noexcept {
  p = abs(p);
  return length(p - min(p.x + p.y, w) * 0.5) - r;
}

// Polygon - exact   (https://www.shadertoy.com/view/wdBXRW)
constexpr
float sdPolygon(vec2[N] v, vec2 p ) noexcept {
  float d = dot(p - v[0], p - v[0]);
  float s = 1.0;
  for(int i=0, j=N - 1; i<N; j=i, i++ ) {
    vec2 e = v[j] - v[i];
    vec2 w =    p - v[i];
    vec2 b = w - e * clamp(dot(w, e) / dot(e, e), 0.0, 1.0 );
    d = min(d, dot(b, b) );
    bvec3 c = bvec3(p.y > =v[i].y, p.y<v[j].y, e.x * w.y > e.y * w.x);
    if (all(c) || all(not(c)) ) {
      s * =-1.0;
    }
  }
  return s * sqrt(d);
}

// Ellipse - exact   (https://www.shadertoy.com/view/4sS3zz)
constexpr
float sdEllipse(vec2 p, vec2 ab ) noexcept {
  p = abs(p);
  if (p.x > p.y ) {
    p=p.yx;ab=ab.yx;
  }
  float l = ab.y * ab.y - ab.x * ab.x;
  float m = ab.x * p.x / l;      float m2 = m * m;
  float n = ab.y * p.y / l;      float n2 = n * n;
  float c = (m2 + n2 - 1.0) / 3.0; float c3 = c * c * c;
  float q = c3 + m2 * n2 * 2.0;
  float d = c3 + m2 * n2;
  float g = m + m * n2;
  float co;
  if (d<0.0 ) {
    float h = acos(q / c3) / 3.0;
    float s = cos(h);
    float t = sin(h) * sqrt(3.0);
    float rx = sqrt(-c * (s + t + 2.0) + m2 );
    float ry = sqrt(-c * (s - t + 2.0) + m2 );
    co = (ry + sign(l) * rx + abs(g) / (rx * ry)- m) / 2.0;
  } else {
    float h = 2.0 * m * n * sqrt(d );
    float s = sign(q + h) * pow(abs(q + h), 1.0 / 3.0);
    float u = sign(q - h) * pow(abs(q - h), 1.0 / 3.0);
    float rx = -s - u - c * 4.0 + 2.0 * m2;
    float ry = (s - u) * sqrt(3.0);
    float rm = sqrt(rx * rx + ry * ry );
    co = (ry / sqrt(rm - rx) + 2.0 * g / rm - m) / 2.0;
  }
  vec2 r = ab * vec2(co, sqrt(1.0 - co * co));
  return length(r - p) * sign(p.y - r.y);
}

// Parabola - exact   (https://www.shadertoy.com/view/ws3GD7)
constexpr
float sdParabola(vec2 pos, float k ) noexcept {
  pos.x = abs(pos.x);
  float ik = 1.0 / k;
  float p = ik * (pos.y - 0.5 * ik) / 3.0;
  float q = 0.25 * ik * ik * pos.x;
  float h = q * q - p * p * p;
  float r = sqrt(abs(h));
  float x = (h > 0.0) ?
      pow(q + r, 1.0 / 3.0) - pow(abs(q - r), 1.0 / 3.0) * sign(r - q) :
      2.0 * cos(atan(r, q) / 3.0) * sqrt(p);
  return length(pos - vec2(x, k * x * x)) * sign(pos.x - x);
}

// Parabola Segment - exact   (https://www.shadertoy.com/view/3lSczz)
constexpr
float sdParabola(vec2 pos, float wi, float he ) noexcept {
  pos.x = abs(pos.x);
  float ik = wi * wi / he;
  float p = ik * (he - pos.y - 0.5 * ik) / 3.0;
  float q = pos.x * ik * ik * 0.25;
  float h = q * q - p * p * p;
  float r = sqrt(abs(h));
  float x = (h > 0.0) ?
      pow(q + r, 1.0 / 3.0) - pow(abs(q - r), 1.0 / 3.0) * sign(r - q) :
      2.0 * cos(atan(r / q) / 3.0) * sqrt(p);
  x = min(x, wi);
  return length(pos - vec2(x, he - x * x / ik)) * 
         sign(ik * (pos.y - he) + pos.x * pos.x);
}

// Quadratic Bezier - exact   (https://www.shadertoy.com/view/MlKcDD)
constexpr
float sdBezier(vec2 pos, vec2 A, vec2 B, vec2 C ) noexcept {
  vec2 a = B - A;
  vec2 b = A - 2.0 * B + C;
  vec2 c = a * 2.0;
  vec2 d = A - pos;
  float kk = 1.0 / dot(b, b);
  float kx = kk * dot(a, b);
  float ky = kk * (2.0 * dot(a, a) + dot(d, b)) / 3.0;
  float kz = kk * dot(d, a);
  float res = 0.0;
  float p = ky - kx * kx;
  float p3 = p * p * p;
  float q = kx * (2.0 * kx * kx - 3.0 * ky) + kz;
  float h = q * q + 4.0 * p3;
  if (h > = 0.0) {
    h = sqrt(h);
    vec2 x = (vec2(h, -h) - q) / 2.0;
    vec2 uv = sign(x) * pow(abs(x), vec2(1.0 / 3.0));
    float t = clamp(uv.x + uv.y - kx, 0.0, 1.0 );
    res = dot2(d + (c + b * t) * t);
  } else {
    float z = sqrt(-p);
    float v = acos(q / (p * z * 2.0) ) / 3.0;
    float m = cos(v);
    float n = sin(v) * 1.732050808;
    vec3  t = clamp(vec3(m + m, -n-m, n - m) * z - kx, 0.0, 1.0);
    res = min(dot2(d + (c + b * t.x) * t.x),
               dot2(d + (c + b * t.y) * t.y) );
// the third root cannot be the closest
// res = min(res, dot2(d + (c + b * t.z) * t.z));
  }
  return sqrt(res );
}

// Bobbly Cross - exact   (https://www.shadertoy.com/view/NssXWM)
constexpr
float sdBlobbyCross(vec2 pos, float he ) noexcept {
  pos = abs(pos);
  pos = vec2(abs(pos.x - pos.y), 1.0 - pos.x - pos.y) / sqrt(2.0);

  float p = (he - pos.y - 0.25 / he) / (6.0 * he);
  float q = pos.x / (he * he * 16.0);
  float h = q * q - p * p * p;

  float x;
  if (h > 0.0 ) {
    float r = sqrt(h); x = pow(q + r, 1.0 / 3.0) - pow(abs(q - r), 1.0 / 3.0) * sign(r - q);
  } else {
    float r = sqrt(p); x = 2.0 * r * cos(acos(q / (p * r)) / 3.0);
  }
  x = min(x, sqrt(2.0) / 2.0);

  vec2 z = vec2(x, he * (1.0 - 2.0 * x * x)) - pos;
  return length(z) * sign(z.y);
}

// Tunnel - exact   (https://www.shadertoy.com/view/flSSDy)
constexpr
float sdTunnel(vec2 p, vec2 wh ) noexcept {
  p.x = abs(p.x); p.y = -p.y;
  vec2 q = p - wh;

  float d1 = dot2(vec2(max(q.x, 0.0), q.y));
  q.x = (p.y > 0.0) ? q.x : length(p) - wh.x;
  float d2 = dot2(vec2(q.x, max(q.y, 0.0)));
  float d = sqrt(min(d1, d2) );

  return (max(q.x, q.y)<0.0) ? -d : d;
}

// Stairs - exact   (https://www.shadertoy.com/view/7tKSWt)
constexpr
float sdStairs(vec2 p, vec2 wh, float n ) noexcept {
  vec2 ba = wh * n;
  float d = min(dot2(p - vec2(clamp(p.x, 0.0, ba.x), 0.0)),
                dot2(p - vec2(ba.x, clamp(p.y, 0.0, ba.y))) );
  float s = sign(max(-p.y, p.x - ba.x) );

  float dia = length(wh);
  p = mat2(wh.x, -wh.y, wh.y, wh.x) * p / dia;
  float id = clamp(round(p.x / dia), 0.0, n - 1.0);
  p.x = p.x - id * dia;
  p = mat2(wh.x, wh.y, -wh.y, wh.x) * p / dia;

  float hh = wh.y / 2.0;
  p.y -= hh;
  if (p.y > hh * sign(p.x) ) {
    s=1.0;
  }
  p = (id<0.5 || p.x > 0.0) ? p : -p;
  d = min(d, dot2(p - vec2(0.0, clamp(p.y, -hh, hh))) );
  d = min(d, dot2(p - vec2(clamp(p.x, 0.0, wh.x), hh)) );

  return sqrt(d) * s;
}

// Quadratic Circle - exact   (https://www.shadertoy.com/view/Nd3cW8)
constexpr
float sdQuadraticCircle(vec2 p ) noexcept {
  p = abs(p);
  if (p.y > p.x ) {
    p=p.yx;
  }

  float a = p.x - p.y;
  float b = p.x + p.y;
  float c = (2.0 * b - 1.0) / 3.0;
  float h = a * a + c * c * c;
  float t;
  if (h > =0.0 ) {
    h = sqrt(h);
    t = sign(h - a) * pow(abs(h - a), 1.0 / 3.0) - pow(h + a, 1.0 / 3.0);
  } else {
    float z = sqrt(-c);
    float v = acos(a / (c * z)) / 3.0;
    t = -z * (cos(v) + sin(v) * 1.732050808);
  }
  t * = 0.5;
  vec2 w = vec2(-t, t) + 0.75 - t * t - p;
  return length(w) * sign(a * a * 0.5 + b - 1.5 );
}

// Hyperbola - exact   (https://www.shadertoy.com/view/DtjXDG)
// k (0, inf)
constexpr
float sdHyperbola(vec2 p, float k, float he ) noexcept {
  p = abs(p);
  p = vec2(p.x - p.y, p.x + p.y) / sqrt(2.0);

  float x2 = p.x * p.x / 16.0;
  float y2 = p.y * p.y / 16.0;
  float r = k * (4.0 * k - p.x * p.y) / 12.0;
  float q = (x2 - y2) * k * k;
  float h = q * q + r * r * r;
  float u;
  if (h<0.0 ) {
    float m = sqrt(-r);
    u = m * cos(acos(q / (r * m)) / 3.0 );
  } else {
    float m = pow(sqrt(h) - q, 1.0 / 3.0);
    u = (m - r / m) / 2.0;
  }
  float w = sqrt(u + x2 );
  float b = k * p.y - x2 * p.x * 2.0;
  float t = p.x / 4.0 - w + sqrt(2.0 * x2 - u + b / w / 4.0 );
  t = max(t, sqrt(he * he * 0.5 + k) - he / sqrt(2.0));
  float d = length(p - vec2(t, k / t) );
  return p.x * p.y < k ? d : -d;
}

// Cool S - exact   (https://www.shadertoy.com/view/clVXWc)
constexpr
float sdfCoolS(vec2 p ) noexcept {
  float six = (p.y<0.0) ? -p.x : p.x;
  p.x = abs(p.x);
  p.y = abs(p.y) - 0.2;
  float rex = p.x - min(round(p.x / 0.4), 0.4);
  float aby = abs(p.y - 0.2) - 0.6;

  float d = dot2(vec2(six, -p.y) - clamp(0.5 * (six - p.y), 0.0, 0.2));
  d = min(d, dot2(vec2(p.x, -aby) - clamp(0.5 * (p.x - aby), 0.0, 0.4)));
  d = min(d, dot2(vec2(rex, p.y  -clamp(p.y          , 0.0, 0.4))));

  float s = 2.0 * p.x + aby + abs(aby + 0.4) - 0.4;
  return sqrt(d) * sign(s);
}

// Circle Wave - exact   (https://www.shadertoy.com/view/stGyzt)
constexpr
float sdCircleWave(vec2 p, float tb, float ra ) noexcept {
  tb = 3.1415927 * 5.0 / 6.0 * max(tb, 0.0001);
  vec2 co = ra * vec2(sin(tb), cos(tb));
  p.x = abs(mod(p.x, co.x * 4.0) - co.x * 2.0);
  vec2  p1 = p;
  vec2  p2 = vec2(abs(p.x - 2.0 * co.x), -p.y + 2.0 * co.y);
  float d1 = ((co.y * p1.x > co.x * p1.y) ? length(p1 - co) : abs(length(p1) - ra));
  float d2 = ((co.y * p2.x > co.x * p2.y) ? length(p2 - co) : abs(length(p2) - ra));
  return min(d1, d2);
}

constexpr
float opRound(const vec2 p, const float r) noexcept {
  return sdShape(p) - r;
}

constexpr
float opOnion(const vec2 p, const float r) noexcept {
  return abs(sdShape(p)) - r;
}

}

}
