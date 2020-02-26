#include "spline.hh"

using namespace gsw;

spline::spline()
  : mPoly0{0, -1, 2, -1}
  , mPoly1{2, 0, -5, 3}
  , mPoly2{0, 1, 4, -3}
  , mPoly3{0, 0, -1, 1}
{}

point2d
spline::operator()(float p)
{
  int p1 = int(p);
  int p0 = p1 - 1;
  int p2 = p1 + 1;
  int p3 = p1 + 2;

  // get the fractional part
  float fract = p - int(p);

  float q0 = mPoly0(fract);
  float q1 = mPoly1(fract);
  float q2 = mPoly2(fract);
  float q3 = mPoly3(fract);

  float tx = 0.5f * (mPoints[p0].x * q0 + mPoints[p1].x * q1 + mPoints[p2].x * q2 + mPoints[p3].x * q3);
  float ty = 0.5f * (mPoints[p0].y * q0 + mPoints[p1].y * q1 + mPoints[p2].y * q2 + mPoints[p3].y * q3);

  return {tx, ty};
}

point2d
spline::gradient(float p)
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

  float tx = 0.5f * (mPoints[p0].x * q0 + mPoints[p1].x * q1 + mPoints[p2].x * q2 + mPoints[p3].x * q3);
  float ty = 0.5f * (mPoints[p0].y * q0 + mPoints[p1].y * q1 + mPoints[p2].y * q2 + mPoints[p3].y * q3);

  return {tx, ty};
}

