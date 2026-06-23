#pragma once

#include <type_traits>

namespace flp {

// https://github.com/lefticus/tools/blob/main/include/lefticus/tools/forwarding_ref.hpp
template<typename Type>
struct [[nodiscard]] ForwardRef {
  using Pointer = std::add_pointer_t<std::remove_reference_t<Type>>;
  using Reference = Type;

  ForwardRef(ForwardRef&&) = delete;
  ForwardRef(const ForwardRef&) = delete;
  ForwardRef& operator=(ForwardRef&&) = delete;
  ForwardRef& operator=(const ForwardRef&) = delete;

  [[nodiscard]]
  constexpr
  ForwardRef(Reference ref [[clang::lifetimebound]]) noexcept
    : pointer(&ref)
  {}

  [[nodiscard]]
  constexpr
  operator Reference() noexcept [[clang::lifetimebound]] {
    return static_cast<Type>(*pointer);
  }

  Pointer pointer;
};

template<typename Type>
ForwardRef(Type&&) -> ForwardRef<Type&&>;

}
