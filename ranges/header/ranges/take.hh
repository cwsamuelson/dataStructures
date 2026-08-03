#pragma once

#include "ranges/traits.hh"

namespace flp::views {

template<typename Container>
struct TakeView {
  constexpr
  TakeView(Container& cntnr, const size_t count) noexcept
    : container(cntnr)
    , counter(count)
  {}

  struct Iterator {
    // change to type_traits
    using Iter_t = decltype(std::begin(std::declval<Container>()));

    // instead of counter?
    // Iter_t first;
    // Iter_t last;
    Iter_t iterator;
    TakeView* view;
    size_t counter{};

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
      if (self.counter != 0) {
        --self.counter;
        ++self.iterator;
      }

      return self;
    }

    constexpr
    Iterator operator++(this auto&& self, int) noexcept {
      Iterator other{self};
      return ++other;
    }

    constexpr
    Iterator& operator--(this auto&& self) noexcept {
      if (self.counter <= self.view->counter) {
        ++self.counter;
        --self.iterator;
      }

      return self;
    }

    constexpr
    Iterator operator--(this auto&& self, int) noexcept {
      Iterator other{self};
      return ++other;
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
    bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept {
      return lhs.view     == rhs.view
         and lhs.counter  == rhs.counter;
    }
  };

  constexpr
  Iterator begin(this auto&& self) noexcept {
    return {std::begin(self.container), &self, self.counter};
  }

  constexpr
  Iterator end(this auto&& self) noexcept {
    auto iter = std::begin(self.container);
    std::advance(iter, self.counter);
    return {iter, &self, 0uz};
  }

  Container& container;
  size_t counter{};
};

struct TakeAdaptor {
  size_t counter{};
};

template<Range Container>
constexpr
TakeView<Container> operator|(Container&& container, TakeAdaptor&& adaptor) noexcept {
  return {std::forward<Container>(container), adaptor.counter};
}

constexpr
TakeAdaptor take(const size_t counter) noexcept {
  return {counter};
}

}
