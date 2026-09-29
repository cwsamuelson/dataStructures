Color Theory
============
Strongly-typed color spaces, and conversion between any two of them, without
writing (or maintaining) an N² matrix of pairwise conversions.

## Color spaces
- `SRGB` - the common, gamma-encoded "RGB" (IEC 61966-2-1).
- `LinearRGB` - linear-light RGB; same primaries/white point as `SRGB`, but
  without its gamma companding. Distinct from `SRGB` because a channel value
  means something different in each, even though both are "red in [0,1]".
- `XYZ` - CIE 1931 XYZ, D65 white point. Device-independent; the root of the
  conversion tree (see below).
- `Lab` - CIE L\*a\*b\*, D65 reference white.
- `HSV` - Hue/Saturation/Value, a cylindrical re-parameterization of `SRGB`.
- `HSL` - Hue/Saturation/Lightness, another cylindrical re-parameterization
  of `SRGB`, distinct from `HSV` (same hue definition, different
  saturation/third-axis definitions).
- `CMYK` - naive `K = 1 - max(r,g,b)` subtractive model off `SRGB`. **Caveat**:
  there is no single canonical CMYK space; real CMYK is press/ink/ICC-profile
  specific. This is the standard textbook approximation used when no profile
  is available.

Every space is `template<std::floating_point Type = float> struct ...`, and
every channel is a `flp::TaggedType<Type, Tag>` with a tag unique to that
(space, channel) pair. `SRGB::Red` and `LinearRGB::Red` are different types,
as are `HSV::Hue` and `HSL::Hue` - values from one can never be silently
assigned into, or compared against, the other, even though the underlying
numeric `Type` is identical. Byte-packed / integral formats (e.g. `0-255`
`uint8_t` RGB) are intentionally out of scope for this module.

## Conversion: shortest path through a tree, not N²
Color spaces form a tree:

```
HSV ──┐
HSL ──┼─ SRGB ── LinearRGB ── XYZ ── Lab
CMYK ─┘
```

Every space except the root (`XYZ`) declares exactly one edge to its parent
via a `ConversionEdge<Space>` specialization (`Parent` type alias +
`to_parent`/`from_parent`). That's it - 2 functions per space, O(N) total.
None of this conversion code lives inside a space's own directory (`srgb/`,
`hsv/`, `xyz/`, ...); every edge lives in `conversions/`, and the generic
traversal machinery lives in its own `convert.hh`, belonging to no single
space.

`convert<To>(value)` (in `convert.hh`) walks `value` up `From`'s parent chain
one step at a time, stopping as soon as it reaches a type that is also an
ancestor of `To`, then descends straight down to `To`. This always takes the
shortest path through the tree: `SRGB -> HSV` takes their single direct edge
rather than detouring all the way up to `XYZ` and back down (which would
otherwise needlessly compound floating point error from the gamma/matrix
steps), while pairs with no direct edge - like `HSV -> Lab` or `CMYK -> HSL` -
still work through the exact same single function, automatically routing
through their lowest common ancestor (`XYZ` and `SRGB`, respectively).

```cpp
#include <color_theory/color_theory.hh>

using namespace flp::ColorTheory;

SRGB<float> orange{SRGB<float>::Red(1.f), SRGB<float>::Green(0.5f), SRGB<float>::Blue(0.f)};

auto hsv  = convert<HSV<float>>(orange);   // direct edge
auto lab  = convert<Lab<float>>(orange);   // 3 hops: SRGB -> LinearRGB -> XYZ -> Lab
auto cmyk = convert<CMYK<float>>(hsv);     // 2 hops: HSV -> SRGB -> CMYK
```

`convert()` also requires `From` and `To` to share the same underlying
numeric `Type` (a `static_assert`), so a precision change must be explicit
rather than happening silently as a side effect of a color conversion.

Adding a new color space means adding one new directory with the space's
struct, and one new file in `conversions/` declaring its single
`ConversionEdge` to whichever existing space it's most naturally defined in
terms of - `convert<To>()` automatically knows how to reach it from
everywhere else in the graph.
