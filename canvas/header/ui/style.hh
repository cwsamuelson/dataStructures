#pragma once

#include "canvas/color.hh"

namespace flp::UI {

static constexpr ColorRGBA32 black(0.f, 0.f, 0.f, 1.f);
static constexpr ColorRGBA32 white(1.f, 1.f, 1.f, 1.f);
static constexpr ColorRGBA32 blank(0, 0, 0, 0);
static constexpr ColorRGBA32 grey (192, 192, 192, 255);

static constexpr ColorRGBA32 red  (1.f, 0.f, 0.f, 1.f);
static constexpr ColorRGBA32 green(0.f, 1.f, 0.f, 1.f);
static constexpr ColorRGBA32 blue (0.f, 0.f, 1.f, 1.f);

static constexpr ColorRGBA32 cyan   (0.f, 1.f, 1.f, 1.f);
static constexpr ColorRGBA32 magenta(1.f, 0.f, 1.f, 1.f);
static constexpr ColorRGBA32 yellow (1.f, 1.f, 0.f, 1.f);

static constexpr ColorRGBA32 dark_grey     (128, 128, 128, 255);
static constexpr ColorRGBA32 very_dark_grey( 64,  64,  64, 255);

static constexpr ColorRGBA32 dark_red     (128, 0, 0, 255);
static constexpr ColorRGBA32 very_dark_red( 64, 0, 0, 255);

static constexpr ColorRGBA32 dark_yellow     (128, 128, 0, 255);
static constexpr ColorRGBA32 very_dark_yellow( 64,  64, 0, 255);

static constexpr ColorRGBA32 dark_green     (0, 128, 0, 255);
static constexpr ColorRGBA32 very_dark_green(0,  64, 0, 255);

static constexpr ColorRGBA32 dark_cyan     (0, 128, 128, 255);
static constexpr ColorRGBA32 very_dark_cyan(0,  64,  64, 255);

static constexpr ColorRGBA32 dark_blue     (0, 0, 128, 255);
static constexpr ColorRGBA32 very_dark_blue(0, 0,  64, 255);

static constexpr ColorRGBA32 dark_magenta     (128, 0, 128, 255);
static constexpr ColorRGBA32 very_dark_magenta( 64, 0,  64, 255);

struct Style {
  flp::ColorRGBA32 fill =  dark_blue;
  flp::ColorRGBA32 hover = blue;
  flp::ColorRGBA32 click = cyan;
  flp::ColorRGBA32 disabled = dark_grey;
  flp::ColorRGBA32 border = white;
  flp::ColorRGBA32 text = white;
};

static constexpr Style default_style {};

}
