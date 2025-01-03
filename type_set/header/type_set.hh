#pragma once

#include <type_pack.hh>

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace flp {

template<typename...>
class TypeSetImpl;

template<>
class TypeSetImpl<> {
public:
  constexpr TypeSetImpl() = default;

  constexpr TypeSetImpl(const TypeSetImpl&) = default;
  constexpr TypeSetImpl(TypeSetImpl&&)      = default;

  constexpr ~TypeSetImpl() = default;

  constexpr TypeSetImpl& operator=(const TypeSetImpl&) = delete;
  constexpr TypeSetImpl& operator=(TypeSetImpl&&)      = delete;

  using Pack = TypePack<>;

  template<typename...>
  friend class TypeSetImpl;

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<typename>
  static constexpr BoolConstant<false> Contains{};

  template<typename...Types>
  using Insert = TypePack<Types...>::Unique::template Rebind<TypeSetImpl>;

  template<typename>
  using Erase = TypeSetImpl<>;

  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSetImpl<OtherArgs...>&) const {
    return sizeof...(OtherArgs) == 0;
  }

  // intersection
  // difference
  // symmetric difference
  // union
};

template<typename T1, typename... Args>
class TypeSetImpl<T1, Args...> {
public:
  constexpr TypeSetImpl() = default;

  constexpr TypeSetImpl(const TypeSetImpl&) = default;
  constexpr TypeSetImpl(TypeSetImpl&&)      = default;

  constexpr ~TypeSetImpl() = default;

  constexpr TypeSetImpl& operator=(const TypeSetImpl&) = delete;
  constexpr TypeSetImpl& operator=(TypeSetImpl&&)      = delete;

  using Pack = TypePack<T1, Args...>;

  template<typename...>
  friend class TypeSetImpl;

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<typename Type>
  static constexpr BoolConstant<std::same_as<Type, T1> or (std::same_as<Type, Args> or ...)> Contains{};

  template<typename... Types>
  using Insert = TypePack<T1, Args..., Types...>::Unique::template Rebind<TypeSetImpl>;

  template<typename Type>
  using Erase = std::conditional_t<
    not Contains<Type>,
        TypeSetImpl,
        std::conditional_t<
          std::same_as<T1, Type>,
            TypePack<Args...>::Unique::template Rebind<TypeSetImpl>,
            TypePack<Args...>::Unique::template Rebind<TypeSetImpl>::Erase<Type>::Insert<T1>
        >
      >;
            
  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSetImpl<OtherArgs...>& other) const {
    return (sizeof...(OtherArgs) == (sizeof...(Args) + 1)) and (Contains<OtherArgs>() and ...)
       and (other.template Contains<T1>() and (other.template Contains<Args>() and ...));
  }
};

template<typename Type>
class TypeSetImpl<Type> {
public:
  constexpr TypeSetImpl() = default;

  constexpr TypeSetImpl(const TypeSetImpl&) = default;
  constexpr TypeSetImpl(TypeSetImpl&&)      = default;

  constexpr ~TypeSetImpl() = default;

  constexpr TypeSetImpl& operator=(const TypeSetImpl&) = delete;
  constexpr TypeSetImpl& operator=(TypeSetImpl&&)      = delete;

  using Pack = TypePack<Type>;

  template<typename...>
  friend class TypeSetImpl;

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<typename OtherType>
  static constexpr BoolConstant<std::same_as<OtherType, Type>> Contains{};

  template<typename... Types>
  using Insert = TypePack<Type, Types...>::Unique::template Rebind<TypeSetImpl>;

  template<typename OtherType>
  static constexpr auto erase() {
    if constexpr (std::same_as<OtherType, Type>) {
      return TypeSetImpl<> {};
    } else {
      return TypeSetImpl {};
    }
  }

  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSetImpl<OtherArgs...>&) const {
    return (Contains<OtherArgs>() and ...);
  }
};

template<typename... Args>
struct TypeSet : TypePack<Args...>::Unique::template Rebind<TypeSetImpl> {};

} // namespace flp
