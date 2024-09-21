#pragma once

#include <measure.hh>
#include <system.hh>

namespace flp {

template<typename Type, Measure measure, System system>
struct Unit {
  Type value;
};

} // namespace flp
