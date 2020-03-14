#ifndef __ALLOCATOR_TRAITS_HH__
#define __ALLOCATOR_TRAITS_HH__

#include<utility>

namespace gsw {

/*! Generic traits of allocators
 *
 * @tparam Alloc Allocator type
 */
template<typename Alloc>
class allocator_traits {
public:
  using allocator_type = Alloc;
  using value_type = typename allocator_type::value_type;
  using size_type  = typename allocator_type::size_type;
  using pointer    = value_type*;
  using reference  = value_type&;

  /*! Allocate a number of objects
   *
   * @param alloc Allocator to allocate through
   *
   * @param number How many objects to allocate
   *
   * @return Pointer to the resulting allocation
   */
  [[nodiscard]]
  static pointer allocate(allocator_type& alloc, size_type number) {
    return alloc.allocate(number);
  }

  /*! Deallocate objects pointed to by ptr
   *
   * @param alloc Allocator used to allocate objects
   *
   * @param ptr Pointer to objects to be deallocated
   *
   * @param number Number of objects which were previously allocated
   */
  static void deallocate(allocator_type& alloc, pointer ptr, size_type number) {
    alloc.deallocate(ptr, number);
  }

  /*! Construct objects located in memory
   *
   * @tparam T Type of objects to be constructed
   *
   * @tparam ...Args Type of arguments being sent to constructor
   *
   * @param alloc Allocator used for allocation
   *
   * @param ptr Pointer to objects to be constructed
   *
   * @param args Arguments to forward to the object constructor
   */
  template<typename T, class ...Args>
  static void construct(allocator_type&, T* ptr, Args&& ... args) {
    ::new(ptr) value_type(std::forward<Args>(args)...);
  }

  /*! Destroy previously constructed objects
   *
   * @param alloc Allocator used for allocation
   *
   * @param ptr Pointer to objects to be destroyed
   */
  static void destroy(allocator_type&, pointer ptr) {
    ptr->~value_type();
  }
};

}

#endif
