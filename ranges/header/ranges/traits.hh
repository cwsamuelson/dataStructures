#pragma once

#include <concepts>
#include <iterator>
#include <utility>

namespace flp {

using ssize_t = std::ptrdiff_t;

template<typename Type>
struct ReferenceableHelper {
  static constexpr bool value = false;
};

template<typename Type>
struct ReferenceableHelper<Type&> {
  static constexpr bool value = true;
};

template<typename Type>
concept Referenceable = ReferenceableHelper<Type>::value;

template<typename Type>
concept Iterator = requires(Type iterator) {
  { ++iterator };//-> std::same_as<Type&>;
  { iterator++ };//-> std::same_as<Type>;
  { *iterator } -> Referenceable;
};

template<typename Type>
concept Range = requires(Type range) {
  { std::begin(range) } -> Iterator;
  { std::end(range) } -> Iterator;
};

}
