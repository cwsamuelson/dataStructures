#include "testing/test_registry.hh"

#include <memory>

namespace flp {

TestRegistry& TestRegistry::instance() {
  if (instance_impl == nullptr) {
    instance_impl = std::make_unique<TestRegistry>();
  }

  return *instance_impl;
}

TestRegistry::TestRegistry() = default;

TestRegistry::~TestRegistry() = default;

}
