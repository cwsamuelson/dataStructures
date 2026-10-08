#pragma once

#include <color_theory/color.hh>

namespace flp::ColorTheory {

MakeComponent(Intensity, intensity, i);

template<typename Type>
using HSI = Color<Type, HueComponent, SaturationComponent, IntensityComponent>;

} // namespace flp::ColorTheory
