#pragma once

#include <vector>

namespace flp {

struct Menu {
  std::vector<Menu> sub_menus;
};

} // namespace flp
