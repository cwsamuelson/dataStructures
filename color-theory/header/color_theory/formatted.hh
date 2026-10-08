#pragma once

namespace flp::ColorTheory {

enum class Format {
  Mono,

  ARGB,
  RGBA,
  ABGR,
  BGRA,

  RGB,
  BGR,

  RG,
  GB,
  RB,

  R,
  G,
  B,
  A,

  Red = R,
  Green = G,
  Blue = B,
  Alpha = A,
};

using ARGB_8888 = FormattedColor<ARGB, uint8_t>;
using RGBA_8888 = FormattedColor<RGBA, uint8_t>;
using ABGR_8888 = FormattedColor<ABGR, uint8_t>;
using BGRA_8888 = FormattedColor<BGRA, uint8_t>;

// ???
using ARGB_16161616 = FormattedColor<ARGB, uint16_t>;
using RGBA_16161616 = FormattedColor<RGBA, uint16_t>;
using ABGR_16161616 = FormattedColor<ABGR, uint16_t>;
using BGRA_16161616 = FormattedColor<BGRA, uint16_t>;

using ARGB_32_Float = FormattedColor<ARGB, float>;
using RGBA_32_Float = FormattedColor<RGBA, float>;
using ABGR_32_Float = FormattedColor<ABGR, float>;
using BGRA_32_Float = FormattedColor<BGRA, float>;

using ARGB_64_Float = FormattedColor<ARGB, double>;
using RGBA_64_Float = FormattedColor<RGBA, double>;
using ABGR_64_Float = FormattedColor<ABGR, double>;
using BGRA_64_Float = FormattedColor<BGRA, double>;

using ARGB_32 = ARGB_8888;
using ARGB_64 = ARGB_16161616;
using ARGB_32_Float = ARGB_FFFF;
using ARGB_64_Float = ARGB_DDDD;

using RGBA_32 = RGBA_8888;
using RGBA_64 = RGBA_16161616;
using RGBA_32_Float = RGBA_FFFF;
using RGBA_64_Float = RGBA_DDDD;

using ABGR_32 = ABGR_8888;
using ABGR_64 = ABGR_16161616;
using ABGR_32_Float = ABGR_FFFF;
using ABGR_64_Float = ABGR_DDDD;

using BGRA_32 = BGRA_8888;
using BGRA_64 = BGRA_16161616;
using BGRA_32_Float = BGRA_FFFF;
using BGRA_64_Float = BGRA_DDDD;

using Mono8 = FormattedColor<Mono, uint8_t>;
using MonoF = FormattedColor<Mono, float>;
using MonoD = FormattedColor<Mono, double>;

template<Format format = R>
using Color1_8 = FormattedColor<format, uint8_t>;
template<Format format = RG>
using Color2_8 = FormattedColor<format, uint8_t>;
template<Format format = RGB>
using Color3_8 = FormattedColor<format, uint8_t>;
template<Format format = RGBA>
using Color4_8 = FormattedColor<format, uint8_t>;

template<Format format = R>
using Color1_f = FormattedColor<format, float>;
template<Format format = RG>
using Color2_f = FormattedColor<format, float>;
template<Format format = RGB>
using Color3_f = FormattedColor<format, float>;
template<Format format = RGBA>
using Color4_f = FormattedColor<format, float>;

template<Format format = R>
using Color1_d = FormattedColor<format, double>;
template<Format format = RG>
using Color2_d = FormattedColor<format, double>;
template<Format format = RGB>
using Color3_d = FormattedColor<format, double>;
template<Format format = RGBA>
using Color4_d = FormattedColor<format, double>;

}
