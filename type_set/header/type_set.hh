#pragma once
#include <type_traits>

namespace flp {

template<typename...>
class TypeSet;

template<typename T1, typename... Args>
class TypeSet<T1, Args...> {
public:
  // add
  // remove

  template<typename Type>
  static constexpr bool contains() {
    return contains_helper<Type>;
  }

private:
  template<typename...>
  friend class TypeSet;

  template<typename Type>
  struct ContainsHelper_t {
    static constexpr bool value = std::is_same_v<Type, T1> or TypeSet<Args...>::template ContainsHelper_t<Type>::value;
  };

  template<typename Type>
  static constexpr bool contains_helper = ContainsHelper_t<Type>::value;
};

template<typename Type>
class TypeSet<Type> {
public:
  // add
  // remove
  template<typename OtherType>
  static constexpr bool contains() {
    return contains_helper<OtherType>;
  }

private:
  template<typename...>
  friend class TypeSet;

  template<typename OtherType>
  struct ContainsHelper_t {
    static constexpr bool value = std::is_same_v<OtherType, Type>;
  };

  template<typename OtherType>
  static constexpr bool contains_helper = ContainsHelper_t<OtherType>::value;
};

template<>
class TypeSet<> {
public:
  // add
  // remove

  template<typename>
  static constexpr bool contains() {
    return false;
  }

private:
  template<typename...>
  friend class TypeSet;

  template<typename>
  struct ContainsHelper_t {
    static constexpr bool value = false;
  };
};

} // namespace flp
