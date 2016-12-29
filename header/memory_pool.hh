#ifndef __MEMORY_POOL_HH__
#define __MEMORY_POOL_HH__

#include<vector>

//TODO: add placement new/delete
template<class T>
class memoryPool{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef unsigned long size_type;
  static const size_type ptrdiff = sizeof( value_type );

private:
  size_type mSize;
  size_type mInUse;
  size_type mTotalBytes;
  char* mStorageStart;
  char* mStorageEnd;
  std::vector<bool> mSlots;
  std::vector<size_type> mSizes;
 
public:
  memoryPool( size_type size ):
    mSize( size ),
    mInUse( 0 ),
    mTotalBytes( mSize * ptrdiff ),
    mStorageStart( new char[mTotalBytes] ),
    mStorageEnd( mStorageStart + mTotalBytes - ptrdiff ),
    mSlots( mSize, false ),
    mSizes( mSize, 0 ){
  }
  virtual ~memoryPool(){ delete[] mStorageStart; }

  pointer allocate( size_type amt ){
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
        mSlots[i] = true;
      }
      mSizes[caveOpening] = amt;

      mInUse += amt;
      return ( pointer )&mStorageStart[caveOpening * ptrdiff];
    } else {
      return nullptr;
    }
  }

  void deallocate( pointer ptr ){
    if( ptr < ( pointer )mStorageStart || ptr > ( pointer )mStorageEnd ){
      return;
    }

    size_type idx = ( ptr - ( pointer )mStorageStart );
    for( size_type i = idx; i < idx + mSizes[idx]; ++i ){
      mSlots[i] = false;
    }
    mInUse -= mSizes[idx];
    mSizes[idx] = 0;
  }

  size_type in_use_count(){
    return mInUse;
  }
  size_type available_space(){
    return mSize - mInUse;
  }
};

#endif

