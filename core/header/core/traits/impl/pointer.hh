#pragma once

#include "core/traits/value_types.hh"

namespace flp {

namespace {

// modify

template<typename Type>
struct RemovePointerImpl {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type*> {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type* const> {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type* const volatile> {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type* volatile> {
  using type = Type;
};

// query

template<typename>
struct IsPointerImpl {
  static constexpr auto value = False;
};

template<typename Type>
struct IsPointerImpl<Type*> {
  static constexpr auto value = True;
};

}

}
