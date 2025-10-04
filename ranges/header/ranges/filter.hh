#pragma once

#include "ranges/traits.hh"

namespace flp::views {

template<typename Container, typename Functor>
struct FilterView {
  constexpr
  FilterView(Container& cntnr, Functor&& functor)
    : container(cntnr)
    , predicate(std::forward<Functor>(functor))
  {}

  struct Iterator {
    using Iter = decltype(std::begin(std::declval<Container>()));
    Iter iterator;
    FilterView* view;

    constexpr
    Iterator(Iter iter, FilterView* vw)
      : iterator(iter)
      , view(vw) {
      while (iterator != std::end(view->container) and not view->predicate(*++iterator)) {}
    }

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
      while (self.iterator != std::end(self.view->container) and not self.view->predicate(*++self.iterator)) {}
      return self;
    }

    constexpr
    Iterator operator++(this auto&& self, int) {
      while (self.iterator != std::end(self.view->container) and not self.view->predicate(++self.iterator)) {}
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
    return {std::begin(self.container), &self};
  }

  constexpr
  Iterator end(this auto&& self) {
    return {std::end(self.container), &self};
  }

  Container& container;
  Functor predicate;
};

template<typename Functor>
struct FilterAdaptor {
  Functor functor;
};

template<Range Container, typename Functor>
constexpr
FilterView<Container, Functor> operator|(Container&& container, FilterAdaptor<Functor>&& adaptor) {
  return {std::forward<Container>(container), std::forward<Functor>(adaptor.functor)};
}

template<typename Functor>
FilterAdaptor<Functor> filter(Functor&& functor) {
  return {std::forward<Functor>(functor)};
}

}
