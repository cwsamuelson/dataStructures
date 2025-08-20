#include <shapes/functions.hh>
#include <shapes/vec2.hh>
#include <shapes/vec3.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Shapes: `vec2`") {
  SECTION("Default ctor") {
    constexpr vec2 v;

    STATIC_CHECK(v.x == 0.F);
    STATIC_CHECK(v.y == 0.F);

    STATIC_CHECK(v == vec2{});
    STATIC_CHECK(v == vec2{ 0.F });
    STATIC_CHECK(v == vec2{ 0.F, 0.F });
    STATIC_CHECK(2.F * v == v);
    STATIC_CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    constexpr vec2 v(3.F);

    STATIC_CHECK(v.x == 3.F);
    STATIC_CHECK(v.y == 3.F);

    STATIC_CHECK(v == vec2{ 3.F });
    STATIC_CHECK(v == vec2{ 3.F, 3.F });
    STATIC_CHECK(2.F * v == vec2{ 6.F });
    STATIC_CHECK(v * 2.F == vec2{ 6.F });

    STATIC_CHECK(v > vec2{});
    STATIC_CHECK(v >= vec2{});
    STATIC_CHECK(vec2{} < v);
    STATIC_CHECK(vec2{} <= v);
    STATIC_CHECK(v != vec2{});
  }
}

