#ifndef __BLOCK_ALLOCATOR_HH__
#define __BLOCK_ALLOCATOR_HH__

#include<bitset>

namespace gsw{

class block_allocation_exception : public std::excepion{
public:
  virtual const char* what() const noexcept{
    return "Allocation size too large!";
  }
};

template<typename T, size_t SIZE = 1>
class block_allocator{
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long long;

private:
  static const size_type alloc_size = SIZE;
  static const size_type block_size = alloc_size * sizeof( value_type );

  struct block_node{
    unsigned char block[block_size];
    std::bitset<alloc_size> indicator;
    block_node* next;
  };

  block_node* mStart;

public:
  block_allocator():
    mStart( nullptr ){
  }

  /*!
   * @todo implement this
   */
  block_allocator( const block_allocator& other ) = delete;

  block_allocator( block_allocator&& other ){
    mStart = other.mStart;

    other.mStart = nullptr;
  }

  pointer allocate( size_type number ){
    if( number > alloc_size ){
      throw block_allocation_exception();
    }

    if( mStart == nullptr ){
      mStart = new block_node;
      mStart->next = nullptr;
    }

    block_node* current = mStart;
    bool space_found = false;
    while( !space_found ){
      if( current->indicator.all() ){
        current->next = new block_node;
        current = current->next;

        for( unsigned int i = 0; i < number; ++i ){
          current->indicator[i] = true;
        }

        return current->block;
      }//TODO: calculate a cave, and return cave
    }
  }

  void deallocate( pointer ptr, size_type number ){
    block_node* current = mStart;

    if( ( ptr > current->block ) &&
        ( ( ptr + number ) <= ( current->block + block_size ) ) ){
      
    }
  }
};

}

#endif

