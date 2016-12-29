#ifndef __MEMORY_POOL_HH__
#define __MEMORY_POOL_HH__

#include<list>

//TODO: switch from value_type to char
template<class T>
class memoryPool{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef unsigned long size_type;
  static const size_type ptrdiff = sizeof( value_type );

private:
  class slot{
  public:
    pointer start;
    pointer end;

    slot( pointer first, pointer second ):
      start( first ),
      end( second ){
    }

    bool operator<( const slot& rhs ){
      return start < rhs.start;
    }
  };
 
  size_type mSize;
  size_type mInUse;
  size_type mTotalBytes;
  char* mStorageStart;
  char* mStorageEnd;
  std::list<slot> mSlots;
 
public:
  memoryPool( size_type size ):
    mSize( size ),
    mInUse( 0 ),
    mTotalBytes( mSize * ptrdiff ),
    mStorageStart( new char[mTotalBytes] ),
    mStorageEnd( mStorageStart + mTotalBytes - ptrdiff ){
  }
  virtual ~memoryPool(){ delete[] mStorageStart; }

  pointer allocate( size_type amt ){
    pointer ret = nullptr;
    size_type allocSize = amt * ptrdiff;
    //If the request is larger than that available, return null;
    if( amt == 0 || ( amt > ( mSize - mInUse ) )  ){
      ret = nullptr;
    } else {
      //Determine where free memory exists to return;
      //If there's no memory in use, return beginning;
      if( mSlots.size() == 0 ){
        mSlots.emplace_back( ( pointer )mStorageStart, ( pointer )( mStorageStart + allocSize ) );
        ret = ( value_type* )mStorageStart;
      } else if( mSlots.begin()->start != ( pointer )mStorageStart ){
        if( ( size_type )( mSlots.begin()->start - ( pointer )mStorageStart ) >= allocSize ){
          mSlots.emplace_back( ( pointer )mStorageStart, ( pointer )( mStorageStart + allocSize ) );
          ret = ( value_type* )mStorageStart;
        }
      } else {
        auto first = mSlots.begin();
        for( auto second = ++mSlots.begin(); second != mSlots.end(); ++second, ++first ){
          if( ( size_type )( second->start - first->end ) >= allocSize ){
            ret = ( value_type* )first->end;
            break;
          }
        }
        //If we get to the end of the list and there's no free space found,
        //  check the tail end;
        if( ( size_type )( ( pointer )mStorageEnd - first->end ) >= amt ){
          mSlots.emplace_back( first->end, first->end + allocSize );
          ret = ( value_type* )first->end;
        }
      }
      //Only re-sort when new things have been added;
      if( ret ){
        mSlots.sort();
      }
    }

    if( ret ){
      mInUse += amt;
    }
    return ret;
  }

  void deallocate( pointer ptr ){
    for( auto it = mSlots.begin(); it != mSlots.end(); ++it ){
      if( it->start == ptr ){
        mInUse -= ( it->end - it->start ) / ptrdiff;
        mSlots.erase( it );
        break;
      }
    }
  }

  size_type in_use_count(){
    return mInUse;
  }
  size_type available_space(){
    return mSize - mInUse;
  }
};

#endif

