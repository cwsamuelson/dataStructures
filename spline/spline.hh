//
// Created by chris on 9/1/2019.
//

#ifndef GALACTICSTRUCTURES_SPLINE_HH
#define GALACTICSTRUCTURES_SPLINE_HH

#include <vector>
#include <initializer_list>

#include "polynomial.hh"

namespace gsw {

struct point2d{
  float x;
  float y;

  bool
  operator==(const point2d& rhs)const
  {
    return (x == rhs.x) && (y == rhs.y);
  }
};

/*! Catmull-Rom
 * maybe take polynomials as an argument?
 * @todo: looping?
 * floats are used because we don't care about the precision of a double, and floats will be faster/smaller
 * splines basically require at least 3 points to be meaningful; does this need to be enforced? or just documented
 */
class spline
{
private:
  gsw::polynomial mPoly0;
  gsw::polynomial mPoly1;
  gsw::polynomial mPoly2;
  gsw::polynomial mPoly3;

  std::vector<point2d> mPoints;

public:
  spline()
    : spline{{}}
  {}

  spline(std::initializer_list<point2d> il);

  point2d
  operator()(float p) const
  {
    return point(p);
  }

  point2d
  point(float p) const;

  point2d
  gradient(float p) const;

  float
  segmentLength(float p, float stepSize = 0.005f) const;
};

}

#endif //GALACTICSTRUCTURES_SPLINE_HH
