#include <cmath>

#include "spline.hh"

using namespace gsw;

spline::spline(std::initializer_list<point2d> il)
  : mPoly0{0, -1, 2, -1}
  , mPoly1{2, 0, -5, 3}
  , mPoly2{0, 1, 4, -3}
  , mPoly3{0, 0, -1, 1}
  , points(il)
{}

point2d
spline::point(float p) const
{
  int p1 = int(p);
  int p0 = p1 - 1;
  int p2 = p1 + 1;
  int p3 = p1 + 2;

  // get the fractional part
  float fract = p - int(p);

  auto q0 = float(mPoly0(fract));
  auto q1 = float(mPoly1(fract));
  auto q2 = float(mPoly2(fract));
  auto q3 = float(mPoly3(fract));

  float tx = 0.5f * (points[p0].x * q0 + points[p1].x * q1 + points[p2].x * q2 + points[p3].x * q3);
  float ty = 0.5f * (points[p0].y * q0 + points[p1].y * q1 + points[p2].y * q2 + points[p3].y * q3);

  return {tx, ty};
}

point2d
spline::gradient(float p) const
{
  int p1 = int(p);
  int p0 = p1 - 1;
  int p2 = p1 + 1;
  int p3 = p1 + 2;

  // get the fractional part
  float fract = p - int(p);

  float q0 = derive(mPoly0)(fract);
  float q1 = derive(mPoly1)(fract);
  float q2 = derive(mPoly2)(fract);
  float q3 = derive(mPoly3)(fract);

  float tx = 0.5f * (points[p0].x * q0 + points[p1].x * q1 + points[p2].x * q2 + points[p3].x * q3);
  float ty = 0.5f * (points[p0].y * q0 + points[p1].y * q1 + points[p2].y * q2 + points[p3].y * q3);

  return {tx, ty};
}

float
spline::segmentLength(float p, float stepSize) const
{
  float length = 0.0f;

  auto oldpt = point(p);
  decltype(oldpt) newpt;

  for(float t = 0.0f; t < 1.0f; t += stepSize)
  {
    newpt = point(p + t);

    auto xdiff = newpt.x - oldpt.x;
    auto ydiff = newpt.y - oldpt.y;
    auto xdiff2 = xdiff * xdiff;
    auto ydiff2 = ydiff * ydiff;
    length += sqrt(xdiff2 + ydiff2);

    oldpt = newpt;
  }

  return length;
}

