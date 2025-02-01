#pragma once

#include <cstdint>
#include <iterator>
#include <utility>

namespace flp {

template<typename Type, typename...>
concept Truth = true;

template<typename Type, typename...>
concept Lies/*?????*/ = false;

template<typename Type, typename... Args>
concept Invokable = requires(Type&& value, Args&&... args) {
  std::forward<Type>(value)(std::forward<Args>(args)...);
  // member dereferencing?
};

// basis
template<typename Type, typename... Args>
concept Constructible = requires(Args... args) { new Type(args...); };

template<typename Type1, typename Type2>
concept Assignable = requires(Type1 value1, Type2 value2) { value1 = value2; };

// no throw
template<typename Type, typename... Args>
concept NothrowConstructible = requires(Args... args) { noexcept(T(args...)); };

template<typename Type1, typename Type2>
concept NothrowAssignable = requires(Type1 value1, Type2 value2) { noexcept(value1 = value2); };

// copyable
template<typename Type>
concept CopyConstructible = Constructible<Type, Type>;

template<typename Type>
concept CopyAssignable = Assignable<Type, Type>;

template<typename Type>
concept Copyable = CopyConstructible<Type> and CopyAssignable<Type>;

// movable
template<typename Type>
concept MoveConstructible = Constructible<Type, Type&&>;

template<typename Type>
concept MoveAssignable = requires(Type value1, Type value2) { value1 = std::move(value2); };

template<typename Type>
concept Movable = MoveConstructible<Type> and MoveAssignable<Type>;

// no throw copy
template<typename Type>
concept NothrowCopyConstructible = NothrowConstructible<Type, Type>;

template<typename Type>
concept NothrowCopyAssignable = NothrowAssignable<Type, Type>;

template<typename Type>
concept NothrowCopyable = NothrowCopyConstructible<Type> and NothrowCopyAssignable<Type>;

// no throw move
template<typename Type>
concept NothrowMoveConstructible = NothrowConstructible<Type, Type&&>;

template<typename Type>
concept NothrowMoveAssignable = NothrowAssignable<Type, Type&&>;

template<typename Type>
concept NothrowMovable = NothrowMoveConstructible<Type> and NothrowMoveAssignable<Type>;

template<typename, template<typename...> class>
inline constexpr bool is_specialization_helper = false;

template<template<typename...> class Target, typename... Args>
inline constexpr bool is_specialization_helper<Target<Args...>, Target> = true;

// using the wrapper and decay handles refs and cv-qual
template<typename Query, template<typename...> typename Target>
inline constexpr bool IsSpecializationOf = is_specialization_helper<std::decay_t<Query>, Target>;

template<typename Type, template<typename...> typename Target>
concept InstanceOf = IsSpecializationOf<Type, Target>;

template<typename Type>
concept BooleanTestable = requires(Type value) {
  {value} -> std::convertible_to<bool>;
  {not value} -> std::convertible_to<bool>;
};

template<typename Type1, typename Type2>
concept EqualityComparableWith = requires(const Type1 value1, const Type2 value2) {
  {value1 == value2} -> BooleanTestable;
  {value2 == value1} -> BooleanTestable;
  {value1 != value2} -> BooleanTestable;
  {value2 != value1} -> BooleanTestable;
};

template<typename Type>
concept EqualityComparable = EqualityComparableWith<Type, Type>;

template<typename Type1, typename Type2>
concept PartiallyOrderedWith = requires(const Type1 value1, const Type2 value2) {
  {value2 < value1} -> BooleanTestable;
  {value2 <= value1} -> BooleanTestable;
  {value2 > value1} -> BooleanTestable;
  {value2 >= value1} -> BooleanTestable;
  {value1 < value2} -> BooleanTestable;
  {value1 <= value2} -> BooleanTestable;
  {value1 > value2} -> BooleanTestable;
  {value1 >= value2} -> BooleanTestable;
};

template<typename Type>
concept PartiallyOrdered = PartiallyOrderedWith<Type, Type>;

template<typename Type1, typename Type2>
concept TotallyOrderedWith = PartiallyOrderedWith<Type1, Type2> and EqualityComparableWith<Type1, Type2>;

template<typename Type>
concept TotallyOrdered = TotallyOrderedWith<Type, Type>;

template<typename Type, typename Referred>
concept Dereferencable = requires(Type value) {
  {*value} -> std::convertible_to<Referred>;
};

template<typename Type, typename Referred>
concept ForwardIterator = Dereferencable<Type, Referred> and requires(Type iterator) {
  ++iterator;
  iterator++;
};

template<typename Type, typename Referred>
concept BidirectionalIterator = ForwardIterator<Type, Referred> and requires(Type iterator) {
  --iterator;
  iterator--;
};

template<typename Type, typename Referred>
concept RandomAccessIterator = BidirectionalIterator<Type, Referred> /*and TotallyOrdered<Type>*/ and requires(Type iterator, const Type citerator, uint64_t uconstant, int64_t sconstant) {
  {iterator + uconstant} -> std::same_as<Type>;
  {iterator + sconstant} -> std::same_as<Type>;
  {iterator += uconstant};
  {iterator += sconstant};
  {iterator - uconstant} -> std::same_as<Type>;
  {iterator - sconstant} -> std::same_as<Type>;
  {iterator -= uconstant};
  {iterator -= sconstant};
  {citerator + uconstant} -> std::same_as<Type>;
  {citerator + sconstant} -> std::same_as<Type>;
  {citerator - uconstant} -> std::same_as<Type>;
  {citerator - sconstant} -> std::same_as<Type>;
};

// contiguous iterator
/*template<typename Type, typename Referred>
concept ContiguousIterator = RandomAccessIterator<Type, Referred> and requires(Type iterator) {
};*/

// simplest iterator
template<typename Type, typename Referred>
concept SimpleIterator = ForwardIterator<Type, Referred>;

template<typename Type, typename Contained>
concept Range = requires(Type value) {
  {std::begin(value)} -> SimpleIterator<Contained>;
  {std::end(value)} -> SimpleIterator<Contained>;
};

template<typename Type>
concept BareRange = requires(Type value) {
  {std::begin(value)};
  {std::end(value)};
};

// orderings
// partial
// total
// strong?
// weak?

} // namespace flp