TEST_CASE("Shapes: `vec3`") {
  SECTION("Default ctor") {
    constexpr vec3 v;

    STATIC_CHECK(v.x == 0.F);
    STATIC_CHECK(v.y == 0.F);
    STATIC_CHECK(v.z == 0.F);

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
    STATIC_CHECK(v.z == 3.F);

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

TEST_CASE("Shapes: `vec4`") {
  SECTION("Default ctor") {
    constexpr vec4 v;

    STATIC_CHECK(v.x == 0.F);
    STATIC_CHECK(v.y == 0.F);
    STATIC_CHECK(v.z == 0.F);
    STATIC_CHECK(v.w == 0.F);

    STATIC_CHECK(v == vec4{});
    STATIC_CHECK(v == vec4{ 0.F });
    STATIC_CHECK(v == vec4{ 0.F, 0.F, 0.F, 0.F });
    STATIC_CHECK(2.F * v == v);
    STATIC_CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    constexpr vec4 v(3.F);

    STATIC_CHECK(v.x == 3.F);
    STATIC_CHECK(v.y == 3.F);
    STATIC_CHECK(v.z == 3.F);
    STATIC_CHECK(v.w == 3.F);

    STATIC_CHECK(v == vec4{ 3.F });
    STATIC_CHECK(v == vec4{ 3.F, 3.F, 3.F, 3.f });
    STATIC_CHECK(2.F * v == vec4{ 6.F });
    STATIC_CHECK(v * 2.F == vec4{ 6.F });

    STATIC_CHECK(v > vec4{});
    STATIC_CHECK(v >= vec4{});
    STATIC_CHECK(vec4{} < v);
    STATIC_CHECK(vec4{} <= v);
    STATIC_CHECK(v != vec4{});
  }
}

TEST_CASE("Shapes: functions") {
  SECTION("Sign") {
    //float sign(float f)
    STATIC_CHECK(sign(0.f) == 0.f);
    STATIC_CHECK(sign(1.f) == 1.f);
    STATIC_CHECK(sign(-1.f) == -1.f);
    STATIC_CHECK(sign(2.f) == 1.f);
    STATIC_CHECK(sign(-2.f) == -1.f);
    STATIC_CHECK(sign(3.14f) == 1.f);
    STATIC_CHECK(sign(-3.14f) == -1.f);

    //vec2 sign(vec2 f)
    STATIC_CHECK(sign(vec2{ 0.f, 3.f }) == vec2{ 0.f, 1.f });
    STATIC_CHECK(sign(vec2{ -1.f, 3.2f }) == vec2{ -1.f, 1.f });

    //vec3 sign(vec3 f)
    STATIC_CHECK(sign(vec3{ 0.f, 3.f, -2.46 }) == vec3{ 0.f, 1.f, -1.f });
    STATIC_CHECK(sign(vec3{ -1.f, 3.2f, 0.f }) == vec3{ -1.f, 1.f, 0.f });

    //vec4 sign(vec4 f)
    STATIC_CHECK(sign(vec4{ 0.f, 3.f, -2.46, -0.f }) == vec4{ 0.f, 1.f, -1.f, 0.f });
    STATIC_CHECK(sign(vec4{ -1.f, 3.2f, 0.f, 1.f }) == vec4{ -1.f, 1.f, 0.f, 1.f });
  }

  SECTION("Clamp") {
    //float clamp(float f, float l, float h)
    STATIC_CHECK(clamp(.5f, .0f, 1.f) == .5f);
    STATIC_CHECK(clamp(.5f, 1.2f, 6.7f) == 1.2f);
    STATIC_CHECK(clamp(.5f, -1.f, .3f) == .3f);

    //vec2 clamp(vec2 f, vec2 l, vec2 h)
    STATIC_CHECK(clamp(vec2{ .5f, .5f }, vec2{ .0f, 1.2f }, vec2{ 1.f, 6.7f }) == vec2{ .5f, 1.2f });
    STATIC_CHECK(clamp(vec2{ .5f, 12.f }, vec2{ -1.f, 10.f }, vec2{ .3f, 11.f }) == vec2{ .3f, 11.f });

    //vec2 clamp(vec2 f, float l, float h)
    STATIC_CHECK(clamp(vec2{ .5f, 15.f }, 1.f, 10.f) == vec2{ 1.f, 10.f });
    STATIC_CHECK(clamp(vec2{ .5f, 12.f }, .0f, .0f) == vec2{ .0f, .0f });

    //vec3 clamp(vec3 f, vec3 l, vec3 h)
    STATIC_CHECK(clamp(vec3{ .5f, .5f, .5f }, vec3{ .0f, 1.2f, -10.f }, vec3{ 1.f, 6.7f, -6.7f }) == vec3{ .5f, 1.2f, -6.7f });

    //vec3 clamp(vec3 f, float l, float h)
    STATIC_CHECK(clamp(vec3{ .5f, 3.f, 7.f }, 2.3f, 5.f) == vec3{ 2.3f, 3.f, 5.f });
  }

  SECTION("abs") {
    //float abs(float f)
    //vec2 abs(vec2 v)
    //vec3 abs(vec3 v)
    //vec4 abs(vec4 v)
  }

  SECTION("dot") {
    //float dot(vec2, vec2)
    //float dot(vec3, vec3)
    //float dot(vec4, vec4)

    //float dot2(vec2 v)
    //float dot2(vec4 v)
    //float ndot(vec2 a, vec2 b)
  }

  SECTION("length") {
    //float length(const vec2& vector)
    STATIC_CHECK(length(vec2{ 1.f, 0.f }) == 1.f);
    STATIC_CHECK(length(vec2{ 0.f, 1.f }) == 1.f);
    STATIC_CHECK(length(vec2{ 3.f, 0.f }) == 3.f);
    STATIC_CHECK(length(vec2{ 0.f, 3.f }) == 3.f);
    STATIC_CHECK(length(vec2{ 3.f, 4.f }) == 5.f);

    //float length(const vec3& vector)
    STATIC_CHECK(length(vec3{ 1.f, 0.f, 0.f }) == 1.f);
    STATIC_CHECK(length(vec3{ 0.f, 1.f, 0.f }) == 1.f);
    STATIC_CHECK(length(vec3{ 0.f, 0.f, 1.f }) == 1.f);
    STATIC_CHECK(length(vec3{ 3.f, 0.f, 0.f }) == 3.f);
    STATIC_CHECK(length(vec3{ 0.f, 3.f, 0.f }) == 3.f);
    STATIC_CHECK(length(vec3{ 0.f, 0.f, 3.f }) == 3.f);

    //float length(const vec4& vector)
    STATIC_CHECK(length(vec4{ 1.f, 0.f, 0.f, 0.f }) == 1.f);
    STATIC_CHECK(length(vec4{ 0.f, 1.f, 0.f, 0.f }) == 1.f);
    STATIC_CHECK(length(vec4{ 0.f, 0.f, 1.f, 0.f }) == 1.f);
    STATIC_CHECK(length(vec4{ 0.f, 0.f, 0.f, 1.f }) == 1.f);

    STATIC_CHECK(length(vec4{ 3.f, 0.f, 0.f, 0.f }) == 3.f);
    STATIC_CHECK(length(vec4{ 0.f, 3.f, 0.f, 0.f }) == 3.f);
    STATIC_CHECK(length(vec4{ 0.f, 0.f, 3.f, 0.f }) == 3.f);
    STATIC_CHECK(length(vec4{ 0.f, 0.f, 0.f, 3.f }) == 3.f);
  }

  SECTION("minmax") {
    //float min(float a, float b)
    //float max(float a, float b)

    //vec2 min(vec2 a, vec2 b)
    //vec2 max(vec2 a, vec2 b)

    //vec3 min(vec3 a, vec3 b)
    //vec3 max(vec3 a, vec3 b)

    //vec4 min(vec4 a, vec4 b)
    //vec4 max(vec4 a, vec4 b)
  }
}

TEST_CASE("Shapes: swizzling") {
}
