#pragma once

#include "color_theory/color.hh"

namespace flp::ColorTheory {

// Common, gamma-encoded "RGB" (IEC 61966-2-1)
// Not identical to LinearRGB, like one might assume

template<typename Type>
using sRGB = Color<Type, RedComponent, GreenComponent, BlueComponent>;

template<typename Type>
using SRGB = sRGB<Type>;

} // namespace flp::ColorTheory
