#pragma once

#include <bit>
#include <compare>
#include <cstdint>
#include <limits>

namespace flp {

#define X0(macro, ...)
#define X1(macro, A, ...) macro(A) X0(macro, __VA_ARGS__)
#define X2(macro, A, ...) macro(A) X1(macro, __VA_ARGS__)
#define X3(macro, A, ...) macro(A) X2(macro, __VA_ARGS__)
#define X4(macro, A, ...) macro(A) X3(macro, __VA_ARGS__)
#define X5(macro, A, ...) macro(A) X4(macro, __VA_ARGS__)
#define X6(macro, A, ...) macro(A) X5(macro, __VA_ARGS__)
#define X7(macro, A, ...) macro(A) X6(macro, __VA_ARGS__)
#define X8(macro, A, ...) macro(A) X7(macro, __VA_ARGS__)
#define X9(macro, A, ...) macro(A) X8(macro, __VA_ARGS__)

#define GET_MACRO(A, B, C, D, E, F, G, H, I, J, ...) J

#define FOR_EACH(macro, ...) \
  GET_MACRO(__VA_ARGS__, X9, X8, X7, X6, X5, X4, X3, x2, X1, X0)(macro, __VA_ARGS__)

template<typename Type>
struct Component {
  constexpr
  Component() = default;

  constexpr
  Component(const Type val)
    : value(val)
  {}

  Type value{};
};

#define MakeComponentName(N) \
  auto& N() noexcept { \
    return Base::value; \
  } \
   \
  auto& N() const noexcept { \
    return Base::value; \
  }

#define MakeComponent(N, ...) \
template<typename Type> \
struct N ## Component : Component<Type> { \
  using Base = Component<Type>; \
 \
  FOR_EACH(MakeComponentName, __VA_ARGS__) \
}; \
static_assert(sizeof(N ## Component<float>) == sizeof(float)); \
static_assert(sizeof(N ## Component<int>) == sizeof(int))

MakeComponent(Red,   Red,   red,   R, r, x);
MakeComponent(Green, Green, green, G, g, y);
MakeComponent(Blue,  Blue,  blue,  B, b, z);
MakeComponent(Alpha, Alpha, alpha, A, a, w);
MakeComponent(Hue, Hue, hue, H, h);
MakeComponent(Saturation, Saturation, saturation, S, s);
MakeComponent(Value, Value, value, V, v, Brightness, brightness, B, b);
MakeComponent(Lightness, Lightness, lightness, L, l);
MakeComponent(Intensity, Intensity, intensity, I, i);

template<typename Type, template<typename...> typename ...Components>
struct Color : Components<Type>... {
  constexpr
  Color() = default;

  // accept normalized floating point values
  template<std::floating_point ...FTypes>
  constexpr
  Color(const FTypes& ...values)
    requires (sizeof...(FTypes) == sizeof...(Components))
    : Components<Type>(static_cast<Type>(values * std::numeric_limits<Type>::max()))...
  {}

  // accept integral types not matching `Type`
  template<std::integral ...ITypes>
  constexpr
  Color(const ITypes& ...values)
    requires ((sizeof...(ITypes) == sizeof...(Components)) and ((not std::same_as<ITypes, Type>) and ...))
    : Components<Type>(static_cast<Type>(values))...
  {}

  // accept values to match to each component
  template<std::same_as<Type> ...Types>
    requires (sizeof...(Types) == sizeof...(Components))
  constexpr
  Color(const Types& ...values)
    : Components<Type>(values)...
  {}

  template<typename OType>
    requires (sizeof(OType) == sizeof(Color))
  constexpr
  Color(const OType& packed) {
    *this = std::bit_cast<Color>(packed);
  }

  // color format interchange
  template<template<typename...> typename ...OComponents>
  constexpr
  Color(const Color<Type, OComponents...>& other) {
    auto try_assign = [this] (auto& ocomp) {
      using Other = std::remove_cvref_t<decltype(ocomp)>;

      static_cast<Other&>(*this).value = static_cast<const Other&>(ocomp).value;
    };

    (try_assign(static_cast<const Components<Type>&>(other)), ...);
  }

  template<typename Packed>
    requires (sizeof(Packed) == sizeof(Color))
  constexpr
  Packed value() const noexcept {
    return std::bit_cast<Packed>(*this);
  }

  template<typename Packed>
    requires (sizeof(Packed) == sizeof(Color))
  constexpr
  void value(const Packed& packed) noexcept {
    *this = std::bit_cast<Color>(packed);
  }
};

template<typename Type, template<typename...> typename ...Components>
using RX = Color<Type, RedComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using GX = Color<Type, GreenComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using BX = Color<Type, BlueComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using RGX = RX<Type, GreenComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using BGX = BX<Type, GreenComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using RGBX = Color<Type, RedComponent, GreenComponent, BlueComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using RGBAX = RGBX<Type, AlphaComponent, Components...>;

using RGBA32 = RGBAX<uint8_t>;
using RGBA8 = RGBA32;
using RGBA8888 = RGBA32;
using R8G8B8A8 = RGBA32;
using RGBA32F = RGBAX<float>;

using RGB8 = RGBX<uint8_t>;
using RGB888 = RGB8;
using R8G8B8 = RGB8;
using RGB32F = RGBX<float>;

template<typename Type>
using HSL = Color<Type, HueComponent, SaturationComponent, ValueComponent>;

template<typename Type>
using HSV = Color<Type, HueComponent, SaturationComponent, LightnessComponent>;

template<typename Type>
using HSI = Color<Type, HueComponent, SaturationComponent, IntensityComponent>;

}
