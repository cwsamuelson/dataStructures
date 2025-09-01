#pragma once

#include <array>
#include <cstddef>

namespace flp {

template<typename Type, size_t Count = 1>
std::array<Type, Count> make_array(Type&& value) {
  return []<size_t ...Indices>(Type&& value, std::integer_sequence<Indices...>) {
    return std::array<Type, Count>{ ((Indices, value), ...) };
  }(std::forward<Type>(value), std::make_integer_sequence<Count>());
}

}
