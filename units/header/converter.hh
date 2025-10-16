#pragma once

#include <dimension.hh>
#include <system.hh>

namespace flp {

template<Dimension dimension, System system1, System system2>
struct Converter{};

template<Dimension dimension, System system>
struct Converter<dimension, system, system> {
  // constexpr auto operator()(Unit value) {
  //   return value;
  // }
};

}
