#pragma once

#include "algorithms/numerics.hh"
#include "core/aligned-buffer.hh"
#include "core/type-pack.hh"

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
  template<typename Type>
  Variant(const Type& value) {
    //buffer.construct(value);
  }

  template<typename ...Args>
  Variant(Args&& ...args) {
    //buffer.construct(std::forward<Args>(args)...);
  }

  AlignedBuffer<max_sizeof<Types...>(), max_alignof<Types...>()> buffer;
  uint32_t index{};
};

struct Monostate {};

template<size_t Index, typename ...Types>
bool holds_alternative(const Variant<Types...>& variant) {
  return Index == variant.index;
}

template<size_t Index, typename ...Types>
auto& get(Variant<Types...>& variant) {
  //VERIFY(Index == variant.index, "");

  using Type = TypePack<Types...>::template Get<Index>;

  return *std::launder<Type>(reinterpret_cast<Type*>(variant.buffer.storage.data()));
}

template<typename Functor, typename ...Types>
decltype(auto) visit(Functor&& functor, Variant<Types...>& variant) {
  //[[nodiscard]]
  //Type& get() noexcept {
  //  return *std::launder<Type>(reinterpret_cast<Type*>(Base::storage.data()));
  //}

  //[[nodiscard]]
  //const Type& get() const noexcept {
  //  return *std::launder<const Type>(reinterpret_cast<const Type*>(Base::storage.data()));
  //}

  //if (variant.index
}

} // namespace flp
