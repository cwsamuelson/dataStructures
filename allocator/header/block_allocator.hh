#ifndef __BLOCK_ALLOCATOR_HH__
#define __BLOCK_ALLOCATOR_HH__

#include<bitset>
#include<exception>

#include<header/static_allocator.hh>

namespace gsw{

/*! Allocate memory blocks at a time
 *
 * @tparam T Type of objects to be stored in a block
 *
 * @tparam SIZE
 */
template<typename T, size_t SIZE = 1>
class block_allocator{
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long long;
  static const size_type ptrdiff = sizeof( value_type );

private:
  static const size_type alloc_size = SIZE;
  static const size_type block_size = alloc_size * ptrdiff;

  struct block_node{
    static_allocator<value_type, alloc_size> alloc;
    block_node* next = nullptr;
  };

  void
  clear( block_node* node ){
    if( node->next != nullptr ){
      clear( node->next );
    }

    delete node;
  }

  block_node* mStart = nullptr;

public:
  /*!
   */
  block_allocator() = default;

  /*!
   * @todo implement this
   */
  block_allocator( const block_allocator& other ) = delete;

  block_allocator( block_allocator&& other )
    : mStart( other.mStart ){
    other.mStart = nullptr;
  }

  /*!
   */
  ~block_allocator(){
    clear( mStart );
  }

  /*!
   *
   * @param number
   */
  pointer
  allocate( size_type number ){
    if( number > alloc_size ){
      throw std::bad_alloc();
    }

    if( mStart == nullptr ){
      mStart = new block_node;
      mStart->next = nullptr;
    }

    block_node* current = mStart;
    block_node* last;
    do{
      try{
        return current->alloc.allocate( number );
      } catch( std::bad_alloc& ){
        last = current;
        current = current->next;
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
  void
  deallocate( pointer ptr, size_type number ){
    if( mStart == nullptr ){
      throw std::bad_alloc();
    }

    block_node* current = mStart;

    // find which block node the pointer is in
    while( !( ( ptr >= current->alloc.storage() ) &&
              ( ptr < ( ( void* )current->alloc.storage() + block_size ) ) ) ){
      current = current->next;

      // couldn't find.  not our pointer to deallocate.
      if( current == nullptr ){
        throw std::bad_alloc();
      }
    }

    current->alloc.deallocate( ptr, number );
  }
};

}

#endif
