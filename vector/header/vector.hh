#pragma once

#include <core/normal_iterator.hh>
#include <aligned_buffer.hh>

#include <error_help.hh>

#include <memory>
#include <numbers>

namespace flp {

template<typename Type>
class Vector {
public:
  using value_type = Type;
  using pointer = value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using const_pointer = const value_type*;
  using iterator = normal_iterator<value_type, Vector>;
  using size_type = size_t;

  static constexpr size_type value_alignment = alignof(value_type);
  static constexpr size_type value_size = sizeof(value_type);

private:
  using Buffer = std::unique_ptr<AlignedBuffer<Type>[]>;
  Buffer buffer;
  size_t current_size{};
  size_t current_capacity{};

  static Buffer create_buffer(const size_type element_count) {
    return Buffer{new AlignedBuffer<Type>[element_count]};
  }

  void ensure_size(const size_type ensured_size) {
    if (ensured_size > current_capacity) {
      if (current_size == 0) {
        reserve(4);
      } else {
        reserve(static_cast<float>(current_size) * std::numbers::phi_v<float>);
      }
    }
    VERIFY(current_capacity >= current_size + 1, "Insufficient capacity available ({}).  Required: {}", current_capacity, current_size + 1);
  }

public:
  Vector() = default;
  Vector(const Vector& other) /*noexcept(std::is_noexcept_copy_constructible_v<value_type>)*/ {
    reserve(other.size());
    for (const auto& element : other) {
      push_back(element);
    }
  }
  Vector(Vector&&) /*noexcept(std::is_noexcept_move_constructible_v<value_type>)*/ = default;

  Vector& operator=(const Vector& other) /*noexcept(std::is_noexcept_copy_assignable_v<value_type>)*/ {
    reserve(other.size());
    for (const auto& element : other) {
      push_back(element);
    }
  }
  Vector& operator=(Vector&&) /*noexcept(std::is_noexcept_move_constructible_v<value_type>)*/ = default;

  ~Vector() /*noexcept(std::is_noexcept_destructible_v<value_type>)*/ {
    clear();
  }

  Vector(const size_type capacity) {
    reserve(capacity);
  }

  Vector(const_reference val, size_type count);

  template<typename inputIter/*, typename = requireInputIter<inputIter>*/>
  Vector(inputIter first, inputIter last);

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, const size_type index) {
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

  template<typename ...Args>
  // requires constructible
  reference emplace_back(Args&& ...args) {
    ensure_size(current_size + 1);

    auto& aligned_buffer = buffer[size()];
    aligned_buffer.construct(std::forward<Args>(args)...);
    ++current_size;

    return aligned_buffer.get();
  }

  void pop_back() {
    auto& aligned_buffer = buffer[size() - 1];
    aligned_buffer.destruct();
    --current_size;
  }

  void clear() {
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

  void resize(const size_type count_target) /*is default constructible*/ {
    reserve(count_target);

    while (size() < count_target) {
      emplace_back();
    }

    while(size() > count_target) {
      pop_back();
    }
  }

  void resize(const size_type count_target, const value_type value) {
    reserve(count_target);

    while (size() < count_target) {
      push_back(value);
    }

    while(size() > count_target) {
      pop_back();
    }
  }

  void reserve(const size_type new_capacity) /*notrhow move assign?*/ {
    if (new_capacity <= current_capacity) {
      return;
    }

    auto new_buffer = create_buffer(new_capacity);
    // exception safety here?
    // if one of these move operations fails, we're in a sad, but I believe valid, state
    for (size_t i{}; i < current_size; ++i) {
      new_buffer[i].construct(std::move(buffer[i].get()));
      buffer[i].destruct();
    }
    buffer = std::move(new_buffer);
    current_capacity = new_capacity;
    VERIFY(current_capacity >= new_capacity, "Failed to allocate new capacity ({})", new_capacity);
  }

  void shrink_to_fit() {
    auto new_buffer = create_buffer(current_size);
    for (size_t i{}; i < current_size; ++i) {
      new_buffer[i].construct(std::move(buffer[i].get()));
      buffer[i].destruct();
    }
    buffer = std::move(new_buffer);
    current_capacity = current_size;
  }

  [[nodiscard]]
  decltype(auto) begin(this auto&& self) noexcept;

  [[nodiscard]]
  decltype(auto) cbegin(this const auto&& self) noexcept;

  [[nodiscard]]
  decltype(auto) rbegin(this auto&& self) noexcept;

  [[nodiscard]]
  decltype(auto) crbegin(this const auto&& self) noexcept;

  [[nodiscard]]
  decltype(auto) end(this auto&& self) noexcept;

  [[nodiscard]]
  decltype(auto) cend(this const auto&& self) noexcept;

  [[nodiscard]]
  decltype(auto) rend(this auto&& self) noexcept;

  [[nodiscard]]
  decltype(auto) crend(this const auto&& self) noexcept;

  [[nodiscard]]
  iterator Iterator(size_type idx);
};

}

