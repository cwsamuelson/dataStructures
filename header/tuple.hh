#ifndef __TUPLE_H__
#define __TUPLE_H__

template<unsigned int N, class ... Args>
class tuple_impl;

template<unsigned int N, class T>
class tuple_impl<N, T>{
public:
    T data;
};

template<unsigned int N, class T, class ... Args>
class tuple_impl<N, T, Args...> : public tuple_impl<N + 1, Args...>{
public:
    T data;
};

template<class ...Args>
class tuple : public tuple_impl<0, Args...>{    };

template<unsigned int M, unsigned int N, class T, class ... Args>
class get_impl{
public:
    static auto& get(tuple_impl<N, T, Args...>& tup){
        return get_impl<M - 1, N + 1, Args...>::get(static_cast<tuple_impl<N + 1, Args...>& >(tup));
    }
};

template<unsigned int N, class T, class ... Args>
class get_impl<0, N, T, Args...>{
public:
    static auto& get(tuple_impl<N, T, Args...>& tup){
        return tup.data;
    }
};

template<unsigned int M, class ... Args>
auto& get(tuple<Args...>& tup){
    return get_impl<M, 0, Args...>::get(static_cast<tuple_impl<0, Args...>& >(tup));
}


#endif

