#include "support.hh"

#include <uuid.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/seq/Operations.h>
#include <rapidcheck/catch.h>

using namespace flp;

TEST_CASE("`UUID`") {
  UUID::UUID uuid;
}
