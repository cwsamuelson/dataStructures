#ifndef __ENABLE_IF_HH__
#define __ENABLE_IF_HH__

namespace gsw{

template<bool B, typename T = void>
class enable_if{
};

template<typename T>
class enable_if<true, T>{
public:
  using type = T;
};

}

#endif

