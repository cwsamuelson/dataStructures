#pragma once

#include <color_theory/color.hh>

namespace flp::ColorTheory {

MakeComponent(Value, value, v, brightness, b);

template<typename Type>
using HSV = Color<Type, HueComponent, SaturationComponent, ValueComponent>;

} // namespace flp::ColorTheory
