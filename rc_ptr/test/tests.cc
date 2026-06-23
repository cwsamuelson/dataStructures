#include <rc_ptr.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

TEST_CASE("`RCPtr`") {
  rc::prop("Something", [](const size_t var) {
    RCPtr<int> rc;

    RC_ASSERT(true);
  });
}
