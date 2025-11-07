#pragma once

#include "canvas/canvas.hh"
#include "canvas/utility.hh"
#include "ui/style.hh"

namespace flp::UI {

struct Widget {
  using Canvas = Canvas<>;

  virtual ~Widget() = default;

  [[nodiscard]]
  virtual bool visible() const noexcept = 0;

  virtual void visible(bool) noexcept = 0;

  struct ButtonState {
    bool pressed;
    bool held;
    bool released;
  };

  struct MouseState {
    ButtonState left_button;
    ButtonState right_button;
    Position2<size_t> position;
  };

  virtual void update(const MouseState& mouse, float delta) = 0;
  virtual void draw(Canvas& canvas, const Style& style) = 0;

  bool _visible = true;
};

}
