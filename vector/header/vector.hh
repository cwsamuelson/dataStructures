#pragma once

#include <core/normal_iterator.hh>

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
  struct BufferDeleter {
    void operator()(void* pointer) {
      std::free(pointer);
    }
  };
  using Buffer = std::unique_ptr<std::byte[], BufferDeleter>;
  Buffer buffer;
  size_t current_size{};
  size_t current_capacity{};

  static reference get_reference(std::byte* buffer, const size_t index) {
    return *get_pointer(buffer, index);
  }
  static pointer get_pointer(std::byte* buffer, const size_t index) {
    VERIFY(buffer != nullptr, "Buffer is null");
    return reinterpret_cast<pointer>(&buffer[index * value_size]);
  }

  static Buffer create_buffer(const size_type element_count) {
    return Buffer{reinterpret_cast<std::byte*>(std::aligned_alloc(value_alignment, element_count * value_size))};
  }

  void ensure_size(const size_type ensured_size) noexcept {
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

  ~Vector() /*noexcept(std::is_noexcept_destructible_v<value_type>)*/ = default;

  Vector(const size_type capacity) {
    reserve(capacity);
  }

  Vector(const_reference val, size_type count);

  template<typename inputIter/*, typename = requireInputIter<inputIter>*/>
  Vector(inputIter first, inputIter last);

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, const size_type index) {
    VERIFY(index < self.size(), "Index ({}) beyond bounds ({})", index, self.size());
    return get_reference(self.buffer.get(), index);
  }

  // deliberately excluding this
  // bounds safe by default
  /*[[nodiscard]]
  decltype(auto) at(this auto&& self, const size_type index) {
  }*/

  [[nodiscard]]
  decltype(auto) front(this auto&& self) noexcept {
    return get_reference(self.buffer.get(), 0);
  }

  [[nodiscard]]
  decltype(auto) back(this auto&& self) noexcept {
    return get_reference(self.buffer.get(), self.size() - 1);
  }

  reference push_back(const_reference data) {
    ensure_size(current_size + 1);
    auto* ptr = get_pointer(buffer.get(), size());
    new (ptr) value_type(data);
    ++current_size;
    return *ptr;
  }

  template<typename ...Args>
  // requires constructible
  reference emplace_back(Args&& ...args) {
    ensure_size(current_size + 1);

    auto* ptr = get_pointer(buffer.get(), size());
    new (ptr) value_type(std::forward<Args>(args)...);
    ++current_size;

    return *ptr;
  }

  void pop_back() {
    auto* ptr = get_pointer(buffer.get(), size() - 1);
    ptr->~value_type();
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

  void resize(const size_type count) /*is default constructible*/ {
    resize(count, value_type{});
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
      const auto buffer_index = i * value_size;
      *reinterpret_cast<pointer>(&new_buffer[buffer_index]) = std::move(*reinterpret_cast<pointer>(&buffer[buffer_index]));
    }
    buffer = std::move(new_buffer);
    current_capacity = new_capacity;
    VERIFY(current_capacity >= new_capacity, "Failed to allocate new capacity ({})", new_capacity);
  }

  void shrink_to_fit() {
    auto new_buffer = create_buffer(current_size);
    // copy buffer over
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

