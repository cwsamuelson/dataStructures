#pragma once

#include <core/concepts.hh>

namespace flp::views {

template<typename Type, flp::Range<Type> Range>
struct All {
  All(Range&& range) {}

  struct Iterator {
    Type operator*() {
      return {};
    }
  };

  Iterator begin() {
    return {};
  }

  Iterator end() {
    return {};
  }
};

template<flp::BareRange Range>
struct RangeTraits {
  using type = decltype(*std::begin(std::declval<Range>()));
};

template<typename Range>
All(Range) -> All<typename RangeTraits<Range>::type, Range>;

static_assert(flp::Range<All<int, int[5]>, int>);

}

