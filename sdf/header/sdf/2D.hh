#pragma once

#include "shapes/functions.hh"
#include "shapes/vec.hh"
#include "shapes/mat2.hh"

#include <vector>

namespace flp {

// Circle - exact (https://www.shadertoy.com/view/3ltSW2)
constexpr
float sdCircle(const fvec2 p, float r) noexcept {
  return length(p) - r;
}

// Rounded Box - exact   (https://www.shadertoy.com/view/4llXD7 and https://www.youtube.com/watch?v=s5NGeUV2EyU)
constexpr
float sdRoundedBox(const fvec2 p, fvec2 b, fvec4 r) noexcept {
  r("xy"_swz) = (p.x() > 0.0f) ? fvec2(r("xy"_swz)) : fvec2(r("zw"_swz));
  r.x()  = (p.y() > 0.0f) ? r.x() : r.y();

  const fvec2 q = abs(p) - b + r.x();
  return min(max(q.x(), q.y()), 0.0f) + length(max(q, 0.0f)) - r.x();
}

// Chamfer Box - exact (https://www.shadertoy.com/view/3fc3zs)
constexpr
float sdChamferBox(fvec2 p, fvec2 b, float chamfer) noexcept {
  p = abs(p) - b;
  p = (p.y() > p.x()) ? fvec2(p("yx"_swz)) : fvec2(p("xy"_swz));
  p.y() += chamfer;

  const float k = 1.0f - sqrt(2.0f);
  if (p.y()<0.0f && p.y() + p.x() * k<0.0f) {
    return p.x();
  }

  if (p.x()<p.y()) {
    return (p.x() + p.y()) * sqrt(0.5f);
  }

  return length(p);
}

// Box - exact (https://www.youtube.com/watch?v=62-pRVZuS5c)
constexpr
float sdBox(const fvec2 p, fvec2 b) noexcept {
  const fvec2 d = abs(p) - b;
  return length(max(d, 0.0f)) + min(max(d.x(), d.y()), 0.0f);
}

// Oriented Box - exact (https://www.shadertoy.com/view/stcfzn)
constexpr
float sdOrientedBox(const fvec2 p, const fvec2 a, const fvec2 b, const float th) noexcept {
  const float l = length(b - a);
  const fvec2 d = (b - a) / l;
  fvec2 q = (p - (a + b) * 0.5f);
  q = mat2x2(d.x(), -d.y(), d.y(), d.x()) * q;
  q = abs(q) - fvec2(l, th) * 0.5f;
  return length(max(q, 0.0f)) + min(max(q.x(), q.y()), 0.0f);
}

// Segment - exact (https://www.shadertoy.com/view/3tdSDj and https://www.youtube.com/watch?v=PMltMdi1Wz()g)
constexpr
float sdSegment(const fvec2 p, fvec2 a, fvec2 b) noexcept {
  const fvec2 pa = p - a, ba = b - a;
  const float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0f, 1.0f);
  return length(pa - ba * h);
}

// Rhombus - exact   (https://www.shadertoy.com/view/XdXcRB)
constexpr
float sdRhombus(fvec2 p, fvec2 b) noexcept {
  p = abs(p);
  const float h = clamp(ndot(b - 2.0f * p, b) / dot(b, b), -1.0f, 1.0f);
  const float d = length(p - 0.5f * b * fvec2(1.0f - h, 1.0f + h));
  return d * sign(p.x() * b.y() + p.y() * b.x() - b.x() * b.y());
}

// Isosceles Trapezoid - exact   (https://www.shadertoy.com/view/MlycD3)
constexpr
float sdTrapezoid(fvec2 p, float r1, float r2, float he) noexcept {
  const fvec2 k1 = fvec2(r2, he);
  const fvec2 k2 = fvec2(r2 - r1, 2.0f * he);
  p.x() = abs(p.x());
  const fvec2 ca = fvec2(p.x() - min(p.x(), (p.y() < 0.0f) ? r1 : r2), abs(p.y()) - he);
  const fvec2 cb = p - k1 + k2 * clamp(dot(k1 - p, k2) / dot2(k2), 0.0f, 1.0f);
  const float s = (cb.x() < 0.0f && ca.y() < 0.0f) ? -1.0f : 1.0f;
  return s * sqrt(min(dot2(ca), dot2(cb)));
}

