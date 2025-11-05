#pragma once

#include <bitset>

namespace flp::UUID {

struct V1 {
  V1(std::bitset<60> timestamp);
};

}
