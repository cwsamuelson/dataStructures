#include <shapes/functions.hh>
#include <shapes/vec.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Shapes: `fvec2`: `constexpr`") {
}

TEST_CASE("Shapes: `fvec2`") {
  SECTION("Default ctor") {
    fvec2 v{};
    CAPTURE(v);

    CHECK(v.x == 0.F);
    CHECK(v.y == 0.F);

    CHECK(v == fvec2{});
    CHECK(v == fvec2{ 0.F });
    CHECK(v == fvec2{ 0.F, 0.F });
    CHECK(2.F * v == v);
    CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    fvec2 v(3.F);
    CAPTURE(v);

    CHECK(v.x == 3.F);
    CHECK(v.y == 3.F);

    CHECK(v == fvec2{ 3.F });
    CHECK(v == fvec2{ 3.F, 3.F });
    CHECK(2.F * v == fvec2{ 6.F });
    CHECK(v * 2.F == fvec2{ 6.F });

    CHECK(v > fvec2{});
    CHECK(v >= fvec2{});
    CHECK(fvec2{} < v);
    CHECK(fvec2{} <= v);
    CHECK(v != fvec2{});
  }
}

TEST_CASE("Shapes: `fvec3`") {
  SECTION("Default ctor") {
    fvec3 v{};
    CAPTURE(v);

    CHECK(v.x == 0.F);
    CHECK(v.y == 0.F);
    CHECK(v.z == 0.F);

    CHECK(v == fvec3{});
    CHECK(v == fvec3{ 0.F });
    CHECK(v == fvec3{ 0.F, 0.F, 0.F });
    CHECK(2.F * v == v);
    CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    fvec3 v(3.F);
    CAPTURE(v);

    CHECK(v.x == 3.F);
    CHECK(v.y == 3.F);
    CHECK(v.z == 3.F);

    CHECK(v == fvec3{ 3.F });
    CHECK(v == fvec3{ 3.F, 3.F, 3.F });
    CHECK(2.F * v == fvec3{ 6.F });
    CHECK(v * 2.F == fvec3{ 6.F });

    CHECK(v > fvec3{});
    CHECK(v >= fvec3{});
    CHECK(fvec3{} < v);
    CHECK(fvec3{} <= v);
    CHECK(v != fvec3{});
  }
}

TEST_CASE("Shapes: `fvec4`") {
  SECTION("Default ctor") {
    fvec4 v{};
    CAPTURE(v);

    CHECK(v.x == 0.F);
    CHECK(v.y == 0.F);
    CHECK(v.z == 0.F);
    CHECK(v.w == 0.F);

    CHECK(v == fvec4{});
    CHECK(v == fvec4{ 0.F });
    CHECK(v == fvec4{ 0.F, 0.F, 0.F, 0.F });
    CHECK(2.F * v == v);
    CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    fvec4 v(3.F);
    CAPTURE(v);

    CHECK(v.x == 3.F);
    CHECK(v.y == 3.F);
    CHECK(v.z == 3.F);
    CHECK(v.w == 3.F);

    CHECK(v == fvec4{ 3.F });
    CHECK(v == fvec4{ 3.F, 3.F, 3.F, 3.f });
    CHECK(2.F * v == fvec4{ 6.F });
    CHECK(v * 2.F == fvec4{ 6.F });

    CHECK(v > fvec4{});
    CHECK(v >= fvec4{});
    CHECK(fvec4{} < v);
    CHECK(fvec4{} <= v);
    CHECK(v != fvec4{});
  }
}

