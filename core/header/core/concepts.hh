#pragma once

namespace flp {

// basis
template<typename Type, typename ...Args>
concept Constructible = requires(Args... args) {
  new Type(args...);
};

template<typename Type1, typename Type2>
concept Assignable = requires(Type1 value1, Type2 value2) {
  value1 = value2;
};

// no throw
template<typename Type, typename ...Args>
concept NothrowConstructible = requires(Args... args) {
  noexcept(T(args...));
};

template<typename Type1, typename Type2>
concept NothrowAssignable = requires(Type1 value1, Type2 value2) {
  noexcept(value1 = value2);
};

// copyable
template<typename Type>
concept CopyConstructible = Constructible<Type, Type>;

template<typename Type>
concept CopyAssignable = Assignable<Type, Type>;

template<typename Type>
concept Copyable =
     CopyConstructible<Type>
 and CopyAssignable<Type>;

// movable
template<typename Type>
concept MoveConstructible = Constructible<Type, Type&&>;

template<typename Type>
concept MoveAssignable = requires(Type value1, Type value2) {
  value1 = std::move(value2);
};

template<typename Type>
concept Movable =
     MoveConstructible<Type>
 and MoveAssignable<Type>;

// no throw copy
template<typename Type>
concept NothrowCopyConstructible = NothrowConstructible<Type, Type>;

template<typename Type>
concept NothrowCopyAssignable = NothrowAssignable<Type, Type>;

template<typename Type>
concept NothrowCopyable =
     NothrowCopyConstructible<Type>
 and NothrowCopyAssignable<Type>;

// no throw move
template<typename Type>
concept NothrowMoveConstructible = NothrowConstructible<Type, Type&&>;

template<typename Type>
concept NothrowMoveAssignable = NothrowAssignable<Type, Type&&>;

template<typename Type>
concept NothrowMovable =
     NothrowMoveConstructible<Type>
 and NothrowMoveAssignable<Type>;

template<typename, template<typename...> class>
inline constexpr bool is_specialization_helper = false;

template<template<typename...> class Target, typename... Args>
inline constexpr bool is_specialization_helper<Target<Args...>, Target> = true;

// using the wrapper and decay handles refs and cv-qual
template<typename Query, template<typename...> typename Target>
inline constexpr bool IsSpecializationOf = is_specialization_helper<std::decay_t<Query>, Target>;

template<typename Type, template<typename...> typename Target>
concept instance_of = IsSpecializationOf<Type, Target>;

/*template<typename Type, typename Referred>
concept Iterator = requires(Type value) {
  ++value;
  value++;
  --value;
  value--;
  *value -> std::convertible_to<Referred>;
};

template<typename Type, typename Contained>
concept Range = requires(Type value, Type cvalue) {
  std::begin(value) -> Iterator<Contained>;
  std::end(value) -> Iterator<Contained>;

  std::begin(cvalue) -> Iterator<const Contained>;
  std::end(cvalue) -> Iterator<const Contained>;

  std::cbegin(value) -> Iterator<const Contained>;
  std::cend(value) -> Iterator<const Contained>;
};*/

}

