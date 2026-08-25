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

  CatmullRom(Container&& container/*, value_type alpha*/, Ending closing = Ending::Default)
    : points(std::move(container)) {
    const value_type alpha = (value_type)1 / (value_type)2;

    // VERIFY(points.size() < 4, "Catmull-Rom spline requires at least 4 points ({} given)", points.size());
    // VERIFY(alpha >= 0 and alpha <= 1, "Catmull-Rom parameterization alpha must be [0, 1]");

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
    // Our objective is i: parameters[i] <= parameter < parameters[i + 1]
    const auto i = std::distance(parameters.begin(), iterator - 1);

    // now do lots of math

    return {};
  }

  value_type parameter(const size_t index) const {
    return parameters.at(index);
  }

  value_type max_parameter() const {
    return max_param;
  }

private:
  static value_type alpha_distance(const Point& p0, const Point& p1, const value_type alpha) {
    // boost uses ADL for things like 'size', 'pow', etc; not necessary yet
    value_type dsq = 0;

    for (size_t i{}; i < p1.size(); ++i) {
      const auto dx = p0[i] - p1[i];
      dsq += dx * dx;
    }

    // sqrt
    return std::pow(dsq, alpha / 2);
  }

  Container points;
  std::vector<value_type> parameters;
  value_type max_param;
};

template<RandomAccessContainer Container>
CatmullRom(Container&&) -> CatmullRom<typename Container::value_type, Container>;

} // namespace flp
