#pragma once

#include <text/string.hh>

namespace flp {

template<typename CharT>
struct BasicStringView {
  constexpr
  BasicStringView() noexcept = default;

  BasicStringView(const BasicStringView&) = default;
  BasicStringView(BasicStringView&&) noexcept = default;

  BasicStringView& operator=(const BasicStringView&) = default;
  BasicStringView& operator=(BasicStringView&&) noexcept = default;

  constexpr
  BasicStringView(const CharT* cstring) noexcept
    : first(cstring)
    , last(cstring + strlen(cstring))
  {}

  template<typename Iterator>
  constexpr
  BasicStringView(Iterator start, Iterator finish) noexcept
    : first(&(*start))
    , last(&(*finish))
  {}

  constexpr
  BasicStringView(const BasicString<CharT>& string) noexcept
    : first(string.begin())
    , last(string.end())
  {}

  constexpr
  BasicStringView& operator=(const BasicString<CharT>& string) noexcept {
    first = string.begin();
    last = string.end();

    return *this;
  }

  ~BasicStringView() noexcept = default;

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, const size_t index) noexcept {
    // VERIFY(index < size, "");

    return *(self.first + index);
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return last - first;
  }

  [[nodiscard]]
  bool empty() const noexcept{
    return first == last;
  }

  decltype(auto) data(this auto&& self) noexcept {
    return self.first;
  }

  [[nodiscard]]
  decltype(auto) begin(this auto&& self) noexcept {
    return self.first;
  }

  [[nodiscard]]
  decltype(auto) end(this auto&& self) noexcept {
    return self.last;
  }

  void clear() noexcept {
    first = nullptr;
    last = nullptr;
  }

  [[nodiscard]]
  explicit
  operator BasicString<CharT>() const {
    return { begin(), end() };
  }

  [[nodiscard]]
  friend
  auto operator<=>(const BasicStringView& lhs, const BasicStringView& rhs) noexcept {
    const auto length = min(lhs.size(), rhs.size());

    for (size_t i{}; i < length; ++i) {
      if (lhs.first[i] != rhs.first[i]) {
        return lhs.first[i] <=> rhs.first[i];
      }
    }

    if (lhs.size() == rhs.size()) {
      return std::strong_ordering::equal;
    }

    return lhs.size() < rhs.size()
      ? std::strong_ordering::less
      : std::strong_ordering::greater;
  }

  [[nodiscard]]
  friend
  bool operator==(const BasicStringView& lhs, const BasicStringView& rhs) noexcept {
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

  const CharT* first = nullptr;
  const CharT* last = nullptr;
};

using StringView = BasicStringView<char>;

template<typename OStream, typename CharT>
OStream& operator<<(OStream& ostream, BasicStringView<CharT>& string) {
  for (const auto chr : string) {
    ostream << chr;
  }

  return ostream;
}

}
