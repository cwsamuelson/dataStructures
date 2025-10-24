#pragma once

#include "text/support.hh"

#include <cstddef>
#include <string>
#include <utility>

namespace flp {

template<typename CharT>
struct BasicString {
  constexpr
  BasicString() noexcept = default;

  constexpr
  BasicString(const char* cstring)
    : ptr(nullptr)
    , length(strlen(cstring))
    , allocated(length) {
    ptr = new CharT[allocated];

    for (size_t i{}; i < allocated; ++i) {
      ptr[i] = cstring[i];
    }
  }

  template<typename Iterator>
  constexpr
  BasicString(Iterator start, Iterator finish)
    : ptr(nullptr)
    , length(finish - start)
    , allocated(length) {
    ptr = new CharT[allocated];

    while (start != finish) {
      ptr[start++];
    }
  }

  constexpr
  BasicString(const BasicString& other)
    : ptr(new CharT[other.length])
    , length(other.length)
    , allocated(length) {

    for (size_t i{}; i < length; ++i) {
      ptr[i] = other.ptr[i];
    }
  }

  constexpr
  BasicString(BasicString&& other) noexcept
    : ptr(std::exchange(other.ptr, nullptr))
    , length(std::exchange(other.length, 0))
    , allocated(std::exchange(other.allocated, 0))
  {}

  constexpr
  BasicString& operator=(BasicString&& other) noexcept {
    if (ptr != nullptr) {
      delete[] ptr;
    }

    ptr = std::exchange(other.ptr, nullptr);
    length = std::exchange(other.length, 0);
    allocated = std::exchange(other.allocated, 0);

    return *this;
  }

  constexpr
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

  constexpr
  ~BasicString() {
    if (ptr != nullptr) {
      delete[] ptr;
    }
  }

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, const size_t index) noexcept {
    // VERIFY(index < length, "");

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

  [[nodiscard]]
  decltype(auto) data(this auto&& self) noexcept {
    return self.ptr;
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
  constexpr
  bool operator==(const BasicString& lhs, const BasicString& rhs) noexcept {
    const auto length = lhs.size();
    if (length != rhs.size()) {
      return false;
    }

    size_t i{};

    while (i < length and lhs[i] == rhs[i]) {
      ++i;
    }

    return i == length;
  }

  CharT* ptr = nullptr;
  size_t length{};
  size_t allocated{};
};

using String = BasicString<char>;

template<typename OStream, typename CharT>
OStream& operator<<(OStream& ostream, BasicString<CharT>& string) {
  for (const auto chr : string) {
    ostream << chr;
  }

  return ostream;
}

}
