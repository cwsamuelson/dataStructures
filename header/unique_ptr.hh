#ifndef __UNIQUE_PTR_HH__
#define __UNIQUE_PTR_HH__

namespace gsw{

/*! Enforced unique pointer to some data
 * @tparam T  Type to which a pointer will be stored
 *
 * Store a pointer of which no copies can be made.  This class enforces the
 * uniquity of a particular pointer.  It can be moved around etc, but only one
 * copy persists, and will be automatically destroyed at the end of the objects
 * lifespan.
 */
template<class T>
class unique_ptr{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef value_type* pointer;

private:
  pointer mData;

public:
  /*! Basic ctor
   *
   * @param ptr  pointer to be stored
   */
  unique_ptr( pointer ptr = nullptr ):
    mData( ptr ){
  }

  /*! Move ctor
   *
   * @param other
   *
   * Performs a move operation
   */
  unique_ptr( unique_ptr&& other ):
    mData( other.mData ){
    other.mData = nullptr;
  }

  /*! Dtor
   *
   * Delete data, if any still exists
   */
  virtual ~unique_ptr(){
    if( mData ){
      delete mData;
    }
  }

  unique_ptr& operator=( pointer other ){
    if( mData ){
      delete mData;
    }
    mData = other;

    return *this;
  }
  unique_ptr& operator=( unique_ptr&& other ){
    if( mData != other.mData && mData ){
      delete mData;

      mData = other.mData;
      other.mData = nullptr;
    }

    return *this;
  }

  /*! Equality operator
   *
   * @param other rhs of equality operator
   *
   * @return whether other is equal to the stored pointer
   */
  bool operator==( pointer other ) const{
    return ( mData == other );
  }

  /*! Equality operator
   *
   * @param other  rhs of equality operator
   *
   * @return whether the pointer stored in other is equal to this instance stored pointer
   *
   * While a valid operation, and will return expected results, this operation
   * contradicts the very concept of this class.  This class is intended to
   * store a unique instance to a pointer, another instance of the same pointer
   * is a contradiction.
   */
  bool operator==( const unique_ptr& other ) const{
    return ( mData == other.mData );
  }
  
  /*! Dereference operator
   *
   * @return reference to stored object
   *
   * Dereference stored pointer, and return reference to stored object
   */
  reference operator*(){
    return *mData;
  }
  
  pointer operator->(){
    return mData;
  }

  pointer get(){
    return mData;
  }

  /*! Release control
   *
   * @return The stored pointer
   *
   * Relinquish control of and return the stored pointer. No memory management
   * is done; so if the return value is not captured, and subsequently deleted
   * a memory leak will occur.
   */
  pointer release(){
    pointer ret = mData;
    mData = nullptr; 

    return ret;
  }
};

template<class T, class ...Args>
unique_ptr<T> make_unique( Args... args ){
  return new T( args... );
}

}

#endif

