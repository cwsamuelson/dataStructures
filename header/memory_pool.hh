#ifndef __MEMORY_POOL_HH__
#define __MEMORY_POOL_HH__

#include<list>

//TODO: investigate whether stored data should be value_type or unsigned char
//        using value_type may( probably does ) call constructors, which is not 
//        desired in this case.  placement new is most likely scenario
template<class T>
class memoryPool{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef unsigned long size_type;

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
 
  pointer mStorageStart;
  void* mStorageEnd;
  size_type mSize;
  size_type mInUse;
  std::list<slot> mSlots;
 
public:
  memoryPool( size_t size ):
    mStorageStart( new value_type[size] ),
    mStorageEnd( mStorageStart + size - 1 ),
    mSize( size ),
    mInUse( 0 ){
  }
  virtual ~memoryPool(){ delete[] mStorageStart; }

  pointer allocate( size_type amt ){
    pointer ret = nullptr;
    //If the request is larger than that available, return null;
    if( amt == 0 || ( amt > ( mSize - mInUse ) )  ){
      ret = nullptr;
    } else {
      //Determine where free memory exists to return;
      //If there's no memory in use, return beginning;
      if( mSlots.size() == 0 ){
        mSlots.emplace_back( mStorageStart, mStorageStart + amt );
        ret = mStorageStart;
      } else if( mSlots.begin()->start != mStorageStart ){
        if( ( size_t )( mSlots.begin()->start - mStorageStart ) >= amt ){
          mSlots.emplace_back( mStorageStart, mStorageStart + amt );
          ret = mStorageStart;
        }
      } else {
        auto first = mSlots.begin();
        for( auto second = ++mSlots.begin(); second != mSlots.end(); ++second, ++first ){
          if( ( size_t )( second->start - first->end ) >= amt ){
            ret = first->end;
            break;
          }
        }
        //If we get to the end of the list and there's no free space found,
        //  check the tail end;
        if( ( size_t )( ( mStorageStart + mSize ) - first->end ) >= amt ){
          mSlots.emplace_back( first->end, first->end + amt );
          ret = first->end;
        }
      }
      //Only re-sort when new things have been added;
      mSlots.sort();
    }

    if( ret ){
      mInUse += amt;
    }
    return ret;
  }

  void deallocate( pointer ptr ){
    for( auto it = mSlots.begin(); it != mSlots.end(); ++it ){
      if( it->start == ptr ){
        mInUse -= ( it->end - it->start ) / sizeof( value_type ) + 1;
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

