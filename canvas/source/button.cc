#include "ui/button.hh"

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
  if (not _enabled) {
    return;
  }

  if (mouse.left_button.pressed and mouse.position > position and mouse.position < (position + size)) {
    held = pressed or held;
    pressed = not pressed;
    released = false;
  } else {
    released = pressed or held;
    pressed = false;
    held = false;
  }
}

void Button::draw(Canvas& canvas, const Style& style) {
  if (_visible) {
    canvas.fill_rectangle(position, size, style.fill);
    canvas.draw_rectangle(position, size, style.border);
    canvas.fill_text(position, text, style.text);
  }
}

}
