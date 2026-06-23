#pragma once

#include <aligned_buffer.hh>

#include <error_help.hh>

#include <core/maybe_const.hh>
#include <core/normal_iterator.hh>
#include <core/traits.hh>

#include <memory>
#include <numbers>

namespace flp {

template<typename Type>
class Vector {
public:
  using value_type      = Type;
  using pointer         = value_type*;
  using reference       = value_type&;
  using const_pointer   = const value_type*;
  using const_reference = const value_type&;
  using size_type       = size_t;

  static constexpr size_type value_alignment = alignof(value_type);
  static constexpr size_type value_size      = sizeof(value_type);

private:
  using Buffer = std::unique_ptr<AlignedTypeBuffer<Type>[]>;
  Buffer buffer;
  size_t current_size {};
  size_t current_capacity {};

  static Buffer create_buffer(const size_type element_count) noexcept {
    return Buffer { new AlignedTypeBuffer<Type>[element_count] };
  }

  void ensure_size(const size_type ensured_size) noexcept(noexcept(reserve(size_t{}))) {
    if (ensured_size > current_capacity) {
      if (current_size == 0) {
        reserve(4);
      } else {
        reserve(static_cast<float>(current_size) * std::numbers::phi_v<float>);
      }
    }

    VERIFY(current_capacity >= current_size + 1,
           "Insufficient capacity available ({}).  Required: {}",
           current_capacity,
           current_size + 1);
  }

public:
  Vector() noexcept = default;

  Vector(const Vector& other) noexcept(std::is_nothrow_copy_constructible_v<value_type>) {
    reserve(other.size());
    for (const auto& element : other) {
      push_back(element);
    }
  }

  Vector(Vector&&) noexcept(std::is_nothrow_move_constructible_v<value_type>) = default;

  Vector& operator=(const Vector& other) noexcept(std::is_nothrow_copy_assignable_v<value_type>) {
    clear();
    reserve(other.size());
    for (const auto& element : other) {
      push_back(element);
    }
  }

  Vector& operator=(Vector&&) noexcept(std::is_nothrow_move_constructible_v<value_type>) = default;

  ~Vector() noexcept(std::is_nothrow_destructible_v<value_type>) {
    clear();
  }

  Vector(const size_type capacity) noexcept(noexcept(reserve(size_t{}))) {
    reserve(capacity);
  }

  Vector(const_reference val, size_type count) noexcept(noexcept(reserve(size_t{}))) {
    reserve(count);
    while (count-- > 0) {
      push_back(val);
    }
  }