// Parallelogram - exact   (https://www.shadertoy.com/view/7dlGRf)
constexpr
float sdParallelogram(fvec2 p, float wi, float he, float sk) noexcept {
  const fvec2 e = fvec2(sk, he);
  p = (p.y()<0.0f) ? -p : p;

  fvec2 w = p - e;
  w.x() -= clamp(w.x(), -wi, wi);

  fvec2 d = fvec2(dot(w, w), -w.y());
  const float s = p.x() * e.y() - p.y() * e.x();
  p = (s<0.0f) ? -p : p;

  fvec2 v = p - fvec2(wi, 0.f);
  v -= e * clamp(dot(v, e) / dot(e, e), -1.0f, 1.0f);
  d = min(d, fvec2(dot(v, v), wi * he - abs(s)));

  return sqrt(d.x()) * sign(-d.y());
}

// Equilateral Triangle - exact   (https://www.shadertoy.com/view/Xl2yDW)
constexpr
float sdEquilateralTriangle(fvec2 p, float r) noexcept {
  const float k = sqrt(3.0f);
  p.x() = abs(p.x()) - r;
  p.y() = p.y() + r / k;

  if (p.x() + k * p.y() > 0.0f) {
    p = fvec2(p.x() - k * p.y(), -k * p.x() - p.y()) / 2.0f;
  }

  p.x() -= clamp(p.x(), -2.0f * r, 0.0f);
  return -length(p) * sign(p.y());
}

// Isosceles Triangle - exact   (https://www.shadertoy.com/view/MldcD7)
constexpr
float sdTriangleIsosceles(fvec2 p, fvec2 q) noexcept {
  p.x() = abs(p.x());
  fvec2 a = p - q * clamp(dot(p, q) / dot(q, q), 0.0f, 1.0f);
  fvec2 b = p - q * fvec2(clamp(p.x() / q.x(), 0.0f, 1.0f), 1.0f);
  float s = -sign(q.y());
  fvec2 d = min(fvec2(dot(a, a), s * (p.x() * q.y() - p.y() * q.x())),
                fvec2(dot(b, b), s * (p.y() - q.y())));
  return -sqrt(d.x()) * sign(d.y());
}

// Triangle - exact   (https://www.shadertoy.com/view/XsXSz4)
constexpr
float sdTriangle(fvec2 p, fvec2 p0, fvec2 p1, fvec2 p2) noexcept {
  const fvec2 e0 = p1 - p0, e1 = p2 - p1, e2 = p0 - p2;
  const fvec2 v0 = p -p0, v1 = p -p1, v2 = p -p2;
  const fvec2 pq0 = v0 - e0 * clamp(dot(v0, e0) / dot(e0, e0), 0.0f, 1.0f);
  const fvec2 pq1 = v1 - e1 * clamp(dot(v1, e1) / dot(e1, e1), 0.0f, 1.0f);
  const fvec2 pq2 = v2 - e2 * clamp(dot(v2, e2) / dot(e2, e2), 0.0f, 1.0f);
  const float s = sign(e0.x() * e2.y() - e0.y() * e2.x());
  const fvec2 d = min(min(fvec2(dot(pq0, pq0), s * (v0.x() * e0.y() - v0.y() * e0.x())),
                         fvec2(dot(pq1, pq1), s * (v1.x() * e1.y() - v1.y() * e1.x()))),
                         fvec2(dot(pq2, pq2), s * (v2.x() * e2.y() - v2.y() * e2.x())));
  return -sqrt(d.x()) * sign(d.y());
}

// Uneven Capsule - exact   (https://www.shadertoy.com/view/4lcBWn)
constexpr
float sdUnevenCapsule(fvec2 p, float r1, float r2, float h) noexcept {
  p.x() = abs(p.x());
  const float b = (r1 - r2) / h;
  const float a = sqrt(1.0f - b * b);
  const float k = dot(p, fvec2(-b, a));

  if (k < 0.0f) {
    return length(p) - r1;
  }

  if (k > a * h) {
    return length(p - fvec2(0.0f, h)) - r2;
  }

  return dot(p, fvec2(a, b)) - r1;
}

