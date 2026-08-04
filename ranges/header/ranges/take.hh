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

  constexpr
  auto begin(this auto&& self) noexcept {
    return std::begin(self.container);
  }

  constexpr
  auto end(this auto&& self) noexcept {
    auto iterator = std::begin(self.container);
    std::advance(iterator, std::min(self.counter, (size_t)std::distance(std::begin(self.container), std::end(self.container))));
    return iterator;
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
