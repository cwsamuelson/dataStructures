#pragma once

#include <string>

namespace flp::Version {

struct Generic {
  Generic(std::string_view rev_string);
};

} // namespace flp
