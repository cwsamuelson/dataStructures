#pragma once

//#include <>

namespace flp::ranges {

struct AllView {
};

template<typename Type, Range<Type>, Range>
struct All_t {
  struct Iterator {
  };

  All_t(Range&& range)
  {}

  //AllView operator|const auto 

  Iterator begin(this auto&& self) {
    return {};
  }

  Iterator end(this auto&& self) {
    return {};
  }
};

static constexpr All = All_t{};

template<typename Type, Range<Type> Range>
struct All;

template<BareRange Range>
struct RangeTraits {
  using type = decltype(*std::begin(std::declval<Range>()));
};

template<typename Range>
All(Range) -> All<typename RangeTraits<Range>::type, Range>;

static_assert(Range<All<int, int[5]>, int>);

} // namespace flp

