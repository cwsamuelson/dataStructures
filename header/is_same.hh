#ifndef __IS_SAME_HH__
#define __IS_SAME_HH__

template<typename T>
class is_same_helper{
public:
    constexpr bool operator==( is_same_helper<T> ){
        return true;
    }
    
    template<typename U>
    constexpr bool operator==( is_same_helper<U> ){
        return false;
    }
};

template<typename T, typename U>
class is_same{
public:
    const static bool value = is_same_helper<T>() == is_same_helper<U>();
};

#endif
