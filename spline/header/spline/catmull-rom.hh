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

  CatmullRom(Container&& container, value_type alpha, const Ending closing = Ending::Default)
    : points(std::move(container)) {
    VERIFY(points.size() >= 4, "Catmull-Rom spline requires at least 4 points ({} given)", points.size());
    VERIFY(alpha >= 0 and alpha <= 1, "Catmull-Rom parameterization alpha must be [0, 1]");

    // shift and rotate to make a closed loop easier

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

    // parameters are ordered, per how they're set -> upper_bound will produce a valid result
    const auto iterator = std::upper_bound(parameters.begin(), parameters.end(), parameter);
    // *iterator > parameter;
    // Our objective is index: parameters[index] <= parameter < parameters[index + 1]
    const auto index = std::distance(parameters.begin(), iterator - 1);

    // now use Barry-Goldman pyramidial algorithm
    // Start with 4 points -> P0  P1  P2  P3
    // Blend those         ->   A0  A1  A2
    // Blend again         ->     B0  B1
    // Blend those into    ->       C
    //   the final result
    // blend(P0, P1) -> A0
    //     blend(P1, P2) -> A1
    //         blend(P2, P3) -> A2
    // blend(A0, A1) -> B0
    //     blend(A1, A2) -> B1
    // blend(B0, B1) -> C
    // -> C

    // get indices
    const auto i0 = index - 1;
    const auto i1 = index + 0;
    const auto i2 = index + 1;
    // account for wrapping
    const auto i3 = index + 2 == parameters.size() ? 0 : index + 2;

    // get points
    const Point P0 = points[i0];
    const Point P1 = points[i1];
    const Point P2 = points[i2];
    const Point P3 = points[i3];

    // get 'parameters' for those points
    const value_type p0 = parameters[i0];
    const value_type p1 = parameters[i1];
    const value_type p2 = parameters[i2];
    const value_type p3 = parameters[i3];

    // get actual scale parameters
    const value_type s0s = p0 - parameter;
    const value_type s1s = p1 - parameter;
    const value_type s2s = p2 - parameter;
    const value_type s3s = p3 - parameter;

    const auto blend = [&](
      const auto& P0, const auto& P1,
      const auto& p0, const auto& p1,
      const auto& ds0, const auto& ds1
    ) {
      Point P;
      const value_type inverse = 1 / (p1 - p0);
      for (size_t axis{}; axis < P0.size(); ++axis) {
        P[axis] = inverse * (ds1 * P0[axis] - ds0 * P1[axis]);
      }
      return P;
    };

    const Point A0 = blend(P0, P1, p0, p1, s0s, s1s);
    const Point A1 = blend(P1, P2, p1, p2, s1s, s2s);
    const Point A2 = blend(P2, P3, p2, p3, s2s, s3s);

    const Point B0 = blend(A0, A1, p0, p2, s0s, s2s);
    const Point B1 = blend(A2, A1, p1, p3, s1s, s3s);

    return blend(B0, B1, p1, p2, s1s, s2s);
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

template<RandomAccessContainer Container, typename ...Args>
CatmullRom(Container&&, Args&& ...) -> CatmullRom<typename Container::value_type, Container>;

template<typename Point, RandomAccessContainer Container = std::vector<Point>>
struct UniformCatmullRom : CatmullRom<Point, Container> {
  using Base = CatmullRom<Point, Container>;

  UniformCatmullRom(Container&& container, const Base::Ending closing = Base::Ending::Default)
    : Base(std::forward<Container>(container), 0, closing)
  {}
};

template<typename Point, RandomAccessContainer Container = std::vector<Point>>
struct CentripetalCatmullRom : CatmullRom<Point, Container> {
  using Base = CatmullRom<Point, Container>;

  CentripetalCatmullRom(Container&& container, const Base::Ending closing = Base::Ending::Default)
    : Base(std::forward<Container>(container), 0.5, closing)
  {}
};

template<typename Point, RandomAccessContainer Container = std::vector<Point>>
struct ChordalCatmullRom : CatmullRom<Point, Container> {
  using Base = CatmullRom<Point, Container>;

  ChordalCatmullRom(Container&& container, const Base::Ending closing = Base::Ending::Default)
    : Base(std::forward<Container>(container), 1, closing)
  {}
};

} // namespace flp
