#ifndef __TUPLE_H__
#define __TUPLE_H__

/*!
 * @example test-tuple.cc
 */

namespace gsw{

template<size_t N, class ...Args>
class tuple_impl;

template<size_t N, class T>
class tuple_impl<N, T>{
public:
  typedef T value_type;

  value_type data;

  tuple_impl():
    data( value_type() ){
  }
  tuple_impl( value_type vt ):
    data( vt ){
  }
};

template<size_t N, class T, class ...Args>
class tuple_impl<N, T, Args...> : public tuple_impl<N + 1, Args...>{
public:
  typedef T value_type;

private:
  typedef tuple_impl<N + 1, Args...> base;

public:
  value_type data;

  tuple_impl():
    data( value_type() ){
  }
  tuple_impl( value_type vt, Args ...args ):
    base( args... ),
    data( vt ){
  }
};

template<class ...Args>
class tuple : public tuple_impl<0, Args...>{
private:
  typedef tuple_impl<0, Args...> base;

public:
  tuple():
    base(){
  }
  tuple( Args... args ):
    base( args... ){
  }
};

template<size_t M, size_t N, class T, class ...Args>
class get_impl{
public:
  static auto& get( tuple_impl<N, T, Args...>& tup ){
    return get_impl<M - 1, N + 1, Args...>::get( static_cast<tuple_impl<N + 1, Args...>& >( tup ) );
  }
  static const auto& get( const tuple_impl<N, T, Args...>& tup ){
    return get_impl<M - 1, N + 1, Args...>::get( static_cast<const tuple_impl<N + 1, Args...>& >( tup ) );
  }
};

template<size_t N, class T, class ...Args>
class get_impl<0, N, T, Args...>{
public:
  static auto& get( tuple_impl<N, T, Args...>& tup ){
    return tup.data;
  }
  static const auto& get( const tuple_impl<N, T, Args...>& tup ){
    return tup.data;
  }};

template<size_t M, class ...Args>
auto& get( tuple<Args...>& tup ){
  return get_impl<M, 0, Args...>::get( static_cast<tuple_impl<0, Args...>& >( tup ) );
}

template<size_t M, class ...Args>
const auto& get( const tuple<Args...>& tup ){
  return get_impl<M, 0, Args...>::get( static_cast<const tuple_impl<0, Args...>& >( tup ) );
}

template<class ...Args>
tuple<Args...> make_tuple( Args... args ){
  return tuple<Args...>( args... );
}

template<size_t N, typename T>
class tuple_element;

template<class HEAD, class ...TAIL>
class tuple_element<0, tuple<HEAD, TAIL...> >{
public:
  typedef HEAD type;
};

template<size_t N, class HEAD, class ...TAIL>
class tuple_element<N, tuple<HEAD, TAIL...> >: public tuple_element<N - 1, tuple<TAIL...> >{
};

}

#endif

