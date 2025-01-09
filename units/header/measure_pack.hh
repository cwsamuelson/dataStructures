#pragma once

#include <value_pack.hh>

namespace flp {

namespace {

// implement uniquity in terms of filter?
template<auto...>
struct UniqueTypeHelper;

template<>
struct UniqueTypeHelper<> {
  using type = ValuePack<>;
};

template<auto V1, auto... Values>
struct UniqueTypeHelper<V1, Values...> {
  static constexpr bool contains = (std::same_as<decltype(V1), decltype(Values)> or ...);

  using type = std::conditional_t<contains,
                                  typename ValuePack<Values...>::Unique,
                                  typename ValuePack<Values...>::Unique::template Prepend<V1>>;
};

template<typename, auto...>
struct SelectHelper;

template<typename Type, auto V1, auto... Values>
struct SelectHelper<Type, V1, Values...> {
  static constexpr auto value = []{
    if constexpr (std::same_as<Type, decltype(V1)>) {
      return V1;
    } else {
      return SelectHelper<Type, Values...>::value;
    }
  }();
};

} // namespace

template<auto... Measures>
struct MeasurePack : ValuePack<Measures...> {
  template<typename Type>
  static constexpr auto Select = SelectHelper<Type, Measures...>::value;

  template<typename Type>
  static constexpr BoolConstant<(std::same_as<decltype(Measures), Type> or ...)> Has {};

  using UniqueTypes = typename UniqueTypeHelper<Measures...>::type;
};

} // namespace flp