  template<typename inputIter /*, typename = requireInputIter<inputIter>*/>
  Vector(inputIter first, inputIter last) {
    /*if constexpr (contiguous iterator?) {
      reserve(last - first);
    }*/

    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  [[nodiscard]] decltype(auto) operator[](this auto&& self, const size_type index) {
    VERIFY(index < self.size(), "Index ({}) beyond bounds ({})", index, self.size());
    return self.buffer[index].get();
  }

  // deliberately excluding this
  // bounds safe by default
  /*[[nodiscard]]
  decltype(auto) at(this auto&& self, const size_type index) {
  }*/

  [[nodiscard]]
  decltype(auto) front(this auto&& self) noexcept {
    VERIFY(not self.empty(), "Accessing front element, but no data allocated");
    return self.buffer[0].get();
  }

  [[nodiscard]]
  decltype(auto) back(this auto&& self) noexcept {
    VERIFY(not self.empty(), "Accessing back element, but no data allocated");
    return self.buffer[self.size() - 1].get();
  }

  reference push_back(const_reference data) {
    ensure_size(current_size + 1);
    auto& aligned_buffer = buffer[size()];
    aligned_buffer.construct(data);
    ++current_size;
    return aligned_buffer.get();
  }

  template<typename... Args>
    requires std::is_constructible_v<value_type, Args...>
  reference emplace_back(Args&&... args) {
    ensure_size(current_size + 1);

    auto& aligned_buffer = buffer[size()];
    aligned_buffer.construct(std::forward<Args>(args)...);
    ++current_size;

    return aligned_buffer.get();
  }

  void pop_back() noexcept(std::is_nothrow_destructible_v<value_type>) {
    auto& aligned_buffer = buffer[size() - 1];
    aligned_buffer.destruct();
    --current_size;
  }

  void clear() noexcept(std::is_nothrow_destructible_v<value_type>) {
    while (not empty()) {
      pop_back();
    }
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return size() == 0;
  }

  [[nodiscard]]
  size_type size() const noexcept {
    return current_size;
  }

  [[nodiscard]]
  size_type capacity() const noexcept {
    return current_capacity;
  }

  void resize(const size_type count_target) noexcept(std::is_nothrow_default_constructible_v<value_type>)
    requires std::is_default_constructible_v<value_type> {
    reserve(count_target);

    while (size() < count_target) {
      emplace_back();
    }

    while (size() > count_target) {
      pop_back();
    }
  }

  void resize(const size_type count_target, const value_type value) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
    requires std::is_copy_constructible_v<value_type> {
    reserve(count_target);

    while (size() < count_target) {
      push_back(value);
    }

    while (size() > count_target) {
      pop_back();
    }
  }

  void reserve(const size_type new_capacity) noexcept(std::is_nothrow_move_assignable_v<value_type>) /*does it need to be nothrow destructible too?*/ {
    if (new_capacity <= current_capacity) {
      return;
    }

    auto new_buffer = create_buffer(new_capacity);
    // exception safety here?
    // if one of these move operations fails, we're in a sad, but I believe valid, state
    for (size_t i {}; i < current_size; ++i) {
      new_buffer[i].construct(std::move(buffer[i].get()));
      buffer[i].destruct();
    }
    buffer           = std::move(new_buffer);
    current_capacity = new_capacity;
    VERIFY(current_capacity >= new_capacity, "Failed to allocate new capacity ({})", new_capacity);
  }

  void shrink_to_fit() noexcept(std::is_nothrow_move_constructible_v<value_type>) {
    auto new_buffer = create_buffer(current_size);
    for (size_t i {}; i < current_size; ++i) {
      new_buffer[i].construct(std::move(buffer[i].get()));
      buffer[i].destruct();
    }
    buffer           = std::move(new_buffer);
    current_capacity = current_size;
  }

  //using iterator = normal_iterator<value_type, Vector>;
  using iterator = pointer;
  using const_iterator = const_pointer;
  template<bool IsConst>
  using maybe_iterator = MaybeConst<value_type, IsConst>*;

  [[nodiscard]]
  auto begin(this auto&& self) noexcept {
    return maybe_iterator<IsConst<decltype(self)>>{&self.buffer.get()->get()};
  }

  [[nodiscard]]
  auto end(this auto&& self) noexcept {
    return maybe_iterator<IsConst<decltype(self)>>{&self.buffer.get()->get() + self.current_size};
  }

  [[nodiscard]]
  const_pointer cbegin(this const auto&& self) noexcept {
    return &self.buffer.get()->get();
  }

  [[nodiscard]]
  const_iterator cend(this const auto&& self) noexcept {
    return &self.buffer.get()->get() + self.current_size;
  }

  [[nodiscard]]
  auto rbegin(this auto&& self) noexcept;

  [[nodiscard]]
  auto rend(this auto&& self) noexcept;

  [[nodiscard]]
  auto crbegin(this const auto&& self) noexcept;

  [[nodiscard]]
  auto crend(this const auto&& self) noexcept;

  [[nodiscard]]
  auto Iterator(this const auto&& self, const size_type idx) {
    return maybe_iterator<IsConst<decltype(self)>>(self.buffer.get() + idx);
  }
};

} // namespace flp
