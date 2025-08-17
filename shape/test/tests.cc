#include <shapes/vec2.hh>
#include <shapes/vec3.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Shapes: `vec2`") {
  SECTION("Default ctor") {
    const vec2 v;

    CHECK(v.x == 0.F);
    CHECK(v.y == 0.F);

    CHECK(v == vec2{});
    CHECK(v == vec2{ 0.F });
    CHECK(v == vec2{ 0.F, 0.F });
    CHECK(2.F * v == v);
    CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    const vec2 v(3.F);

    CHECK(v.x == 3.F);
    CHECK(v.y == 3.F);

    CHECK(v == vec2{ 3.F });
    CHECK(v == vec2{ 3.F, 3.F });
    CHECK(2.F * v == vec2{ 6.F });
    CHECK(v * 2.F == vec2{ 6.F });

    CHECK(v > vec2{});
    CHECK(v >= vec2{});
    CHECK(vec2{} < v);
    CHECK(vec2{} <= v);
    CHECK(v != vec2{});
  }
}

TEST_CASE("Shapes: `vec3`") {
  SECTION("Default ctor") {
    constexpr vec3 v;

    STATIC_CHECK(v.x == 0.F);
    STATIC_CHECK(v.y == 0.F);

    STATIC_CHECK(v == vec3{});
    STATIC_CHECK(v == vec3{ 0.F });
    STATIC_CHECK(v == vec3{ 0.F, 0.F, 0.F });
    STATIC_CHECK(2.F * v == v);
    STATIC_CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    constexpr vec3 v(3.F);

    STATIC_CHECK(v.x == 3.F);
    STATIC_CHECK(v.y == 3.F);

    STATIC_CHECK(v == vec3{ 3.F });
    STATIC_CHECK(v == vec3{ 3.F, 3.F, 3.F });
    STATIC_CHECK(2.F * v == vec3{ 6.F });
    STATIC_CHECK(v * 2.F == vec3{ 6.F });

    STATIC_CHECK(v > vec3{});
    STATIC_CHECK(v >= vec3{});
    STATIC_CHECK(vec3{} < v);
    STATIC_CHECK(vec3{} <= v);
    STATIC_CHECK(v != vec3{});
  }
}

TEST_CASE("Shapes: functions") {
}

TEST_CASE("Shapes: swizzling") {
}