// Regular Pentagon - exact   (https://www.shadertoy.com/view/llVyWW())
constexpr
float sdPentagon(fvec2 p, float r) noexcept {
  const fvec3 k = fvec3(0.809016994f, 0.587785252f, 0.726542528f);
  p.x() = abs(p.x());
  p -= 2.0f * min(dot(fvec2(-k.x(), k.y()), p), 0.0f) * fvec2(-k.x(), k.y());
  p -= 2.0f * min(dot(fvec2(k.x(), k.y()), p), 0.0f) * fvec2(k.x(), k.y());
  p -= fvec2(clamp(p.x(), -r * k.z(), r * k.z()), r);
  return length(p) * sign(p.y());
}

// Regular Hexagon - exact
constexpr
float sdHexagon(fvec2 p, float r) noexcept {
  const fvec3 k = fvec3(-0.866025404f, 0.5f, 0.577350269f);
  p = abs(p);
  p -= 2.0f * min(dot(k("xy"_swz), p), 0.0f) * k("xy"_swz);
  p -= fvec2(clamp(p.x(), -k.z() * r, k.z() * r), r);
  return length(p) * sign(p.y());
}

// Regular Octogon - exact   (https://www.shadertoy.com/view/llGfDG)
constexpr
float sdOctogon(fvec2 p, const float r) noexcept {
  const fvec3 k = fvec3(-0.9238795325f, 0.3826834323f, 0.4142135623f);
  p = abs(p);
  p -= 2.0f * min(dot(fvec2(k.x(), k.y()), p), 0.0f) * fvec2(k.x(), k.y());
  p -= 2.0f * min(dot(fvec2(-k.x(), k.y()), p), 0.0f) * fvec2(-k.x(), k.y());
  p -= fvec2(clamp(p.x(), -k.z() * r, k.z() * r), r);
  return length(p) * sign(p.y());
}

// Hexagram - exact   (https://www.shadertoy.com/view/tt23RR)
constexpr
float sdHexagram(fvec2 p, float r) noexcept {
  const fvec4 k = fvec4(-0.5f, 0.8660254038f, 0.5773502692f, 1.7320508076f);
  p = abs(p);
  p -= 2.0f * min(dot(k("xy"_swz), p), 0.0f) * k("xy"_swz);
  p -= 2.0f * min(dot(k("yx"_swz), p), 0.0f) * k("yx"_swz);
  p -= fvec2(clamp(p.x(), r * k.z(), r * k.w()), r);
  return length(p) * sign(p.y());
}

// Pentagram - exact   (https://www.shadertoy.com/view/t3X3z4)
constexpr
float sdPentagram(fvec2 p, float r) noexcept {
  const float k1x = 0.809016994f;// cosf(π / 5) = ¼(√5 + 1)
  const float k2x = 0.309016994f;// sinf(π / 10) = ¼(√5 - 1)
  const float k1y = 0.587785252f;// sinf(π / 5) = ¼√(10 - 2√5)
  const float k2y = 0.951056516f;// cosf(π / 10) = ¼√(10 + 2√5)
  const float k1z = 0.726542528f;// tanf(π / 5) = √(5 - 2√5)
  const fvec2  v1  = fvec2(k1x, -k1y);
  const fvec2  v2  = fvec2(-k1x, -k1y);
  const fvec2  v3  = fvec2(k2x, -k2y);

  p.x() = abs(p.x());
  p -= 2.0f * max(dot(v1, p), 0.0f) * v1;
  p -= 2.0f * max(dot(v2, p), 0.0f) * v2;
  p.x() = abs(p.x());
  p.y() -= r;
  return length(p - v3 * clamp(dot(p, v3), 0.0f, k1z * r))
 * sign(p.y() * v3.x() - p.x() * v3.y());
}

// Regular Star - exact   (https://www.shadertoy.com/view/3tSGDy)
constexpr
float sdStar(fvec2 p, float r, int n, float m) noexcept {
  // next 4 lines can be precomputed for a given shape
  const float an = 3.141593f / float(n);
  const float en = 3.141593f / m;// m is between 2 and n
  const fvec2 acs = fvec2(cosf(an), sinf(an));
  const fvec2 ecs = fvec2(cosf(en), sinf(en));// ecs=fvec2(0, 1) for regular polygon

  const float bn = fmod(atanf(p.x() / p.y()), 2.0f * an) - an;
  p = length(p) * fvec2(cosf(bn), abs(sinf(bn)));
  p -= r * acs;
  p += ecs * clamp(-dot(p, ecs), 0.0f, r * acs.y() / ecs.y());
  return length(p) * sign(p.x());
}

