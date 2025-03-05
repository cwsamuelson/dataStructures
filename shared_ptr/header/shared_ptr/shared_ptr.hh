#pragma once

#include <memory>
#include <optional>
#include <span>
#include <stack>

namespace flp {

template<typename Type>
struct SharedPointer {
  struct ControlBlock {
    using delete_func = void(*)(Type*);

    Type* pointer = nullptr;
    size_t ref_count{};
    delete_func deleter = nullptr;
  };

  ControlBlock* control_block = nullptr;

  SharedPointer(Type* ptr)
    : control_block(new ControlBlock{ptr, 1, &default_deleter})
  {}

  template<typename Deleter>
  SharedPointer(Type* ptr, Deleter deleter) {
  }

  template<typename Deleter>
  SharedPointer(Type value, Deleter deleter) {
  }

  SharedPointer() = default;

  SharedPointer(const SharedPointer& other)
    : control_block(other.control_block) {
    increment();
  }

  SharedPointer(SharedPointer&& other)
    : control_block(other.control_block) {
    other.control_block = nullptr;
  }

  SharedPointer& operator=(const SharedPointer& other) {
    if (control_block != nullptr) {
      decrement();
    }

    control_block = other.control_block;
    increment();
    return *this;
  }

  SharedPointer& operator=(SharedPointer&& other) {
    if (control_block != nullptr) {
      decrement();
    }

    control_block = other.control_block;
    other.control_block = nullptr;
    return *this;
  }

  ~SharedPointer() {
    decrement();
  }

  [[nodiscard]]
  explicit operator bool() const {
    return control_block != nullptr and control_block->pointer != nullptr;
  }

  [[nodiscard]]
  Type* get() const {
    return control_block == nullptr
      ? nullptr
      : control_block->pointer;
  }

  [[nodiscard]]
  size_t use_count() const {
    return control_block == nullptr
      ? 0
      : control_block->ref_count;
  }

  void reset() {
    decrement();
  }

  [[nodiscard]]
  Type& operator*() const {
    return *control_block->pointer;
  }

  [[nodiscard]]
  Type* operator->() const {
    return control_block->pointer;
  }

private:
  static void default_deleter(Type* pointer) {
    delete pointer;
  }

  void decrement() {
    --control_block->ref_count;
    if (control_block->ref_count == 0) {
      control_block->deleter(control_block->pointer);
      delete control_block;
    }
    control_block = nullptr;
  }

  void increment() {
    ++control_block->ref_count;
  }
};

} // namespace flp

