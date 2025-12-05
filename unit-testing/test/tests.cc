#include <testing/framework/test-case.hh>
#include <testing/framework/check.hh>

#include <stdexcept>

TEST_CASE("A") {
  CHECK(true);
}

TEST_CASE("B") {
  CHECK(false);
}
