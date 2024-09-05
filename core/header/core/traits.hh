#pragma once

#include <type_traits>

namespace flp {

// --- const

template<typename Type>
struct RemoveConstImpl {
  using type = Type;
};

template<typename Type>
struct RemoveConstImpl<const Type> {
  using type = Type;
};

template<typename Type>
using RemoveConst = RemoveConstImpl<Type>::type;

template<typename Type>
using AddConst = const Type;

// --- volatile
template<typename Type>
struct RemoveVolatileImpl {
  using type = Type;
};

template<typename Type>
struct RemoveVolatileImpl<volatile Type> {
  using type = Type;
};

template<typename Type>
using RemoveVolatile = RemoveVolatileImpl<Type>::type;

template<typename Type>
using AddVolatile = volatile Type;

// --- CV
template<typename Type>
using RemoveCV = RemoveConst<RemoveVolatile<Type>>;

template<typename Type>
using AddCV = AddConst<AddVolatile<Type>>;

// --- reference
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

template<typename Type>
using RemoveReference = RemoveReferenceImpl<Type>::type;

template<typename Type>
using AddLValueReference = Type&;

template<typename Type>
using AddRValueReference = Type&&;

} // namespace flp

