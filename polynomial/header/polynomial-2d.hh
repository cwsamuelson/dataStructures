#pragma once

#include <cmath>
#include <format>
#include <initializer_list>
#include <ranges>
#include <string>
#include <set>
#include <vector>

namespace flp {

template<typename Type>
struct Polynomial2D {
  Polynomial2D() = default;

  // Conceptual for now
  // Polynomial2D(XCoordinate);
  // Polynomial2D(YCoordinate);

  Polynomial2D(const Type& value) {
    coefficients.push_back(value);
  }

  template<typename Iterator>
  Polynomial2D(Iterator first, Iterator last)
    : coefficients(first, last)
  {}

  Polynomial2D(std::initializer_list<Type> coeffs)
    : coefficients(coeffs.begin(), coeffs.end())
  {}

  Polynomial2D(const Polynomial2D&)     = default;
  Polynomial2D(Polynomial2D&&) noexcept = default;

  Polynomial2D& operator=(const Polynomial2D&)     = default;
  Polynomial2D& operator=(Polynomial2D&&) noexcept = default;

  ~Polynomial2D() = default;

  [[nodiscard]]
  friend auto operator<=>(const Polynomial2D&, const Polynomial2D&) noexcept = default;

  [[nodiscard]]
  friend bool operator==(const Polynomial2D&, const Polynomial2D&) noexcept = default;

  Polynomial2D& operator+() noexcept {
    return *this;
  }

  [[nodiscard]]
  Polynomial2D operator-() const noexcept {
    auto result = *this;

    for (auto& coefficient : result.coefficients) {
      coefficient = -coefficient;
    }

    return result;
  }

  Polynomial2D& operator+=(const Polynomial2D& other) {
    for (auto&& [a, b] : std::views::zip(coefficients, other.coefficients)) {
      a += b;
    }

    return *this;
  }

  Polynomial2D& operator-=(const Polynomial2D& other) {
    for (auto&& [a, b] : std::views::zip(coefficients, other.coefficients)) {
      a -= b;
    }

    return *this;
  }

  Polynomial2D& operator*=(const Polynomial2D& other) {
    std::vector<Type> vec(coefficients.size() + other.coefficients.size() - 1);

    for(unsigned int i = 0; i < coefficients.size(); ++i) {
      for(unsigned int j = 0; j < other.coefficients.size(); ++j) {
        vec[i + j] += coefficients.at(i) * other.coefficients.at(j);
      }
    }

    coefficients = move(vec);

    return *this;
  }

  Polynomial2D& operator/=(const Polynomial2D& other) {
    std::vector<Type> quotient(coefficients.size() + other.coefficients.size() - 1);
    auto remainder = *this;

    // perform long division
    while(remainder.order() > 0) {
      auto term_order = remainder.order() - other.order();
      double term_value = (quotient.at(term_order) = remainder.coefficients.back() / other.coefficients.back());
      std::vector<Type> term_vec(term_order);
      term_vec.push_back(term_value);
      Polynomial2D term(term_vec.begin(), term_vec.end());
      remainder -= term * other;
    }

    coefficients = move(quotient);

    return *this;
  }

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, const size_t index) {
    self.expand(index);
    return self.coefficients.at(index);
  }

  [[nodiscard]]
  auto evaluate(const Type& input) const noexcept {
    auto value = coefficients.back();

    //for (const auto& coefficient : coefficients | std::views::reverse | std::views::drop(1)) {
    //  value *= input;
    //  value += coefficient;
    //}

    for (signed long long i = coefficients.size() - 2; i >= 0; --i) {
      value *= input;
      value += coefficients.at(i);
    }

    return value;
  }

  [[nodiscard]]
  auto operator()(const Type& input) const noexcept {
    return evaluate(input);
  }

  [[nodiscard]]
  std::set<Type> solve() const {
    return solve(1.f, {6});
  }

  [[nodiscard]]
  std::set<Type> solve(Type hint) const {
    return solve(std::move(hint), 6);
  }

  [[nodiscard]]
  std::set<Type> solve(const unsigned int iterations) const {
    return solve(1.f, iterations);
  }

