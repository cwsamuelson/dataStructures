#ifndef __ACCESSOR_HH__
#define __ACCESSOR_HH__

/*!
 * @example test-accessor.cc
 */

#include<functional>

namespace gsw{

/*! Accessor to allow access to internal members
 *
 * @tparam T  Type of reference to be stored
 *
 * Allows access to an internal member, and yet maintain control over said
 * member's modification using a callback.  In construction an object reference
 * and a callback are received; the stored callback will be executed on
 * assignment, and dictates whether the assignment will occur, and allows for
 * preparation before assignment.
 */
template<typename T>
class accessor{
public:
  /*! Stored type
   */
  using value_type = T;

  /*! Ref shorthand
   */
  using reference = value_type&;

  /*! Cref shorthand
   */
  using const_reference = const value_type&;

  /*! Callback definition
   *
   * Type of callback that will be called when this is assigned to.  Also type
   * taken as a parameter to ctor.
   */
  using callback = std::function<bool( value_type )>;

private:
  reference mRef;
  callback mcb;

public:
  /*! ctor simply storing the ref and assignment callback
   *
   * @param ref  Reference to an object to store
   *
   * @param cb  A callback to be run on assignment
   *
   * The reference will be stored, and will be assigned to when this object is
   * assigned to.  The callback dictates whether assignment will actually occur
   * based upon the value that was to be assigned.
   */
  accessor( reference ref, callback cb )
    : mRef( ref )
    , mcb( cb ){
  }

  /*! Value_type operator allowing usage as raw stored type
   */
  operator value_type(){
    return mRef;
  }

  /*!
   */
  operator const value_type() const{
    return mRef;
  }

  /*! Assignment operator, assigns to stored reference
   *
   * @param cref  New value to be assigned
   *
   * @return Reference to stored value; will equal cref if call to mcb returns true
   *
   * Conditionally assigns new value to stored reference, based upon the result
   * of the callback function provided at construction.
   */
  reference operator=( const_reference cref ){
    if( mcb( cref ) ){
      mRef = cref;
    }

    return mRef;
  }

  /*! Move assignment operator, moves to stored reference
   *
   * @param other  New value to be moved
   *
   * @return Reference to stored value; will equal cref if call to mcb returns true
   *
   * Conditionally moves new value to stored reference, based upon the result
   * of the callback function provided at construction.
   */
  template<typename U>
  reference operator=( U&& other ){
    if( mcb( other ) ){
      mRef = std::forward<U>( other );
    }

    return mRef;
  }
};

}

#endif
