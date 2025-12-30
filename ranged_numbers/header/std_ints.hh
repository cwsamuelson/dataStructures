#pragma once

#include "ranged_int.hh"

#include <cstdint>
#include <limits>

namespace flp {

using u8  = RangedInt<{
  std::numeric_limits<uint8_t>::min(),
  std::numeric_limits<uint8_t>::max()
}>;
using s8  = RangedInt<{
  std::numeric_limits<int8_t>::min(),
  std::numeric_limits<int8_t>::max()
}>;

using u16 = RangedInt<{
  std::numeric_limits<uint16_t>::min(),
  std::numeric_limits<uint16_t>::max()
}>;
using s16 = RangedInt<{
  std::numeric_limits<int16_t>::min(),
  std::numeric_limits<int16_t>::max()
}>;

using u32 = RangedInt<{
  std::numeric_limits<uint32_t>::min(),
  std::numeric_limits<uint32_t>::max()
}>;
using s32 = RangedInt<{
  std::numeric_limits<int32_t>::min(),
  std::numeric_limits<int32_t>::max()
}>;

using u64 = RangedInt<{
  std::numeric_limits<uint64_t>::min(),
  std::numeric_limits<uint64_t>::max()
}>;
using s64 = RangedInt<{
  std::numeric_limits<int64_t>::min(),
  std::numeric_limits<int64_t>::max()
}>;

}
