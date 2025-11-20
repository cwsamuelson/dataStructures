#include <testing/framework/test-case.hh>

#include <stdexcept>

TEST_CASE("A") {
  CHECK(false);
}

TEST_CASE("B") {
  CHECK(true);
}
