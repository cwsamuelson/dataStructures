#ifndef __TUPLE_H__
#define __TUPLE_H__

#include<utility>

/*!
 * @example test-tuple.cc
 */

namespace gsw{

/*!
 * @tparam N tuple size
 *
 * @tparam ...Args parameter pack of stored types
 */
template<size_t N, typename ...Args>
class tuple_impl;

/*! Recursion termination tuple_impl
 *
 * @tparam N Index value of this storage unit
 *
 * @tparam T Storage type of this storage unit
 *
 * The tail end of a tuple chain.  Contains the tail's type and value.
 */
template<size_t N, typename T>
class tuple_impl<N, T>{
public:
  /*! Type of value stored here
   */
  using value_type = T;

  value_type data;

  /*! Default ctor
   */
  tuple_impl():
    data( value_type() ){
  }

  /*! Basic init ctor
   *
   * @param vt Value of data to store in this unit
   */
  tuple_impl( value_type vt ):
    data( vt ){
  }
};

/*! Tuple element
 *
 * @tparam N Index value of this storage unit
 *
 * @tparam T Storage type of this storage unit
 *
 * @tparam ...Args Remaining types of the containing tuple
 *
 * Tuple chain link.  Each link inherits from the next link, creating a
 * compile-time linked list
 */
template<size_t N, typename T, typename ...Args>
class tuple_impl<N, T, Args...> : public tuple_impl<N + 1, Args...>{
public:
  using value_type = T;

private:
  using base = tuple_impl<N + 1, Args...>;

public:
  value_type data;

  /*! Default ctor
   */
  tuple_impl():
    data( value_type() ){
  }

  /*! Basic init ctor
   *
   * @tparam ...ARGS List of types for upcoming chain elements
   *
   * @param vt Data for this chain element
   *
   * @param args Arguments for future chain elements
   */
  template<typename ...ARGS>
  tuple_impl( value_type vt, ARGS... args ):
    base( std::forward<ARGS>( args )... ),
    data( vt ){
  }
};

/*! Containing tuple class
 *
 * @tparam ...Args
 *
 * Inherits from first element in actual tuple chain.  Tuple works as
 * template/compile-time linked list; this class is effectively a pointer to
 * the head.
 */
template<typename ...Args>
class tuple : public tuple_impl<0, Args...>{
private:
  using base = tuple_impl<0, Args...>;

public:
  /*! Default ctor
   */
  tuple():
    base(){
  }

  /*! Basic init ctor
   *
   * @tparam ...ARGS List of argument types to be passed into tuple implementation
   *
   * @param args List af arguments to be passed into tuple implementation
   */
  template<typename ...ARGS>
  tuple( ARGS... args ):
    base( std::forward<ARGS>( args )... ){
  }
};

/*! Tuple chain crawler
 *
 * @tparam M Remaining indexes to crawl
 *
 * @tparam N Current value index
 *
 * @tparam T Type of current chain link
 *
 * @tparam ...Args Remaining types in tuple
 */
template<size_t M, size_t N, typename T, typename ...Args>
class get_impl{
public:
  /*! Get data from a provided tuple
   *
   * @param tup Tuple to get data from
   *
   * @return Reference to requested value
   *
   * Crawl the tuple until the result is found
   */
  static auto& get( tuple_impl<N, T, Args...>& tup ){
    return get_impl<M - 1, N + 1, Args...>::get( static_cast<tuple_impl<N + 1, Args...>& >( tup ) );
  }

  /*! Get data from a provided tuple
   *
   * @param tup Tuple to get data from
   *
   * @return Const reference to requested value
   */
  static const auto& get( const tuple_impl<N, T, Args...>& tup ){
    return get_impl<M - 1, N + 1, Args...>::get( static_cast<const tuple_impl<N + 1, Args...>& >( tup ) );
  }
};

/*! Recursion terminator; gets the final value
 *
 * @tparam N Current link index
 *
 * @tparam T Type of current link
 *
 * @tparam ...Args Remaining types in tuple 
 *
 * If a tuple is thought of as a linked list, this is the final node from a get
 * operation.
 */
template<size_t N, typename T, typename ...Args>
class get_impl<0, N, T, Args...>{
public:
  /*! Get data from a provided tuple
   *
   * @param tup Tuple to get data from
   *
   * @return Reference to requested value
   *
   * Final location; where the requested value is stored.
   */
  static auto& get( tuple_impl<N, T, Args...>& tup ){
    return tup.data;
  }

  /*! Get data from a provided tuple
   *
   * @param tup Tuple to get data from
   *
   * @return Reference to requested value
   *
   * Final location; where the requested value is stored.
   */
  static const auto& get( const tuple_impl<N, T, Args...>& tup ){
    return tup.data;
  }
};

/*! Tuple getter method
 *
 * @tparam M Index of desired element from tup
 *
 * @tparam ...Args List of types in tup
 *
 * @param tup Tuple to get data from
 *
 * @return Reference to the data at M in tup
 */
template<size_t M, typename ...Args>
auto& get( tuple<Args...>& tup ){
  return get_impl<M, 0, Args...>::get( static_cast<tuple_impl<0, Args...>& >( tup ) );
}

/*! Tuple getter method
 *
 * @tparam M Index of desired element from tup
 *
 * @tparam ...Args List of types in tup
 *
 * @param tup Tuple to get data from
 *
 * @return Const reference to the data at M in tup
 */
template<size_t M, typename ...Args>
const auto& get( const tuple<Args...>& tup ){
  return get_impl<M, 0, Args...>::get( static_cast<const tuple_impl<0, Args...>& >( tup ) );
}

/*! Tuple factory method
 *
 * @tparam ...Args List of types to be given to the new tuple
 *
 * @param args List of data to give to the new tuple
 *
 * Using a factory method allows template type deduction to occur; useful when
 * many types are desired in the tuple, and it would appear nasty to specify
 * all of them.
 */
template<typename ...Args>
tuple<Args...> make_tuple( Args... args ){
  return tuple<Args...>( std::forward<Args>( args )... );
}

/*!
 * @tparam N
 *
 * @tparam T
 */
template<size_t N, typename T>
class tuple_element;

/*!
 * @tparam HEAD
 *
 * @tparam ...TAIL
 */
template<typename HEAD, typename ...TAIL>
class tuple_element<0, tuple<HEAD, TAIL...> >{
public:
  using type = HEAD;
};

/*!
 * @tparam N
 *
 * @tparam HEAD
 *
 * @tparam ...TAIL
 */
template<size_t N, typename HEAD, typename ...TAIL>
class tuple_element<N, tuple<HEAD, TAIL...> > : public tuple_element<N - 1, tuple<TAIL...> >{
};

}

#endif