  [[nodiscard]]
  std::set<Type> solve(Type root, const unsigned int iterations) const noexcept {
    if (coefficients.size() == 0 or coefficients.size() == 1) {
      return {};
    }

    if (order() == 2) {
      return quad_solve();
    }

    std::set<Type> roots;

    auto intermediate = *this;

    // use Newton's method to approximate roots.
    // I believe in practice 6 iterations is considered fully sufficient

    for (size_t i{}; i < coefficients.size(); ++i) {
      auto derivative = intermediate.derive();

      // Apply newton approximation
      for (size_t j{}; j < iterations; ++j) {
        root = root - (intermediate(root) / derivative(root));
      }

      roots.insert(root);

      // divide out the found root
      intermediate /= Polynomial2D({ -root, 1 });
    }

    return roots;
  }

  //[[nodiscard]]
  //std::set<Polynomial2D> factor() const noexcept {
  //}

  [[nodiscard]]
  std::set<Type> quad_solve() const noexcept {
    // Apply quadratic formula to find the roots
    //const auto [x1, x2] = (-b +- sqrt(b^2 - 4ac)) / 2a;
    const auto& a = coefficients.at(2);
    const auto& b = coefficients.at(1);
    const auto& c = coefficients.at(0);

    const auto b24ac = std::sqrt((b * b) - (4.f * a * c));
    const auto denom = 2.f * a;

    const auto x1 = (-b + b24ac) / denom;
    const auto x2 = (-b - b24ac) / denom;

    return {x1, x2};
  }

  [[nodiscard]]
  size_t order() const {
    reduce();

    if (coefficients.empty()) {
      return 0;
    }

    return coefficients.size() - 1;
  }

  [[nodiscard]]
  Polynomial2D derive() const {
    std::vector<Type> coeffs;

    for (const auto& [i, coefficient] : coefficients | std::views::enumerate | std::views::drop(1)) {
      coeffs.push_back(coefficient * i);
    }

    return { coeffs.begin(), coeffs.end() };
  }

  [[nodiscard]]
  Polynomial2D antiderive() const {
    Polynomial2D result;

    result.coefficients.push_back(0);

    for (size_t i{}; i < coefficients.size(); ++i) {
      result.coefficients.push_back(coefficients.at(i) / (i + 1));
    }

    return result;
  }

  [[nodiscard]]
  auto integrate(const Type upper_bound, const Type lower_bound) const {
    const auto anti = antiderive();

    return anti(upper_bound) - anti(lower_bound);
  }

  [[nodiscard]]
  friend
  Polynomial2D operator+(const Polynomial2D& lhs, const Polynomial2D& rhs) noexcept {
    auto result = lhs;

    result += rhs;

    return result;
  }

  [[nodiscard]]
  friend
  Polynomial2D operator-(const Polynomial2D& lhs, const Polynomial2D& rhs) noexcept {
    auto result = lhs;

    result -= rhs;

    return result;
  }

  [[nodiscard]]
  friend
  Polynomial2D operator*(const Polynomial2D& lhs, const Polynomial2D& rhs) noexcept {
    auto result = lhs;

    result *= rhs;

    return result;
  }

  [[nodiscard]]
  friend
  Polynomial2D operator/(const Polynomial2D& lhs, const Polynomial2D& rhs) noexcept {
    auto result = lhs;

    result /= rhs;

    return result;
  }

  // [[nodiscard]]
  // friend
  // auto operator<=>(const Polynomial2d&, const Coordinate2D&) noexcept;

private:
  void reduce() const {
    while (not coefficients.empty() and coefficients.back() == 0) {
      coefficients.pop_back();
    }
  }

  void expand(const size_t index) const {
    coefficients.reserve(index + 1);

    while (coefficients.size() <= index) {
      coefficients.push_back(0.f);
    }
  }

  friend std::formatter<flp::Polynomial2D<Type>>;

  // this is one of the few, rare cases I find `mutable` to be acceptable.
  // There are 2 operations that may modify the coefficients vector without
  // violating logical `const`-ness.  That is `reduce`, and `expand`.  These
  // operations remove null coefficients and inserts null coefficients, which
  // has no observable effect on the polynomial results.
  // These operations exist primarily for convenience when doing other operations.
  mutable
  std::vector<Type> coefficients;
};

}

template<typename Type>
struct std::formatter<flp::Polynomial2D<Type>>
  : std::formatter<std::string_view> {
  constexpr
  auto format(const flp::Polynomial2D<Type>& polynomial, std::format_context& context) const {
    if (polynomial.coefficients.empty()) {
      return std::format_to(context.out(), "0");
    }

    const auto t = polynomial.coefficients
      | std::views::enumerate
      | std::views::drop(1)
      | std::views::transform([](const auto& pair) {
          auto&& [power, coefficient] = pair;
          return std::format("({}X^{})", coefficient, power);
        }
      )
      | std::views::reverse;

    const auto u = 
    std::views::concat(
      t,
      std::views::single(std::to_string(polynomial.coefficients.front()))
    );

    const auto v = u
      | std::views::join_with('+')
      | std::ranges::to<std::string>();

    return std::formatter<std::string_view>::format(v, context);
  }
};

