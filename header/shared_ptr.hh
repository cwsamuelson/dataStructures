#ifndef __SHARED_PTR_HH__
#define __SHARED_PTR_HH__

/*!
 * @example test-shared.cc
 */

namespace gsw{

template<class T>
class shared_ptr{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef unsigned long count_t;

private:
  pointer mData;
  count_t* mCount;

public:
  shared_ptr():
    mData( nullptr ),
    mCount( nullptr ){
  }
  shared_ptr( pointer ptr ):
    mData( ptr ){
    if( mData != nullptr ){
      mCount = new count_t( 1 );
    } else {
      mCount = nullptr;
    }
  }
  shared_ptr( const shared_ptr& other ):
    mData( other.mData ),
    mCount( other.mCount ){
    ++( *mCount );
  }
  shared_ptr( shared_ptr&& other ):
    mData( other.mData ),
    mCount( other.mcount ){

    other.mData = nullptr;
    other.mCount = nullptr;
  }
  virtual ~shared_ptr(){
    if( ( mCount != nullptr ) &&
        ( --( *mCount ) == 0 ) ){
      delete mData;
      delete mCount;
    }
  }

  shared_ptr& operator=( pointer other ){
    if( mData != other ){
      if( ( mCount != nullptr ) &&
          ( --( *mCount ) == 0 ) ){
        delete mData;
        delete mCount;
      }
      mData = other;
      mCount = new count_t( 1 );
    }
    return *this;
  }
  shared_ptr& operator=( shared_ptr& other ){
    if( mData != other.mData ){
      if( --( *mCount ) == 0 ){
        delete mData;
        delete mCount;
      }
      mData = other.mData;
      mCount = other.mCount;
      ++( *mCount );
    }
    return *this;
  }
  shared_ptr& operator=( shared_ptr&& other ){
    mData = other.mData;
    mCount = other.mCount;

    other.mData = nullptr;
    other.mCount = nullptr;
  }

  bool operator==( pointer other ) const{
    return mData == other;
  }
  bool operator==( const shared_ptr& other ) const{
    return ( mData == other.mData ) && ( mCount == other.mCount );
  }
  
  reference operator*(){
    return *mData;
  }
  
  pointer operator->(){
    return mData;
  }
};

template<class T, class ... Args>
shared_ptr<T> make_shared( Args ...args ){
  T* temp = new T( args... );

  return shared_ptr<T>( temp );
}

}

#endif

