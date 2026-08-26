#pragma once

#include <error_help.hh>

#include <cmath>
#include <vector>

// https://www.cs.cmu.edu/~fp/courses/graphics/asst5/catmullRom.pdf
// https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
// https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull%E2%80%93Rom_spline

namespace flp::Spline {

template<typename Type>
concept Container = requires(Type container) {
  // value_type?
  // ADL this?.. =/
  // using std::begin;
  // using std::end;
  std::begin(container);
  std::end(container);
};

template<typename Type>
concept RandomAccessContainer = Container<Type> and requires(Type container, size_t index) {
  container[index]/*->std::convertible_to<Type::value_type>*/;
};

template<typename Point, RandomAccessContainer Container = std::vector<Point>>
struct CatmullRom {
  using value_type = Point::value_type;
  // using value_type = ContainerTraits<Point>::value_type;

  enum Ending {
    Closed,
    Open,

    Looped = Closed,
    Unlooped = Open,
    Straight = Open,

    Default = Open,
  };

  CatmullRom(Container&& container/*, value_type alpha*/, const Ending closing = Ending::Default)
    : points(std::move(container)) {
    const value_type alpha = (value_type)1 / (value_type)2;

    VERIFY(points.size() >= 4, "Catmull-Rom spline requires at least 4 points ({} given)", points.size());
    VERIFY(alpha >= 0 and alpha <= 1, "Catmull-Rom parameterization alpha must be [0, 1]");

    // { A, B, C, D, ..., Y, Z

    const auto num_points = points.size();
    points.resize(num_points + 3);

    // { A, B, C, D, ..., Y, Z, 0, 0, 0}

    points[num_points + 1] = points[0];
    points[num_points + 2] = points[1];

    // { A, B, C, D, ..., Y, Z, 0, A, B}

    const auto temp = points[num_points - 1];
    for (size_t i = num_points; i > 0; --i) {
      points[i] = points[i - 1];
    }
    // { A, A, B, C, D, ..., Y, Z, A, B}

    points[0] = temp;
    // { Z, A, B, C, D, ..., Y, Z, A, B}

    parameters.resize(points.size());

    parameters[0] = -alpha_distance(points[0], points[1], alpha);
    // After the 'rotation' above, p1 is the intended beginning; therefore,
    // set its parameter to '0', as a starting reference point
    parameters[1] = 0;

    for (size_t i{2}; i < parameters.size(); ++i) {
      const auto d = alpha_distance(points[i], points[i - 1], alpha);
      parameters[i] = parameters[i - 1] + d;
    }

    if (closing == Ending::Closed) {
      max_param = parameters[num_points + 1];
    } else {
      max_param = parameters[num_points];
    }
  }

  // splines are 'parameterized'.  This is that parameter.
  // idk, they're sorta reverse-parameterized or de-parameterized, but this works anyway
  Point operator()(const value_type parameter) const {
    VERIFY(parameter >= 0 and parameter <= max_param, "Catmull-Rom interpolation parameter must be [0, {}]", max_param);

    // parameters are ordered, per how they're set
    const auto iterator = std::upper_bound(parameters.begin(), parameters.end(), parameter);
    // *iterator >= parameter;
    // Our objective is index: parameters[index] <= parameter < parameters[index + 1]
    const auto index = std::distance(parameters.begin(), iterator - 1);

    // now use Barry-Goldman pyramidial algorithm

    // Start with 4 points P0, P1, P2, P3
    // use those to blend into A0, A1, A2
    // Then blend those to B0, B2
    // Finally blend these into the final C
    // P0  P1  P2  P3
    //   A0  A1  A2
    //     B0  B1
    //       C
    // blend(P0, P1) -> A0
    // blend(P1, P2) -> A1
    // blend(P2, P3) -> A2
    // blend(A0, A1) -> B0
    // blend(A1, A2) -> B1
    // blend(B0, B1) -> C
    // -> C

    const size_t index3 = parameters.size() == index + 2 ? 0 : index + 2;
    const Point P0 = points[index - 1];
    const Point P1 = points[index + 0];
    const Point P2 = points[index + 1];
    const Point P3 = points[index3];

    const value_type p0 = parameters[index - 1];
    const value_type p1 = parameters[index + 0];
    const value_type p2 = parameters[index + 1];
    const value_type p3 = parameters[index3];

    const value_type s0s = p0 - parameter;
    const value_type s1s = p1 - parameter;
    const value_type s2s = p2 - parameter;
    const value_type s3s = p3 - parameter;

    const value_type inverse_ds21 = 1 / (p2 - p1);

    const auto blendP = [&](
      const auto& P0, const auto& P1,
      const auto& p0, const auto& p1,
      const auto& ds0, const auto& ds1
    ){
      Point P;
      const value_type inverse = 1 / (p1 - p0);
      for (size_t axis{}; axis < P0.size(); ++axis) {
        P[axis] = inverse * (ds1 * P0[axis] - ds0 * P1[axis]);
      }
      return P;
    };

    const Point A0 = blendP(P0, P1, p0, p1, s0s, s1s);

    // Point A0;
    // const value_type inverse_ds10 = 1 / (P1 - P0);
    // for (size_t axis{}; axis < points.at(index).size(); ++axis) {
    //   A0[axis] = inverse_ds10 * (s1s * P0[axis] - s0s * P1[axis]);
    // }

    const Point A1 = blendP(P1, P2, p1, p2, s2s, s1s);

    // Point A1;
    // for (size_t axis{}; axis < points.at(index).size(); ++axis) {
    //   A1[axis] = inverse_ds21 * (s2s * P1[axis] - s1s * P2[axis]);
    // }

    const Point A2 = blendP(P2, P3, p2, p3, s2s, s3s);

    // Point A2;
    // const value_type inverse_ds32 = 1 / (P3 - P2);
    // for (size_t axis{}; axis < points.at(index).size(); ++axis) {
    //   A2[axis] = inverse_ds32 * (s3s * P2[axis] - s2s * P3[axis]);
    // }

    Point B0;
    const value_type inverse_ds20 = 1 / (p2 - p0);
    for (size_t axis{}; axis < points.at(index).size(); ++axis) {
      B0[axis] = inverse_ds20 * (s2s * A0[axis] - s0s * A1[axis]);
    }

    Point B1;
    const value_type inverse_ds31 = 1 / (p3 - p1);
    for (size_t axis{}; axis < points.at(index).size(); ++axis) {
      B1[axis] = inverse_ds31 * (s3s * A1[axis] - s1s * A2[axis]);
    }

    Point C;
    for (size_t axis{}; axis < points.at(index).size(); ++axis) {
      C[axis] = inverse_ds21 * (s2s * B0[axis] - s1s * B1[axis]);
    }

    return C;
  }

  value_type parameter(const size_t index) const {
    return parameters.at(index + 1);
  }

  value_type max_parameter() const {
    return max_param;
  }

private:
  static value_type alpha_distance(const Point& p0, const Point& p1, const value_type alpha) {
    // boost uses ADL for things like 'size', 'pow', etc; not necessary yet
    value_type dsq = 0;

    for (size_t i{}; i < p0.size(); ++i) {
      const auto dx = p0[i] - p1[i];
      dsq += dx * dx;
    }

    // sqrt
    return std::pow(dsq, alpha / 2);
  }

  Container points;
  std::vector<value_type> parameters;
  value_type max_param{};
};

template<RandomAccessContainer Container>
CatmullRom(Container&&) -> CatmullRom<typename Container::value_type, Container>;

} // namespace flp
