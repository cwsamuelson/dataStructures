#include <testing/framework.hh>

#include <stdexcept>

#include <print>

TEST_CASE() {
  std::println("hello?");
  throw std::runtime_error("nope");
}

TEST_CASE() {
  std::println("Hello, there!");
  throw std::runtime_error("yepp");
}
