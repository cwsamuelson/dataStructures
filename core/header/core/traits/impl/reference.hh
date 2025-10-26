#pragma once

#include "core/traits/value_types.hh"

namespace flp {

namespace {

// modify

template<typename Type>
struct RemoveReferenceImpl {
  using type = Type;
};

template<typename Type>
struct RemoveReferenceImpl<Type&> {
  using type = Type;
};

template<typename Type>
struct RemoveReferenceImpl<Type&&> {
  using type = Type;
};

// query

template<typename>
struct IsReferenceImpl {
  static constexpr auto value = False;
};

template<typename Type>
struct IsReferenceImpl<Type&&> {
  static constexpr auto value = True;
};

template<typename Type>
struct IsReferenceImpl<Type&> {
  static constexpr auto value = True;
};

}

}
