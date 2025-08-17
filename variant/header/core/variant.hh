#pragma once

#include "algorithms/max.hh"
#include "aligned_buffer.hh"

#include <cstddef>
#include <cstdint>

namespace flp {

namespace {

template<typename ...Args>
constexpr
decltype(auto) max_sizeof() noexcept {
  size_t max_size{};

  ((max_size = max(max_size, sizeof(Args))), ...);

  return max_size;
}

template<typename ...Args>
constexpr
decltype(auto) max_alignof() noexcept {
  size_t max_size{};

  ((max_size = max(max_size, alignof(Args))), ...);

  return max_size;
}

}

template<typename ...Types>
struct Variant {
  AlignedBuffer<max_sizeof<Types...>(), max_alignof<Types...>()> buffer;
  uint32_t index{};
};

struct Monostate {};

template<typename Functor, typename ...Types>
decltype(auto) visit(Functor&& functor, Variant<Types...>& variant) {
}

} // namespace flp
