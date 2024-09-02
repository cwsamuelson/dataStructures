#include <catch2/catch_all.hpp>

#include <core/traits.hh>

template<typename>
struct Template {};

TEST_CASE("") {
  CHECK(flp::is_specialization_of<Template<int>, Template>);
  CHECK(not flp::is_specialization_of<int, Template>);
}

