#ifndef __LAMBDA_HH__
#define __LAMBDA_HH__

namespace gsw {

struct Zero {
  enum { value = 0 };
};

template<typename T>
struct literal {};

struct True {};
struct False {};

template<typename cond, typename then, typename els>
struct If {};

struct empty_env {};

template<typename name, typename body>
struct lambda {};

template<typename lmda, typename environment>
struct closure {};

template<typename name>
struct ref {};

template<typename expression, typename environment>
struct eval {};

template<typename proc, typename value>
struct apply {};

template<typename fn, typename arg>
struct app {};


template<typename N, int M = 1>
struct succeed {
  enum { value = N::value + M };
};

template<typename N> using increment = succeed<N, 1>;

template<typename N> using decrement = succeed<N, -1>;

// bind value to a name
// chains of bindings constitute an environment
template<typename name, typename value, typename environment = empty_env>
struct binding {};

// basic lookup signature
template<typename name, typename environment>
struct lookup {};

// failed lookup
template<typename name>
struct lookup<name, empty_env> {};

// successful lookup
template<typename name, typename value, typename environment>
struct lookup<name, binding<name, value, environment>> {
  using result = value;
};

// continuing lookup
template<typename name, typename name2, typename value, typename environment>
struct lookup<name, binding<name2, value, environment>> {
  using result = typename lookup<name, environment>::result;
};


template<typename name, typename body, typename environment>
struct eval<lambda<name, body>, environment> {
  using result = closure<lambda<name, body>, environment>;
};

template<typename name, typename environment>
struct eval<ref<name>, environment> {
  using result = typename lookup<name, environment>::result;
};

template<typename T, typename environment>
struct eval<literal<T>, environment> {
  using result = T;
};

template<typename then, typename els, typename environment>
struct eval<If<True, then, els>, environment> {
  using result = then;
};

template<typename then, typename els, typename environment>
struct eval<If<False, then, els>, environment> {
  using result = els;
};

template<typename cond, typename then, typename els, typename environment>
struct eval<If<cond, then, els>, environment> {
  using result = typename eval<If<typename eval<cond, environment>::result, then, els>, environment>::result;
};

template<typename name, typename body, typename value, typename environment>
struct apply<closure<lambda<name, body>, environment>, value> {
  using result = typename eval<body, binding<name, value, environment>>::result;
};

template<typename fn, typename arg, typename environment>
struct eval<app<fn, arg>, environment> {
  using result = typename apply<typename eval<fn, environment>::result,
                                typename eval<arg, environment>::result>::result;
};

}

#endif

