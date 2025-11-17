#pragma once

#include <set>

namespace flp {

template<typename Type>
struct Set {
  Set operator and(const Set&) const noexcept {
    return {};
  }

  Set operator or(const Set&) const noexcept {
    return {};
  }

  std::set<Type> items;
};

} // namespace flp
