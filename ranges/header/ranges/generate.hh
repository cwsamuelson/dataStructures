#pragma once

#include "ranges/traits.hh"

namespace flp::ranges {

template<typename Functor>
struct GenerateView {
  constexpr
  GenerateView(Functor&& functor) noexcept
    : predicate(std::forward<Functor>(functor))
  {}

  struct Iterator {
    GenerateView* view;

    constexpr
    decltype(auto) operator*(this auto&& self) noexcept {
      return self.view->predicate();
    }

    constexpr
    decltype(auto) operator->(this auto&& self) noexcept {
      return &self.view->predicate();
    }

    constexpr
    Iterator& operator++(this auto&& self) noexcept {
      return self;
    }

    constexpr
    Iterator operator++(this auto&& self, int) noexcept {
      return {};
    }

    constexpr
    Iterator& operator--(this auto&& self) noexcept {
      return self;
    }

    constexpr
    Iterator operator--(this auto&& self, int) noexcept {
      return {};
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
    return {&self};
  }

  constexpr
  Iterator end(this auto&& self) noexcept {
    return {&self};
  }

  Functor predicate;
};

template<typename Functor>
constexpr
GenerateView<Functor> generate(Functor&& functor) noexcept {
  return {std::forward<Functor>(functor)};
}

}