// Pie - exact   (https://www.shadertoy.com/view/3l23RK)
constexpr
float sdPie(fvec2 p, fvec2 c, float r) noexcept {
  p.x() = abs(p.x());
  const float l = length(p) - r;
  const float m = length(p - c * clamp(dot(p, c), 0.0f, r));// c=sinf / cosf of aperture
  return max(l, m * sign(c.y() * p.x() - c.x() * p.y()));
}

// Cut Disk - exact   (https://www.shadertoy.com/view/ftVXRc)
constexpr
float sdCutDisk(fvec2 p, float r, float h) noexcept {
  const float w = sqrt(r * r - h * h);// constant for any given shape
  p.x() = abs(p.x());
  const float s = max((h - r) * p.x() * p.x() + w * w * (h + r - 2.0f * p.y()), h * p.x() - w * p.y());
  return (s < 0.0f) ? length(p) - r :
         (p.x() < w) ? h - p.y()     :
                   length(p - fvec2(w, h));
}

// Arc - exact   (https://www.shadertoy.com/view/wl23RK)
constexpr
float sdArc(fvec2 p, fvec2 sc, float ra, float rb) noexcept {
// sc is the sinf/cosf of the arc's aperture
  p.x() = abs(p.x());
  return ((sc.y() * p.x() > sc.x() * p.y()) ? length(p - sc * ra) :
                                abs(length(p) - ra)) - rb;
}

// Ring - exact   (https://www.shadertoy.com/view/DsccDH)
constexpr
float sdRing(fvec2 p, fvec2 n, float r, float th) noexcept {
  p.x() = abs(p.x());
  p = mat2x2(n.x(), n.y(), -n.y(), n.x()) * p;
  return max(abs(length(p) - r) - th * 0.5f,
              length(fvec2(p.x(), max(0.0f, abs(r - p.y()) - th * 0.5f))) * sign(p.x()));
}

// Horseshoe - exact   (https://www.shadertoy.com/view/WlSGW1)
constexpr
float sdHorseshoe(fvec2 p, fvec2 c, float r, fvec2 w) noexcept {
  p.x() = abs(p.x());
  float l = length(p);
  p = mat2x2(-c.x(), c.y(), c.y(), c.x()) * p;
  p = fvec2((p.y() > 0.0f || p.x() > 0.0f) ? p.x() : l * sign(-c.x()),
           (p.x() > 0.0f) ? p.y() : l);
  p = fvec2(p.x(), abs(p.y() - r)) - w;
  return length(max(p, 0.0f)) + min(0.0f, max(p.x(), p.y()));
}

// Vesica - exact   (https://www.shadertoy.com/view/XtVfRW)
constexpr
float sdVesica(fvec2 p, float w, float h) noexcept {
  const float d = 0.5f * (w * w - h * h) / h;
  p = abs(p);
  const fvec3 c = (w * p.y() < d * (p.x() - w))
                    ? fvec3(0.0f, w, 0.0f)
                    : fvec3(-d, 0.0f, d + h);
  return length(p - c("yx"_swz)) - c.z();
}

// Oriented Vesica - exact   (https://www.shadertoy.com/view/cs2yzG)
constexpr
float sdOrientedVesica(fvec2 p, fvec2 a, fvec2 b, float w) noexcept {
  const float r = 0.5f * length(b - a);
  const float d = 0.5f * (r * r - w * w) / w;
  const fvec2 v = (b - a) / r;
  const fvec2 c = (b + a) * 0.5f;
  const fvec2 q = 0.5f * abs(mat2x2(v.y(), v.x(), -v.x(), v.y()) * (p - c));
  const fvec3 h = (r * q.x() < d * (q.y() - r)) ? fvec3(0.0f, r, 0.0f) : fvec3(-d, 0.0f, d + w);
  return length(q - h("xy"_swz)) - h.z();
}

