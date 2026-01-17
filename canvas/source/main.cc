#include "utility/graphical-term.hh"

#include <canvas/canvas.hh>
#include <ui/button.hh>
#include <ui/check-box.hh>
#include <ui/manager.hh>
#include <ui/style.hh>

#include <fstream>
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

using Canvas = flp::Canvas<>;

void draw_button(auto& canvas, const std::string_view text, const Canvas::Position& position, const Canvas::Size& dimensions, const flp::UI::Style& style) {
  canvas.fill_rectangle(position, dimensions, style.fill);
  canvas.draw_rectangle(position, dimensions, style.border);
  canvas.fill_text(position, text, style.text);
}

int main() {
  const auto style = flp::UI::default_style;

  const auto state = std::make_unique<GraphicalTermState>();

  GraphicalTermStart(state.get());
  GraphicalTermHideTextualCursor(state.get());

  // initialize a single frame to get dimensions
  GraphicalTermFrameBegin(state.get());
  flp::Canvas<> canvas(state->framebuffer.width, state->framebuffer.height);
  GraphicalTermFrameEnd(state.get());

  flp::UI::Manager ui_manager;
  ui_manager.add(
    std::make_shared<flp::UI::Button>(
      "Button!", flp::Position2<size_t>{500, 500}, flp::Size2<size_t>{200, 100}
    )
  );
  ui_manager.add(
    std::make_shared<flp::UI::CheckBox>(
      "Checkbox!", flp::Position2<size_t>{1000, 1000}, flp::Size2<size_t>{200, 100}
    )
  );

  auto prev_state = state->mouse;

  bool running = true;
  while (running) {
    GraphicalTermFrameBegin(state.get());
    if (GraphicalTermIsKeyDown(state.get(), GTKEY_ESCAPE)) {
      running = false;
    }

    // only clear + draw when there is an active framebuffer
    if (state->framebufferPending) {
      canvas.clear(flp::UI::black);

      flp::UI::Widget::MouseState mouse_state;

      mouse_state.position.x = state->mouse.x;
      mouse_state.position.y = state->mouse.y;

      mouse_state.left_button.pressed = false;
      mouse_state.left_button.released = false;
      if (state->mouse.buttons & 0x01 != prev_state.buttons & 0x01) {
        mouse_state.left_button.pressed = state->mouse.buttons & 0x01;
        mouse_state.left_button.released = not state->mouse.buttons & 0x01;
        mouse_state.left_button.held = false;
      } else {
        mouse_state.left_button.held = state->mouse.buttons & 0x01;
      }

      mouse_state.right_button.pressed = false;
      mouse_state.right_button.released = false;
      if (state->mouse.buttons & 0x04 != prev_state.buttons & 0x04) {
        mouse_state.right_button.pressed = state->mouse.buttons & 0x04;
        mouse_state.right_button.released = not state->mouse.buttons & 0x04;
        mouse_state.right_button.held = false;
      } else {
        mouse_state.right_button.held = state->mouse.buttons & 0x04;
      }

      prev_state = state->mouse;

      ui_manager.update(mouse_state, 0.f);
      ui_manager.draw(canvas);

      canvas.draw_circle({1200, 1200}, 100, {0, 1, 0, 1});

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
