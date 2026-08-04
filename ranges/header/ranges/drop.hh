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

  constexpr
  auto begin(this auto&& self) noexcept {
    auto iterator = std::begin(self.container);
    // advance the iterator, but don't advance past the end
    std::advance(iterator, std::min(self.counter, (size_t)std::distance(std::begin(self.container), std::end(self.container))));
    return iterator;
  }

  constexpr
  auto end(this auto&& self) noexcept {
    return self.container.end();
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
DropAdaptor drop(const size_t counter) noexcept {
  return {counter};
}

}
