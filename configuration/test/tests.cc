#include <configuration.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct Config {};

TEST_CASE("configuration") {
  Configuration<Config> configuration;
}
