#ifndef __ACCESSOR_HH__
#define __ACCESSOR_HH__

#include<functional>

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
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::function<bool(value_type)> callback;

private:
  reference mRef;
  callback mcb;

public:
  /*! ctor simply storing the ref and assignment callback
   *
   * @param ref  Reference to an object to store
   *
   * @param cb  A callback to be run on assignment
   */
  accessor( reference ref, callback cb ):
    mRef( ref ),
    mcb( cb ){
  }

  /*! Value_type operator allowing usage as raw stored type
   */
  operator value_type(){
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
  reference operator=( value_type&& other ){
    if( mcb( other ) ){
      mRef = std::forward<value_type>( other );
    }
    return mRef;
  }

  /*! Equality check operator
   *
   * @param cref  Value for stored reference to be compared against
   *
   * @return Whether cref is equal to mRef 
   *
   * Allows for convenient comparison against stored reference. 
   */
  bool operator==( const_reference cref ){
    return mRef == cref;
  }
};

#endif

