#ifndef __COMMON_TYPE_HH__
#define __COMMON_TYPE_HH__

#include<type_traits>
#include<utility>

namespace gsw{

namespace detail{

template<typename T, typename U>
struct common_type_helper{
  using type = decltype( false ? std::declval<std::decay_t<T> >() :
                                 std::declval<std::decay_t<U> >() );
};

}//detail

template<typename ...Args>
struct common_type;

/*!
 * @tparam Args
 */
template<typename ...Args>
using common_type_t = typename common_type<Args...>::type;

/*! Single template parameter specialization
 *
 * @tparam T
 */
template<typename T>
struct common_type<T>{
  using type = std::decay_t<T>;
};

/*!
 *
 * @tparam T
 *
 * @tparam U
 *
 * @tparam Args
 */
template<typename T, typename U, typename ...Args>
struct common_type<T, U, Args...>{
  using type = common_type_t<typename detail::common_type_helper<T, U>::type, Args...>;
};

}

#endif