// Moon - exact   (https://www.shadertoy.com/view/WtdBRS)
constexpr
float sdMoon(fvec2 p, float d, float ra, float rb) noexcept {
  p.y() = abs(p.y());
  float a = (ra * ra - rb * rb + d * d) / (2.0f * d);
  float b = sqrt(max(ra * ra - a * a, 0.0f));
  if (d * (p.x() * b - p.y() * a) > d * d * max(b - p.y(), 0.0f)) {
    return length(p - fvec2(a, b));
  }

  return max((length(p             ) - ra),
            -(length(p - fvec2(d, 0.f)) - rb));
}

// Circle Cross - exact   (https://www.shadertoy.com/view/NslXDM)
constexpr
float sdRoundedCross(fvec2 p, float h) noexcept {
  float k = 0.5f * (h + 1.0f / h);
  p = abs(p);
  return (p.x() < 1.0f && p.y() < p.x() * (k - h) + h) ?
           k - sqrt(dot2(p - fvec2(1.f, k)))  :
         sqrt(min(dot2(p - fvec2(0.f, h)),
                  dot2(p - fvec2(1.f, 0.f))));
}

// Simple Egg - exact   (https://www.shadertoy.com/view/XtVfRW)
constexpr
float sdEgg(fvec2 p, float ra, float rb) noexcept {
  const float k = sqrt(3.f);
  p.x() = abs(p.x());
  float r = ra - rb;
  return ((p.y() < 0.f)            ? length(fvec2(p.x(),     p.y())) - r :
          (k * (p.x() + r) < p.y()) ? length(fvec2(p.x(),     p.y() - k * r)) :
                                      length(fvec2(p.x() + r, p.y())) - 2.0f * r) - rb;
}

// Heart - exact   (https://www.shadertoy.com/view/3tyBzV)
constexpr
float sdHeart(fvec2 p) noexcept {
  p.x() = abs(p.x());

  if (p.y() + p.x() > 1.f) {
    return sqrt(dot2(p - fvec2(0.25f, 0.75f))) - sqrt(2.f) / 4.f;
  }

  return sqrt(min(dot2(p - fvec2(0.00f, 1.00f)),
                  dot2(p - .5f * max(p.x() + p.y(), 0.f)))) * sign(p.x() - p.y());
}

// Cross - exact exterior, bound interior   (https://www.shadertoy.com/view/XtGfzw())
constexpr
float sdCross(fvec2 p, fvec2 b, float r) noexcept  {
  p = abs(p);
  p = (p.y() > p.x()) ? fvec2(p("yx"_swz)) : fvec2(p("xy"_swz));
  fvec2  q = p - b;
  float k = max(q.y(), q.x());
  fvec2  w = (k > 0.0f) ? q : fvec2(b.y() - p.x(), -k);
  return sign(k) * length(max(w, 0.0f)) + r;
}

// Rounded X - exact   (https://www.shadertoy.com/view/3dKSDc)
constexpr
float sdRoundedX(fvec2 p, float w, float r) noexcept {
  p = abs(p);
  return length(p - min(p.x() + p.y(), w) * 0.5f) - r;
}

// Polygon - exact   (https://www.shadertoy.com/view/wdBXRW)
constexpr
float sdPolygon(const std::vector<fvec2>& v, fvec2 p) noexcept {
  const auto N = v.size();
  float d = dot(p - v[0], p - v[0]);
  float s = 1.0f;
  for(int i = 0, j = N - 1; i < N; j = i, i++) {
    fvec2 e = v[j] - v[i];
    fvec2 w =    p - v[i];
    fvec2 b = w - e * clamp(dot(w, e) / dot(e, e), 0.0f, 1.0f);
    d = min(d, dot(b, b));
    bvec3 c = bvec3(p.y() >= v[i].y(), p.y() < v[j].y(), e.x() * w.y() > e.y() * w.x());
    if (all(c) || all(negate(c))) {
      s *= -1.0f;
    }
  }
  return s * sqrt(d);
}

