#ifndef __REFERENCE_WRAPPER_HH__
#define __REFERENCE_WRAPPER_HH__

/*!
 * @example test-wrapper.cc
 */

namespace gsw{

/*! Wrapper around a reference type
 *
 * @tparam T Type of stored reference
 *
 * The fundamental use is to enable the storage of references in std and gsw
 * types. For example
 * vector<int&>
 * is illegal, but
 * vector<reference_wrapper<int> >
 * is legal.
 */
template<typename T>
class reference_wrapper{
public:
  /*! Type of stored reference
   */
  typedef T value_type;
  /*! Stored type; reference to value_type
   */
  typedef value_type& reference;
  /*! Const reference to value_type
   */
  typedef const value_type& const_ref;

private:
  reference mRef;

public:
  /*! Basic ctor
   *
   * @param ref Reference to be 'stored'
   */
  reference_wrapper( reference ref )
    : mRef( ref ){
  }

  /*! Get wrapped reference
   */
  operator reference(){
    return mRef;
  }

  /*!
   */
  operator const_ref() const{
    return mRef;
  }

  /*! Get wrapped reference
   */
  reference
  get(){
    return mRef;
  }

  /*! Get const version of wrapped reference
   */
  const reference
  cget() const{
    return mRef;
  }
};

}

#endif
