#ifndef __IS_VOID_HH__
#define __IS_VOID_HH__

#include<integral_constant.hh>

namespace gsw{

template<typename T>
class is_void : public bool_constant<false>{ };

template<>
class is_void<void> : public bool_constant<true>{ };

}

#endif