// Ellipse - exact   (https://www.shadertoy.com/view/4sS3zz())
constexpr
float sdEllipse(fvec2 p, fvec2 ab) noexcept {
  p = abs(p);
  if (p.x() > p.y()) {
    p = p("yx"_swz);
    ab = ab("yx"_swz);
  }

  const float l = ab.y() * ab.y() - ab.x() * ab.x();
  const float m = ab.x() * p.x() / l;
  const float m2 = m * m;
  const float n = ab.y() * p.y() / l;
  const float n2 = n * n;
  const float c = (m2 + n2 - 1.0f) / 3.0f;
  const float c3 = c * c * c;
  const float q = c3 + m2 * n2 * 2.0f;
  const float d = c3 + m2 * n2;
  const float g = m + m * n2;
  float co;

  if (d<0.0f) {
    const float h = acosf(q / c3) / 3.0f;
    const float s = cosf(h);
    const float t = sinf(h) * sqrt(3.0f);
    const float rx = sqrt(-c * (s + t + 2.0f) + m2);
    const float ry = sqrt(-c * (s - t + 2.0f) + m2);
    co = (ry + sign(l) * rx + abs(g) / (rx * ry)- m) / 2.0f;
  } else {
    const float h = 2.0f * m * n * sqrt(d);
    const float s = sign(q + h) * pow(abs(q + h), 1.0f / 3.0f);
    const float u = sign(q - h) * pow(abs(q - h), 1.0f / 3.0f);
    const float rx = -s - u - c * 4.0f + 2.0f * m2;
    const float ry = (s - u) * sqrt(3.0f);
    const float rm = sqrt(rx * rx + ry * ry);
    co = (ry / sqrt(rm - rx) + 2.0f * g / rm - m) / 2.0f;
  }

  const fvec2 r = ab * fvec2(co, sqrtf(1.0f - co * co));
  return length(r - p) * sign(p.y() - r.y());
}

// Parabola - exact   (https://www.shadertoy.com/view/ws3GD7)
constexpr
float sdParabola(fvec2 pos, float k) noexcept {
  pos.x() = abs(pos.x());
  const float ik = 1.0f / k;
  const float p = ik * (pos.y() - 0.5f * ik) / 3.0f;
  const float q = 0.25f * ik * ik * pos.x();
  const float h = q * q - p * p * p;
  const float r = sqrt(abs(h));
  const float x = (h > 0.0f) ?
      pow(q + r, 1.0f / 3.0f) - pow(abs(q - r), 1.0f / 3.0f) * sign(r - q) :
      2.0f * cosf(atanf(r / q) / 3.0f) * sqrt(p);
  return length(pos - fvec2(x, k * x * x)) * sign(pos.x() - x);
}

// Parabola Segment - exact   (https://www.shadertoy.com/view/3lSczz())
constexpr
float sdParabola(fvec2 pos, float wi, float he) noexcept {
  pos.x() = abs(pos.x());
  float ik = wi * wi / he;
  float p = ik * (he - pos.y() - 0.5f * ik) / 3.0f;
  float q = pos.x() * ik * ik * 0.25f;
  float h = q * q - p * p * p;
  float r = sqrt(abs(h));
  float x = (h > 0.0f) ?
      pow(q + r, 1.0f / 3.0f) - pow(abs(q - r), 1.0f / 3.0f) * sign(r - q) :
      2.0f * cosf(atanf(r / q) / 3.0f) * sqrt(p);
  x = min(x, wi);
  return length(pos - fvec2(x, he - x * x / ik)) * 
         sign(ik * (pos.y() - he) + pos.x() * pos.x());
}

// Quadratic Bezier - exact   (https://www.shadertoy.com/view/MlKcDD)
constexpr
float sdBezier(fvec2 pos, fvec2 A, fvec2 B, fvec2 C) noexcept {
  const fvec2 a = B - A;
  const fvec2 b = A - 2.0f * B + C;
  const fvec2 c = a * 2.0f;
  const fvec2 d = A - pos;
  const float kk = 1.0f / dot(b, b);
  const float kx = kk * dot(a, b);
  const float ky = kk * (2.0f * dot(a, a) + dot(d, b)) / 3.0f;
  const float kz = kk * dot(d, a);
  const float p = ky - kx * kx;
  const float p3 = p * p * p;
  const float q = kx * (2.0f * kx * kx - 3.0f * ky) + kz;

  float res = 0.0f;
  float h = q * q + 4.0f * p3;

  if (h >= 0.0f) {
    h = sqrt(h);
    const fvec2 x = (fvec2(h, -h) - q) / 2.0f;
    const fvec2 uv = sign(x) * pow(abs(x), fvec2(1.0f / 3.0f));
    const float t = clamp(uv.x() + uv.y() - kx, 0.0f, 1.0f);

    res = dot2(d + (c + b * t) * t);
  } else {
    const float z = sqrt(-p);
    const float v = acosf(q / (p * z * 2.0f)) / 3.0f;
    const float m = cosf(v);
    const float n = sinf(v) * 1.732050808f;
    const fvec3 t = clamp(fvec3(m + m, -n - m, n - m) * z - kx, 0.0f, 1.0f);

    res = min(dot2(d + (c + b * t.x()) * t.x()),
               dot2(d + (c + b * t.y()) * t.y()));
  // the third root cannot be the closest
  // res = min(res, dot2(d + (c + b * t.z()) * t.z()));
  }

  return sqrt(res);
}

