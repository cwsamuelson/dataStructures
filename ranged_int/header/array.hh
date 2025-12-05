#pragma once

#include <ranged_int.hh>

namespace flp {

// the array should be able to be specified by the range itself, or by array size.
// `Array<T, {X, Y}>` or `Array<T, N>`

template<typename Type, size_t Count, typename Policy = ErrorPolicy>
struct Array {
  Type values[Count];

  using Index = RangedInt<{}, Policy>;
};

}
