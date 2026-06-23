#pragma once

#include <type_traits>

namespace flp {

// https://github.com/lefticus/tools/blob/main/include/lefticus/tools/moving_ref.hpp
template<typename Type>
concept Movable =
      std::is_move_constructible_v<Type>
  and std::is_move_assignable_v<Type>
  and not std::is_const_v<Type>
  and not std::is_pointer_v<Type>
  and not std::is_reference_v<Type>
;

template<Movable Type>
struct [[nodiscard]] MoveRef {
  using Pointer = std::add_pointer_t<Type>;
  using Reference = std::add_rvalue_reference_t<Type>;

  MoveRef() = delete("Can't have an empty reference");
  MoveRef(MoveRef&&) = delete("Moving a reference");
  MoveRef(const MoveRef&) = delete("copying a move reference???");
  MoveRef& operator=(MoveRef&&) = delete("Moving a reference");
  MoveRef& operator=(const MoveRef&) = delete("copying a move reference???");

  MoveRef(const Type&) = delete("MoveRef is only to be used with rvalue references");

  [[nodiscard]]
  constexpr
  explicit
  MoveRef(Reference val [[clang::lifetimebound]]) noexcept
    : value(&val)
  {}

  [[nodiscard]]
  constexpr
  operator Reference() noexcept [[clang::lifetimebound]] {
    return std::move(*value);
  }

  Type* value;
};

}
