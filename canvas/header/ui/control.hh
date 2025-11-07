#pragma once

#include "ui/widget.hh"

namespace flp::UI {

struct Control : Widget {
  ~Control() override = default;

  [[nodiscard]]
  virtual bool enabled() const noexcept = 0;
  virtual void enabled(bool) noexcept = 0;

  bool _enabled = true;
};

}
