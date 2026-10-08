#pragma once

#include <color_theory/color.hh>

namespace flp::ColorTheory {

template<typename Type>
using HSL = Color<Type, HueComponent, SaturationComponent, LightnessComponent>;

} // namespace flp::ColorTheory
