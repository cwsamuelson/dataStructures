#pragma once

#include "color_theory/color.hh"

namespace flp::ColorTheory {

// Linear-light RGB
// Uses the same primaries/white point as sRGB
// Most correct space to apply color math to (sRGB must be linearized first)

MakeComponent(LinearRed,   red,   r, x);
MakeComponent(LinearGreen, green, g, y);
MakeComponent(LinearBlue,  blue,  b, z);

template<typename Type>
using LinearRGB = Color<Type, LinearRedComponent, LinearGreenComponent, LinearBlueComponent>;

} // namespace flp::ColorTheory