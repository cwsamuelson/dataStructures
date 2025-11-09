#pragma once

#include "ui/control.hh"

namespace flp::UI {

struct CheckBox : Control {
  CheckBox(std::string_view txt, Position2<size_t> pos, Size2<size_t> sz);
  ~CheckBox() override = default;

  [[nodiscard]]
  bool visible() const noexcept override;

  void visible(const bool state) noexcept override;

  [[nodiscard]]
  bool enabled() const noexcept override;

  void enabled(const bool state) noexcept override;

  void update(const MouseState& mouse, float delta) override;

  void draw(Canvas& canvas, const Style& style) override;

  Position2<size_t> position;
  Size2<size_t> size;
  std::string text;
  bool check_state = false;

  bool pressed = false;
  bool held = false;
  bool released = false;
};

}
