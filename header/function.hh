#ifndef __FUNCTION_HH__
#define __FUNCTION_HH__

/*!
 * @example test-functional.cc
 */

#include<tuple.hh>

namespace gsw{

template<class T>
class function;

/*! General functor class
 *
 * @tparam R  Type of the functor result
 *
 * @tparam ...Args  Parameter pack of argument types
 *
 * Function pointer wrapper
 */
template<class R, class ...Args>
class function<R( Args... )>{
public:
  typedef R( *func )( Args... );
  typedef R result;
  typedef tuple<Args...> args;

private:
  func f;

public:
  /*! Ctor
   *
   * @param parm  function pointer to bo stored
   *
   * Store provided function pointer
   */
  function( func parm = nullptr ):
    f( parm ){
  }
  
  /*! Function call operator
   *
   * @param args  Parameter pack of arguments to stored function
   *
   * Call stored function with provided arguments
   */
  R operator()( Args... args ){
    return f( args... );
  }
  
  /*! Copy assignment operator
   *
   * @param rhs  Function object to be copied
   *
   * Store the function pointer stored in rhs
   */
  function& operator=( const function& rhs ){
    f = rhs.f;
    return *this;
  }

  /*! Assignment operator
   *
   * @param F  Function pointer to be saved
   *
   * Store function pointer F
   */
  function& operator=( func F ){
    f = F;
    return *this;
  }
};

}

#endif

