#include <template.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

TEST_CASE("`Template`") {
  rc::prop("different major", [](const size_t var) {
    RC_ASSERT(true);
  });
}