// Bobbly Cross - exact   (https://www.shadertoy.com/view/NssXW()M)
constexpr
float sdBlobbyCross(fvec2 pos, float he) noexcept {
  pos = abs(pos);
  pos = fvec2(abs(pos.x() - pos.y()), 1.0f - pos.x() - pos.y()) / sqrt(2.0f);

  const float p = (he - pos.y() - 0.25f / he) / (6.0f * he);
  const float q = pos.x() / (he * he * 16.0f);
  const float h = q * q - p * p * p;

  float x;
  if (h > 0.0f) {
    const float r = sqrt(h);
    x = pow(q + r, 1.0f / 3.0f) - pow(abs(q - r), 1.0f / 3.0f) * sign(r - q);
  } else {
    const float r = sqrt(p);
    x = 2.0f * r * cosf(acosf(q / (p * r)) / 3.0f);
  }

  x = min(x, sqrt(2.0f) / 2.0f);

  const fvec2 z = fvec2(x, he * (1.0f - 2.0f * x * x)) - pos;

  return length(z) * sign(z.y());
}

// Tunnel - exact   (https://www.shadertoy.com/view/flSSDy)
constexpr
float sdTunnel(fvec2 p, fvec2 wh) noexcept {
  p.x() = abs(p.x());
  p.y() = -p.y();
  fvec2 q = p - wh;

  const float d1 = dot2(fvec2(max(q.x(), 0.0f), q.y()));
  q.x() = (p.y() > 0.0f) ? q.x() : length(p) - wh.x();
  const float d2 = dot2(fvec2(q.x(), max(q.y(), 0.0f)));
  const float d = sqrt(min(d1, d2));

  return (max(q.x(), q.y())<0.0f) ? -d : d;
}

// Stairs - exact   (https://www.shadertoy.com/view/7tKSWt)
constexpr
float sdStairs(fvec2 p, fvec2 wh, float n) noexcept {
  fvec2 ba = wh * n;
  float d = min(dot2(p - fvec2(clamp(p.x(), 0.0f, ba.x()), 0.0f)),
                dot2(p - fvec2(ba.x(), clamp(p.y(), 0.0f, ba.y()))));
  float s = sign(max(-p.y(), p.x() - ba.x()));

  float dia = length(wh);
  p = mat2x2(wh.x(), -wh.y(), wh.y(), wh.x()) * p / dia;
  float id = clamp(round(p.x() / dia), 0.0f, n - 1.0f);
  p.x() = p.x() - id * dia;
  p = mat2x2(wh.x(), wh.y(), -wh.y(), wh.x()) * p / dia;

  float hh = wh.y() / 2.0f;
  p.y() -= hh;
  if (p.y() > hh * sign(p.x())) {
    s=1.0f;
  }
  p = (id < 0.5f || p.x() > 0.0f) ? p : -p;
  d = min(d, dot2(p - fvec2(0.0f, clamp(p.y(), -hh, hh))));
  d = min(d, dot2(p - fvec2(clamp(p.x(), 0.0f, wh.x()), hh)));

  return sqrt(d) * s;
}

