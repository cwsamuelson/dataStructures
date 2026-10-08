#pragma once

#include "color_theory/color.hh"

namespace flp::ColorTheory {

// CIE 1931 XYZ tristimulus values
// D65 white point (Xn=0.95047, Yn=1.0, Zn=1.08883).
// Device-independent
// This is effectively the 'canonical' color space, and is typically used to define other color spaces.
// Therefore it is the 'hub' or central space ultimately leveraged to convert color spaces between each other.

MakeComponent(X, x);
MakeComponent(Y, y);
MakeComponent(Z, z);

template<typename Type>
using XYZ = Color<Type, XComponent, YComponent, ZComponent>;

} // namespace flp::ColorTheory
