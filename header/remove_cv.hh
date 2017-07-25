#ifndef __REMOVE_CV_HH__
#define __REMOVE_CV_HH__

namespace gsw{

template<typename T>
class remove_const{
public:
  using type = T;
};

template<typename T>
class remove_const<const T>{
public:
  using type = T;
};

template<typename T>
class remove_volatile{
public:
  using type = T;
};

template<typename T>
class remove_volatile<volatile T>{
public:
  using type = T;
};

template<typename T>
class remove_cv{
public:
  using type = typename remove_const<typename remove_volatile<T>::type>::type;
};

}

#endif

