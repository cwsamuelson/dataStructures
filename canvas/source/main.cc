#include "utility/graphical-term.hh"

#include <canvas/canvas.hh>

#include <memory>
#include <print>
#include <ranges>

namespace Terminal {

constexpr flp::ColorRGBA32 black(0, 0, 0, 0);
constexpr flp::ColorRGBA32 white(1, 1, 1, 0);

void Draw(const flp::Canvas<>& canvas) {
  for (const auto& line : canvas.canvas) {
    std::println("{}", line | std::views::transform([&](const auto& value) {
      return value == black ? 'x' : (value == white ? '#' : '?');
    }) | std::ranges::to<std::string>());
  }

  std::println("");
}

}

namespace Kitty {

constexpr flp::ColorRGBA32 black(0.f, 0.f, 0.f, 1.f);
constexpr flp::ColorRGBA32 white(1.f, 1.f, 1.f, 1.f);
constexpr flp::ColorRGBA32 blank(0, 0, 0, 0);
constexpr flp::ColorRGBA32 grey (192, 192, 192, 255);

constexpr flp::ColorRGBA32 red  (1.f, 0.f, 0.f, 1.f);
constexpr flp::ColorRGBA32 green(0.f, 1.f, 0.f, 1.f);
constexpr flp::ColorRGBA32 blue (0.f, 0.f, 1.f, 1.f);

constexpr flp::ColorRGBA32 cyan   (0.f, 1.f, 1.f, 1.f);
constexpr flp::ColorRGBA32 magenta(1.f, 0.f, 1.f, 1.f);
constexpr flp::ColorRGBA32 yellow (1.f, 1.f, 0.f, 1.f);

constexpr flp::ColorRGBA32 dark_grey     (128, 128, 128, 255);
constexpr flp::ColorRGBA32 very_dark_grey( 64,  64,  64, 255);

constexpr flp::ColorRGBA32 dark_red     (128, 0, 0, 255);
constexpr flp::ColorRGBA32 very_dark_red( 64, 0, 0, 255);

constexpr flp::ColorRGBA32 dark_yellow     (128, 128, 0, 255);
constexpr flp::ColorRGBA32 very_dark_yellow( 64,  64, 0, 255);

constexpr flp::ColorRGBA32 dark_green     (0, 128, 0, 255);
constexpr flp::ColorRGBA32 very_dark_green(0,  64, 0, 255);

constexpr flp::ColorRGBA32 dark_cyan     (0, 128, 128, 255);
constexpr flp::ColorRGBA32 very_dark_cyan(0,  64,  64, 255);

constexpr flp::ColorRGBA32 dark_blue     (0, 0, 128, 255);
constexpr flp::ColorRGBA32 very_dark_blue(0, 0,  64, 255);

constexpr flp::ColorRGBA32 dark_magenta     (128, 0, 128, 255);
constexpr flp::ColorRGBA32 very_dark_magenta( 64, 0,  64, 255);

void Draw(const flp::Canvas<>& canvas) {
}

}

using Canvas = flp::Canvas<>;

struct Style {
  flp::ColorRGBA32 fill;
  flp::ColorRGBA32 border;
  flp::ColorRGBA32 text;
};

void draw_button(auto& canvas, const std::string_view text, const Canvas::Position& position, const Canvas::Size& dimensions, const Style& style) {
  canvas.fill_rectangle(position, dimensions, style.fill);
  canvas.draw_rectangle(position, dimensions, style.border);
  canvas.fill_text(position, text, style.text);
}

int main() {
  const Style style {
    .fill = Kitty::dark_blue,
    .border = Kitty::white,
    .text = Kitty::white,
    // normal dark_blue DARK_BLUE(0, 0, 128),
    // hover blue BLUE(0, 0, 255),
    // click cyan CYAN(0, 255, 255),
    // disable dark_grey DARK_GREY(128, 128, 128),
    // border white WHITE(255, 255, 255),
  };
  const auto state = std::make_unique<GraphicalTermState>();
  GraphicalTermStart(state.get());
  GraphicalTermHideTextualCursor(state.get());

  // initialize a single frame to get dimensions
  GraphicalTermFrameBegin(state.get());
  flp::Canvas<> canvas(state->framebuffer.width, state->framebuffer.height);
  GraphicalTermFrameEnd(state.get());

  bool running = true;
  while (running) {
    GraphicalTermFrameBegin(state.get());
    if (GraphicalTermIsKeyDown(state.get(), GTKEY_ESCAPE)) {
      running = false;
    }

    // only clear + draw when there is an active framebuffer
    if (state->framebufferPending) {
      canvas.clear(Kitty::black);

      draw_button(canvas, "HI!", {500, 500}, {100, 100}, style);

      for (size_t y = 0; y < state->framebuffer.height; y++) {
        const size_t yoff = y * state->framebuffer.width;
        for (size_t x = 0; x < state->framebuffer.width; x++) {
          const auto& pixel = canvas.canvas.at(y).at(x);
          const uint32_t value =
              (static_cast<uint32_t>(pixel.a) << 24)
            | (static_cast<uint32_t>(pixel.b) << 16)
            | (static_cast<uint32_t>(pixel.g) <<  8)
            | (static_cast<uint32_t>(pixel.r) <<  0)
          ;
          state->framebuffer.ptr[yoff + x] = value;
        }
      }
    }

    GraphicalTermFrameEnd(state.get());
  }

  GraphicalTermStop(state.get());
}
