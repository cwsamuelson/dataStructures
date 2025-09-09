#pragma once

#include <cstddef>
#include <string>
#include <utility>

namespace flp {

template<typename CharT>
struct BasicString {
  BasicString() noexcept = default;

  BasicString(const char* cstring){}

  template<typename Iterator>
  BasicString(Iterator start, Iterator finish){}

  BasicString(const BasicString& other)
    : ptr(new CharT[other.length])
    , length(other.length)
    , allocated(length) {

    for (size_t i{}; i < length; ++i) {
      ptr[i] = other.ptr[i];
    }
  }

  BasicString(BasicString&& other) noexcept
    : ptr(std::exchange(other.ptr, nullptr))
    , length(std::exchange(other.length, 0))
    , allocated(std::exchange(other.allocated, 0))
  {}

  BasicString& operator=(BasicString&& other) noexcept {
    if (ptr != nullptr) {
      delete[] ptr;
    }

    ptr = std::exchange(other.ptr, nullptr);
    length = std::exchange(other.length, 0);
    allocated = std::exchange(other.allocated, 0);

    return *this;
  }

  BasicString& operator=(const BasicString& other) noexcept {
    if (other.length > allocated) {
      delete[] ptr;
      ptr = new CharT[other.length];
      length = other.length;
      allocated = length;
    }

    for (size_t i{}; i < length; ++i) {
      ptr[i] = other.ptr[i];
    }

    return *this;
  }

  ~BasicString() {
    if (ptr != nullptr) {
      delete[] ptr;
    }
  }

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, const size_t index) noexcept {
    // VERIFY(index < size, "");

    return self.ptr[index];
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return length == 0;
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return length;
  }

  [[nodiscard]]
  size_t capacity() const noexcept {
    return allocated;
  }

  [[nodiscard]]
  decltype(auto) begin(this auto&& self) noexcept {
    return self.ptr;
  }

  [[nodiscard]]
  decltype(auto) end(this auto&& self) noexcept {
    return self.ptr + self.length;
  }

  void clear() {
    if (ptr == nullptr) {
      return;
    }

    length = 0;
    ptr[0] = '\0';
  }

  [[nodiscard]]
  friend
  bool operator==(const BasicString& lhs, const BasicString& rhs) noexcept {
    const auto length = lhs.size();
    if (length != rhs.size()) {
      return false;
    }

    size_t i{};

    while (i < length and lhs[i] == rhs[i]) {
    }

    return i == length;
  }

  CharT* ptr = nullptr;
  size_t length{};
  size_t allocated{};
};

using String = BasicString<char>;

}
