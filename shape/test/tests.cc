#include <shapes/functions.hh>
#include <shapes/swizzling.hh>
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
  SECTION("vec2") {
    vec2 vec(1.f, 2.f);

    SECTION("vec2 result") {
      CHECK(vec.xx() == vec2{ 1.f, 1.f });
      CHECK(vec.xy() == vec2{ 1.f, 2.f });
      CHECK(vec.yx() == vec2{ 2.f, 1.f });
      CHECK(vec.yy() == vec2{ 2.f, 2.f });

      vec.xx() = vec2{ 3.f, 4.f };
      CHECK(vec == vec2{ 4.f, 2.f });
      CHECK(vec.x == 4.f);
      CHECK(vec.y == 2.f);
    }

    SECTION("vec3 result") {
    }

    SECTION("vec4 result") {
    }
  }

  SECTION("vec3") {
    vec3 vec(1.f, 2.f, 3.f);

    SECTION("vec2 result") {
      //CHECK(vec.xx() == vec2{ 1.f, 1.f });
      //CHECK(vec.xy() == vec2{ 1.f, 2.f });
      //CHECK(vec.yx() == vec2{ 2.f, 1.f });
      //CHECK(vec.yy() == vec2{ 2.f, 2.f });

      //vec.xx() = vec2{ 3.f, 4.f };
      //CHECK(vec == vec2{ 4.f, 2.f });
      //CHECK(vec.x == 4.f);
      //CHECK(vec.y == 2.f);
    }

    SECTION("vec3 result") {
      CHECK(vec.xxx() == vec3{ 1.f, 1.f, 1.f });
      CHECK(vec.xxy() == vec3{ 1.f, 1.f, 2.f });
      CHECK(vec.xxz() == vec3{ 1.f, 1.f, 3.f });
      CHECK(vec.xyx() == vec3{ 1.f, 2.f, 1.f });
      CHECK(vec.xyy() == vec3{ 1.f, 2.f, 2.f });
      CHECK(vec.xyz() == vec3{ 1.f, 2.f, 3.f });
      CHECK(vec.xzx() == vec3{ 1.f, 3.f, 1.f });
      CHECK(vec.xzy() == vec3{ 1.f, 3.f, 2.f });
      CHECK(vec.xzz() == vec3{ 1.f, 3.f, 3.f });
      CHECK(vec.yxx() == vec3{ 2.f, 1.f, 1.f });
      CHECK(vec.yxy() == vec3{ 2.f, 1.f, 2.f });
      CHECK(vec.yxz() == vec3{ 2.f, 1.f, 3.f });
      CHECK(vec.yyx() == vec3{ 2.f, 2.f, 1.f });
      CHECK(vec.yyy() == vec3{ 2.f, 2.f, 2.f });
      CHECK(vec.yyz() == vec3{ 2.f, 2.f, 3.f });
      CHECK(vec.yzx() == vec3{ 2.f, 3.f, 1.f });
      CHECK(vec.yzy() == vec3{ 2.f, 3.f, 2.f });
      CHECK(vec.yzz() == vec3{ 2.f, 3.f, 3.f });
      CHECK(vec.zxx() == vec3{ 3.f, 1.f, 1.f });
      CHECK(vec.zxy() == vec3{ 3.f, 1.f, 2.f });
      CHECK(vec.zxz() == vec3{ 3.f, 1.f, 3.f });
      CHECK(vec.zyx() == vec3{ 3.f, 2.f, 1.f });
      CHECK(vec.zyy() == vec3{ 3.f, 2.f, 2.f });
      CHECK(vec.zyz() == vec3{ 3.f, 2.f, 3.f });
      CHECK(vec.zzx() == vec3{ 3.f, 3.f, 1.f });
      CHECK(vec.zzy() == vec3{ 3.f, 3.f, 2.f });
      CHECK(vec.zzz() == vec3{ 3.f, 3.f, 3.f });
    }

    SECTION("vec4 result") {
    }
  }

  SECTION("vec4") {
    vec4 vec(1.f, 2.f, 3.f, 4.f);

    SECTION("vec2 result") {
    }

    SECTION("vec3 result") {
    }

    SECTION("vec4 result") {
      CHECK(vec.xxxx() == vec4{ 1.f, 1.f, 1.f, 1.f });
      CHECK(vec.xxxy() == vec4{ 1.f, 1.f, 1.f, 2.f });
      CHECK(vec.xxxz() == vec4{ 1.f, 1.f, 1.f, 3.f });
      CHECK(vec.xxxw() == vec4{ 1.f, 1.f, 1.f, 4.f });
      CHECK(vec.xxyx() == vec4{ 1.f, 1.f, 2.f, 1.f });
      CHECK(vec.xxyy() == vec4{ 1.f, 1.f, 2.f, 2.f });
      CHECK(vec.xxyz() == vec4{ 1.f, 1.f, 2.f, 3.f });
      CHECK(vec.xxyw() == vec4{ 1.f, 1.f, 2.f, 4.f });
      CHECK(vec.xxzx() == vec4{ 1.f, 1.f, 3.f, 1.f });
      CHECK(vec.xxzy() == vec4{ 1.f, 1.f, 3.f, 2.f });
      CHECK(vec.xxzz() == vec4{ 1.f, 1.f, 3.f, 3.f });
      CHECK(vec.xxzw() == vec4{ 1.f, 1.f, 3.f, 4.f });
      CHECK(vec.xxwx() == vec4{ 1.f, 1.f, 4.f, 1.f });
      CHECK(vec.xxwy() == vec4{ 1.f, 1.f, 4.f, 2.f });
      CHECK(vec.xxwz() == vec4{ 1.f, 1.f, 4.f, 3.f });
      CHECK(vec.xxww() == vec4{ 1.f, 1.f, 4.f, 4.f });
      CHECK(vec.xyxx() == vec4{ 1.f, 2.f, 1.f, 1.f });
      CHECK(vec.xyxy() == vec4{ 1.f, 2.f, 1.f, 2.f });
      CHECK(vec.xyxz() == vec4{ 1.f, 2.f, 1.f, 3.f });
      CHECK(vec.xyxw() == vec4{ 1.f, 2.f, 1.f, 4.f });
      CHECK(vec.xyyx() == vec4{ 1.f, 2.f, 2.f, 1.f });
      CHECK(vec.xyyy() == vec4{ 1.f, 2.f, 2.f, 2.f });
      CHECK(vec.xyyz() == vec4{ 1.f, 2.f, 2.f, 3.f });
      CHECK(vec.xyyw() == vec4{ 1.f, 2.f, 2.f, 4.f });
      CHECK(vec.xyzx() == vec4{ 1.f, 2.f, 3.f, 1.f });
      CHECK(vec.xyzy() == vec4{ 1.f, 2.f, 3.f, 2.f });
      CHECK(vec.xyzz() == vec4{ 1.f, 2.f, 3.f, 3.f });
      CHECK(vec.xyzw() == vec4{ 1.f, 2.f, 3.f, 4.f });
      CHECK(vec.xywx() == vec4{ 1.f, 2.f, 4.f, 1.f });
      CHECK(vec.xywy() == vec4{ 1.f, 2.f, 4.f, 2.f });
      CHECK(vec.xywz() == vec4{ 1.f, 2.f, 4.f, 3.f });
      CHECK(vec.xyww() == vec4{ 1.f, 2.f, 4.f, 4.f });
      CHECK(vec.xzxx() == vec4{ 1.f, 3.f, 1.f, 1.f });
      CHECK(vec.xzxy() == vec4{ 1.f, 3.f, 1.f, 2.f });
      CHECK(vec.xzxz() == vec4{ 1.f, 3.f, 1.f, 3.f });
      CHECK(vec.xzxw() == vec4{ 1.f, 3.f, 1.f, 4.f });
      CHECK(vec.xzyx() == vec4{ 1.f, 3.f, 2.f, 1.f });
      CHECK(vec.xzyy() == vec4{ 1.f, 3.f, 2.f, 2.f });
      CHECK(vec.xzyz() == vec4{ 1.f, 3.f, 2.f, 3.f });
      CHECK(vec.xzyw() == vec4{ 1.f, 3.f, 2.f, 4.f });
      CHECK(vec.xzzx() == vec4{ 1.f, 3.f, 3.f, 1.f });
      CHECK(vec.xzzy() == vec4{ 1.f, 3.f, 3.f, 2.f });
      CHECK(vec.xzzz() == vec4{ 1.f, 3.f, 3.f, 3.f });
      CHECK(vec.xzzw() == vec4{ 1.f, 3.f, 3.f, 4.f });
      CHECK(vec.xzwx() == vec4{ 1.f, 3.f, 4.f, 1.f });
      CHECK(vec.xzwy() == vec4{ 1.f, 3.f, 4.f, 2.f });
      CHECK(vec.xzwz() == vec4{ 1.f, 3.f, 4.f, 3.f });
      CHECK(vec.xzww() == vec4{ 1.f, 3.f, 4.f, 4.f });
      CHECK(vec.xwxx() == vec4{ 1.f, 4.f, 1.f, 1.f });
      CHECK(vec.xwxy() == vec4{ 1.f, 4.f, 1.f, 2.f });
      CHECK(vec.xwxz() == vec4{ 1.f, 4.f, 1.f, 3.f });
      CHECK(vec.xwxw() == vec4{ 1.f, 4.f, 1.f, 4.f });
      CHECK(vec.xwyx() == vec4{ 1.f, 4.f, 2.f, 1.f });
      CHECK(vec.xwyy() == vec4{ 1.f, 4.f, 2.f, 2.f });
      CHECK(vec.xwyz() == vec4{ 1.f, 4.f, 2.f, 3.f });
      CHECK(vec.xwyw() == vec4{ 1.f, 4.f, 2.f, 4.f });
      CHECK(vec.xwzx() == vec4{ 1.f, 4.f, 3.f, 1.f });
      CHECK(vec.xwzy() == vec4{ 1.f, 4.f, 3.f, 2.f });
      CHECK(vec.xwzz() == vec4{ 1.f, 4.f, 3.f, 3.f });
      CHECK(vec.xwzw() == vec4{ 1.f, 4.f, 3.f, 4.f });
      CHECK(vec.xwwx() == vec4{ 1.f, 4.f, 4.f, 1.f });
      CHECK(vec.xwwy() == vec4{ 1.f, 4.f, 4.f, 2.f });
      CHECK(vec.xwwz() == vec4{ 1.f, 4.f, 4.f, 3.f });
      CHECK(vec.xwww() == vec4{ 1.f, 4.f, 4.f, 4.f });
      CHECK(vec.yxxx() == vec4{ 2.f, 1.f, 1.f, 1.f });
      CHECK(vec.yxxy() == vec4{ 2.f, 1.f, 1.f, 2.f });
      CHECK(vec.yxxz() == vec4{ 2.f, 1.f, 1.f, 3.f });
      CHECK(vec.yxxw() == vec4{ 2.f, 1.f, 1.f, 4.f });
      CHECK(vec.yxyx() == vec4{ 2.f, 1.f, 2.f, 1.f });
      CHECK(vec.yxyy() == vec4{ 2.f, 1.f, 2.f, 2.f });
      CHECK(vec.yxyz() == vec4{ 2.f, 1.f, 2.f, 3.f });
      CHECK(vec.yxyw() == vec4{ 2.f, 1.f, 2.f, 4.f });
      CHECK(vec.yxzx() == vec4{ 2.f, 1.f, 3.f, 1.f });
      CHECK(vec.yxzy() == vec4{ 2.f, 1.f, 3.f, 2.f });
      CHECK(vec.yxzz() == vec4{ 2.f, 1.f, 3.f, 3.f });
      CHECK(vec.yxzw() == vec4{ 2.f, 1.f, 3.f, 4.f });
      CHECK(vec.yxwx() == vec4{ 2.f, 1.f, 4.f, 1.f });
      CHECK(vec.yxwy() == vec4{ 2.f, 1.f, 4.f, 2.f });
      CHECK(vec.yxwz() == vec4{ 2.f, 1.f, 4.f, 3.f });
      CHECK(vec.yxww() == vec4{ 2.f, 1.f, 4.f, 4.f });
      CHECK(vec.yyxx() == vec4{ 2.f, 2.f, 1.f, 1.f });
      CHECK(vec.yyxy() == vec4{ 2.f, 2.f, 1.f, 2.f });
      CHECK(vec.yyxz() == vec4{ 2.f, 2.f, 1.f, 3.f });
      CHECK(vec.yyxw() == vec4{ 2.f, 2.f, 1.f, 4.f });
      CHECK(vec.yyyx() == vec4{ 2.f, 2.f, 2.f, 1.f });
      CHECK(vec.yyyy() == vec4{ 2.f, 2.f, 2.f, 2.f });
      CHECK(vec.yyyz() == vec4{ 2.f, 2.f, 2.f, 3.f });
      CHECK(vec.yyyw() == vec4{ 2.f, 2.f, 2.f, 4.f });
      CHECK(vec.yyzx() == vec4{ 2.f, 2.f, 3.f, 1.f });
      CHECK(vec.yyzy() == vec4{ 2.f, 2.f, 3.f, 2.f });
      CHECK(vec.yyzz() == vec4{ 2.f, 2.f, 3.f, 3.f });
      CHECK(vec.yyzw() == vec4{ 2.f, 2.f, 3.f, 4.f });
      CHECK(vec.yywx() == vec4{ 2.f, 2.f, 4.f, 1.f });
      CHECK(vec.yywy() == vec4{ 2.f, 2.f, 4.f, 2.f });
      CHECK(vec.yywz() == vec4{ 2.f, 2.f, 4.f, 3.f });
      CHECK(vec.yyww() == vec4{ 2.f, 2.f, 4.f, 4.f });
      CHECK(vec.yzxx() == vec4{ 2.f, 3.f, 1.f, 1.f });
      CHECK(vec.yzxy() == vec4{ 2.f, 3.f, 1.f, 2.f });
      CHECK(vec.yzxz() == vec4{ 2.f, 3.f, 1.f, 3.f });
      CHECK(vec.yzxw() == vec4{ 2.f, 3.f, 1.f, 4.f });
      CHECK(vec.yzyx() == vec4{ 2.f, 3.f, 2.f, 1.f });
      CHECK(vec.yzyy() == vec4{ 2.f, 3.f, 2.f, 2.f });
      CHECK(vec.yzyz() == vec4{ 2.f, 3.f, 2.f, 3.f });
      CHECK(vec.yzyw() == vec4{ 2.f, 3.f, 2.f, 4.f });
      CHECK(vec.yzzx() == vec4{ 2.f, 3.f, 3.f, 1.f });
      CHECK(vec.yzzy() == vec4{ 2.f, 3.f, 3.f, 2.f });
      CHECK(vec.yzzz() == vec4{ 2.f, 3.f, 3.f, 3.f });
      CHECK(vec.yzzw() == vec4{ 2.f, 3.f, 3.f, 4.f });
      CHECK(vec.yzwx() == vec4{ 2.f, 3.f, 4.f, 1.f });
      CHECK(vec.yzwy() == vec4{ 2.f, 3.f, 4.f, 2.f });
      CHECK(vec.yzwz() == vec4{ 2.f, 3.f, 4.f, 3.f });
      CHECK(vec.yzww() == vec4{ 2.f, 3.f, 4.f, 4.f });
      CHECK(vec.ywxx() == vec4{ 2.f, 4.f, 1.f, 1.f });
      CHECK(vec.ywxy() == vec4{ 2.f, 4.f, 1.f, 2.f });
      CHECK(vec.ywxz() == vec4{ 2.f, 4.f, 1.f, 3.f });
      CHECK(vec.ywxw() == vec4{ 2.f, 4.f, 1.f, 4.f });
      CHECK(vec.ywyx() == vec4{ 2.f, 4.f, 2.f, 1.f });
      CHECK(vec.ywyy() == vec4{ 2.f, 4.f, 2.f, 2.f });
      CHECK(vec.ywyz() == vec4{ 2.f, 4.f, 2.f, 3.f });
      CHECK(vec.ywyw() == vec4{ 2.f, 4.f, 2.f, 4.f });
      CHECK(vec.ywzx() == vec4{ 2.f, 4.f, 3.f, 1.f });
      CHECK(vec.ywzy() == vec4{ 2.f, 4.f, 3.f, 2.f });
      CHECK(vec.ywzz() == vec4{ 2.f, 4.f, 3.f, 3.f });
      CHECK(vec.ywzw() == vec4{ 2.f, 4.f, 3.f, 4.f });
      CHECK(vec.ywwx() == vec4{ 2.f, 4.f, 4.f, 1.f });
      CHECK(vec.ywwy() == vec4{ 2.f, 4.f, 4.f, 2.f });
      CHECK(vec.ywwz() == vec4{ 2.f, 4.f, 4.f, 3.f });
      CHECK(vec.ywww() == vec4{ 2.f, 4.f, 4.f, 4.f });
      CHECK(vec.zxxx() == vec4{ 3.f, 1.f, 1.f, 1.f });
      CHECK(vec.zxxy() == vec4{ 3.f, 1.f, 1.f, 2.f });
      CHECK(vec.zxxz() == vec4{ 3.f, 1.f, 1.f, 3.f });
      CHECK(vec.zxxw() == vec4{ 3.f, 1.f, 1.f, 4.f });
      CHECK(vec.zxyx() == vec4{ 3.f, 1.f, 2.f, 1.f });
      CHECK(vec.zxyy() == vec4{ 3.f, 1.f, 2.f, 2.f });
      CHECK(vec.zxyz() == vec4{ 3.f, 1.f, 2.f, 3.f });
      CHECK(vec.zxyw() == vec4{ 3.f, 1.f, 2.f, 4.f });
      CHECK(vec.zxzx() == vec4{ 3.f, 1.f, 3.f, 1.f });
      CHECK(vec.zxzy() == vec4{ 3.f, 1.f, 3.f, 2.f });
      CHECK(vec.zxzz() == vec4{ 3.f, 1.f, 3.f, 3.f });
      CHECK(vec.zxzw() == vec4{ 3.f, 1.f, 3.f, 4.f });
      CHECK(vec.zxwx() == vec4{ 3.f, 1.f, 4.f, 1.f });
      CHECK(vec.zxwy() == vec4{ 3.f, 1.f, 4.f, 2.f });
      CHECK(vec.zxwz() == vec4{ 3.f, 1.f, 4.f, 3.f });
      CHECK(vec.zxww() == vec4{ 3.f, 1.f, 4.f, 4.f });
      CHECK(vec.zyxx() == vec4{ 3.f, 2.f, 1.f, 1.f });
      CHECK(vec.zyxy() == vec4{ 3.f, 2.f, 1.f, 2.f });
      CHECK(vec.zyxz() == vec4{ 3.f, 2.f, 1.f, 3.f });
      CHECK(vec.zyxw() == vec4{ 3.f, 2.f, 1.f, 4.f });
      CHECK(vec.zyyx() == vec4{ 3.f, 2.f, 2.f, 1.f });
      CHECK(vec.zyyy() == vec4{ 3.f, 2.f, 2.f, 2.f });
      CHECK(vec.zyyz() == vec4{ 3.f, 2.f, 2.f, 3.f });
      CHECK(vec.zyyw() == vec4{ 3.f, 2.f, 2.f, 4.f });
      CHECK(vec.zyzx() == vec4{ 3.f, 2.f, 3.f, 1.f });
      CHECK(vec.zyzy() == vec4{ 3.f, 2.f, 3.f, 2.f });
      CHECK(vec.zyzz() == vec4{ 3.f, 2.f, 3.f, 3.f });
      CHECK(vec.zyzw() == vec4{ 3.f, 2.f, 3.f, 4.f });
      CHECK(vec.zywx() == vec4{ 3.f, 2.f, 4.f, 1.f });
      CHECK(vec.zywy() == vec4{ 3.f, 2.f, 4.f, 2.f });
      CHECK(vec.zywz() == vec4{ 3.f, 2.f, 4.f, 3.f });
      CHECK(vec.zyww() == vec4{ 3.f, 2.f, 4.f, 4.f });
      CHECK(vec.zzxx() == vec4{ 3.f, 3.f, 1.f, 1.f });
      CHECK(vec.zzxy() == vec4{ 3.f, 3.f, 1.f, 2.f });
      CHECK(vec.zzxz() == vec4{ 3.f, 3.f, 1.f, 3.f });
      CHECK(vec.zzxw() == vec4{ 3.f, 3.f, 1.f, 4.f });
      CHECK(vec.zzyx() == vec4{ 3.f, 3.f, 2.f, 1.f });
      CHECK(vec.zzyy() == vec4{ 3.f, 3.f, 2.f, 2.f });
      CHECK(vec.zzyz() == vec4{ 3.f, 3.f, 2.f, 3.f });
      CHECK(vec.zzyw() == vec4{ 3.f, 3.f, 2.f, 4.f });
      CHECK(vec.zzzx() == vec4{ 3.f, 3.f, 3.f, 1.f });
      CHECK(vec.zzzy() == vec4{ 3.f, 3.f, 3.f, 2.f });
      CHECK(vec.zzzz() == vec4{ 3.f, 3.f, 3.f, 3.f });
      CHECK(vec.zzzw() == vec4{ 3.f, 3.f, 3.f, 4.f });
      CHECK(vec.zzwx() == vec4{ 3.f, 3.f, 4.f, 1.f });
      CHECK(vec.zzwy() == vec4{ 3.f, 3.f, 4.f, 2.f });
      CHECK(vec.zzwz() == vec4{ 3.f, 3.f, 4.f, 3.f });
      CHECK(vec.zzww() == vec4{ 3.f, 3.f, 4.f, 4.f });
      CHECK(vec.zwxx() == vec4{ 3.f, 4.f, 1.f, 1.f });
      CHECK(vec.zwxy() == vec4{ 3.f, 4.f, 1.f, 2.f });
      CHECK(vec.zwxz() == vec4{ 3.f, 4.f, 1.f, 3.f });
      CHECK(vec.zwxw() == vec4{ 3.f, 4.f, 1.f, 4.f });
      CHECK(vec.zwyx() == vec4{ 3.f, 4.f, 2.f, 1.f });
      CHECK(vec.zwyy() == vec4{ 3.f, 4.f, 2.f, 2.f });
      CHECK(vec.zwyz() == vec4{ 3.f, 4.f, 2.f, 3.f });
      CHECK(vec.zwyw() == vec4{ 3.f, 4.f, 2.f, 4.f });
      CHECK(vec.zwzx() == vec4{ 3.f, 4.f, 3.f, 1.f });
      CHECK(vec.zwzy() == vec4{ 3.f, 4.f, 3.f, 2.f });
      CHECK(vec.zwzz() == vec4{ 3.f, 4.f, 3.f, 3.f });
      CHECK(vec.zwzw() == vec4{ 3.f, 4.f, 3.f, 4.f });
      CHECK(vec.zwwx() == vec4{ 3.f, 4.f, 4.f, 1.f });
      CHECK(vec.zwwy() == vec4{ 3.f, 4.f, 4.f, 2.f });
      CHECK(vec.zwwz() == vec4{ 3.f, 4.f, 4.f, 3.f });
      CHECK(vec.zwww() == vec4{ 3.f, 4.f, 4.f, 4.f });
      CHECK(vec.wxxx() == vec4{ 4.f, 1.f, 1.f, 1.f });
      CHECK(vec.wxxy() == vec4{ 4.f, 1.f, 1.f, 2.f });
      CHECK(vec.wxxz() == vec4{ 4.f, 1.f, 1.f, 3.f });
      CHECK(vec.wxxw() == vec4{ 4.f, 1.f, 1.f, 4.f });
      CHECK(vec.wxyx() == vec4{ 4.f, 1.f, 2.f, 1.f });
      CHECK(vec.wxyy() == vec4{ 4.f, 1.f, 2.f, 2.f });
      CHECK(vec.wxyz() == vec4{ 4.f, 1.f, 2.f, 3.f });
      CHECK(vec.wxyw() == vec4{ 4.f, 1.f, 2.f, 4.f });
      CHECK(vec.wxzx() == vec4{ 4.f, 1.f, 3.f, 1.f });
      CHECK(vec.wxzy() == vec4{ 4.f, 1.f, 3.f, 2.f });
      CHECK(vec.wxzz() == vec4{ 4.f, 1.f, 3.f, 3.f });
      CHECK(vec.wxzw() == vec4{ 4.f, 1.f, 3.f, 4.f });
      CHECK(vec.wxwx() == vec4{ 4.f, 1.f, 4.f, 1.f });
      CHECK(vec.wxwy() == vec4{ 4.f, 1.f, 4.f, 2.f });
      CHECK(vec.wxwz() == vec4{ 4.f, 1.f, 4.f, 3.f });
      CHECK(vec.wxww() == vec4{ 4.f, 1.f, 4.f, 4.f });
      CHECK(vec.wyxx() == vec4{ 4.f, 2.f, 1.f, 1.f });
      CHECK(vec.wyxy() == vec4{ 4.f, 2.f, 1.f, 2.f });
      CHECK(vec.wyxz() == vec4{ 4.f, 2.f, 1.f, 3.f });
      CHECK(vec.wyxw() == vec4{ 4.f, 2.f, 1.f, 4.f });
      CHECK(vec.wyyx() == vec4{ 4.f, 2.f, 2.f, 1.f });
      CHECK(vec.wyyy() == vec4{ 4.f, 2.f, 2.f, 2.f });
      CHECK(vec.wyyz() == vec4{ 4.f, 2.f, 2.f, 3.f });
      CHECK(vec.wyyw() == vec4{ 4.f, 2.f, 2.f, 4.f });
      CHECK(vec.wyzx() == vec4{ 4.f, 2.f, 3.f, 1.f });
      CHECK(vec.wyzy() == vec4{ 4.f, 2.f, 3.f, 2.f });
      CHECK(vec.wyzz() == vec4{ 4.f, 2.f, 3.f, 3.f });
      CHECK(vec.wyzw() == vec4{ 4.f, 2.f, 3.f, 4.f });
      CHECK(vec.wywx() == vec4{ 4.f, 2.f, 4.f, 1.f });
      CHECK(vec.wywy() == vec4{ 4.f, 2.f, 4.f, 2.f });
      CHECK(vec.wywz() == vec4{ 4.f, 2.f, 4.f, 3.f });
      CHECK(vec.wyww() == vec4{ 4.f, 2.f, 4.f, 4.f });
      CHECK(vec.wzxx() == vec4{ 4.f, 3.f, 1.f, 1.f });
      CHECK(vec.wzxy() == vec4{ 4.f, 3.f, 1.f, 2.f });
      CHECK(vec.wzxz() == vec4{ 4.f, 3.f, 1.f, 3.f });
      CHECK(vec.wzxw() == vec4{ 4.f, 3.f, 1.f, 4.f });
      CHECK(vec.wzyx() == vec4{ 4.f, 3.f, 2.f, 1.f });
      CHECK(vec.wzyy() == vec4{ 4.f, 3.f, 2.f, 2.f });
      CHECK(vec.wzyz() == vec4{ 4.f, 3.f, 2.f, 3.f });
      CHECK(vec.wzyw() == vec4{ 4.f, 3.f, 2.f, 4.f });
      CHECK(vec.wzzx() == vec4{ 4.f, 3.f, 3.f, 1.f });
      CHECK(vec.wzzy() == vec4{ 4.f, 3.f, 3.f, 2.f });
      CHECK(vec.wzzz() == vec4{ 4.f, 3.f, 3.f, 3.f });
      CHECK(vec.wzzw() == vec4{ 4.f, 3.f, 3.f, 4.f });
      CHECK(vec.wzwx() == vec4{ 4.f, 3.f, 4.f, 1.f });
      CHECK(vec.wzwy() == vec4{ 4.f, 3.f, 4.f, 2.f });
      CHECK(vec.wzwz() == vec4{ 4.f, 3.f, 4.f, 3.f });
      CHECK(vec.wzww() == vec4{ 4.f, 3.f, 4.f, 4.f });
      CHECK(vec.wwxx() == vec4{ 4.f, 4.f, 1.f, 1.f });
      CHECK(vec.wwxy() == vec4{ 4.f, 4.f, 1.f, 2.f });
      CHECK(vec.wwxz() == vec4{ 4.f, 4.f, 1.f, 3.f });
      CHECK(vec.wwxw() == vec4{ 4.f, 4.f, 1.f, 4.f });
      CHECK(vec.wwyx() == vec4{ 4.f, 4.f, 2.f, 1.f });
      CHECK(vec.wwyy() == vec4{ 4.f, 4.f, 2.f, 2.f });
      CHECK(vec.wwyz() == vec4{ 4.f, 4.f, 2.f, 3.f });
      CHECK(vec.wwyw() == vec4{ 4.f, 4.f, 2.f, 4.f });
      CHECK(vec.wwzx() == vec4{ 4.f, 4.f, 3.f, 1.f });
      CHECK(vec.wwzy() == vec4{ 4.f, 4.f, 3.f, 2.f });
      CHECK(vec.wwzz() == vec4{ 4.f, 4.f, 3.f, 3.f });
      CHECK(vec.wwzw() == vec4{ 4.f, 4.f, 3.f, 4.f });
      CHECK(vec.wwwx() == vec4{ 4.f, 4.f, 4.f, 1.f });
      CHECK(vec.wwwy() == vec4{ 4.f, 4.f, 4.f, 2.f });
      CHECK(vec.wwwz() == vec4{ 4.f, 4.f, 4.f, 3.f });
      CHECK(vec.wwww() == vec4{ 4.f, 4.f, 4.f, 4.f });
    }
  }
}
