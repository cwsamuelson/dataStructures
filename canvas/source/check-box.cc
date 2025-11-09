#include "ui/check-box.hh"

namespace flp::UI {

CheckBox::CheckBox(const std::string_view txt, const Position2<size_t> pos, const Size2<size_t> sz)
  : text(txt)
  , position(pos)
  , size(sz)
{}

bool CheckBox::visible() const noexcept {
  return true;
}

void CheckBox::visible(const bool state) noexcept {
  _visible = state;
}

bool CheckBox::enabled() const noexcept {
  return true;
}

void CheckBox::enabled(const bool state) noexcept {
  _enabled = state;
}

void CheckBox::update(const MouseState& mouse, float delta) {
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

void CheckBox::draw(Canvas& canvas, const Style& style) {
  if (not _visible) {
    return;
  }

  // body
  canvas.fill_rectangle(position, size, style.fill);
  canvas.draw_rectangle(position, size, style.border);

  const size_t margin = 10;
  const auto total_margin = margin * 2;
  const auto small_side = std::min(size.width - total_margin, size.height - total_margin);
  const Size2<size_t> box_size{ small_side, small_side };

  // check
  canvas.fill_rectangle(position + vec2<size_t>{margin, margin}, box_size, white);
  canvas.draw_rectangle(position + vec2<size_t>{margin, margin}, box_size, black);

  const auto text_offset = small_side + 2 * margin;
  canvas.fill_text({position.x + text_offset, position.y + (size.height / 2)}, text, style.text);
}

}
