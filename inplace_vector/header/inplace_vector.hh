#pragma once

#include "aligned_buffer.hh"

#include <error_help.hh>

#include <array>
#include <cstddef>

namespace flp {

template<typename Type, size_t Capacity>
struct InplaceVector {
  void push_back(const Type& value) {
    VERIFY(count < Capacity, "Insufficient allocated capacity for inplace vector");
    buffers[count++].construct(value);
  }

  template<typename ...Args>
  Type& emplace_back(Args&& ...args) {
    VERIFY(count < Capacity, "Insufficient allocated capacity for inplace vector");
    return *buffers[count++].construct(std::forward<Args>(args)...);
  }

  void pop_back() noexcept(noexcept(buffers[0].destruct())) {
    VERIFY(not empty(), "`pop_back` called on empty vector container");
    --count;
    buffers[count].destruct();
  }

  [[nodiscard]]
  Type& at(const size_t index) {
    VERIFY(index < count, "Out of bounds access");
    return buffers[index].get();
  }

  [[nodiscard]]
  const Type& at(const size_t index) const {
    VERIFY(index < count, "Out of bounds access");
    return buffers[index].get();
  }

  [[nodiscard]]
  Type& operator[](const size_t index) {
    VERIFY(index < count, "Out of bounds access");
    return buffers[index].get();
  }

  [[nodiscard]]
  const Type& operator[](const size_t index) const {
    VERIFY(index < count, "Out of bounds access");
    return buffers[index].get();
  }

  [[nodiscard]]
  size_t capacity() const noexcept {
    return Capacity;
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return count;
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return count == 0;
  }

  [[nodiscard]]
  Type& front() {
    VERIFY(not empty(), "Can't allocate `front` of empty vector.");
    return buffers[0].get();
  }

  [[nodiscard]]
  const Type& front() const {
    VERIFY(not empty(), "Can't allocate `front` of empty vector.");
    return buffers[0].get();
  }

  [[nodiscard]]
  Type& back() {
    VERIFY(not empty(), "Can't allocate `back` of empty vector.");
    return buffers[count - 1].get();
  }

  [[nodiscard]]
  const Type& back() const {
    VERIFY(not empty(), "Can't allocate `back` of empty vector.");
    return buffers[count - 1].get();
  }

  [[nodiscard]]
  Type* begin() noexcept {
    return &buffers[0].get();
  }

  [[nodiscard]]
  Type* end() noexcept {
    return &buffers[count].get();
  }

  [[nodiscard]]
  const Type* begin() const noexcept {
    return &buffers[0].get();
  }

  [[nodiscard]]
  const Type* end() const noexcept {
    return &buffers[count].get();
  }

  [[nodiscard]]
  const Type* cbegin() const noexcept {
    return &buffers[0].get();
  }

  [[nodiscard]]
  const Type* cend() const noexcept {
    return &buffers[count].get();
  }

  size_t count{};
  std::array<AlignedTypeBuffer<Type>, Capacity> buffers;
};

} // namespace flp
