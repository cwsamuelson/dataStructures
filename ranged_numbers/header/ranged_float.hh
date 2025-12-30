#pragma once

#include <core/range.hh>

namespace flp {

// Float with range

template<Range ValueRange, typename Policy = ErrorPolicy>
struct RangedFloat {
};

// Float with precision?

template<size_t Mantissa, typename Policy = ErrorPolicy>
struct PrecisedFloat {
};

}
