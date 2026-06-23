#pragma once

#include <aligned_buffer.hh>

#include <error_help.hh>

#include <cstddef>
#include <memory>
#include <utility>

namespace flp::imm {

template<typename Type>
struct Vector {
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
  // use a normal vector?
  using Buffer = std::unique_ptr<AlignedTypeBuffer<Type>[]>;
  Buffer buffer;
  size_t current_size {};

  static Buffer create_buffer(const size_type element_count) noexcept {
    return Buffer { new AlignedTypeBuffer<Type>[element_count] };
  }

  Vector(Buffer buf, const size_t sz)
    : buffer(std::move(buf))
    , current_size(sz)
  {}

public:
  Vector() noexcept = default;

  Vector(const Vector& other) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
    : buffer(create_buffer(other.size()))
    , current_size(other.size()) {
    for (size_t index{}; const auto& element : other) {
      buffer[index++].construct(element);
    }
  }

  Vector(Vector&&) = delete("Moving implies modification of the other member");

  Vector& operator=(const Vector&) = delete("Copying changes the state of this vector");

  Vector& operator=(Vector&&) = delete("Moving implies modification of the other member");

  ~Vector() noexcept(std::is_nothrow_destructible_v<value_type>) {
    for (size_t i{}; i < size(); ++i) {
      buffer[i].destruct();
    }
  }

  Vector(std::initializer_list<Type> il)
    : Vector(il.begin(), il.end())
  {}

  Vector(const_reference val, size_type count) noexcept
    : buffer(create_buffer(count))
    , current_size(count) {
    while (count-- > 0) {
      buffer[count - 1].construct(val);
    }
  }

  template<typename inputIter /*, typename = requireInputIter<inputIter>*/>
  Vector(inputIter first, inputIter last)
    : buffer(create_buffer(last - first))
    , current_size(last - first) {
    for (size_t i{}; first != last; ++i, ++first) {
      buffer[i].construct(*first);
    }
  }

  [[nodiscard]]
  const_reference operator[](const size_type index) const {
    VERIFY(index < size(), "Index ({}) beyond bounds ({})", index, size());
    return buffer[index].get();
  }

  // deliberately excluding this
  // bounds safe by default
  /*[[nodiscard]]
  decltype(auto) at(this auto&& self, const size_type index) {
  }*/

  [[nodiscard]]
  const_reference front() const noexcept {
    VERIFY(not empty(), "Accessing front element, but no data allocated");
    return buffer[0].get();
  }

  [[nodiscard]]
  const_reference back() const noexcept {
    VERIFY(not empty(), "Accessing back element, but no data allocated");
    return buffer[size() - 1].get();
  }

  [[nodiscard]]
  Vector push_back(const_reference data) const {
    auto new_buffer = create_buffer(size() + 1);

    for (size_t i{}; i < size(); ++i) {
      new_buffer[i].construct(buffer[i].get());
    }

    new_buffer[size()].construct(data);

    return Vector(std::move(new_buffer), size() + 1);
  }

  template<typename... Args>
    requires std::is_constructible_v<value_type, Args...>
  [[nodiscard]]
  Vector emplace_back(Args&&... args) const {
    auto new_buffer = create_buffer(size() + 1);

    for (size_t i{}; i < size(); ++i) {
      new_buffer[i].construct(buffer[i].get());
    }

    new_buffer[size()].construct(std::forward<Args>(args)...);

    return {std::move(new_buffer)};
  }

  [[nodiscard]]
  Vector pop_back() const noexcept(std::is_nothrow_destructible_v<value_type>) {
    auto new_buffer = create_buffer(size() - 1);

    for (size_t i{}; i < size() - 1; ++i) {
      new_buffer[i].construct(buffer[i].get());
    }

    return {std::move(new_buffer)};
  }

  [[nodiscard]]
  Vector clear() const noexcept(std::is_nothrow_destructible_v<value_type>) {
    return {};
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return size() == 0;
  }

  [[nodiscard]]
  size_type size() const noexcept {
    return current_size;
  }

  using const_iterator = const_pointer;

  [[nodiscard]]
  const_iterator begin() const noexcept {
    return const_iterator{&buffer.get()->get()};
  }

  [[nodiscard]]
  const_iterator end() const noexcept {
    return const_iterator{&buffer.get()->get() + current_size};
  }

  [[nodiscard]]
  const_iterator Iterator(const size_type idx) const {
    return const_iterator(buffer.get() + idx);
  }
};

} // namespace flp
