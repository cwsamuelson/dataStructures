#include "ui/manager.hh"

namespace flp::UI {

Manager::Manager() = default;

Manager::Manager(const Style& stl)
  : style(stl)
{}

Manager::Manager(const Manager* prnt, const Position2<size_t>& offset)
  : _parent(prnt)
  , offset(offset)
{}

Manager::Manager(const Manager* prnt, const Position2<size_t>& offset, const Style& stl)
  : _parent(prnt)
  , offset(offset)
  , style(stl)
{}

std::optional<const Manager*> Manager::parent() const noexcept {
  return _parent;
}

void Manager::parent(const Manager* prnt) noexcept {
  if (prnt == nullptr) {
    _parent = std::nullopt;
  } else {
    _parent = prnt;
  }
}

bool Manager::visible() const noexcept {
  return _visible;
}

void Manager::visible(const bool state) noexcept {
  _visible = state;
}

void Manager::update(const Widget::MouseState& mouse, const float delta) {
  for (const auto& control : controls) {
    control->update(mouse, delta);
  }
}

void Manager::draw(Canvas& canvas) {
  for (const auto& control : controls) {
    control->draw(canvas, style);
  }
}

void Manager::add(std::shared_ptr<Widget> widget) {
  controls.emplace_back(std::move(widget));
}

Position2<size_t> Manager::position_offset() const noexcept {
  if (not _parent.has_value()) {
    return {0, 0};
  }

  // return _parent.value()->position_offset() + offset;
  return _parent.value()->position_offset();
}

}
