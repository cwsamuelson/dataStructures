#pragma once

#include "ranges/traits.hh"

namespace flp::views {

template<typename Container, typename Functor>
struct TransformView {
  constexpr
  TransformView(Container& cntnr, Functor&& functor)
    : container(cntnr)
    , predicate(std::forward<Functor>(functor))
  {}

  struct Iterator {
    using Iter = decltype(std::begin(std::declval<Container>()));
    Iter iterator;
    TransformView* view;

    constexpr
    decltype(auto) operator*(this auto&& self) {
      return self.view->predicate(*self.iterator);
    }

    constexpr
    decltype(auto) operator->(this auto&& self) {
      return &self.view->predicate(*self.iterator);
    }

    constexpr
    Iterator& operator++(this auto&& self) {
      ++self.iterator;
      return self;
    }

    constexpr
    Iterator operator++(this auto&& self, int) {
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
struct TransformAdaptor {
  Functor functor;
};

template<Range Container, typename Functor>
constexpr
TransformView<Container, Functor> operator|(Container&& container, TransformAdaptor<Functor>&& adaptor) {
  return {std::forward<Container>(container), std::forward<Functor>(adaptor.functor)};
}

template<typename Functor>
TransformAdaptor<Functor> transform(Functor&& functor) {
  return {std::forward<Functor>(functor)};
}

}
