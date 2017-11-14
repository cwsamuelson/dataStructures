#ifndef __BLOCK_ALLOCATOR_HH__
#define __BLOCK_ALLOCATOR_HH__

#include<bitset>
#include<exception>

#include<static_allocator.hh>

namespace gsw{

class block_allocation_exception : public std::exception{
public:
  virtual const char* what() const noexcept{
    return "Allocation size too large!";
  }
};

/*! Allocate memory blocks at a time
 *
 * @tparam T Type of objects to be stored in a block
 *
 * @tparam SIZE
 *
 */
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
    static_allocator<value_type, alloc_size> alloc;
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

  /*!
   *
   * @param number
   */
  pointer allocate( size_type number ){
    if( number > alloc_size ){
      throw block_allocation_exception();
    }

    if( mStart == nullptr ){
      mStart = new block_node;
      mStart->next = nullptr;
    }

    block_node* current = mStart;
    block_node* last;
    do{
      if( current->alloc.free_space( number ) ){
        try{
          return current->alloc.allocate( number );
        } catch( bad_alloc& ){
          last = current;
          current = current->next;
        }
      }
    } while( current != nullptr );

    // if a node with space exists, it should have been found.
    // if not, create it now
    current = last;
    current->next = new block_node;
    current = current->next;
    return current->alloc.allocate( number );
  }

  /*!
   *
   * @param ptr
   *
   * @param number
   */
  void deallocate( pointer ptr, size_type number ){
    if( mStart == nullptr ){
      throw block_allocation_exception();
    }

    block_node* current = mStart;

    // find which block node the pointer is in
    while( !( ( ptr >= current->alloc.storage() ) &&
              ( ( ptr + number ) < ( current->alloc.storage() + block_size ) ) ) ){
      current = current->next;

      // couldn't find.  not our pointer to deallocate.
      if( current == nullptr ){
        throw block_allocation_exception();
      }
    }

    current->alloc.deallocate( ptr, number );
  }
};

}

#endif

