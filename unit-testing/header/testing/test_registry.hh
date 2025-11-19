#pragma once

#include <functional>
#include <map>
#include <memory>

namespace flp {

struct TestRegistry {
  static TestRegistry& instance();

  std::map<std::string, std::function<void()>> tests;

private:
  friend class std::unique_ptr<TestRegistry>;
  friend class std::default_delete<TestRegistry>;
  friend constexpr std::unique_ptr<TestRegistry> std::make_unique<TestRegistry>();

  TestRegistry();
  ~TestRegistry();

  static inline std::unique_ptr<TestRegistry> instance_impl;
};

}
