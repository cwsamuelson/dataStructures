#pragma once

#include <array>
#include <list>

// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0447r17.html
namespace flp {

struct hive_limits {
  size_t min, max;
  hive_limits(size_t minimum, size_t maximum) noexcept : min(minimum), max(maximum) {}
};


enum struct hive_priority { performance, memory_use };


template <class T, class Allocator = allocator<T>, hive_priority Priority = hive_priority::performance>
class hive {
public:
  // types
  using value_type = T;
  using allocator_type = Allocator;
  using pointer = typename allocator_traits<Allocator>::pointer;
  using const_pointer = typename allocator_traits<Allocator>::const_pointer;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = implementation-defined; // see 22.2
  using difference_type = implementation-defined; // see 22.2
  using iterator = implementation-defined; // see 22.2
  using const_iterator = implementation-defined; // see 22.2
  using reverse_iterator = implementation-defined; // see 22.2
  using const_reverse_iterator = implementation-defined; // see 22.2



  hive() noexcept(noexcept(Allocator())) : hive(Allocator()) { }
  explicit hive(std::hive_limits block_capacity_limits) noexcept(noexcept(Allocator())) : hive(Allocator()) { }
  explicit hive(const Allocator&) noexcept;
  explicit hive(std::hive_limits block_capacity_limits, const Allocator&) noexcept;
  explicit hive(size_type n, std::hive_limits block_capacity_limits = implementation-defined, const Allocator& = Allocator());
  hive(size_type n, const T& value, std::hive_limits block_capacity_limits = implementation-defined, const Allocator& = Allocator());
  template<class InputIterator1, class InputIterator2>
    hive(InputIterator1 first, InputIterator2 last, std::hive_limits block_capacity_limits = implementation-defined, const Allocator& = Allocator());
  hive(const hive& x);
  hive(hive&&) noexcept;
  hive(const hive&, const Allocator&);
  hive(hive&&, const Allocator&);
  hive(initializer_list<T>, std::hive_limits block_capacity_limits = implementation-defined, const Allocator& = Allocator());
  ~hive() noexcept;
  hive& operator= (const hive& x);
  hive& operator= (hive&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value);
  hive& operator= (initializer_list<T>);
  template<class InputIterator1, class InputIterator2> void assign(InputIterator1 first, InputIterator2 last);
  void assign(size_type n, const T& t);
  void assign(initializer_list<T>);
  allocator_type get_allocator() const noexcept;



  // iterators
  iterator               begin() noexcept;
  const_iterator         begin() const noexcept;
  iterator               end() noexcept;
  const_iterator         end() const noexcept;
  reverse_iterator       rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  reverse_iterator       rend() noexcept;
  const_reverse_iterator rend() const noexcept;

  const_iterator         cbegin() const noexcept;
  const_iterator         cend() const noexcept;
  const_reverse_iterator crbegin() const noexcept;
  const_reverse_iterator crend() const noexcept;


  // capacity
  [[nodiscard]] bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  size_type capacity() const noexcept;
  size_type memory() const noexcept;
  void reserve(size_type n);
  void shrink_to_fit();
  void trim() noexcept;


  // modifiers
  template <class... Args> iterator emplace(Args&&... args);
  iterator insert(const T& x);
  iterator insert(T&& x);
  void insert(size_type n, const T& x);
  template <class InputIterator1, class InputIterator2> void insert(InputIterator1 first, InputIterator2 last);
  void insert(initializer_list<T> il);
  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);
  void swap(hive&) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value);
  void clear() noexcept;


  // hive operations
  void splice(hive &x);

  std::hive_limits block_capacity_limits() const noexcept;
  void reshape(std::hive_limits block_capacity_limits);

  iterator get_iterator(pointer p) noexcept;
  const_iterator get_iterator(const_pointer p) const noexcept;

  void sort();
  template <class Compare> void sort(Compare comp);

  friend bool operator== (const hive &x, const hive &y);
  friend bool operator!= (const hive &x, const hive &y);


  class iterator
  {
    friend void advance(iterator &it, Distance n);
    friend iterator next(iterator it, difference_type distance = 1);
    friend iterator prev(iterator it, difference_type distance = 1);
    friend difference_type distance(iterator first, iterator last);
  }


  class const_iterator
  {
    friend void advance(const_iterator &it, Distance n);
    friend const_iterator next(const_iterator it, difference_type distance = 1);
    friend const_iterator prev(const_iterator it, difference_type distance = 1);
    friend difference_type distance(const_iterator first, const_iterator last);
  }


  class reverse_iterator
  {
    friend void advance(reverse_iterator &it, Distance n);
    friend reverse_iterator next(reverse_iterator it, difference_type distance = 1);
    friend reverse_iterator prev(reverse_iterator it, difference_type distance = 1);
    friend difference_type distance(reverse_iterator first, reverse_iterator last);
  }


  class const_reverse_iterator
  {
    friend void advance(const_reverse_iterator &it, Distance n);
    friend const_reverse_iterator next(const_reverse_iterator it, difference_type distance = 1);
    friend const_reverse_iterator prev(const_reverse_iterator it, difference_type distance = 1);
    friend difference_type distance(const_reverse_iterator first, const_reverse_iterator last);
  }


  // swap
  friend void swap(hive& x, hive& y)
    noexcept(noexcept(x.swap(y)));


  // erase
  template <class Predicate>
    friend size_type erase_if(hive& c, Predicate pred);
  template <class U>
    friend size_type erase(hive& c, const U& value);
}


template<class InputIterator, class Allocator = allocator<iter-value-type <InputIterator>>>
  hive(InputIterator, InputIterator, Allocator = Allocator())
    -> hive<iter-value-type <InputIterator>, Allocator>;

} // namespace flp