// Quadratic Circle - exact   (https://www.shadertoy.com/view/Nd3cW8)
constexpr
float sdQuadraticCircle(fvec2 p) noexcept {
  p = abs(p);
  if (p.y() > p.x()) {
    p = p("yx"_swz);
  }

  float a = p.x() - p.y();
  float b = p.x() + p.y();
  float c = (2.0f * b - 1.0f) / 3.0f;
  float h = a * a + c * c * c;
  float t;
  if (h >=0.f) {
    h = sqrt(h);
    t = sign(h - a) * pow(abs(h - a), 1.0f / 3.0f) - pow(h + a, 1.0f / 3.0f);
  } else {
    float z = sqrt(-c);
    float v = acosf(a / (c * z)) / 3.0f;
    t = -z * (cosf(v) + sinf(v) * 1.732050808f);
  }
  t *= 0.5f;
  fvec2 w = fvec2(-t, t) + 0.75f - t * t - p;
  return length(w) * sign(a * a * 0.5f + b - 1.5f);
}

// Hyperbola - exact   (https://www.shadertoy.com/view/DtjXDG)
// k (0, inf)
constexpr
float sdHyperbola(fvec2 p, float k, float he) noexcept {
  p = abs(p);
  p = fvec2(p.x() - p.y(), p.x() + p.y()) / sqrt(2.0f);

  float x2 = p.x() * p.x() / 16.0f;
  float y2 = p.y() * p.y() / 16.0f;
  float r = k * (4.0f * k - p.x() * p.y()) / 12.0f;
  float q = (x2 - y2) * k * k;
  float h = q * q + r * r * r;
  float u;
  if (h<0.0f) {
    float m = sqrt(-r);
    u = m * cosf(acosf(q / (r * m)) / 3.0f);
  } else {
    float m = pow(sqrt(h) - q, 1.0f / 3.0f);
    u = (m - r / m) / 2.0f;
  }
  float w = sqrt(u + x2);
  float b = k * p.y() - x2 * p.x() * 2.0f;
  float t = p.x() / 4.0f - w + sqrt(2.0f * x2 - u + b / w / 4.0f);
  t = max(t, sqrt(he * he * 0.5f + k) - he / sqrt(2.0f));
  float d = length(p - fvec2(t, k / t));
  return p.x() * p.y() < k ? d : -d;
}

// Cool S - exact   (https://www.shadertoy.com/view/clVXW()c)
constexpr
float sdfCoolS(fvec2 p) noexcept {
  float six = (p.y()<0.0f) ? -p.x() : p.x();
  p.x() = abs(p.x());
  p.y() = abs(p.y()) - 0.2f;
  float rex = p.x() - min(round(p.x() / 0.4f), 0.4f);
  float aby = abs(p.y() - 0.2f) - 0.6f;

  float d = dot2(fvec2(six, -p.y()) - clamp(0.5f * (six - p.y()), 0.0f, 0.2f));
  d = min(d, dot2(fvec2(p.x(), -aby) - clamp(0.5f * (p.x() - aby), 0.0f, 0.4f)));
  d = min(d, dot2(fvec2(rex, p.y()  -clamp(p.y()          , 0.0f, 0.4f))));

  float s = 2.0f * p.x() + aby + abs(aby + 0.4f) - 0.4f;
  return sqrt(d) * sign(s);
}

// Circle Wave - exact   (https://www.shadertoy.com/view/stGyz()t)
constexpr
float sdCircleWave(fvec2 p, float tb, float ra) noexcept {
  tb = 3.1415927f * 5.0f / 6.0f * max(tb, 0.0001f);
  fvec2 co = ra * fvec2(sinf(tb), cosf(tb));
  p.x() = abs(fmod(p.x(), co.x() * 4.0f) - co.x() * 2.0f);
  fvec2  p1 = p;
  fvec2  p2 = fvec2(abs(p.x() - 2.0f * co.x()), -p.y() + 2.0f * co.y());
  float d1 = ((co.y() * p1.x() > co.x() * p1.y()) ? length(p1 - co) : abs(length(p1) - ra));
  float d2 = ((co.y() * p2.x() > co.x() * p2.y()) ? length(p2 - co) : abs(length(p2) - ra));
  return min(d1, d2);
}

//constexpr
//float opRound(const fvec2 p, const float r) noexcept {
//  return sdShape(p) - r;
//}
//
//constexpr
//float opOnion(const fvec2 p, const float r) noexcept {
//  return abs(sdShape(p)) - r;
//}

}
