#pragma once

#include <concepts>
#include <iterator>
#include <utility>

#include <vector>

namespace flp {

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

static_assert(Range<std::vector<int>>);
// static_assert(Range<int[5]>);

// static_assert(Range<AllView<int[5]>>);
// static_assert(Range<AllView<std::vector<int>>>);

}
