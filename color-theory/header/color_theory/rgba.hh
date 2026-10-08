#pragma once

#include <color_theory/color.hh>

namespace flp::ColorTheory {

MakeComponent(Alpha, alpha, a, w);

template<typename Type>
using RGBA = RGBX<Type, RedComponent, GreenComponent, BlueComponent, AlphaComponent>;

// RGBA32 and RGBA8 are the same
// The names come from different perspectives
// 32 referring to the bits of the entire color value
// 8 referring to the bits of each component
// These are, notably, also identical to RGBA8888 and R8G8B8A8

template<typename Type, template<typename...> typename ...Components>
using RGBAX = RGBX<Type, AlphaComponent, Components...>;

using RGBA32 = RGBAX<uint8_t>;
using RGBA8 = RGBA32;
using RGBA8888 = RGBA32;
using R8G8B8A8 = RGBA32;
using RGBA32F = RGBAX<float>;

} // namespace flp::ColorTheory
