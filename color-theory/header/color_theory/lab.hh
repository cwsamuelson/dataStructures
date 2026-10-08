#pragma once

#include "color_theory/color.hh"

namespace flp::ColorTheory {

// CIE L*a*b*, D65 reference white.
// Perceptually-uniform-ish device independent space

MakeComponent(A, a);
MakeComponent(B, b);

template<typename Type>
using LAB = Color<Type, LightnessComponent, AComponent, BComponent>;

} // namespace flp::ColorTheory
