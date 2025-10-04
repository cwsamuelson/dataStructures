#pragma once

#include "ranges/traits.hh"

#include <cstddef>
#include <utility>
#include <vector>

namespace flp::ranges {

template<typename Container>
struct AllView {
  constexpr
  AllView(Container& cntnr) noexcept
    : container(cntnr)
  {}

  struct Iterator {
    using Iter = decltype(std::begin(std::declval<Container>()));
    Iter iterator;

    constexpr
    decltype(auto) operator*(this auto&& self) noexcept {
      return *self.iterator;
    }

    constexpr
    decltype(auto) operator->(this auto&& self) noexcept {
      return &*self.iterator;
    }

    constexpr
    Iterator& operator++(this auto&& self) noexcept {
      ++self.iterator;
      return self;
    }

    constexpr
    Iterator operator++(this auto&& self, int) noexcept {
      return {self.iterator++};
    }

    constexpr
    Iterator& operator--(this auto&& self) noexcept {
      --self.iterator;
      return self;
    }

    constexpr
    Iterator operator--(this auto&& self, int) noexcept {
      return {self.iterator--};
    }

    friend
    constexpr
    Iterator operator+(const Iterator& iterator, const ssize_t offset) noexcept {
      return {iterator.iterator + offset};
    }

    friend
    constexpr
    Iterator operator-(const Iterator& iterator, const ssize_t offset) noexcept {
      return {iterator.iterator - offset};
    }

    friend
    constexpr
    auto operator<=>(const Iterator&, const Iterator&) noexcept = default;

    friend
    constexpr
    bool operator==(const Iterator&, const Iterator&) noexcept = default;
  };

  constexpr
  Iterator begin(this auto&& self) noexcept {
    return {std::begin(self.container)};
  }

  constexpr
  Iterator end(this auto&& self) noexcept {
    return {std::end(self.container)};
  }

  Container& container;
};

struct All_t {};

template<Range Container>
static
constexpr
AllView<Container> operator|(Container&& range, const All_t&) noexcept {
  return {std::forward<Container>(range)};
}

static constexpr All_t all;

} // namespace flp
