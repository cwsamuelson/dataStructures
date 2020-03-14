#ifndef __IS_SAME_HH__
#define __IS_SAME_HH__

/*!
 * @example test-same.cc
 */

namespace gsw {

namespace detail {

/*! 'Stores' a type, and checks equality with another type
 *
 * @tparam T 'stored' type
 *
 * This class provides equality check operator that uses template
 * specialization to determine type equality compared to the 'stored' type T.
 */
template<typename T>
class is_same_helper {
public:
  constexpr bool operator==(is_same_helper<T>) {
    return true;
  }

  template<typename U>
  constexpr bool operator==(is_same_helper<U>) {
    return false;
  }
};

}

/*! Type trait to determine if 2 types are equivalent
 *
 * @tparam T  First type
 *
 * @tparam U  Second type
 *
 * value static member contains result of type equality
 */
template<typename T, typename U>
class is_same {
public:
  static constexpr bool value = detail::is_same_helper<T>() == detail::is_same_helper<U>();
};

}

#endif
