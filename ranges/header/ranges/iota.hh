#pragma once

#include "ranges/traits.hh"

namespace flp::ranges {

template<typename Container, typename Functor>
struct IotaView {
  constexpr
  IotaView(Container& cntnr, Functor&& functor)
    : container(cntnr)
  {}

  struct Iterator {
    using Iter = decltype(std::begin(std::declval<Container>()));
    Iter iterator;

    constexpr
    decltype(auto) operator*(this auto&& self) {
      return *self.iterator;
    }

    constexpr
    decltype(auto) operator->(this auto&& self) {
      return &*self.iterator;
    }

    constexpr
    Iterator& operator++(this auto&& self) {
      while (predicate(*++self.iterator)) {}
      return self;
    }

    constexpr
    Iterator operator++(this auto&& self, int) {
      while (predicate(++self.iterator)) {}
      return {self.iterator++};
    }

    constexpr
    Iterator& operator--(this auto&& self) {
      --self.iterator;
      return self;
    }

    constexpr
    Iterator operator--(this auto&& self, int) {
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
  Iterator begin(this auto&& self) {
    return {std::begin(self.container)};
  }

  constexpr
  Iterator end(this auto&& self) {
    return {std::end(self.container)};
  }

  Container& container;
};

struct Iota_t {};



template<Range Container>
IotaView<Container> operator|(Container&& container, const Iota_t&) {
  return {std::forward<Container>(container)};
}

}
