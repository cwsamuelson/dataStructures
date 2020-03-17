#ifndef GALACTICSTRUCTURES_SPLINE_HH
#define GALACTICSTRUCTURES_SPLINE_HH

#include <vector>
#include <polynomial.hh>

namespace gsw {

struct point2d {
  float x;
  float y;
};

/** Catmull-Rom
 * maybe take a polynomial as an argument?
 */
//!@todo: looping?
class spline {
private:
  std::vector<point2d> mPoints;
  gsw::polynomial mPoly0;
  gsw::polynomial mPoly1;
  gsw::polynomial mPoly2;
  gsw::polynomial mPoly3;

public:
  spline();

  [[nodiscard]]
  point2d operator()(float p);

  [[nodiscard]]
  point2d gradient(float p);
};

}

#endif //GALACTICSTRUCTURES_SPLINE_HH
