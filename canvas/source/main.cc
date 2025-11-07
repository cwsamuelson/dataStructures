#include "graphical-term-util.hh"

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

constexpr flp::ColorRGBA32 black  (0.f, 0.f, 0.f, 1.f);
constexpr flp::ColorRGBA32 white  (1.f, 1.f, 1.f, 1.f);

constexpr flp::ColorRGBA32 red    (1.f, 0.f, 0.f, 1.f);
constexpr flp::ColorRGBA32 green  (0.f, 1.f, 0.f, 1.f);
constexpr flp::ColorRGBA32 blue   (0.f, 0.f, 1.f, 1.f);

constexpr flp::ColorRGBA32 cyan   (0.f, 1.f, 1.f, 1.f);
constexpr flp::ColorRGBA32 magenta(1.f, 0.f, 1.f, 1.f);
constexpr flp::ColorRGBA32 yellow (1.f, 1.f, 0.f, 1.f);

void Draw(const flp::Canvas<>& canvas) {
}

}

int main() {
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

      canvas.draw_line({}, {canvas.width(), canvas.height()}, Kitty::red);

      for (size_t i = 0; i < canvas.height() / 2; ++i) {
        canvas.draw_line({0, i}, {canvas.width(), i}, Kitty::green);
      }

      for (size_t i = 0; i < canvas.width() / 2; ++i) {
        canvas.draw_line({i, 0}, {i, canvas.height()}, Kitty::blue);
      }

      canvas.draw_line({}, {canvas.width(), canvas.height()}, Kitty::magenta);

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
