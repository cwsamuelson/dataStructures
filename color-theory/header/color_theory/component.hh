#pragma once

namespace flp::ColorTheory {

#define X0(macro, ...)
#define X1(macro, A, ...) macro(A) X0(macro, __VA_ARGS__)
#define X2(macro, A, ...) macro(A) X1(macro, __VA_ARGS__)
#define X3(macro, A, ...) macro(A) X2(macro, __VA_ARGS__)
#define X4(macro, A, ...) macro(A) X3(macro, __VA_ARGS__)
#define X5(macro, A, ...) macro(A) X3(macro, __VA_ARGS__)
#define X6(macro, A, ...) macro(A) X3(macro, __VA_ARGS__)
#define X7(macro, A, ...) macro(A) X3(macro, __VA_ARGS__)
#define X8(macro, A, ...) macro(A) X3(macro, __VA_ARGS__)
#define X9(macro, A, ...) macro(A) X3(macro, __VA_ARGS__)

#define GET_MACRO(A, B, C, D, E, F, G, H, I, J, ...) J

#define FOR_EACH(macro, ...) \
  GET_MACRO(__VA_ARGS__, X9, X8, X7, X6, X5, X4, X3, X2, X1, X0)(macro, __VA_ARGS__)

template<typename Type>
struct Component {
  constexpr
  Component() = default;

  constexpr
  Component(const Type val)
    : value_(val)
  {}

  explicit
  constexpr
  operator Type() {
    return value_;
  }

  Type value_{};

  friend
  constexpr
  bool operator==(const Component&, const Component&) noexcept = default;

  friend
  constexpr
  auto operator<=>(const Component&, const Component&) noexcept = default;
};

#define MakeComponentName(N) \
  auto& N() noexcept { \
    return Base::value_; \
  } \
   \
  auto& N() const noexcept { \
    return Base::value_; \
  }

// using N = N ## Component<Type>;
#define MakeComponent(N, ...) \
template<typename Type> \
struct N ## Component : Component<Type> { \
  using Base = Component<Type>; \
 \
  using N = N ## Component; \
 \
  FOR_EACH(MakeComponentName, __VA_ARGS__) \
 \
  friend \
  constexpr \
  bool operator==(const N&, const N&) noexcept = default; \
 \
  friend \
  constexpr \
  auto operator<=>(const N&, const N&) noexcept = default; \
}; \
static_assert(sizeof(N ## Component<float>) == sizeof(float)); \
static_assert(sizeof(N ## Component<int>) == sizeof(int))

// shared components
MakeComponent(Red,   red,   r, x); // RGB, RGBA
MakeComponent(Green, green, g, y); // RGB, RGBA
MakeComponent(Blue,  blue,  b, z); // RGB, RGBA
MakeComponent(Hue, hue, h); // HSL, HSV, HSI
MakeComponent(Saturation, saturation, s); // HSL, HSV, HSI
// Luminance vs Lightness?
MakeComponent(Lightness, lightness, l); // HSL, LAB

}
