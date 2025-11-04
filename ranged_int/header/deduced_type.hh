#pragma once

#include <core/range.hh>

#include <cstdint>
#include <limits>

namespace flp {

// using BoundRange like this doesn't work how I want it to
// The problem is that it doesn't support negative values, and using a negative type instead can't support the upper range of i.e. size_t
// using BoundRange = Range<size_t>;

namespace {

template<Range>
struct DeducedTypeImpl;

template<Range range>
  requires(range.start >= 0
       and range.finish <= std::numeric_limits<uint8_t>::max()
  )
struct DeducedTypeImpl<range> {
  using type = uint8_t;
};

template<Range range>
  requires(range.start >= 0
       and range.finish <= std::numeric_limits<uint16_t>::max()
       and range.finish > std::numeric_limits<uint8_t>::max()
  )
struct DeducedTypeImpl<range> {
  using type = uint16_t;
};

template<Range range>
  requires(range.start >= 0
       and range.finish <= std::numeric_limits<uint32_t>::max()
       and range.finish > std::numeric_limits<uint16_t>::max()
  )
struct DeducedTypeImpl<range> {
  using type = uint32_t;
};

template<Range range>
  requires(range.start >= 0
       and range.finish <= std::numeric_limits<uint64_t>::max()
       and range.finish > std::numeric_limits<uint32_t>::max()
  )
struct DeducedTypeImpl<range> {
  using type = uint64_t;
};

template<Range range>
  requires(range.start < 0
       and range.start >= std::numeric_limits<int8_t>::min()
       and range.finish <= std::numeric_limits<int8_t>::max()
  )
struct DeducedTypeImpl<range> {
  using type = int8_t;
};

template<Range range>
  requires(range.start < 0
       and range.start >= std::numeric_limits<int16_t>::min()
       and range.finish <= std::numeric_limits<int16_t>::max()
       and (range.start<std::numeric_limits<int8_t>::min()
         or range.finish> std::numeric_limits<int8_t>::max()
       )
  )
struct DeducedTypeImpl<range> {
  using type = int16_t;
};

template<Range range>
  requires(range.start < 0
       and range.start >= std::numeric_limits<int32_t>::min()
       and range.finish <= std::numeric_limits<int32_t>::max()
       and (range.start<std::numeric_limits<int16_t>::min()
         or range.finish> std::numeric_limits<int16_t>::max()
       )
  )
struct DeducedTypeImpl<range> {
  using type = int32_t;
};

template<Range range>
  requires(range.start < 0
       and range.start >= std::numeric_limits<int64_t>::min()
       and range.finish <= std::numeric_limits<int64_t>::max()
       and (range.start<std::numeric_limits<int32_t>::min()
         or range.finish> std::numeric_limits<int32_t>::max()
      )
  )
struct DeducedTypeImpl<range> {
  using type = int64_t;
};

}

template<Range range>
using DeducedType = typename DeducedTypeImpl<range>::type;

}
