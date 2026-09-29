#pragma once

#include <color_theory/cmyk/cmyk.hh>
#include <color_theory/convert.hh>
#include <color_theory/srgb/srgb.hh>

#include <algorithm>

namespace flp::ColorTheory {

// Naive K=1-max(r,g,b) subtractive model (see the caveat in `cmyk.hh`).
template<std::floating_point Type>
struct ConversionEdge<CMYK<Type>> {
  using Parent = SRGB<Type>;

  static constexpr Parent to_parent(CMYK<Type> value) noexcept {
    const Type c = Type(value.cyan);
    const Type m = Type(value.magenta);
    const Type y = Type(value.yellow);
    const Type k = Type(value.key);

    const Type inv_k = Type(1) - k;
    return Parent{
      typename Parent::Red  ((Type(1) - c) * inv_k),
      typename Parent::Green((Type(1) - m) * inv_k),
      typename Parent::Blue ((Type(1) - y) * inv_k),
    };
  }

  static constexpr CMYK<Type> from_parent(Parent value) noexcept {
    const Type r = Type(value.red);
    const Type g = Type(value.green);
    const Type b = Type(value.blue);

    const Type k = Type(1) - std::max({r, g, b});
    const Type inv_k = Type(1) - k;

    using Result = CMYK<Type>;
    if (inv_k <= Type(0)) {
      // pure black: cyan/magenta/yellow are conventionally 0 rather than
      // divide-by-zero indeterminate.
      return Result{
        typename Result::Cyan(Type(0)),
        typename Result::Magenta(Type(0)),
        typename Result::Yellow(Type(0)),
        typename Result::Key(k),
      };
    }

    return Result{
      typename Result::Cyan(   (Type(1) - r - k) / inv_k),
      typename Result::Magenta((Type(1) - g - k) / inv_k),
      typename Result::Yellow( (Type(1) - b - k) / inv_k),
      typename Result::Key(k),
    };
  }
};

} // namespace flp::ColorTheory