TEST_CASE("Shapes: functions") {
  SECTION("Sign") {
    //float sign(float f)
    CHECK(sign(0.f) == 0.f);
    CHECK(sign(1.f) == 1.f);
    CHECK(sign(-1.f) == -1.f);
    CHECK(sign(2.f) == 1.f);
    CHECK(sign(-2.f) == -1.f);
    CHECK(sign(3.14f) == 1.f);
    CHECK(sign(-3.14f) == -1.f);

    //fvec2 sign(fvec2 f)
    CHECK(sign(fvec2{ 0.f, 3.f }) == fvec2{ 0.f, 1.f });
    CHECK(sign(fvec2{ -1.f, 3.2f }) == fvec2{ -1.f, 1.f });

    //fvec3 sign(fvec3 f)
    CHECK(sign(fvec3{ 0.f, 3.f, -2.46 }) == fvec3{ 0.f, 1.f, -1.f });
    CHECK(sign(fvec3{ -1.f, 3.2f, 0.f }) == fvec3{ -1.f, 1.f, 0.f });

    //fvec4 sign(fvec4 f)
    CHECK(sign(fvec4{ 0.f, 3.f, -2.46, -0.f }) == fvec4{ 0.f, 1.f, -1.f, 0.f });
    CHECK(sign(fvec4{ -1.f, 3.2f, 0.f, 1.f }) == fvec4{ -1.f, 1.f, 0.f, 1.f });
  }

  SECTION("Clamp") {
    //float clamp(float f, float l, float h)
    CHECK(clamp(.5f, .0f, 1.f) == .5f);
    CHECK(clamp(.5f, 1.2f, 6.7f) == 1.2f);
    CHECK(clamp(.5f, -1.f, .3f) == .3f);

    //fvec2 clamp(fvec2 f, fvec2 l, fvec2 h)
    CHECK(clamp(fvec2{ .5f, .5f }, fvec2{ .0f, 1.2f }, fvec2{ 1.f, 6.7f }) == fvec2{ .5f, 1.2f });
    CHECK(clamp(fvec2{ .5f, 12.f }, fvec2{ -1.f, 10.f }, fvec2{ .3f, 11.f }) == fvec2{ .3f, 11.f });

    //fvec2 clamp(fvec2 f, float l, float h)
    CHECK(clamp(fvec2{ .5f, 15.f }, 1.f, 10.f) == fvec2{ 1.f, 10.f });
    CHECK(clamp(fvec2{ .5f, 12.f }, .0f, .0f) == fvec2{ .0f, .0f });

    //fvec3 clamp(fvec3 f, fvec3 l, fvec3 h)
    CHECK(clamp(fvec3{ .5f, .5f, .5f }, fvec3{ .0f, 1.2f, -10.f }, fvec3{ 1.f, 6.7f, -6.7f }) == fvec3{ .5f, 1.2f, -6.7f });

    //fvec3 clamp(fvec3 f, float l, float h)
    CHECK(clamp(fvec3{ .5f, 3.f, 7.f }, 2.3f, 5.f) == fvec3{ 2.3f, 3.f, 5.f });
  }

  SECTION("abs") {
    //float abs(float f)
    //fvec2 abs(fvec2 v)
    //fvec3 abs(fvec3 v)
    //fvec4 abs(fvec4 v)
  }

  SECTION("dot") {
    //float dot(fvec2, fvec2)
    //float dot(fvec3, fvec3)
    //float dot(fvec4, fvec4)

    //float dot2(fvec2 v)
    //float dot2(fvec4 v)
    //float ndot(fvec2 a, fvec2 b)
  }

  SECTION("length") {
    //float length(const fvec2& vector)
    CHECK(length(fvec2{ 1.f, 0.f }) == 1.f);
    CHECK(length(fvec2{ 0.f, 1.f }) == 1.f);
    CHECK(length(fvec2{ 3.f, 0.f }) == 3.f);
    CHECK(length(fvec2{ 0.f, 3.f }) == 3.f);
    CHECK(length(fvec2{ 3.f, 4.f }) == 5.f);

    //float length(const fvec3& vector)
    CHECK(length(fvec3{ 1.f, 0.f, 0.f }) == 1.f);
    CHECK(length(fvec3{ 0.f, 1.f, 0.f }) == 1.f);
    CHECK(length(fvec3{ 0.f, 0.f, 1.f }) == 1.f);
    CHECK(length(fvec3{ 3.f, 0.f, 0.f }) == 3.f);
    CHECK(length(fvec3{ 0.f, 3.f, 0.f }) == 3.f);
    CHECK(length(fvec3{ 0.f, 0.f, 3.f }) == 3.f);

    //float length(const fvec4& vector)
    CHECK(length(fvec4{ 1.f, 0.f, 0.f, 0.f }) == 1.f);
    CHECK(length(fvec4{ 0.f, 1.f, 0.f, 0.f }) == 1.f);
    CHECK(length(fvec4{ 0.f, 0.f, 1.f, 0.f }) == 1.f);
    CHECK(length(fvec4{ 0.f, 0.f, 0.f, 1.f }) == 1.f);

    CHECK(length(fvec4{ 3.f, 0.f, 0.f, 0.f }) == 3.f);
    CHECK(length(fvec4{ 0.f, 3.f, 0.f, 0.f }) == 3.f);
    CHECK(length(fvec4{ 0.f, 0.f, 3.f, 0.f }) == 3.f);
    CHECK(length(fvec4{ 0.f, 0.f, 0.f, 3.f }) == 3.f);
  }

  SECTION("minmax") {
    //float min(float a, float b)
    //float max(float a, float b)

    //fvec2 min(fvec2 a, fvec2 b)
    //fvec2 max(fvec2 a, fvec2 b)

    //fvec3 min(fvec3 a, fvec3 b)
    //fvec3 max(fvec3 a, fvec3 b)

    //fvec4 min(fvec4 a, fvec4 b)
    //fvec4 max(fvec4 a, fvec4 b)
  }
}

TEST_CASE("Shapes: swizzling") {
  fvec2 vec(1.f, 2.f);
}

