#pragma once

#include "canvas/canvas.hh"
#include "ui/style.hh"
#include "ui/widget.hh"

#include <memory>
#include <vector>

namespace flp::UI {

struct Manager {
  using Canvas = Canvas<>;

  Manager() = default;

  Manager(const Style& stl)
    : style(stl)
  {}

  [[nodiscard]]
  bool visible() const noexcept {
    return true;
  }

  void visible(const bool state) noexcept {
    _visible = state;
  }

  void update(const Widget::MouseState& mouse, const float delta) {
    for (const auto& control : controls) {
      control->update(mouse, delta);
    }
  }

  void draw(Canvas& canvas) {
    for (const auto& control : controls) {
      control->draw(canvas, style);
    }
  }

  void add(std::shared_ptr<Widget> widget) {
    controls.emplace_back(std::move(widget));
  }

  bool _visible = true;
  Style style = default_style;
  std::vector<std::shared_ptr<Widget>> controls;
};

}
