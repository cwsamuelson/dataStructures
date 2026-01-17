#include "ui/button.hh"

#include <print>

namespace flp::UI {

Button::Button(const std::string_view txt, const Position2<size_t> pos, const Size2<size_t> sz)
  : text(txt)
  , position(pos)
  , size(sz)
{}

bool Button::visible() const noexcept {
  return true;
}

void Button::visible(const bool state) noexcept {
  _visible = state;
}

bool Button::enabled() const noexcept {
  return true;
}

void Button::enabled(const bool state) noexcept {
  _enabled = state;
}

void Button::update(const MouseState& mouse, float delta) {
  if (not _enabled or not _visible) {
    return;
  }

  pressed  = false;
  released = false;
  clicked  = false;
  held     = false;
  hovered  = mouse.position > position and mouse.position < (position + size);

  // -[x] clicked
  // -[x] hovered
  // -[x] pressed
  // -[x] held
  // -[ ] released

  if (hovered) {
    pressed = mouse.left_button.pressed;

    if (pressed) {
      clicked = true;

      held = clicked and mouse.left_button.held;
    }
  } else {
  }

}

void Button::draw(Canvas& canvas, const Style& style) {
  if (not _visible) {
    return;
  }

  // canvas.fill_rectangle(position, size, clicked ? white : style.fill);
  // canvas.draw_rectangle(position, size, style.border);
  // canvas.fill_text(position, text, style.text);

  // canvas.draw_circle(position, 100, style.fill);
  canvas.fill_circle(position, 100, style.fill);
}

}