//TEST_CASE("Shapes: swizzling") {
//  SECTION("fvec2") {
//    fvec2 vec(1.f, 2.f);
//
//    SECTION("fvec2 result") {
//      CHECK(vec.xx() == fvec2{ 1.f, 1.f });
//      CHECK(vec.xy() == fvec2{ 1.f, 2.f });
//      CHECK(vec.yx() == fvec2{ 2.f, 1.f });
//      CHECK(vec.yy() == fvec2{ 2.f, 2.f });
//
//      vec.xx() = fvec2{ 3.f, 4.f };
//      CHECK(vec == fvec2{ 4.f, 2.f });
//      CHECK(vec.x == 4.f);
//      CHECK(vec.y == 2.f);
//    }
//
//    SECTION("fvec3 result") {
//    }
//
//    SECTION("fvec4 result") {
//    }
//  }
//
//  SECTION("fvec3") {
//    fvec3 vec(1.f, 2.f, 3.f);
//
//    SECTION("fvec2 result") {
//      //CHECK(vec.xx() == fvec2{ 1.f, 1.f });
//      //CHECK(vec.xy() == fvec2{ 1.f, 2.f });
//      //CHECK(vec.yx() == fvec2{ 2.f, 1.f });
//      //CHECK(vec.yy() == fvec2{ 2.f, 2.f });
//
//      //vec.xx() = fvec2{ 3.f, 4.f };
//      //CHECK(vec == fvec2{ 4.f, 2.f });
//      //CHECK(vec.x == 4.f);
//      //CHECK(vec.y == 2.f);
//    }
//
//    SECTION("fvec3 result") {
//      CHECK(vec.xxx() == fvec3{ 1.f, 1.f, 1.f });
//      CHECK(vec.xxy() == fvec3{ 1.f, 1.f, 2.f });
//      CHECK(vec.xxz() == fvec3{ 1.f, 1.f, 3.f });
//      CHECK(vec.xyx() == fvec3{ 1.f, 2.f, 1.f });
//      CHECK(vec.xyy() == fvec3{ 1.f, 2.f, 2.f });
//      CHECK(vec.xyz() == fvec3{ 1.f, 2.f, 3.f });
//      CHECK(vec.xzx() == fvec3{ 1.f, 3.f, 1.f });
//      CHECK(vec.xzy() == fvec3{ 1.f, 3.f, 2.f });
//      CHECK(vec.xzz() == fvec3{ 1.f, 3.f, 3.f });
//      CHECK(vec.yxx() == fvec3{ 2.f, 1.f, 1.f });
//      CHECK(vec.yxy() == fvec3{ 2.f, 1.f, 2.f });
//      CHECK(vec.yxz() == fvec3{ 2.f, 1.f, 3.f });
//      CHECK(vec.yyx() == fvec3{ 2.f, 2.f, 1.f });
//      CHECK(vec.yyy() == fvec3{ 2.f, 2.f, 2.f });
//      CHECK(vec.yyz() == fvec3{ 2.f, 2.f, 3.f });
//      CHECK(vec.yzx() == fvec3{ 2.f, 3.f, 1.f });
//      CHECK(vec.yzy() == fvec3{ 2.f, 3.f, 2.f });
//      CHECK(vec.yzz() == fvec3{ 2.f, 3.f, 3.f });
//      CHECK(vec.zxx() == fvec3{ 3.f, 1.f, 1.f });
//      CHECK(vec.zxy() == fvec3{ 3.f, 1.f, 2.f });
//      CHECK(vec.zxz() == fvec3{ 3.f, 1.f, 3.f });
//      CHECK(vec.zyx() == fvec3{ 3.f, 2.f, 1.f });
//      CHECK(vec.zyy() == fvec3{ 3.f, 2.f, 2.f });
//      CHECK(vec.zyz() == fvec3{ 3.f, 2.f, 3.f });
//      CHECK(vec.zzx() == fvec3{ 3.f, 3.f, 1.f });
//      CHECK(vec.zzy() == fvec3{ 3.f, 3.f, 2.f });
//      CHECK(vec.zzz() == fvec3{ 3.f, 3.f, 3.f });
//    }
//
//    SECTION("fvec4 result") {
//    }
//  }
//
//  SECTION("fvec4") {
//    fvec4 vec(1.f, 2.f, 3.f, 4.f);
//
//    SECTION("fvec2 result") {
//    }
//
//    SECTION("fvec3 result") {
//    }
//
//    SECTION("fvec4 result") {
//      CHECK(vec.xxxx() == fvec4{ 1.f, 1.f, 1.f, 1.f });
//      CHECK(vec.xxxy() == fvec4{ 1.f, 1.f, 1.f, 2.f });
//      CHECK(vec.xxxz() == fvec4{ 1.f, 1.f, 1.f, 3.f });
//      CHECK(vec.xxxw() == fvec4{ 1.f, 1.f, 1.f, 4.f });
//      CHECK(vec.xxyx() == fvec4{ 1.f, 1.f, 2.f, 1.f });
//      CHECK(vec.xxyy() == fvec4{ 1.f, 1.f, 2.f, 2.f });
//      CHECK(vec.xxyz() == fvec4{ 1.f, 1.f, 2.f, 3.f });
//      CHECK(vec.xxyw() == fvec4{ 1.f, 1.f, 2.f, 4.f });
//      CHECK(vec.xxzx() == fvec4{ 1.f, 1.f, 3.f, 1.f });
//      CHECK(vec.xxzy() == fvec4{ 1.f, 1.f, 3.f, 2.f });
//      CHECK(vec.xxzz() == fvec4{ 1.f, 1.f, 3.f, 3.f });
//      CHECK(vec.xxzw() == fvec4{ 1.f, 1.f, 3.f, 4.f });
//      CHECK(vec.xxwx() == fvec4{ 1.f, 1.f, 4.f, 1.f });
//      CHECK(vec.xxwy() == fvec4{ 1.f, 1.f, 4.f, 2.f });
//      CHECK(vec.xxwz() == fvec4{ 1.f, 1.f, 4.f, 3.f });
//      CHECK(vec.xxww() == fvec4{ 1.f, 1.f, 4.f, 4.f });
//      CHECK(vec.xyxx() == fvec4{ 1.f, 2.f, 1.f, 1.f });
//      CHECK(vec.xyxy() == fvec4{ 1.f, 2.f, 1.f, 2.f });
//      CHECK(vec.xyxz() == fvec4{ 1.f, 2.f, 1.f, 3.f });
//      CHECK(vec.xyxw() == fvec4{ 1.f, 2.f, 1.f, 4.f });
//      CHECK(vec.xyyx() == fvec4{ 1.f, 2.f, 2.f, 1.f });
//      CHECK(vec.xyyy() == fvec4{ 1.f, 2.f, 2.f, 2.f });
//      CHECK(vec.xyyz() == fvec4{ 1.f, 2.f, 2.f, 3.f });
//      CHECK(vec.xyyw() == fvec4{ 1.f, 2.f, 2.f, 4.f });
//      CHECK(vec.xyzx() == fvec4{ 1.f, 2.f, 3.f, 1.f });
//      CHECK(vec.xyzy() == fvec4{ 1.f, 2.f, 3.f, 2.f });
//      CHECK(vec.xyzz() == fvec4{ 1.f, 2.f, 3.f, 3.f });
//      CHECK(vec.xyzw() == fvec4{ 1.f, 2.f, 3.f, 4.f });
//      CHECK(vec.xywx() == fvec4{ 1.f, 2.f, 4.f, 1.f });
//      CHECK(vec.xywy() == fvec4{ 1.f, 2.f, 4.f, 2.f });
//      CHECK(vec.xywz() == fvec4{ 1.f, 2.f, 4.f, 3.f });
//      CHECK(vec.xyww() == fvec4{ 1.f, 2.f, 4.f, 4.f });
//      CHECK(vec.xzxx() == fvec4{ 1.f, 3.f, 1.f, 1.f });
//      CHECK(vec.xzxy() == fvec4{ 1.f, 3.f, 1.f, 2.f });
//      CHECK(vec.xzxz() == fvec4{ 1.f, 3.f, 1.f, 3.f });
//      CHECK(vec.xzxw() == fvec4{ 1.f, 3.f, 1.f, 4.f });
//      CHECK(vec.xzyx() == fvec4{ 1.f, 3.f, 2.f, 1.f });
//      CHECK(vec.xzyy() == fvec4{ 1.f, 3.f, 2.f, 2.f });
//      CHECK(vec.xzyz() == fvec4{ 1.f, 3.f, 2.f, 3.f });
//      CHECK(vec.xzyw() == fvec4{ 1.f, 3.f, 2.f, 4.f });
//      CHECK(vec.xzzx() == fvec4{ 1.f, 3.f, 3.f, 1.f });
//      CHECK(vec.xzzy() == fvec4{ 1.f, 3.f, 3.f, 2.f });
//      CHECK(vec.xzzz() == fvec4{ 1.f, 3.f, 3.f, 3.f });
//      CHECK(vec.xzzw() == fvec4{ 1.f, 3.f, 3.f, 4.f });
//      CHECK(vec.xzwx() == fvec4{ 1.f, 3.f, 4.f, 1.f });
//      CHECK(vec.xzwy() == fvec4{ 1.f, 3.f, 4.f, 2.f });
//      CHECK(vec.xzwz() == fvec4{ 1.f, 3.f, 4.f, 3.f });
//      CHECK(vec.xzww() == fvec4{ 1.f, 3.f, 4.f, 4.f });
//      CHECK(vec.xwxx() == fvec4{ 1.f, 4.f, 1.f, 1.f });
//      CHECK(vec.xwxy() == fvec4{ 1.f, 4.f, 1.f, 2.f });
//      CHECK(vec.xwxz() == fvec4{ 1.f, 4.f, 1.f, 3.f });
//      CHECK(vec.xwxw() == fvec4{ 1.f, 4.f, 1.f, 4.f });
//      CHECK(vec.xwyx() == fvec4{ 1.f, 4.f, 2.f, 1.f });
//      CHECK(vec.xwyy() == fvec4{ 1.f, 4.f, 2.f, 2.f });
//      CHECK(vec.xwyz() == fvec4{ 1.f, 4.f, 2.f, 3.f });
//      CHECK(vec.xwyw() == fvec4{ 1.f, 4.f, 2.f, 4.f });
//      CHECK(vec.xwzx() == fvec4{ 1.f, 4.f, 3.f, 1.f });
//      CHECK(vec.xwzy() == fvec4{ 1.f, 4.f, 3.f, 2.f });
//      CHECK(vec.xwzz() == fvec4{ 1.f, 4.f, 3.f, 3.f });
//      CHECK(vec.xwzw() == fvec4{ 1.f, 4.f, 3.f, 4.f });
//      CHECK(vec.xwwx() == fvec4{ 1.f, 4.f, 4.f, 1.f });
//      CHECK(vec.xwwy() == fvec4{ 1.f, 4.f, 4.f, 2.f });
//      CHECK(vec.xwwz() == fvec4{ 1.f, 4.f, 4.f, 3.f });
//      CHECK(vec.xwww() == fvec4{ 1.f, 4.f, 4.f, 4.f });
//      CHECK(vec.yxxx() == fvec4{ 2.f, 1.f, 1.f, 1.f });
//      CHECK(vec.yxxy() == fvec4{ 2.f, 1.f, 1.f, 2.f });
//      CHECK(vec.yxxz() == fvec4{ 2.f, 1.f, 1.f, 3.f });
//      CHECK(vec.yxxw() == fvec4{ 2.f, 1.f, 1.f, 4.f });
//      CHECK(vec.yxyx() == fvec4{ 2.f, 1.f, 2.f, 1.f });
//      CHECK(vec.yxyy() == fvec4{ 2.f, 1.f, 2.f, 2.f });
//      CHECK(vec.yxyz() == fvec4{ 2.f, 1.f, 2.f, 3.f });
//      CHECK(vec.yxyw() == fvec4{ 2.f, 1.f, 2.f, 4.f });
//      CHECK(vec.yxzx() == fvec4{ 2.f, 1.f, 3.f, 1.f });
//      CHECK(vec.yxzy() == fvec4{ 2.f, 1.f, 3.f, 2.f });
//      CHECK(vec.yxzz() == fvec4{ 2.f, 1.f, 3.f, 3.f });
//      CHECK(vec.yxzw() == fvec4{ 2.f, 1.f, 3.f, 4.f });
//      CHECK(vec.yxwx() == fvec4{ 2.f, 1.f, 4.f, 1.f });
//      CHECK(vec.yxwy() == fvec4{ 2.f, 1.f, 4.f, 2.f });
//      CHECK(vec.yxwz() == fvec4{ 2.f, 1.f, 4.f, 3.f });
//      CHECK(vec.yxww() == fvec4{ 2.f, 1.f, 4.f, 4.f });
//      CHECK(vec.yyxx() == fvec4{ 2.f, 2.f, 1.f, 1.f });
//      CHECK(vec.yyxy() == fvec4{ 2.f, 2.f, 1.f, 2.f });
//      CHECK(vec.yyxz() == fvec4{ 2.f, 2.f, 1.f, 3.f });
//      CHECK(vec.yyxw() == fvec4{ 2.f, 2.f, 1.f, 4.f });
//      CHECK(vec.yyyx() == fvec4{ 2.f, 2.f, 2.f, 1.f });
//      CHECK(vec.yyyy() == fvec4{ 2.f, 2.f, 2.f, 2.f });
//      CHECK(vec.yyyz() == fvec4{ 2.f, 2.f, 2.f, 3.f });
//      CHECK(vec.yyyw() == fvec4{ 2.f, 2.f, 2.f, 4.f });
//      CHECK(vec.yyzx() == fvec4{ 2.f, 2.f, 3.f, 1.f });
//      CHECK(vec.yyzy() == fvec4{ 2.f, 2.f, 3.f, 2.f });
//      CHECK(vec.yyzz() == fvec4{ 2.f, 2.f, 3.f, 3.f });
//      CHECK(vec.yyzw() == fvec4{ 2.f, 2.f, 3.f, 4.f });
//      CHECK(vec.yywx() == fvec4{ 2.f, 2.f, 4.f, 1.f });
//      CHECK(vec.yywy() == fvec4{ 2.f, 2.f, 4.f, 2.f });
//      CHECK(vec.yywz() == fvec4{ 2.f, 2.f, 4.f, 3.f });
//      CHECK(vec.yyww() == fvec4{ 2.f, 2.f, 4.f, 4.f });
//      CHECK(vec.yzxx() == fvec4{ 2.f, 3.f, 1.f, 1.f });
//      CHECK(vec.yzxy() == fvec4{ 2.f, 3.f, 1.f, 2.f });
//      CHECK(vec.yzxz() == fvec4{ 2.f, 3.f, 1.f, 3.f });
//      CHECK(vec.yzxw() == fvec4{ 2.f, 3.f, 1.f, 4.f });
//      CHECK(vec.yzyx() == fvec4{ 2.f, 3.f, 2.f, 1.f });
//      CHECK(vec.yzyy() == fvec4{ 2.f, 3.f, 2.f, 2.f });
//      CHECK(vec.yzyz() == fvec4{ 2.f, 3.f, 2.f, 3.f });
//      CHECK(vec.yzyw() == fvec4{ 2.f, 3.f, 2.f, 4.f });
//      CHECK(vec.yzzx() == fvec4{ 2.f, 3.f, 3.f, 1.f });
//      CHECK(vec.yzzy() == fvec4{ 2.f, 3.f, 3.f, 2.f });
//      CHECK(vec.yzzz() == fvec4{ 2.f, 3.f, 3.f, 3.f });
//      CHECK(vec.yzzw() == fvec4{ 2.f, 3.f, 3.f, 4.f });
//      CHECK(vec.yzwx() == fvec4{ 2.f, 3.f, 4.f, 1.f });
//      CHECK(vec.yzwy() == fvec4{ 2.f, 3.f, 4.f, 2.f });
//      CHECK(vec.yzwz() == fvec4{ 2.f, 3.f, 4.f, 3.f });
//      CHECK(vec.yzww() == fvec4{ 2.f, 3.f, 4.f, 4.f });
//      CHECK(vec.ywxx() == fvec4{ 2.f, 4.f, 1.f, 1.f });
//      CHECK(vec.ywxy() == fvec4{ 2.f, 4.f, 1.f, 2.f });
//      CHECK(vec.ywxz() == fvec4{ 2.f, 4.f, 1.f, 3.f });
//      CHECK(vec.ywxw() == fvec4{ 2.f, 4.f, 1.f, 4.f });
//      CHECK(vec.ywyx() == fvec4{ 2.f, 4.f, 2.f, 1.f });
//      CHECK(vec.ywyy() == fvec4{ 2.f, 4.f, 2.f, 2.f });
//      CHECK(vec.ywyz() == fvec4{ 2.f, 4.f, 2.f, 3.f });
//      CHECK(vec.ywyw() == fvec4{ 2.f, 4.f, 2.f, 4.f });
//      CHECK(vec.ywzx() == fvec4{ 2.f, 4.f, 3.f, 1.f });
//      CHECK(vec.ywzy() == fvec4{ 2.f, 4.f, 3.f, 2.f });
//      CHECK(vec.ywzz() == fvec4{ 2.f, 4.f, 3.f, 3.f });
//      CHECK(vec.ywzw() == fvec4{ 2.f, 4.f, 3.f, 4.f });
//      CHECK(vec.ywwx() == fvec4{ 2.f, 4.f, 4.f, 1.f });
//      CHECK(vec.ywwy() == fvec4{ 2.f, 4.f, 4.f, 2.f });
//      CHECK(vec.ywwz() == fvec4{ 2.f, 4.f, 4.f, 3.f });
//      CHECK(vec.ywww() == fvec4{ 2.f, 4.f, 4.f, 4.f });
//      CHECK(vec.zxxx() == fvec4{ 3.f, 1.f, 1.f, 1.f });
//      CHECK(vec.zxxy() == fvec4{ 3.f, 1.f, 1.f, 2.f });
//      CHECK(vec.zxxz() == fvec4{ 3.f, 1.f, 1.f, 3.f });
//      CHECK(vec.zxxw() == fvec4{ 3.f, 1.f, 1.f, 4.f });
//      CHECK(vec.zxyx() == fvec4{ 3.f, 1.f, 2.f, 1.f });
//      CHECK(vec.zxyy() == fvec4{ 3.f, 1.f, 2.f, 2.f });
//      CHECK(vec.zxyz() == fvec4{ 3.f, 1.f, 2.f, 3.f });
//      CHECK(vec.zxyw() == fvec4{ 3.f, 1.f, 2.f, 4.f });
//      CHECK(vec.zxzx() == fvec4{ 3.f, 1.f, 3.f, 1.f });
//      CHECK(vec.zxzy() == fvec4{ 3.f, 1.f, 3.f, 2.f });
//      CHECK(vec.zxzz() == fvec4{ 3.f, 1.f, 3.f, 3.f });
//      CHECK(vec.zxzw() == fvec4{ 3.f, 1.f, 3.f, 4.f });
//      CHECK(vec.zxwx() == fvec4{ 3.f, 1.f, 4.f, 1.f });
//      CHECK(vec.zxwy() == fvec4{ 3.f, 1.f, 4.f, 2.f });
//      CHECK(vec.zxwz() == fvec4{ 3.f, 1.f, 4.f, 3.f });
//      CHECK(vec.zxww() == fvec4{ 3.f, 1.f, 4.f, 4.f });
//      CHECK(vec.zyxx() == fvec4{ 3.f, 2.f, 1.f, 1.f });
//      CHECK(vec.zyxy() == fvec4{ 3.f, 2.f, 1.f, 2.f });
//      CHECK(vec.zyxz() == fvec4{ 3.f, 2.f, 1.f, 3.f });
//      CHECK(vec.zyxw() == fvec4{ 3.f, 2.f, 1.f, 4.f });
//      CHECK(vec.zyyx() == fvec4{ 3.f, 2.f, 2.f, 1.f });
//      CHECK(vec.zyyy() == fvec4{ 3.f, 2.f, 2.f, 2.f });
//      CHECK(vec.zyyz() == fvec4{ 3.f, 2.f, 2.f, 3.f });
//      CHECK(vec.zyyw() == fvec4{ 3.f, 2.f, 2.f, 4.f });
//      CHECK(vec.zyzx() == fvec4{ 3.f, 2.f, 3.f, 1.f });
//      CHECK(vec.zyzy() == fvec4{ 3.f, 2.f, 3.f, 2.f });
//      CHECK(vec.zyzz() == fvec4{ 3.f, 2.f, 3.f, 3.f });
//      CHECK(vec.zyzw() == fvec4{ 3.f, 2.f, 3.f, 4.f });
//      CHECK(vec.zywx() == fvec4{ 3.f, 2.f, 4.f, 1.f });
//      CHECK(vec.zywy() == fvec4{ 3.f, 2.f, 4.f, 2.f });
//      CHECK(vec.zywz() == fvec4{ 3.f, 2.f, 4.f, 3.f });
//      CHECK(vec.zyww() == fvec4{ 3.f, 2.f, 4.f, 4.f });
//      CHECK(vec.zzxx() == fvec4{ 3.f, 3.f, 1.f, 1.f });
//      CHECK(vec.zzxy() == fvec4{ 3.f, 3.f, 1.f, 2.f });
//      CHECK(vec.zzxz() == fvec4{ 3.f, 3.f, 1.f, 3.f });
//      CHECK(vec.zzxw() == fvec4{ 3.f, 3.f, 1.f, 4.f });
//      CHECK(vec.zzyx() == fvec4{ 3.f, 3.f, 2.f, 1.f });
//      CHECK(vec.zzyy() == fvec4{ 3.f, 3.f, 2.f, 2.f });
//      CHECK(vec.zzyz() == fvec4{ 3.f, 3.f, 2.f, 3.f });
//      CHECK(vec.zzyw() == fvec4{ 3.f, 3.f, 2.f, 4.f });
//      CHECK(vec.zzzx() == fvec4{ 3.f, 3.f, 3.f, 1.f });
//      CHECK(vec.zzzy() == fvec4{ 3.f, 3.f, 3.f, 2.f });
//      CHECK(vec.zzzz() == fvec4{ 3.f, 3.f, 3.f, 3.f });
//      CHECK(vec.zzzw() == fvec4{ 3.f, 3.f, 3.f, 4.f });
//      CHECK(vec.zzwx() == fvec4{ 3.f, 3.f, 4.f, 1.f });
//      CHECK(vec.zzwy() == fvec4{ 3.f, 3.f, 4.f, 2.f });
//      CHECK(vec.zzwz() == fvec4{ 3.f, 3.f, 4.f, 3.f });
//      CHECK(vec.zzww() == fvec4{ 3.f, 3.f, 4.f, 4.f });
//      CHECK(vec.zwxx() == fvec4{ 3.f, 4.f, 1.f, 1.f });
//      CHECK(vec.zwxy() == fvec4{ 3.f, 4.f, 1.f, 2.f });
//      CHECK(vec.zwxz() == fvec4{ 3.f, 4.f, 1.f, 3.f });
//      CHECK(vec.zwxw() == fvec4{ 3.f, 4.f, 1.f, 4.f });
//      CHECK(vec.zwyx() == fvec4{ 3.f, 4.f, 2.f, 1.f });
//      CHECK(vec.zwyy() == fvec4{ 3.f, 4.f, 2.f, 2.f });
//      CHECK(vec.zwyz() == fvec4{ 3.f, 4.f, 2.f, 3.f });
//      CHECK(vec.zwyw() == fvec4{ 3.f, 4.f, 2.f, 4.f });
//      CHECK(vec.zwzx() == fvec4{ 3.f, 4.f, 3.f, 1.f });
//      CHECK(vec.zwzy() == fvec4{ 3.f, 4.f, 3.f, 2.f });
//      CHECK(vec.zwzz() == fvec4{ 3.f, 4.f, 3.f, 3.f });
//      CHECK(vec.zwzw() == fvec4{ 3.f, 4.f, 3.f, 4.f });
//      CHECK(vec.zwwx() == fvec4{ 3.f, 4.f, 4.f, 1.f });
//      CHECK(vec.zwwy() == fvec4{ 3.f, 4.f, 4.f, 2.f });
//      CHECK(vec.zwwz() == fvec4{ 3.f, 4.f, 4.f, 3.f });
//      CHECK(vec.zwww() == fvec4{ 3.f, 4.f, 4.f, 4.f });
//      CHECK(vec.wxxx() == fvec4{ 4.f, 1.f, 1.f, 1.f });
//      CHECK(vec.wxxy() == fvec4{ 4.f, 1.f, 1.f, 2.f });
//      CHECK(vec.wxxz() == fvec4{ 4.f, 1.f, 1.f, 3.f });
//      CHECK(vec.wxxw() == fvec4{ 4.f, 1.f, 1.f, 4.f });
//      CHECK(vec.wxyx() == fvec4{ 4.f, 1.f, 2.f, 1.f });
//      CHECK(vec.wxyy() == fvec4{ 4.f, 1.f, 2.f, 2.f });
//      CHECK(vec.wxyz() == fvec4{ 4.f, 1.f, 2.f, 3.f });
//      CHECK(vec.wxyw() == fvec4{ 4.f, 1.f, 2.f, 4.f });
//      CHECK(vec.wxzx() == fvec4{ 4.f, 1.f, 3.f, 1.f });
//      CHECK(vec.wxzy() == fvec4{ 4.f, 1.f, 3.f, 2.f });
//      CHECK(vec.wxzz() == fvec4{ 4.f, 1.f, 3.f, 3.f });
//      CHECK(vec.wxzw() == fvec4{ 4.f, 1.f, 3.f, 4.f });
//      CHECK(vec.wxwx() == fvec4{ 4.f, 1.f, 4.f, 1.f });
//      CHECK(vec.wxwy() == fvec4{ 4.f, 1.f, 4.f, 2.f });
//      CHECK(vec.wxwz() == fvec4{ 4.f, 1.f, 4.f, 3.f });
//      CHECK(vec.wxww() == fvec4{ 4.f, 1.f, 4.f, 4.f });
//      CHECK(vec.wyxx() == fvec4{ 4.f, 2.f, 1.f, 1.f });
//      CHECK(vec.wyxy() == fvec4{ 4.f, 2.f, 1.f, 2.f });
//      CHECK(vec.wyxz() == fvec4{ 4.f, 2.f, 1.f, 3.f });
//      CHECK(vec.wyxw() == fvec4{ 4.f, 2.f, 1.f, 4.f });
//      CHECK(vec.wyyx() == fvec4{ 4.f, 2.f, 2.f, 1.f });
//      CHECK(vec.wyyy() == fvec4{ 4.f, 2.f, 2.f, 2.f });
//      CHECK(vec.wyyz() == fvec4{ 4.f, 2.f, 2.f, 3.f });
//      CHECK(vec.wyyw() == fvec4{ 4.f, 2.f, 2.f, 4.f });
//      CHECK(vec.wyzx() == fvec4{ 4.f, 2.f, 3.f, 1.f });
//      CHECK(vec.wyzy() == fvec4{ 4.f, 2.f, 3.f, 2.f });
//      CHECK(vec.wyzz() == fvec4{ 4.f, 2.f, 3.f, 3.f });
//      CHECK(vec.wyzw() == fvec4{ 4.f, 2.f, 3.f, 4.f });
//      CHECK(vec.wywx() == fvec4{ 4.f, 2.f, 4.f, 1.f });
//      CHECK(vec.wywy() == fvec4{ 4.f, 2.f, 4.f, 2.f });
//      CHECK(vec.wywz() == fvec4{ 4.f, 2.f, 4.f, 3.f });
//      CHECK(vec.wyww() == fvec4{ 4.f, 2.f, 4.f, 4.f });
//      CHECK(vec.wzxx() == fvec4{ 4.f, 3.f, 1.f, 1.f });
//      CHECK(vec.wzxy() == fvec4{ 4.f, 3.f, 1.f, 2.f });
//      CHECK(vec.wzxz() == fvec4{ 4.f, 3.f, 1.f, 3.f });
//      CHECK(vec.wzxw() == fvec4{ 4.f, 3.f, 1.f, 4.f });
//      CHECK(vec.wzyx() == fvec4{ 4.f, 3.f, 2.f, 1.f });
//      CHECK(vec.wzyy() == fvec4{ 4.f, 3.f, 2.f, 2.f });
//      CHECK(vec.wzyz() == fvec4{ 4.f, 3.f, 2.f, 3.f });
//      CHECK(vec.wzyw() == fvec4{ 4.f, 3.f, 2.f, 4.f });
//      CHECK(vec.wzzx() == fvec4{ 4.f, 3.f, 3.f, 1.f });
//      CHECK(vec.wzzy() == fvec4{ 4.f, 3.f, 3.f, 2.f });
//      CHECK(vec.wzzz() == fvec4{ 4.f, 3.f, 3.f, 3.f });
//      CHECK(vec.wzzw() == fvec4{ 4.f, 3.f, 3.f, 4.f });
//      CHECK(vec.wzwx() == fvec4{ 4.f, 3.f, 4.f, 1.f });
//      CHECK(vec.wzwy() == fvec4{ 4.f, 3.f, 4.f, 2.f });
//      CHECK(vec.wzwz() == fvec4{ 4.f, 3.f, 4.f, 3.f });
//      CHECK(vec.wzww() == fvec4{ 4.f, 3.f, 4.f, 4.f });
//      CHECK(vec.wwxx() == fvec4{ 4.f, 4.f, 1.f, 1.f });
//      CHECK(vec.wwxy() == fvec4{ 4.f, 4.f, 1.f, 2.f });
//      CHECK(vec.wwxz() == fvec4{ 4.f, 4.f, 1.f, 3.f });
//      CHECK(vec.wwxw() == fvec4{ 4.f, 4.f, 1.f, 4.f });
//      CHECK(vec.wwyx() == fvec4{ 4.f, 4.f, 2.f, 1.f });
//      CHECK(vec.wwyy() == fvec4{ 4.f, 4.f, 2.f, 2.f });
//      CHECK(vec.wwyz() == fvec4{ 4.f, 4.f, 2.f, 3.f });
//      CHECK(vec.wwyw() == fvec4{ 4.f, 4.f, 2.f, 4.f });
//      CHECK(vec.wwzx() == fvec4{ 4.f, 4.f, 3.f, 1.f });
//      CHECK(vec.wwzy() == fvec4{ 4.f, 4.f, 3.f, 2.f });
//      CHECK(vec.wwzz() == fvec4{ 4.f, 4.f, 3.f, 3.f });
//      CHECK(vec.wwzw() == fvec4{ 4.f, 4.f, 3.f, 4.f });
//      CHECK(vec.wwwx() == fvec4{ 4.f, 4.f, 4.f, 1.f });
//      CHECK(vec.wwwy() == fvec4{ 4.f, 4.f, 4.f, 2.f });
//      CHECK(vec.wwwz() == fvec4{ 4.f, 4.f, 4.f, 3.f });
//      CHECK(vec.wwww() == fvec4{ 4.f, 4.f, 4.f, 4.f });
//    }
//  }
//}
