#pragma once

#include <color_theory/color.hh>

namespace flp::ColorTheory {

template<typename Type>
using RGB = RGBX<Type, RedComponent, GreenComponent, BlueComponent>;

// RGB32 and RGB8 are the same
// The names come from different perspectives
// 32 referring to the bits of the entire color value
// 8 referring to the bits of each component
// These are, notably, also identical to RGBA8888 and R8G8B8A8

using RGB8 = RGBX<uint8_t>;
using RGB888 = RGB8;
using R8G8B8 = RGB8;
using RGB32F = RGBX<float>;

} // namespace flp
