#include <spline/catmull-rom.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <vector>

#include <print>

using namespace flp;

TEST_CASE("`Spline`::Catmull-Rom") {
  using Point = std::array<double, 3>;
  const Spline::CatmullRom spline(std::vector{Point{0, 0, 0}, Point{1, 0, 0}, Point{2, 0, 0}, Point{3, 0, 0}}, 0.5);

  CHECK(spline.max_parameter() == 3);
  const auto p0 = spline(0);
  CHECK(p0[0] == 0.);
  CHECK(p0[1] == 0.);
  CHECK(p0[2] == 0.);
  const auto p1 = spline(1);
  CHECK(p1[0] == 1.);
  CHECK(p1[1] == 0.);
  CHECK(p1[2] == 0.);
  const auto p2 = spline(2);
  CHECK(p2[0] == 2.);
  CHECK(p2[1] == 0.);
  CHECK(p2[2] == 0.);
  const auto p3 = spline(3);
  CHECK(p3[0] == 3.);
  CHECK(p3[1] == 0.);
  CHECK(p3[2] == 0.);

  CHECK_THAT(
    spline.parameter(0),
    Catch::Matchers::WithinRel(0., 0.001)
  );
  CHECK_THAT(
    spline.parameter(1),
    Catch::Matchers::WithinRel(1., 0.001)
  );
  CHECK_THAT(
    spline.parameter(2),
    Catch::Matchers::WithinRel(2., 0.001)
  );
  CHECK_THAT(
    spline.parameter(3),
    Catch::Matchers::WithinRel(3., 0.001)
  );

  for (double s{1}; s < 2; s += 0.01) {
    const auto point = spline(s);
    CHECK_THAT(
      point[0],
      Catch::Matchers::WithinRel(s, 0.01)
    );
    CHECK_THAT(
      point[1],
      Catch::Matchers::WithinRel(0., 0.001)
    );
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
