#pragma once

#include <core/aligned-buffer.hh>

#include <error_help.hh>

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

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
  using Buffer = std::vector<Type>;

  std::vector<Type> buffer;

  Vector(Buffer buf)
    : buffer(std::move(buf))
  {}

public:
  Vector() noexcept = default;

  Vector(const Vector& other) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
    : buffer(other.buffer)
  {}

  Vector(Vector&&) = delete("Moving implies modification of the vector moved from");

  Vector& operator=(const Vector&) = delete("Copying changes the state of this vector");

  Vector& operator=(Vector&&) = delete("Moving implies modification of the vector moved from");

  ~Vector() noexcept(std::is_nothrow_destructible_v<value_type>) = default;

  template<typename ...Args>
  Vector(Args&& ...args)
    : buffer{std::forward<Args>(args)...}
  {}

  [[nodiscard]]
  const_reference operator[](const size_type index) const {
    return buffer.at(index);
  }

  // deliberately excluding this
  // bounds safe by default
  /*[[nodiscard]]
  decltype(auto) at(this auto&& self, const size_type index) {
  }*/

  [[nodiscard]]
  const_reference front() const {
    VERIFY(not empty(), "Accessing front element, but no data allocated");
    return buffer.front();
  }

  [[nodiscard]]
  const_reference back() const {
    VERIFY(not empty(), "Accessing back element, but no data allocated");
    return buffer.back();
  }

  [[nodiscard]]
  Vector push_back(const_reference data) const {
    auto new_buffer = buffer;

    new_buffer.push_back(data);

    return new_buffer;
  }

  template<typename... Args>
    requires std::is_constructible_v<value_type, Args...>
  [[nodiscard]]
  Vector emplace_back(Args&&... args) const {
    auto new_buffer = buffer;

    new_buffer.emplace_back(std::forward<Args>(args)...);

    return new_buffer;
  }

  [[nodiscard]]
  Vector pop_back() const noexcept(std::is_nothrow_destructible_v<value_type>) {
    auto new_buffer = buffer;

    new_buffer.pop_back();

    return new_buffer;
  }

  [[nodiscard]]
  Vector clear() const noexcept(std::is_nothrow_destructible_v<value_type>) {
    return {};
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return buffer.empty();
  }

  [[nodiscard]]
  size_type size() const noexcept {
    return buffer.size();
  }

  using const_iterator = const_pointer;

  [[nodiscard]]
  const_iterator begin() const noexcept {
    return buffer.begin();
  }

  [[nodiscard]]
  const_iterator end() const noexcept {
    return buffer.end();
  }
};

template<typename ...Args>
Vector(Args&& ...args) -> Vector<typename decltype(std::vector{std::declval<Args>()...})::value_type>;

} // namespace flp
