#pragma once

#include "core/random/random.hh"

#include <fstream>
#include <limits>

namespace flp::Random {

struct DevRandom {
  using Result = size_t;

  static
  Result min() noexcept {
    return std::numeric_limits<Result>::min();
  }

  static
  Result max() noexcept {
    return std::numeric_limits<Result>::max();
  }

  [[nodiscard]]
  Result operator()() {
    std::ifstream random("/dev/random", std::ios::in | std::ios::binary);

    Result result;
    random.read(reinterpret_cast<char*>(&result), sizeof(result));

    return result;
  }
};
static_assert(Source<DevRandom>);

}
