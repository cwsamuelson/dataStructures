#pragma once

#include "shapes/functions.hh"
#include "shapes/vec3.hh"

namespace flp {

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
