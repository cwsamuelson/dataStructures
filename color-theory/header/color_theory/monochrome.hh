#pragma once

#include "color_theory/color.hh"

namespace flp::ColorTheory {

MakeComponent(Gray, gray, grey, g, value, shade);

template<typename ...Args>
using Grey = Gray<Args...>;

template<typename Type>
using Monochrome = Color<Type, GrayComponent>;

}
