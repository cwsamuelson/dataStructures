#pragma once

#include "canvas/canvas.hh"
#include "ui/style.hh"
#include "ui/widget.hh"

#include <memory>
#include <optional>
#include <vector>

namespace flp::UI {

struct Manager {
  using Canvas = Canvas<>;

  Manager();

  Manager(const Style& stl);

  Manager(const Manager* prnt, const Position2<size_t>& offset);

  Manager(const Manager* prnt, const Position2<size_t>& offset, const Style& stl);

  [[nodiscard]]
  std::optional<const Manager*> parent() const noexcept;

  void parent(const Manager* prnt) noexcept;

  [[nodiscard]]
  bool visible() const noexcept;

  void visible(const bool state) noexcept;

  void update(const Widget::MouseState& mouse, const float delta);

  void draw(Canvas& canvas);

  void add(std::shared_ptr<Widget> widget);

  [[nodiscard]]
  Position2<size_t> position_offset() const noexcept;

  bool _visible = true;
  Style style = default_style;
  std::vector<std::shared_ptr<Widget>> controls;
  std::optional<const Manager*> _parent;
  Position2<size_t> offset;
};

}
