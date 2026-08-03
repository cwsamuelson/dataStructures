#pragma once

#include "ranges/traits.hh"

#include <limits>

namespace flp::ranges {

template<Incrementable Counting>
struct IotaView {
  constexpr
  IotaView(const Counting start, const Counting ending) noexcept
    : first(start)
    , last(ending)
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

  // we COULD capture a const&, so that copies aren't made unnecessarily, but
  // that would break other things, so it would have to be optional...
  Counting first{};
  Counting last{};
};

template<Incrementable Counting>
constexpr
IotaView<Counting> iota(const Counting start, const Counting finish = std::numeric_limits<Counting>::max()) noexcept {
  return {start, finish};
}

}
