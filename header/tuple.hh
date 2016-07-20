#ifndef __TUPLE_H__
#define __TUPLE_H__

template<unsigned int N, class ... Args>
class tuple_impl;

template<unsigned int N, class T>
class tuple_impl<N, T>{
public:
  typedef T value_type;

  value_type data;

  tuple_impl():
    data(value_type()){
  }
  tuple_impl(value_type vt):
    data(vt){
  }
};

template<unsigned int N, class T, class ... Args>
class tuple_impl<N, T, Args...> : public tuple_impl<N + 1, Args...>{
public:
  typedef T value_type;

private:
  typedef tuple_impl<N + 1, Args...> base;

public:
  value_type data;

  tuple_impl():
    data(value_type()){
  }
  tuple_impl(value_type vt, Args ...args):
    base(args...),
    data(vt){
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
  tuple(Args... args):
    base(args...){
  }
};

template<unsigned int M, unsigned int N, class T, class ... Args>
class get_impl{
public:
  static auto& get(tuple_impl<N, T, Args...>& tup){
    return get_impl<M - 1, N + 1, Args...>::get(static_cast<tuple_impl<N + 1, Args...>& >(tup));
  }
  static const auto& get(const tuple_impl<N, T, Args...>& tup){
    return get_impl<M - 1, N + 1, Args...>::get(static_cast<const tuple_impl<N + 1, Args...>& >(tup));
  }
};

template<unsigned int N, class T, class ... Args>
class get_impl<0, N, T, Args...>{
public:
  static auto& get(tuple_impl<N, T, Args...>& tup){
    return tup.data;
  }
  static const auto& get(const tuple_impl<N, T, Args...>& tup){
    return tup.data;
  }};

template<unsigned int M, class ... Args>
auto& get(tuple<Args...>& tup){
  return get_impl<M, 0, Args...>::get(static_cast<tuple_impl<0, Args...>& >(tup));
}

template<unsigned int M, class ... Args>
const auto& get(const tuple<Args...>& tup){
  return get_impl<M, 0, Args...>::get(static_cast<const tuple_impl<0, Args...>& >(tup));
}

template<class X, class Y>
tuple<X, Y> make_tuple(X x, Y y){
  return tuple<X, Y>(x, y);
}

#endif

