#pragma once

#include "ranges/traits.hh"

#include <limits>

namespace flp::ranges {

template<Incrementable Counting>
struct IotaView {
  constexpr
  IotaView(Counting&& start, Counting&& ending) noexcept
    : first(std::forward<Counting>(start))
    , last(std::forward<Counting>(ending))
  {}

  struct Iterator {
    IotaView* view;
    Counting counter{};

    constexpr
    Iterator(IotaView* vw, Counting count) noexcept
      : view(vw)
      , counter(count)
    {}

    constexpr
    decltype(auto) operator*(this auto&& self) noexcept {
      return self.counter;
    }

    constexpr
    decltype(auto) operator->(this auto&& self) noexcept {
      return &self.counter;
    }

    constexpr
    Iterator& operator++(this auto&& self) noexcept {
      ++self.counter;
      return self;
    }

    constexpr
    Iterator operator++(this auto&& self, int) noexcept {
      return {self.view, self.counter++};
    }

    constexpr
    Iterator& operator--(this auto&& self) noexcept {
      --self.counter;
      return self;
    }

    constexpr
    Iterator operator--(this auto&& self, int) noexcept {
      return {self.view, self.counter--};
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
    return {&self, self.first};
  }

  constexpr
  Iterator end(this auto&& self) noexcept {
    return {&self, self.last};
  }

  Counting first{};
  Counting last{};
};

template<Incrementable Counting>
constexpr
IotaView<Counting> iota(Counting&& start, Counting&& finish = std::numeric_limits<Counting>::max()) noexcept {
  return {std::forward<Counting>(start), std::forward<Counting>(finish)};
}

}
