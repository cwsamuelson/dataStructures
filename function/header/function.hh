#ifndef __FUNCTION_HH__
#define __FUNCTION_HH__

/*!
 * @example test-functional.cc
 */
#include<memory>
#include<utility>

#include<tuple.hh>

namespace gsw {

template<typename T>
class function;

/*! General functor class
 *
 * @tparam R  Type of the functor result
 *
 * @tparam ...Args  Parameter pack of argument types
 *
 * Function pointer wrapper
 */
template<typename R, typename ...Args>
class function<R(Args...)> {
public:
  typedef R( * func )(Args...);

  typedef R result;

  typedef tuple<Args...> args;

private:
  class interface {
  public:
    virtual result operator()(Args...) = 0;
  };

  template<typename T>
  class wrapper : public interface {
  private:
    T mUnder;

  public:
    wrapper(const T& t)
            : mUnder(t) {
    }

    result operator()(Args... args) {
      return mUnder(std::forward<Args>(args)...);
    }
  };

  std::shared_ptr<interface> f;

public:
  /*!
   */
  function() = default;

  /*! Ctor
   *
   * @param parm  function pointer to bo stored
   *
   * Store provided function pointer
   */
  template<typename T>
  function(const T& t)
          : f(t) {
  }

  /*! Function call operator
   *
   * @param args  Parameter pack of arguments to stored function
   *
   * Call stored function with provided arguments
   */
  result operator()(Args... args) {
    return f->operator()(std::forward<Args>(args)...);
  }

  /*! Copy assignment operator
   *
   * @param rhs  Function object to be copied
   *
   * Store the function pointer stored in rhs
   */
  function& operator=(const function& rhs) {
    f = rhs.f;
    return *this;
  }

  /*! Assignment operator
   *
   * @param F  Function pointer to be saved
   *
   * Store function pointer F
   */
  template<typename T>
  function& operator=(const T& t) {
    f = std::make_shared<wrapper<T>>(t);

    return *this;
  }

  template<typename R1, typename ...Args1>
  function& operator=(R1(* t)(Args...)) {
    f = std::make_shared<wrapper<R1(*)(Args...)>>(t);

    return *this;
  }
};

}

#endif
