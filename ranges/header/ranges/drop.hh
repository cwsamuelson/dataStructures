#pragma once

#include "ranges/traits.hh"

namespace flp::views {

template<typename Container>
struct DropView {
  constexpr
  DropView(Container& cntnr, const size_t count) noexcept
    : container(cntnr)
    , counter(count)
  {}

  struct Iterator {
    using Iter = decltype(std::begin(std::declval<Container>()));

    Iter iterator;
    DropView* view;
    size_t counter{};

    constexpr
    Iterator(DropView* vw) noexcept
      : view(vw)
    {}

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

    // friend
    // constexpr
    // Iterator operator+(const Iterator& iterator, const ssize_t offset) {
    //   return {iterator.iterator + offset};
    // }

    // friend
    // constexpr
    // Iterator operator-(const Iterator& iterator, const ssize_t offset) {
    //   return {iterator.iterator - offset};
    // }

    friend
    constexpr
    auto operator<=>(const Iterator&, const Iterator&) noexcept = default;

    friend
    constexpr
    bool operator==(const Iterator&, const Iterator&) noexcept = default;
  };

  constexpr
  Iterator begin(this auto&& self) noexcept {
    return {std::begin(self.container), &self, counter};
  }

  constexpr
  Iterator end(this auto&& self) noexcept {
    return {std::end(self.container), &self};
  }

  Container& container;
  size_t counter{};
};

struct DropAdaptor {
  size_t counter{};
};

template<Range Container>
constexpr
DropView<Container> operator|(Container&& container, DropAdaptor&& adaptor) noexcept {
  return {std::forward<Container>(container), adaptor.counter};
}

constexpr
DropAdaptor take(const size_t counter) noexcept {
  return {counter};
}

}
