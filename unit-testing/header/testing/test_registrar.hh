#pragma once

#include "testing/test_registry.hh"

#include <source_location>
#include <string>

namespace flp {

struct TestAutoRegistrar {
  template<typename Functor>
  TestAutoRegistrar(
    const std::source_location location,
    const std::string& name,
    Functor&& functor) {
    TestRegistry::instance().tests.emplace(name, std::forward<Functor>(functor));
  }
};

}
