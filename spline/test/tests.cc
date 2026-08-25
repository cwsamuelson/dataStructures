#include <spline/catmull-rom.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <vector>

using namespace flp;

TEST_CASE("`Spline`::Catmull-Rom") {
  using Point = std::array<double, 2>;
  const Spline::CatmullRom spline(std::vector{Point{0, 0}, Point{1, 0}, Point{2, 0}, Point{3, 0}});

  CHECK(spline.max_parameter() == 3);
  const auto p0 = spline(0);
  CHECK(p0[0] == 0.);
  CHECK(p0[1] == 0.);
  const auto p1 = spline(1);
  CHECK(p1[0] == 1.);
  CHECK(p1[1] == 0.);
  const auto p2 = spline(2);
  CHECK(p2[0] == 2.);
  CHECK(p2[1] == 0.);
  const auto p3 = spline(3);
  CHECK(p3[0] == 3.);
  CHECK(p3[1] == 0.);

  const auto s0 = spline.parameter(0);
  CHECK(s0 == 0.);
  const auto s1 = spline.parameter(1);
  CHECK(s1 == 0.);
  const auto s2 = spline.parameter(2);
  CHECK(s2 == 0.);
  const auto s3 = spline.parameter(3);
  CHECK(s3 == 0.);

  for (double s{1}; s < 2; s += 0.01) {
    const auto point = spline(s);
    CHECK(point[0] == s);
    CHECK(point[1] == 0);
  }
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

/*auto de_boor(int k, int x, const std::vector<Point>& t, const std::vector<Point>& c, int p) {
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
}*/

TEST_CASE("`Spline`::sandbox") {
}
