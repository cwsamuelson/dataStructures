#pragma once

#include <source_location>
#include <string>

namespace flp {

struct TestAutoRegistrar {
  template<typename Functor>
  TestAutoRegistrar(
    const std::source_location location,
    Functor&& functor) {
  }
};

}
