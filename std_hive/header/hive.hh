#pragma once

#include <array>
#include <list>

// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0447r17.html
namespace flp {

struct hive_limits {
  size_t    min;
  size_t    max;
  constexpr hive_limits(size_t minimum, size_t maximum) noexcept
    : min(minimum)
    , max(maximum) {}
};


template<class T, class Allocator = allocator<T>>
class hive {
private:
  hive_limits current - limits = implementation - defined; // exposition only

public:
  // types
  using value_type             = T;
  using allocator_type         = Allocator;
  using pointer                = typename allocator_traits<Allocator>::pointer;
  using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
  using reference              = value_type&;
  using const_reference        = const value_type&;
  using size_type              = implementation - defined; // see [container.requirements]
  using difference_type        = implementation - defined; // see [container.requirements]
  using iterator               = implementation - defined; // see [container.requirements]
  using const_iterator         = implementation - defined; // see [container.requirements]
  using reverse_iterator       = std::reverse_iterator<iterator>; // see [container.requirements]
  using const_reverse_iterator = std::reverse_iterator<const_iterator>; // see [container.requirements]


  constexpr hive() noexcept(noexcept(Allocator()))
    : hive(Allocator()) {}
  explicit hive(const Allocator&) noexcept;
  explicit hive(hive_limits block_limits)
    : hive(block_limits, Allocator()) {}
           hive(hive_limits block_limits, const Allocator&);
  explicit hive(size_type n, const Allocator& = Allocator());
           hive(size_type n, hive_limits block_limits, const Allocator& = Allocator());
           hive(size_type n, const T& value, const Allocator& = Allocator());
           hive(size_type n, const T& value, hive_limits block_limits, const Allocator& = Allocator());
  template<class InputIterator>
  hive(InputIterator first, InputIterator last, const Allocator& = Allocator());
  template<class InputIterator>
  hive(InputIterator first, InputIterator last, hive_limits block_limits, const Allocator& = Allocator());
  template<container - compatible - range<T> R>
  hive(from_range_t, R&& rg, const Allocator& = Allocator());
  template<container - compatible - range<T> R>
  hive(from_range_t, R&& rg, hive_limits block_limits, const Allocator& = Allocator());
  hive(const hive& x);
  hive(hive&&) noexcept;
  hive(const hive&, const type_identity_t<Allocator>&);
  hive(hive&&, const type_identity_t<Allocator>&);
  hive(initializer_list<T> il, const Allocator& = Allocator());
  hive(initializer_list<T> il, hive_limits block_limits, const Allocator& = Allocator());

  ~hive();

  hive& operator=(const hive& x);
  hive& operator=(hive&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value
                                     || allocator_traits<Allocator>::is_always_equal::value);
  hive& operator=(initializer_list<T>);
  template<class InputIterator>
  void assign(InputIterator first, InputIterator last);
  template<container - compatible - range<T> R>
  void assign_range(R&& rg);
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
  [[nodiscard]]
  bool      empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  size_type capacity() const noexcept;
  void      reserve(size_type n);
  void      shrink_to_fit();
  void      trim_capacity() noexcept;
  void      trim_capacity(size_type n) noexcept;


  // modifiers
  template<class... Args>
  iterator emplace(Args&&... args);
  iterator insert(const T& x);
  iterator insert(T&& x);
  void     insert(size_type n, const T& x);
  template<class InputIterator>
  void insert(InputIterator first, InputIterator last);
  template<container - compatible - range<T> R>
  void insert_range(R&& rg);
  void insert(initializer_list<T> il);

  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);
  void     swap(hive&) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
                            || allocator_traits<Allocator>::is_always_equal::value);
  void     clear() noexcept;


  // hive operations
  void      splice(hive& x);
  void      splice(hive&& x);
  size_type unique();
  template<class BinaryPredicate>
  size_type unique(BinaryPredicate binary_pred);

  constexpr hive_limits        block_capacity_limits() const noexcept;
  static constexpr hive_limits block_capacity_hard_limits() noexcept;
  void                         reshape(hive_limits block_limits);

  iterator       get_iterator(const_pointer p) noexcept;
  const_iterator get_iterator(const_pointer p) const noexcept;

  void sort();
  template<class Compare>
  void sort(Compare comp);
};


template<class InputIterator,
         class Allocator
         = allocator<iter - value - type<InputIterator>> hive(InputIterator, InputIterator, Allocator = Allocator())
           -> hive<iter - value - type<InputIterator>, Allocator>;

template<class InputIterator,
         class Allocator = allocator<iter - value - type<InputIterator>> hive(
           InputIterator, InputIterator, hive_limits block_limits, Allocator = Allocator())
           -> hive<iter - value - type<InputIterator>, block_limits, Allocator>;

template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
hive(from_range_t, R&&, Allocator = Allocator()) -> hive<ranges::range_value_t<R>, Allocator>;

template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
hive(from_range_t, R&&, hive_limits block_limits, Allocator = Allocator())
  -> hive<ranges::range_value_t<R>, block_limits, Allocator>;

} // namespace flp
