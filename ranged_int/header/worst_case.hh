#pragma once

#include "deduced_type.hh"

namespace flp {

template<Range op1_range, Range op2_range, typename Op>
struct WorstCaseRange {
  constexpr static std::array values { Op {}(op1_range.start, op2_range.start),
                                       Op {}(op1_range.start, op2_range.finish),
                                       Op {}(op1_range.finish, op2_range.start),
                                       Op {}(op1_range.finish, op2_range.finish) };

  constexpr static Range range = {
    *std::ranges::min_element(values),
    *std::ranges::max_element(values),
  };

  using Type = DeducedType<range>;
};

}
