#pragma once

#include "color_theory/color.hh"

namespace flp::ColorTheory {

// Cyan/Magenta/Yellow/Key(black), naive subtractive model off `SRGB`.
//!@NOTE a real CMYK model is specific to the printer/ink in use.
// This means there's no 'canonical' CMYK color-space.
// This uses a typical K=1-max(r,g,b) approximation.
// Don't use for 'real' CMYK/inking use
//!@TODO make conversion parameterizable

MakeComponent(Cyan,    cyan, c);
MakeComponent(Magenta, magenta, m);
MakeComponent(Yellow,  yellow, y);
MakeComponent(Key,     key, k);

template<typename Type>
using CMYK = Color<Type, CyanComponent, MagentaComponent, YellowComponent, KeyComponent>;

} // namespace flp::ColorTheory
