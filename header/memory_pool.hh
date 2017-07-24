#ifndef __MEMORY_POOL_HH__
#define __MEMORY_POOL_HH__

/*!
 * @example test-mempool.cc
 */

#include<vector>

namespace gsw{

/*!
 * @tparam T
 */
template<typename T>
class memoryPool{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef unsigned long size_type;
  typedef char storage_type;
  typedef char* storage_ptr;
  static const size_type ptrdiff = sizeof( value_type );

private:
  size_type mSize;
  size_type mInUse;
  storage_ptr mStorageStart;
  storage_ptr mStorageEnd;
  std::vector<bool> mSlots;
  std::vector<size_type> mSizes;
 
public:
  /*!
   * @param size
   */
  memoryPool( size_type size ):
    mSize( size ),
    mInUse( 0 ),
    mStorageStart( new storage_type[mSize * ptrdiff] ),
    mStorageEnd( mStorageStart + ( mSize * ptrdiff ) - ptrdiff ),
    mSlots( mSize, false ),
    mSizes( mSize, 0 ){
  }

  /*!
   */
  virtual ~memoryPool(){
    delete[] mStorageStart;
  }

  /*!
   */
  template<typename ...Args>
  pointer allocate( size_type amt, Args... args ){
    size_type caveSize = 0;
    bool caveFound = false;
    size_type caveOpening = 0;

    for( unsigned int i = 0; i < mSize; ++i ){
      if( !mSlots[i] ){
        if( ++caveSize == amt ){
          caveFound = true;
          break;
        }
      } else {
        caveOpening = i + 1;
      }
    }

    if( caveFound ){
      for( size_type i = caveOpening; i < caveOpening + amt; ++i ){
        new( mStorageStart + ( caveOpening * ptrdiff ) ) value_type( std::forward<Args>( args )...);
        mSlots[i] = true;
      }
      mSizes[caveOpening] = amt;

      mInUse += amt;
      return ( pointer )&mStorageStart[caveOpening * ptrdiff];
    } else {
      return nullptr;
    }
  }

  /*!
   */
  void deallocate( pointer ptr ){
    if( ptr < ( pointer )mStorageStart || ptr > ( pointer )mStorageEnd ){
      return;
    }

    size_type idx = ( ptr - ( pointer )mStorageStart );
    for( size_type i = idx; i < idx + mSizes[idx]; ++i ){
      ( ( value_type* )( mStorageStart + ( idx * ptrdiff ) ) )->~value_type();
      mSlots[i] = false;
    }
    mInUse -= mSizes[idx];
    mSizes[idx] = 0;
  }

  /*!
   */
  size_type in_use_count(){
    return mInUse;
  }

  /*!
   */
  size_type available_space(){
    return mSize - mInUse;
  }
};

}

#endif

