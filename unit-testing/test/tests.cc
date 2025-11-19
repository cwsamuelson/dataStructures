#include <testing/framework.hh>

#include <stdexcept>

#include <print>

TEST_CASE("A") {
  std::println("hello?");
  throw std::runtime_error("nope");
}

TEST_CASE("B") {
  std::println("Hello, there!");
  throw std::runtime_error("yepp");
}
