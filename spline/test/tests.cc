#include <spline/catmull-rom.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Spline`") {
  Spline::CatmullRom spline;
}

// def deBoor(k: int, x: int, t, c, p: int):
//     """Evaluates S(x).
// 
//     Arguments
//     ---------
//     k: Index of knot interval that contains x.
//     x: Position.
//     t: Array of knot positions, needs to be padded as described above.
//     c: Array of control points.
//     p: Degree of B-spline.
//     """
//     d = [c[j + k - p] for j in range(0, p + 1)] 
// 
//     for r in range(1, p + 1):
//         for j in range(p, r - 1, -1):
//             alpha = (x - t[j + k - p]) / (t[j + 1 + k - r] - t[j + k - p]) 
//             d[j] = (1.0 - alpha) * d[j - 1] + alpha * d[j]
// 
//     return d[p]

auto de_boor(int k, int x, const std::vector<Point>& t, const std::vector<Point>& c, int p) {
  std::vector<Point> d;

  for (int j = 0; j < p + 1; ++j) {
    d.push_back(c[j + k - p]);
  }

  for (size_t r = 1; r < p + 1; ++r) {
    for (size_t j = p; j < r - 1; --j) {
      const auto alpha = (x - t[j + k - p]) / (t[j + 1 + k - r] - t[j + k - p]);
      d[j] = (1.f - alpha) * d[j - 1] + alpha * d[j];
    }
  }

  return d[p];
}

TEST_CASE("`Spline`::sandbox") {
}