//template<typename Type>
//struct std::formatter<flp::Polynomial2D<Type>>
//  : std::formatter<std::string_view> {
//  // constexpr
//  // auto parse(std::format_parse_context& context) {
//  //   auto iterator = context.begin();
//  //   while (iterator != context.end() and *iterator != '}') {
//  //     ++iterator;
//  //   }
//
//  //   if (iterator == context.end() or *iterator != '}') {
//  //     throw std::format_error("invalid format");
//  //   }
//
//  //   return iterator;
//  // }
//
//  constexpr
//  auto format(const flp::Polynomial2D<Type>& polynomial, std::format_context& context) const {
//    std::optional<Type> front;
//
//    if (not polynomial.empty()) {
//      front = polynomial.front();
//    }
//
//    const auto a =
//        polynomial.coefficients
//      | std::views::enumerate
//      | std::views::drop(1)
//      | std::views::transform([](const auto& pair) {
//          auto&& [power, coefficient] = pair;
//          return std::format("({}X^{})", coefficient, power);
//        }
//      )
//      | std::views::reverse;
//
//    const auto b = std::views::concat(
//      a,
//      std::views::single(std::to_string(polynomial.coefficients.front()))
//    );
//
//    const auto poly_str = b
//      | std::views::join_with('+')
//      | std::ranges::to<std::string>();
//
//    return std::formatter<std::string_view>::format(poly_str, context);
//
//    // ----
//
//    // const auto poly_str =
//    //   polynomial.coefficients
//    // | std::views::enumerate
//    // | std::views::drop(1)
//    // | std::views::transform([](const auto& pair) -> std::string {
//    //     auto&& [power, coefficient] = pair;
//    //     return std::format("({}X^{})", coefficient, power);
//    //   }
//    // )
//    // | std::views::reverse
//    // | std::views::concat(
//    //   //std::views::single(std::format("{}", polynomial.coefficients.front()))
//    //   std::format("{}", polynomial.coefficients.front())
//    // )
//    // | std::views::join_with('+');
//
//    // return std::formatter<std::string_view>::format(poly_str, context);
//
//    // ----
//
//    // auto iter = context.out();
//
//    // for (const auto& [power, coefficient]
//    //   : std::views::enumerate(polynomial.coefficients)
//    //   | std::views::drop(1)
//    //   | std::views::reverse) {
//    //   iter = std::format_to(iter, "({}^{})", coefficient, power);
//    // }
//
//    // return std::format_to(iter, "{}", polynomial.coefficients.front());
//
//    // ----
//
//    // if (polynomial.order() == 0 and polynomial.coefficients.empty()) {
//    //   return std::format_to(context.out(), "0");
//    // }
//
//    // std::string poly_str;
//
//    // for (size_t power{}; const auto& coefficient : polynomial.coefficients) {
//    //   std::string term;
//    //   if (power == 0) {
//    //     std::format_to(std::back_inserter(term), "{}", coefficient);
//    //   } else {
//    //     std::format_to(std::back_inserter(term), "({}^{})", coefficient, power);
//    //   }
//
//    //   std::format_to(std::back_inserter(poly_str), "{} + {}", term, poly_str);
//
//    //   ++power;
//    // }
//
//    // //return std::format_to(context.out(), poly_str.c_str());
//    // return std::formatter<std::string_view>::format(poly_str, context);
//  }
//};

template<typename OStream, typename Type>
OStream& operator<<(OStream& ostream, const flp::Polynomial2D<Type>& polynomial) {
  return ostream << std::format("{}", polynomial);
}
// 
// operand types are
// std::ranges::reverse_view<
//   std::ranges::transform_view<
//     std::ranges::drop_view<
//       std::ranges::enumerate_view<
//         std::ranges::ref_view<
//           std::vector<float, std::allocator<float>>
//         >
//       >
//     >,
//     std::formatter<flp::Polynomial2D<float>, char>
//     ::format(const flp::Polynomial2D<float>&, std::format_context&) const
//       ::<lambda(const auto:63&)>
//   >
// >
// and
// std::ranges::single_view<std::__cxx11::basic_string<char> >
// 
