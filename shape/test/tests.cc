#include <shapes/functions.hh>
#include <shapes/vec.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`shapes`::`fvec2`::`constexpr`") {
}

TEST_CASE("`shapes`::`fvec2`") {
  SECTION("Default ctor") {
    fvec2 v{};
    CAPTURE(v);

    CHECK(v.x() == 0.F);
    CHECK(v.y() == 0.F);

    CHECK(v == fvec2{});
    CHECK(v == fvec2(0.F));
    CHECK(v == fvec2(0.F, 0.F));
    CHECK(2.F * v == v);
    CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    fvec2 v(3.F);
    CAPTURE(v);

    CHECK(v.x() == 3.F);
    CHECK(v.y() == 3.F);

    CHECK(v == fvec2(3.F));
    CHECK(v == fvec2(3.F, 3.F));
    CHECK(2.F * v == fvec2(6.F));
    CHECK(v * 2.F == fvec2(6.F));

    CHECK(v > fvec2{});
    CHECK(v >= fvec2{});
    CHECK(fvec2{} < v);
    CHECK(fvec2{} <= v);
    CHECK(v != fvec2{});
  }
}

TEST_CASE("`shape`::`fvec3`") {
  SECTION("Default ctor") {
    fvec3 v{};
    CAPTURE(v);

    CHECK(v.x() == 0.F);
    CHECK(v.y() == 0.F);
    CHECK(v.z() == 0.F);

    CHECK(v == fvec3{});
    CHECK(v == fvec3(0.F));
    CHECK(v == fvec3(0.F, 0.F, 0.F));
    CHECK(2.F * v == v);
    CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    fvec3 v(3.F);
    CAPTURE(v);

    CHECK(v.x() == 3.F);
    CHECK(v.y() == 3.F);
    CHECK(v.z() == 3.F);

    CHECK(v == fvec3(3.F));
    CHECK(v == fvec3(3.F, 3.F, 3.F));
    CHECK(2.F * v == fvec3(6.F));
    CHECK(v * 2.F == fvec3(6.F));

    CHECK(v > fvec3{});
    CHECK(v >= fvec3{});
    CHECK(fvec3{} < v);
    CHECK(fvec3{} <= v);
    CHECK(v != fvec3{});
  }
}

TEST_CASE("`shapes`::`fvec4`") {
  SECTION("Default ctor") {
    fvec4 v{};
    CAPTURE(v);

    CHECK(v.x() == 0.F);
    CHECK(v.y() == 0.F);
    CHECK(v.z() == 0.F);
    CHECK(v.w() == 0.F);

    CHECK(v == fvec4{});
    CHECK(v == fvec4(0.F));
    CHECK(v == fvec4(0.F, 0.F, 0.F, 0.F));
    CHECK(2.F * v == v);
    CHECK(v * 2.F == v);
  }

  SECTION("Single value ctor") {
    fvec4 v(3.F);
    CAPTURE(v);

    CHECK(v.x() == 3.F);
    CHECK(v.y() == 3.F);
    CHECK(v.z() == 3.F);
    CHECK(v.w() == 3.F);

    CHECK(v == fvec4(3.F));
    CHECK(v == fvec4(3.F, 3.F, 3.F, 3.f));
    CHECK(2.F * v == fvec4(6.F));
    CHECK(v * 2.F == fvec4(6.F));

    CHECK(v > fvec4{});
    CHECK(v >= fvec4{});
    CHECK(fvec4{} < v);
    CHECK(fvec4{} <= v);
    CHECK(v != fvec4{});
  }
}

TEST_CASE("`shapes`::functions") {
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
    CHECK(sign(fvec2(0.f, 3.f)) == fvec2(0.f, 1.f));
    CHECK(sign(fvec2(-1.f, 3.2f)) == fvec2(-1.f, 1.f));

    //fvec3 sign(fvec3 f)
    CHECK(sign(fvec3(0.f, 3.f, -2.4f)) == fvec3(0.f, 1.f, -1.f));
    CHECK(sign(fvec3(-1.f, 3.2f, 0.f)) == fvec3(-1.f, 1.f, 0.f));

    //fvec4 sign(fvec4 f)
    CHECK(sign(fvec4(0.f, 3.f, -2.4f, -0.f)) == fvec4(0.f, 1.f, -1.f, 0.f));
    CHECK(sign(fvec4(-1.f, 3.2f, 0.f, 1.f)) == fvec4(-1.f, 1.f, 0.f, 1.f));
  }

  SECTION("Clamp") {
    //float clamp(float f, float l, float h)
    CHECK(clamp(.5f, .0f, 1.f) == .5f);
    CHECK(clamp(.5f, 1.2f, 6.7f) == 1.2f);
    CHECK(clamp(.5f, -1.f, .3f) == .3f);

    //fvec2 clamp(fvec2 f, fvec2 l, fvec2 h)
    CHECK(clamp(fvec2(.5f, .5f), fvec2(.0f, 1.2f), fvec2(1.f, 6.7f)) == fvec2(.5f, 1.2f));
    CHECK(clamp(fvec2(.5f, 12.f), fvec2(-1.f, 10.f), fvec2(.3f, 11.f)) == fvec2(.3f, 11.f));

    //fvec2 clamp(fvec2 f, float l, float h)
    CHECK(clamp(fvec2(.5f, 15.f), 1.f, 10.f) == fvec2(1.f, 10.f));
    CHECK(clamp(fvec2(.5f, 12.f), .0f, .0f) == fvec2(.0f, .0f));

    //fvec3 clamp(fvec3 f, fvec3 l, fvec3 h)
    CHECK(clamp(fvec3(.5f, .5f, .5f), fvec3(.0f, 1.2f, -10.f), fvec3(1.f, 6.7f, -6.7f)) == fvec3(.5f, 1.2f, -6.7f));

    //fvec3 clamp(fvec3 f, float l, float h)
    CHECK(clamp(fvec3(.5f, 3.f, 7.f), 2.3f, 5.f) == fvec3(2.3f, 3.f, 5.f));
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
    CHECK(length(fvec2(1.f, 0.f)) == 1.f);
    CHECK(length(fvec2(0.f, 1.f)) == 1.f);

    CHECK(length(fvec2(3.f, 0.f)) == 3.f);
    CHECK(length(fvec2(0.f, 3.f)) == 3.f);

    CHECK(length(fvec2(3.f, 4.f)) == 5.f);

    //float length(const fvec3& vector)
    CHECK(length(fvec3(1.f, 0.f, 0.f)) == 1.f);
    CHECK(length(fvec3(0.f, 1.f, 0.f)) == 1.f);
    CHECK(length(fvec3(0.f, 0.f, 1.f)) == 1.f);

    CHECK(length(fvec3(3.f, 0.f, 0.f)) == 3.f);
    CHECK(length(fvec3(0.f, 3.f, 0.f)) == 3.f);
    CHECK(length(fvec3(0.f, 0.f, 3.f)) == 3.f);

    //float length(const fvec4& vector)
    CHECK(length(fvec4(1.f, 0.f, 0.f, 0.f)) == 1.f);
    CHECK(length(fvec4(0.f, 1.f, 0.f, 0.f)) == 1.f);
    CHECK(length(fvec4(0.f, 0.f, 1.f, 0.f)) == 1.f);
    CHECK(length(fvec4(0.f, 0.f, 0.f, 1.f)) == 1.f);

    CHECK(length(fvec4(3.f, 0.f, 0.f, 0.f)) == 3.f);
    CHECK(length(fvec4(0.f, 3.f, 0.f, 0.f)) == 3.f);
    CHECK(length(fvec4(0.f, 0.f, 3.f, 0.f)) == 3.f);
    CHECK(length(fvec4(0.f, 0.f, 0.f, 3.f)) == 3.f);
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

  SECTION("pow") {
    // float pow(float a, float b) noexcept;
    // fvec2 pow(fvec2 a, fvec2 b) noexcept;
    // fvec3 pow(fvec3 a, fvec3 b) noexcept;
    // fvec4 pow(fvec4 a, fvec4 b) noexcept;
  }

  SECTION("all") {
    // bool all(bvec2& vec) noexcept;
    // bool all(bvec3& vec) noexcept;
    // bool all(bvec4& vec) noexcept;
  }

  SECTION("negate") {
    // bvec2 negate(bvec2& vec) noexcept;
    // bvec3 negate(bvec3& vec) noexcept;
    // bvec4 negate(bvec4& vec) noexcept;
  }
}

TEST_CASE("`shapes`::swizzling") {
  SECTION("sandbox") {
    SECTION("Member quantity when swizzling") {
      fvec3 vec(1.f, 2.f, 3.f);

      // this doesn't work for some reason...
      // CHECK(vec("x"_swz) == 1.f);
      CHECK(vec("xx"_swz) == vecn<float, 2>(1.f, 1.f));
      CHECK(vec("xxx"_swz) == vecn<float, 3>(1.f, 1.f, 1.f));
      CHECK(vec("xxxx"_swz) == vecn<float, 4>(1.f, 1.f, 1.f, 1.f));
      CHECK(vec("xxxxx"_swz) == vecn<float, 5>(1.f, 1.f, 1.f, 1.f, 1.f));
      CHECK(vec("xxxxxx"_swz) == vecn<float, 6>(1.f, 1.f, 1.f, 1.f, 1.f, 1.f));
      CHECK(vec("xxxxxxx"_swz) == vecn<float, 7>(1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f));
    }

    SECTION("math") {
      fvec2 vec1;
      fvec2 vec2;

      vec1 < vec2;
      vec1 <= vec2;
      vec1 > vec2;
      vec1 >= vec2;
      vec1 != vec2;
      vec1 == vec2;

      vec1 + vec2;
      vec1 - vec2;
      vec1 * vec2;
      vec1 / vec2;

      vec1 += vec2;
      vec1 -= vec2;
      vec1 *= vec2;
      vec1 /= vec2;
    }
  }

  SECTION("fvec2") {
    fvec2 vec(1.f, 2.f);

    SECTION("fvec2 result") {
      SECTION("rvalue") {
        CHECK(vec("xx"_swz) == fvec2(1.f, 1.f));
        CHECK(vec("xy"_swz) == fvec2(1.f, 2.f));
        CHECK(vec("yx"_swz) == fvec2(2.f, 1.f));
        CHECK(vec("yy"_swz) == fvec2(2.f, 2.f));
      }

      SECTION("lvalue") {
        vec("xy"_swz) = fvec2(3.f, 4.f);
        CHECK(vec == fvec2(3.f, 4.f));

        vec = fvec2(1.f, 2.f);

        vec("xx"_swz) = fvec2(3.f, 4.f);
        CHECK(vec == fvec2(3.f, 2.f));
        CHECK(vec.x() == 3.f);
        CHECK(vec.y() == 2.f);
      }
    }

    SECTION("fvec3 result") {
      CHECK(vec("xxx"_swz) == fvec3(1.f, 1.f, 1.f));
      CHECK(vec("xxy"_swz) == fvec3(1.f, 1.f, 2.f));
      CHECK(vec("xyx"_swz) == fvec3(1.f, 2.f, 1.f));
      CHECK(vec("xyy"_swz) == fvec3(1.f, 2.f, 2.f));
      CHECK(vec("yxx"_swz) == fvec3(2.f, 1.f, 1.f));
      CHECK(vec("yxy"_swz) == fvec3(2.f, 1.f, 2.f));
      CHECK(vec("yyx"_swz) == fvec3(2.f, 2.f, 1.f));
      CHECK(vec("yyy"_swz) == fvec3(2.f, 2.f, 2.f));
    }

    SECTION("fvec4 result") {
      CHECK(vec("xxxx"_swz) == fvec4(1.f, 1.f, 1.f, 1.f));
      CHECK(vec("xxxy"_swz) == fvec4(1.f, 1.f, 1.f, 2.f));
      CHECK(vec("xxyx"_swz) == fvec4(1.f, 1.f, 2.f, 1.f));
      CHECK(vec("xxyy"_swz) == fvec4(1.f, 1.f, 2.f, 2.f));
      CHECK(vec("xyxx"_swz) == fvec4(1.f, 2.f, 1.f, 1.f));
      CHECK(vec("xyxy"_swz) == fvec4(1.f, 2.f, 1.f, 2.f));
      CHECK(vec("xyyx"_swz) == fvec4(1.f, 2.f, 2.f, 1.f));
      CHECK(vec("xyyy"_swz) == fvec4(1.f, 2.f, 2.f, 2.f));
      CHECK(vec("yxxx"_swz) == fvec4(2.f, 1.f, 1.f, 1.f));
      CHECK(vec("yxxy"_swz) == fvec4(2.f, 1.f, 1.f, 2.f));
      CHECK(vec("yxyx"_swz) == fvec4(2.f, 1.f, 2.f, 1.f));
      CHECK(vec("yxyy"_swz) == fvec4(2.f, 1.f, 2.f, 2.f));
      CHECK(vec("yyxx"_swz) == fvec4(2.f, 2.f, 1.f, 1.f));
      CHECK(vec("yyxy"_swz) == fvec4(2.f, 2.f, 1.f, 2.f));
      CHECK(vec("yyyx"_swz) == fvec4(2.f, 2.f, 2.f, 1.f));
      CHECK(vec("yyyy"_swz) == fvec4(2.f, 2.f, 2.f, 2.f));
    }
  }

  SECTION("fvec3") {
    fvec3 vec(1.f, 2.f, 3.f);

    SECTION("fvec2 result") {
      SECTION("rvalue") {
        CHECK(vec("xx"_swz) == fvec2(1.f, 1.f));
        CHECK(vec("xy"_swz) == fvec2(1.f, 2.f));
        CHECK(vec("xz"_swz) == fvec2(1.f, 3.f));
        CHECK(vec("yx"_swz) == fvec2(2.f, 1.f));
        CHECK(vec("yy"_swz) == fvec2(2.f, 2.f));
        CHECK(vec("yz"_swz) == fvec2(2.f, 3.f));
        CHECK(vec("zx"_swz) == fvec2(3.f, 1.f));
        CHECK(vec("zy"_swz) == fvec2(3.f, 2.f));
        CHECK(vec("zz"_swz) == fvec2(3.f, 3.f));
      }

      SECTION("lvalue") {
        vec("xy"_swz) = fvec2(3.f, 4.f);
        CHECK(vec == fvec3(3.f, 4.f, 3.f));

        vec = fvec3(1.f, 2.f, 3.f);

        vec("xx"_swz) = fvec2(3.f, 4.f);
        CHECK(vec == fvec3(3.f, 2.f, 3.f));
        CHECK(vec.x() == 3.f);
        CHECK(vec.y() == 2.f);
        CHECK(vec.z() == 3.f);
      }
    }

    SECTION("fvec3 result") {
      CHECK(vec("xxx"_swz) == fvec3(1.f, 1.f, 1.f));
      CHECK(vec("xxy"_swz) == fvec3(1.f, 1.f, 2.f));
      CHECK(vec("xxz"_swz) == fvec3(1.f, 1.f, 3.f));
      CHECK(vec("xyx"_swz) == fvec3(1.f, 2.f, 1.f));
      CHECK(vec("xyy"_swz) == fvec3(1.f, 2.f, 2.f));
      CHECK(vec("xyz"_swz) == fvec3(1.f, 2.f, 3.f));
      CHECK(vec("xzx"_swz) == fvec3(1.f, 3.f, 1.f));
      CHECK(vec("xzy"_swz) == fvec3(1.f, 3.f, 2.f));
      CHECK(vec("xzz"_swz) == fvec3(1.f, 3.f, 3.f));
      CHECK(vec("yxx"_swz) == fvec3(2.f, 1.f, 1.f));
      CHECK(vec("yxy"_swz) == fvec3(2.f, 1.f, 2.f));
      CHECK(vec("yxz"_swz) == fvec3(2.f, 1.f, 3.f));
      CHECK(vec("yyx"_swz) == fvec3(2.f, 2.f, 1.f));
      CHECK(vec("yyy"_swz) == fvec3(2.f, 2.f, 2.f));
      CHECK(vec("yyz"_swz) == fvec3(2.f, 2.f, 3.f));
      CHECK(vec("yzx"_swz) == fvec3(2.f, 3.f, 1.f));
      CHECK(vec("yzy"_swz) == fvec3(2.f, 3.f, 2.f));
      CHECK(vec("yzz"_swz) == fvec3(2.f, 3.f, 3.f));
      CHECK(vec("zxx"_swz) == fvec3(3.f, 1.f, 1.f));
      CHECK(vec("zxy"_swz) == fvec3(3.f, 1.f, 2.f));
      CHECK(vec("zxz"_swz) == fvec3(3.f, 1.f, 3.f));
      CHECK(vec("zyx"_swz) == fvec3(3.f, 2.f, 1.f));
      CHECK(vec("zyy"_swz) == fvec3(3.f, 2.f, 2.f));
      CHECK(vec("zyz"_swz) == fvec3(3.f, 2.f, 3.f));
      CHECK(vec("zzx"_swz) == fvec3(3.f, 3.f, 1.f));
      CHECK(vec("zzy"_swz) == fvec3(3.f, 3.f, 2.f));
      CHECK(vec("zzz"_swz) == fvec3(3.f, 3.f, 3.f));
    }

    SECTION("fvec4 result") {
      CHECK(vec("xxxx"_swz) == fvec4(1.f, 1.f, 1.f, 1.f));
      CHECK(vec("xxxy"_swz) == fvec4(1.f, 1.f, 1.f, 2.f));
      CHECK(vec("xxxz"_swz) == fvec4(1.f, 1.f, 1.f, 3.f));
      CHECK(vec("xxyx"_swz) == fvec4(1.f, 1.f, 2.f, 1.f));
      CHECK(vec("xxyy"_swz) == fvec4(1.f, 1.f, 2.f, 2.f));
      CHECK(vec("xxyz"_swz) == fvec4(1.f, 1.f, 2.f, 3.f));
      CHECK(vec("xxzx"_swz) == fvec4(1.f, 1.f, 3.f, 1.f));
      CHECK(vec("xxzy"_swz) == fvec4(1.f, 1.f, 3.f, 2.f));
      CHECK(vec("xxzz"_swz) == fvec4(1.f, 1.f, 3.f, 3.f));
      CHECK(vec("xyxx"_swz) == fvec4(1.f, 2.f, 1.f, 1.f));
      CHECK(vec("xyxy"_swz) == fvec4(1.f, 2.f, 1.f, 2.f));
      CHECK(vec("xyxz"_swz) == fvec4(1.f, 2.f, 1.f, 3.f));
      CHECK(vec("xyyx"_swz) == fvec4(1.f, 2.f, 2.f, 1.f));
      CHECK(vec("xyyy"_swz) == fvec4(1.f, 2.f, 2.f, 2.f));
      CHECK(vec("xyyz"_swz) == fvec4(1.f, 2.f, 2.f, 3.f));
      CHECK(vec("xyzx"_swz) == fvec4(1.f, 2.f, 3.f, 1.f));
      CHECK(vec("xyzy"_swz) == fvec4(1.f, 2.f, 3.f, 2.f));
      CHECK(vec("xyzz"_swz) == fvec4(1.f, 2.f, 3.f, 3.f));
      CHECK(vec("xzxx"_swz) == fvec4(1.f, 3.f, 1.f, 1.f));
      CHECK(vec("xzxy"_swz) == fvec4(1.f, 3.f, 1.f, 2.f));
      CHECK(vec("xzxz"_swz) == fvec4(1.f, 3.f, 1.f, 3.f));
      CHECK(vec("xzyx"_swz) == fvec4(1.f, 3.f, 2.f, 1.f));
      CHECK(vec("xzyy"_swz) == fvec4(1.f, 3.f, 2.f, 2.f));
      CHECK(vec("xzyz"_swz) == fvec4(1.f, 3.f, 2.f, 3.f));
      CHECK(vec("xzzx"_swz) == fvec4(1.f, 3.f, 3.f, 1.f));
      CHECK(vec("xzzy"_swz) == fvec4(1.f, 3.f, 3.f, 2.f));
      CHECK(vec("xzzz"_swz) == fvec4(1.f, 3.f, 3.f, 3.f));
      CHECK(vec("yxxx"_swz) == fvec4(2.f, 1.f, 1.f, 1.f));
      CHECK(vec("yxxy"_swz) == fvec4(2.f, 1.f, 1.f, 2.f));
      CHECK(vec("yxxz"_swz) == fvec4(2.f, 1.f, 1.f, 3.f));
      CHECK(vec("yxyx"_swz) == fvec4(2.f, 1.f, 2.f, 1.f));
      CHECK(vec("yxyy"_swz) == fvec4(2.f, 1.f, 2.f, 2.f));
      CHECK(vec("yxyz"_swz) == fvec4(2.f, 1.f, 2.f, 3.f));
      CHECK(vec("yxzx"_swz) == fvec4(2.f, 1.f, 3.f, 1.f));
      CHECK(vec("yxzy"_swz) == fvec4(2.f, 1.f, 3.f, 2.f));
      CHECK(vec("yxzz"_swz) == fvec4(2.f, 1.f, 3.f, 3.f));
      CHECK(vec("yyxx"_swz) == fvec4(2.f, 2.f, 1.f, 1.f));
      CHECK(vec("yyxy"_swz) == fvec4(2.f, 2.f, 1.f, 2.f));
      CHECK(vec("yyxz"_swz) == fvec4(2.f, 2.f, 1.f, 3.f));
      CHECK(vec("yyyx"_swz) == fvec4(2.f, 2.f, 2.f, 1.f));
      CHECK(vec("yyyy"_swz) == fvec4(2.f, 2.f, 2.f, 2.f));
      CHECK(vec("yyyz"_swz) == fvec4(2.f, 2.f, 2.f, 3.f));
      CHECK(vec("yyzx"_swz) == fvec4(2.f, 2.f, 3.f, 1.f));
      CHECK(vec("yyzy"_swz) == fvec4(2.f, 2.f, 3.f, 2.f));
      CHECK(vec("yyzz"_swz) == fvec4(2.f, 2.f, 3.f, 3.f));
      CHECK(vec("yzxx"_swz) == fvec4(2.f, 3.f, 1.f, 1.f));
      CHECK(vec("yzxy"_swz) == fvec4(2.f, 3.f, 1.f, 2.f));
      CHECK(vec("yzxz"_swz) == fvec4(2.f, 3.f, 1.f, 3.f));
      CHECK(vec("yzyx"_swz) == fvec4(2.f, 3.f, 2.f, 1.f));
      CHECK(vec("yzyy"_swz) == fvec4(2.f, 3.f, 2.f, 2.f));
      CHECK(vec("yzyz"_swz) == fvec4(2.f, 3.f, 2.f, 3.f));
      CHECK(vec("yzzx"_swz) == fvec4(2.f, 3.f, 3.f, 1.f));
      CHECK(vec("yzzy"_swz) == fvec4(2.f, 3.f, 3.f, 2.f));
      CHECK(vec("yzzz"_swz) == fvec4(2.f, 3.f, 3.f, 3.f));
      CHECK(vec("zxxx"_swz) == fvec4(3.f, 1.f, 1.f, 1.f));
      CHECK(vec("zxxy"_swz) == fvec4(3.f, 1.f, 1.f, 2.f));
      CHECK(vec("zxxz"_swz) == fvec4(3.f, 1.f, 1.f, 3.f));
      CHECK(vec("zxyx"_swz) == fvec4(3.f, 1.f, 2.f, 1.f));
      CHECK(vec("zxyy"_swz) == fvec4(3.f, 1.f, 2.f, 2.f));
      CHECK(vec("zxyz"_swz) == fvec4(3.f, 1.f, 2.f, 3.f));
      CHECK(vec("zxzx"_swz) == fvec4(3.f, 1.f, 3.f, 1.f));
      CHECK(vec("zxzy"_swz) == fvec4(3.f, 1.f, 3.f, 2.f));
      CHECK(vec("zxzz"_swz) == fvec4(3.f, 1.f, 3.f, 3.f));
      CHECK(vec("zyxx"_swz) == fvec4(3.f, 2.f, 1.f, 1.f));
      CHECK(vec("zyxy"_swz) == fvec4(3.f, 2.f, 1.f, 2.f));
      CHECK(vec("zyxz"_swz) == fvec4(3.f, 2.f, 1.f, 3.f));
      CHECK(vec("zyyx"_swz) == fvec4(3.f, 2.f, 2.f, 1.f));
      CHECK(vec("zyyy"_swz) == fvec4(3.f, 2.f, 2.f, 2.f));
      CHECK(vec("zyyz"_swz) == fvec4(3.f, 2.f, 2.f, 3.f));
      CHECK(vec("zyzx"_swz) == fvec4(3.f, 2.f, 3.f, 1.f));
      CHECK(vec("zyzy"_swz) == fvec4(3.f, 2.f, 3.f, 2.f));
      CHECK(vec("zyzz"_swz) == fvec4(3.f, 2.f, 3.f, 3.f));
      CHECK(vec("zzxx"_swz) == fvec4(3.f, 3.f, 1.f, 1.f));
      CHECK(vec("zzxy"_swz) == fvec4(3.f, 3.f, 1.f, 2.f));
      CHECK(vec("zzxz"_swz) == fvec4(3.f, 3.f, 1.f, 3.f));
      CHECK(vec("zzyx"_swz) == fvec4(3.f, 3.f, 2.f, 1.f));
      CHECK(vec("zzyy"_swz) == fvec4(3.f, 3.f, 2.f, 2.f));
      CHECK(vec("zzyz"_swz) == fvec4(3.f, 3.f, 2.f, 3.f));
      CHECK(vec("zzzx"_swz) == fvec4(3.f, 3.f, 3.f, 1.f));
      CHECK(vec("zzzy"_swz) == fvec4(3.f, 3.f, 3.f, 2.f));
      CHECK(vec("zzzz"_swz) == fvec4(3.f, 3.f, 3.f, 3.f));
    }
  }

  SECTION("fvec4") {
    fvec4 vec(1.f, 2.f, 3.f, 4.f);

    SECTION("fvec2 result") {
      SECTION("rvalue") {
        CHECK(vec("xx"_swz) == fvec2(1.f, 1.f));
        CHECK(vec("xy"_swz) == fvec2(1.f, 2.f));
        CHECK(vec("xz"_swz) == fvec2(1.f, 3.f));
        CHECK(vec("xw"_swz) == fvec2(1.f, 4.f));
        CHECK(vec("yx"_swz) == fvec2(2.f, 1.f));
        CHECK(vec("yy"_swz) == fvec2(2.f, 2.f));
        CHECK(vec("yz"_swz) == fvec2(2.f, 3.f));
        CHECK(vec("yw"_swz) == fvec2(2.f, 4.f));
        CHECK(vec("zx"_swz) == fvec2(3.f, 1.f));
        CHECK(vec("zy"_swz) == fvec2(3.f, 2.f));
        CHECK(vec("zz"_swz) == fvec2(3.f, 3.f));
        CHECK(vec("zw"_swz) == fvec2(3.f, 4.f));
        CHECK(vec("wx"_swz) == fvec2(4.f, 1.f));
        CHECK(vec("wy"_swz) == fvec2(4.f, 2.f));
        CHECK(vec("wz"_swz) == fvec2(4.f, 3.f));
        CHECK(vec("ww"_swz) == fvec2(4.f, 4.f));
      }

      SECTION("lvalue") {
        vec("xy"_swz) = fvec2(3.f, 4.f);
        CHECK(vec == fvec4(3.f, 4.f, 3.f, 4.f));

        vec = fvec4(1.f, 2.f, 3.f, 4.f);

        vec("xx"_swz) = fvec2(3.f, 4.f);
        CHECK(vec == fvec4(3.f, 2.f, 3.f, 4.f));
        CHECK(vec.x() == 3.f);
        CHECK(vec.y() == 2.f);
      }
    }

    SECTION("fvec3 result") {
      CHECK(vec("xxx"_swz) == fvec3(1.f, 1.f, 1.f));
      CHECK(vec("xxy"_swz) == fvec3(1.f, 1.f, 2.f));
      CHECK(vec("xxz"_swz) == fvec3(1.f, 1.f, 3.f));
      CHECK(vec("xxw"_swz) == fvec3(1.f, 1.f, 4.f));
      CHECK(vec("xyx"_swz) == fvec3(1.f, 2.f, 1.f));
      CHECK(vec("xyy"_swz) == fvec3(1.f, 2.f, 2.f));
      CHECK(vec("xyz"_swz) == fvec3(1.f, 2.f, 3.f));
      CHECK(vec("xyw"_swz) == fvec3(1.f, 2.f, 4.f));
      CHECK(vec("xzx"_swz) == fvec3(1.f, 3.f, 1.f));
      CHECK(vec("xzy"_swz) == fvec3(1.f, 3.f, 2.f));
      CHECK(vec("xzz"_swz) == fvec3(1.f, 3.f, 3.f));
      CHECK(vec("xzw"_swz) == fvec3(1.f, 3.f, 4.f));
      CHECK(vec("xwx"_swz) == fvec3(1.f, 4.f, 1.f));
      CHECK(vec("xwy"_swz) == fvec3(1.f, 4.f, 2.f));
      CHECK(vec("xwz"_swz) == fvec3(1.f, 4.f, 3.f));
      CHECK(vec("xww"_swz) == fvec3(1.f, 4.f, 4.f));
      CHECK(vec("yxx"_swz) == fvec3(2.f, 1.f, 1.f));
      CHECK(vec("yxy"_swz) == fvec3(2.f, 1.f, 2.f));
      CHECK(vec("yxz"_swz) == fvec3(2.f, 1.f, 3.f));
      CHECK(vec("yxw"_swz) == fvec3(2.f, 1.f, 4.f));
      CHECK(vec("yyx"_swz) == fvec3(2.f, 2.f, 1.f));
      CHECK(vec("yyy"_swz) == fvec3(2.f, 2.f, 2.f));
      CHECK(vec("yyz"_swz) == fvec3(2.f, 2.f, 3.f));
      CHECK(vec("yyw"_swz) == fvec3(2.f, 2.f, 4.f));
      CHECK(vec("yzx"_swz) == fvec3(2.f, 3.f, 1.f));
      CHECK(vec("yzy"_swz) == fvec3(2.f, 3.f, 2.f));
      CHECK(vec("yzz"_swz) == fvec3(2.f, 3.f, 3.f));
      CHECK(vec("yzw"_swz) == fvec3(2.f, 3.f, 4.f));
      CHECK(vec("ywx"_swz) == fvec3(2.f, 4.f, 1.f));
      CHECK(vec("ywy"_swz) == fvec3(2.f, 4.f, 2.f));
      CHECK(vec("ywz"_swz) == fvec3(2.f, 4.f, 3.f));
      CHECK(vec("yww"_swz) == fvec3(2.f, 4.f, 4.f));
      CHECK(vec("zxx"_swz) == fvec3(3.f, 1.f, 1.f));
      CHECK(vec("zxy"_swz) == fvec3(3.f, 1.f, 2.f));
      CHECK(vec("zxz"_swz) == fvec3(3.f, 1.f, 3.f));
      CHECK(vec("zxw"_swz) == fvec3(3.f, 1.f, 4.f));
      CHECK(vec("zyx"_swz) == fvec3(3.f, 2.f, 1.f));
      CHECK(vec("zyy"_swz) == fvec3(3.f, 2.f, 2.f));
      CHECK(vec("zyz"_swz) == fvec3(3.f, 2.f, 3.f));
      CHECK(vec("zyw"_swz) == fvec3(3.f, 2.f, 4.f));
      CHECK(vec("zzx"_swz) == fvec3(3.f, 3.f, 1.f));
      CHECK(vec("zzy"_swz) == fvec3(3.f, 3.f, 2.f));
      CHECK(vec("zzz"_swz) == fvec3(3.f, 3.f, 3.f));
      CHECK(vec("zzw"_swz) == fvec3(3.f, 3.f, 4.f));
      CHECK(vec("zwx"_swz) == fvec3(3.f, 4.f, 1.f));
      CHECK(vec("zwy"_swz) == fvec3(3.f, 4.f, 2.f));
      CHECK(vec("zwz"_swz) == fvec3(3.f, 4.f, 3.f));
      CHECK(vec("zww"_swz) == fvec3(3.f, 4.f, 4.f));
      CHECK(vec("wxx"_swz) == fvec3(4.f, 1.f, 1.f));
      CHECK(vec("wxy"_swz) == fvec3(4.f, 1.f, 2.f));
      CHECK(vec("wxz"_swz) == fvec3(4.f, 1.f, 3.f));
      CHECK(vec("wxw"_swz) == fvec3(4.f, 1.f, 4.f));
      CHECK(vec("wyx"_swz) == fvec3(4.f, 2.f, 1.f));
      CHECK(vec("wyy"_swz) == fvec3(4.f, 2.f, 2.f));
      CHECK(vec("wyz"_swz) == fvec3(4.f, 2.f, 3.f));
      CHECK(vec("wyw"_swz) == fvec3(4.f, 2.f, 4.f));
      CHECK(vec("wzx"_swz) == fvec3(4.f, 3.f, 1.f));
      CHECK(vec("wzy"_swz) == fvec3(4.f, 3.f, 2.f));
      CHECK(vec("wzz"_swz) == fvec3(4.f, 3.f, 3.f));
      CHECK(vec("wzw"_swz) == fvec3(4.f, 3.f, 4.f));
      CHECK(vec("wwx"_swz) == fvec3(4.f, 4.f, 1.f));
      CHECK(vec("wwy"_swz) == fvec3(4.f, 4.f, 2.f));
      CHECK(vec("wwz"_swz) == fvec3(4.f, 4.f, 3.f));
      CHECK(vec("www"_swz) == fvec3(4.f, 4.f, 4.f));
    }

    SECTION("fvec4 result") {
      CHECK(vec("xxxx"_swz) == fvec4(1.f, 1.f, 1.f, 1.f));
      CHECK(vec("xxxy"_swz) == fvec4(1.f, 1.f, 1.f, 2.f));
      CHECK(vec("xxxz"_swz) == fvec4(1.f, 1.f, 1.f, 3.f));
      CHECK(vec("xxxw"_swz) == fvec4(1.f, 1.f, 1.f, 4.f));
      CHECK(vec("xxyx"_swz) == fvec4(1.f, 1.f, 2.f, 1.f));
      CHECK(vec("xxyy"_swz) == fvec4(1.f, 1.f, 2.f, 2.f));
      CHECK(vec("xxyz"_swz) == fvec4(1.f, 1.f, 2.f, 3.f));
      CHECK(vec("xxyw"_swz) == fvec4(1.f, 1.f, 2.f, 4.f));
      CHECK(vec("xxzx"_swz) == fvec4(1.f, 1.f, 3.f, 1.f));
      CHECK(vec("xxzy"_swz) == fvec4(1.f, 1.f, 3.f, 2.f));
      CHECK(vec("xxzz"_swz) == fvec4(1.f, 1.f, 3.f, 3.f));
      CHECK(vec("xxzw"_swz) == fvec4(1.f, 1.f, 3.f, 4.f));
      CHECK(vec("xxwx"_swz) == fvec4(1.f, 1.f, 4.f, 1.f));
      CHECK(vec("xxwy"_swz) == fvec4(1.f, 1.f, 4.f, 2.f));
      CHECK(vec("xxwz"_swz) == fvec4(1.f, 1.f, 4.f, 3.f));
      CHECK(vec("xxww"_swz) == fvec4(1.f, 1.f, 4.f, 4.f));
      CHECK(vec("xyxx"_swz) == fvec4(1.f, 2.f, 1.f, 1.f));
      CHECK(vec("xyxy"_swz) == fvec4(1.f, 2.f, 1.f, 2.f));
      CHECK(vec("xyxz"_swz) == fvec4(1.f, 2.f, 1.f, 3.f));
      CHECK(vec("xyxw"_swz) == fvec4(1.f, 2.f, 1.f, 4.f));
      CHECK(vec("xyyx"_swz) == fvec4(1.f, 2.f, 2.f, 1.f));
      CHECK(vec("xyyy"_swz) == fvec4(1.f, 2.f, 2.f, 2.f));
      CHECK(vec("xyyz"_swz) == fvec4(1.f, 2.f, 2.f, 3.f));
      CHECK(vec("xyyw"_swz) == fvec4(1.f, 2.f, 2.f, 4.f));
      CHECK(vec("xyzx"_swz) == fvec4(1.f, 2.f, 3.f, 1.f));
      CHECK(vec("xyzy"_swz) == fvec4(1.f, 2.f, 3.f, 2.f));
      CHECK(vec("xyzz"_swz) == fvec4(1.f, 2.f, 3.f, 3.f));
      CHECK(vec("xyzw"_swz) == fvec4(1.f, 2.f, 3.f, 4.f));
      CHECK(vec("xywx"_swz) == fvec4(1.f, 2.f, 4.f, 1.f));
      CHECK(vec("xywy"_swz) == fvec4(1.f, 2.f, 4.f, 2.f));
      CHECK(vec("xywz"_swz) == fvec4(1.f, 2.f, 4.f, 3.f));
      CHECK(vec("xyww"_swz) == fvec4(1.f, 2.f, 4.f, 4.f));
      CHECK(vec("xzxx"_swz) == fvec4(1.f, 3.f, 1.f, 1.f));
      CHECK(vec("xzxy"_swz) == fvec4(1.f, 3.f, 1.f, 2.f));
      CHECK(vec("xzxz"_swz) == fvec4(1.f, 3.f, 1.f, 3.f));
      CHECK(vec("xzxw"_swz) == fvec4(1.f, 3.f, 1.f, 4.f));
      CHECK(vec("xzyx"_swz) == fvec4(1.f, 3.f, 2.f, 1.f));
      CHECK(vec("xzyy"_swz) == fvec4(1.f, 3.f, 2.f, 2.f));
      CHECK(vec("xzyz"_swz) == fvec4(1.f, 3.f, 2.f, 3.f));
      CHECK(vec("xzyw"_swz) == fvec4(1.f, 3.f, 2.f, 4.f));
      CHECK(vec("xzzx"_swz) == fvec4(1.f, 3.f, 3.f, 1.f));
      CHECK(vec("xzzy"_swz) == fvec4(1.f, 3.f, 3.f, 2.f));
      CHECK(vec("xzzz"_swz) == fvec4(1.f, 3.f, 3.f, 3.f));
      CHECK(vec("xzzw"_swz) == fvec4(1.f, 3.f, 3.f, 4.f));
      CHECK(vec("xzwx"_swz) == fvec4(1.f, 3.f, 4.f, 1.f));
      CHECK(vec("xzwy"_swz) == fvec4(1.f, 3.f, 4.f, 2.f));
      CHECK(vec("xzwz"_swz) == fvec4(1.f, 3.f, 4.f, 3.f));
      CHECK(vec("xzww"_swz) == fvec4(1.f, 3.f, 4.f, 4.f));
      CHECK(vec("xwxx"_swz) == fvec4(1.f, 4.f, 1.f, 1.f));
      CHECK(vec("xwxy"_swz) == fvec4(1.f, 4.f, 1.f, 2.f));
      CHECK(vec("xwxz"_swz) == fvec4(1.f, 4.f, 1.f, 3.f));
      CHECK(vec("xwxw"_swz) == fvec4(1.f, 4.f, 1.f, 4.f));
      CHECK(vec("xwyx"_swz) == fvec4(1.f, 4.f, 2.f, 1.f));
      CHECK(vec("xwyy"_swz) == fvec4(1.f, 4.f, 2.f, 2.f));
      CHECK(vec("xwyz"_swz) == fvec4(1.f, 4.f, 2.f, 3.f));
      CHECK(vec("xwyw"_swz) == fvec4(1.f, 4.f, 2.f, 4.f));
      CHECK(vec("xwzx"_swz) == fvec4(1.f, 4.f, 3.f, 1.f));
      CHECK(vec("xwzy"_swz) == fvec4(1.f, 4.f, 3.f, 2.f));
      CHECK(vec("xwzz"_swz) == fvec4(1.f, 4.f, 3.f, 3.f));
      CHECK(vec("xwzw"_swz) == fvec4(1.f, 4.f, 3.f, 4.f));
      CHECK(vec("xwwx"_swz) == fvec4(1.f, 4.f, 4.f, 1.f));
      CHECK(vec("xwwy"_swz) == fvec4(1.f, 4.f, 4.f, 2.f));
      CHECK(vec("xwwz"_swz) == fvec4(1.f, 4.f, 4.f, 3.f));
      CHECK(vec("xwww"_swz) == fvec4(1.f, 4.f, 4.f, 4.f));
      CHECK(vec("yxxx"_swz) == fvec4(2.f, 1.f, 1.f, 1.f));
      CHECK(vec("yxxy"_swz) == fvec4(2.f, 1.f, 1.f, 2.f));
      CHECK(vec("yxxz"_swz) == fvec4(2.f, 1.f, 1.f, 3.f));
      CHECK(vec("yxxw"_swz) == fvec4(2.f, 1.f, 1.f, 4.f));
      CHECK(vec("yxyx"_swz) == fvec4(2.f, 1.f, 2.f, 1.f));
      CHECK(vec("yxyy"_swz) == fvec4(2.f, 1.f, 2.f, 2.f));
      CHECK(vec("yxyz"_swz) == fvec4(2.f, 1.f, 2.f, 3.f));
      CHECK(vec("yxyw"_swz) == fvec4(2.f, 1.f, 2.f, 4.f));
      CHECK(vec("yxzx"_swz) == fvec4(2.f, 1.f, 3.f, 1.f));
      CHECK(vec("yxzy"_swz) == fvec4(2.f, 1.f, 3.f, 2.f));
      CHECK(vec("yxzz"_swz) == fvec4(2.f, 1.f, 3.f, 3.f));
      CHECK(vec("yxzw"_swz) == fvec4(2.f, 1.f, 3.f, 4.f));
      CHECK(vec("yxwx"_swz) == fvec4(2.f, 1.f, 4.f, 1.f));
      CHECK(vec("yxwy"_swz) == fvec4(2.f, 1.f, 4.f, 2.f));
      CHECK(vec("yxwz"_swz) == fvec4(2.f, 1.f, 4.f, 3.f));
      CHECK(vec("yxww"_swz) == fvec4(2.f, 1.f, 4.f, 4.f));
      CHECK(vec("yyxx"_swz) == fvec4(2.f, 2.f, 1.f, 1.f));
      CHECK(vec("yyxy"_swz) == fvec4(2.f, 2.f, 1.f, 2.f));
      CHECK(vec("yyxz"_swz) == fvec4(2.f, 2.f, 1.f, 3.f));
      CHECK(vec("yyxw"_swz) == fvec4(2.f, 2.f, 1.f, 4.f));
      CHECK(vec("yyyx"_swz) == fvec4(2.f, 2.f, 2.f, 1.f));
      CHECK(vec("yyyy"_swz) == fvec4(2.f, 2.f, 2.f, 2.f));
      CHECK(vec("yyyz"_swz) == fvec4(2.f, 2.f, 2.f, 3.f));
      CHECK(vec("yyyw"_swz) == fvec4(2.f, 2.f, 2.f, 4.f));
      CHECK(vec("yyzx"_swz) == fvec4(2.f, 2.f, 3.f, 1.f));
      CHECK(vec("yyzy"_swz) == fvec4(2.f, 2.f, 3.f, 2.f));
      CHECK(vec("yyzz"_swz) == fvec4(2.f, 2.f, 3.f, 3.f));
      CHECK(vec("yyzw"_swz) == fvec4(2.f, 2.f, 3.f, 4.f));
      CHECK(vec("yywx"_swz) == fvec4(2.f, 2.f, 4.f, 1.f));
      CHECK(vec("yywy"_swz) == fvec4(2.f, 2.f, 4.f, 2.f));
      CHECK(vec("yywz"_swz) == fvec4(2.f, 2.f, 4.f, 3.f));
      CHECK(vec("yyww"_swz) == fvec4(2.f, 2.f, 4.f, 4.f));
      CHECK(vec("yzxx"_swz) == fvec4(2.f, 3.f, 1.f, 1.f));
      CHECK(vec("yzxy"_swz) == fvec4(2.f, 3.f, 1.f, 2.f));
      CHECK(vec("yzxz"_swz) == fvec4(2.f, 3.f, 1.f, 3.f));
      CHECK(vec("yzxw"_swz) == fvec4(2.f, 3.f, 1.f, 4.f));
      CHECK(vec("yzyx"_swz) == fvec4(2.f, 3.f, 2.f, 1.f));
      CHECK(vec("yzyy"_swz) == fvec4(2.f, 3.f, 2.f, 2.f));
      CHECK(vec("yzyz"_swz) == fvec4(2.f, 3.f, 2.f, 3.f));
      CHECK(vec("yzyw"_swz) == fvec4(2.f, 3.f, 2.f, 4.f));
      CHECK(vec("yzzx"_swz) == fvec4(2.f, 3.f, 3.f, 1.f));
      CHECK(vec("yzzy"_swz) == fvec4(2.f, 3.f, 3.f, 2.f));
      CHECK(vec("yzzz"_swz) == fvec4(2.f, 3.f, 3.f, 3.f));
      CHECK(vec("yzzw"_swz) == fvec4(2.f, 3.f, 3.f, 4.f));
      CHECK(vec("yzwx"_swz) == fvec4(2.f, 3.f, 4.f, 1.f));
      CHECK(vec("yzwy"_swz) == fvec4(2.f, 3.f, 4.f, 2.f));
      CHECK(vec("yzwz"_swz) == fvec4(2.f, 3.f, 4.f, 3.f));
      CHECK(vec("yzww"_swz) == fvec4(2.f, 3.f, 4.f, 4.f));
      CHECK(vec("ywxx"_swz) == fvec4(2.f, 4.f, 1.f, 1.f));
      CHECK(vec("ywxy"_swz) == fvec4(2.f, 4.f, 1.f, 2.f));
      CHECK(vec("ywxz"_swz) == fvec4(2.f, 4.f, 1.f, 3.f));
      CHECK(vec("ywxw"_swz) == fvec4(2.f, 4.f, 1.f, 4.f));
      CHECK(vec("ywyx"_swz) == fvec4(2.f, 4.f, 2.f, 1.f));
      CHECK(vec("ywyy"_swz) == fvec4(2.f, 4.f, 2.f, 2.f));
      CHECK(vec("ywyz"_swz) == fvec4(2.f, 4.f, 2.f, 3.f));
      CHECK(vec("ywyw"_swz) == fvec4(2.f, 4.f, 2.f, 4.f));
      CHECK(vec("ywzx"_swz) == fvec4(2.f, 4.f, 3.f, 1.f));
      CHECK(vec("ywzy"_swz) == fvec4(2.f, 4.f, 3.f, 2.f));
      CHECK(vec("ywzz"_swz) == fvec4(2.f, 4.f, 3.f, 3.f));
      CHECK(vec("ywzw"_swz) == fvec4(2.f, 4.f, 3.f, 4.f));
      CHECK(vec("ywwx"_swz) == fvec4(2.f, 4.f, 4.f, 1.f));
      CHECK(vec("ywwy"_swz) == fvec4(2.f, 4.f, 4.f, 2.f));
      CHECK(vec("ywwz"_swz) == fvec4(2.f, 4.f, 4.f, 3.f));
      CHECK(vec("ywww"_swz) == fvec4(2.f, 4.f, 4.f, 4.f));
      CHECK(vec("zxxx"_swz) == fvec4(3.f, 1.f, 1.f, 1.f));
      CHECK(vec("zxxy"_swz) == fvec4(3.f, 1.f, 1.f, 2.f));
      CHECK(vec("zxxz"_swz) == fvec4(3.f, 1.f, 1.f, 3.f));
      CHECK(vec("zxxw"_swz) == fvec4(3.f, 1.f, 1.f, 4.f));
      CHECK(vec("zxyx"_swz) == fvec4(3.f, 1.f, 2.f, 1.f));
      CHECK(vec("zxyy"_swz) == fvec4(3.f, 1.f, 2.f, 2.f));
      CHECK(vec("zxyz"_swz) == fvec4(3.f, 1.f, 2.f, 3.f));
      CHECK(vec("zxyw"_swz) == fvec4(3.f, 1.f, 2.f, 4.f));
      CHECK(vec("zxzx"_swz) == fvec4(3.f, 1.f, 3.f, 1.f));
      CHECK(vec("zxzy"_swz) == fvec4(3.f, 1.f, 3.f, 2.f));
      CHECK(vec("zxzz"_swz) == fvec4(3.f, 1.f, 3.f, 3.f));
      CHECK(vec("zxzw"_swz) == fvec4(3.f, 1.f, 3.f, 4.f));
      CHECK(vec("zxwx"_swz) == fvec4(3.f, 1.f, 4.f, 1.f));
      CHECK(vec("zxwy"_swz) == fvec4(3.f, 1.f, 4.f, 2.f));
      CHECK(vec("zxwz"_swz) == fvec4(3.f, 1.f, 4.f, 3.f));
      CHECK(vec("zxww"_swz) == fvec4(3.f, 1.f, 4.f, 4.f));
      CHECK(vec("zyxx"_swz) == fvec4(3.f, 2.f, 1.f, 1.f));
      CHECK(vec("zyxy"_swz) == fvec4(3.f, 2.f, 1.f, 2.f));
      CHECK(vec("zyxz"_swz) == fvec4(3.f, 2.f, 1.f, 3.f));
      CHECK(vec("zyxw"_swz) == fvec4(3.f, 2.f, 1.f, 4.f));
      CHECK(vec("zyyx"_swz) == fvec4(3.f, 2.f, 2.f, 1.f));
      CHECK(vec("zyyy"_swz) == fvec4(3.f, 2.f, 2.f, 2.f));
      CHECK(vec("zyyz"_swz) == fvec4(3.f, 2.f, 2.f, 3.f));
      CHECK(vec("zyyw"_swz) == fvec4(3.f, 2.f, 2.f, 4.f));
      CHECK(vec("zyzx"_swz) == fvec4(3.f, 2.f, 3.f, 1.f));
      CHECK(vec("zyzy"_swz) == fvec4(3.f, 2.f, 3.f, 2.f));
      CHECK(vec("zyzz"_swz) == fvec4(3.f, 2.f, 3.f, 3.f));
      CHECK(vec("zyzw"_swz) == fvec4(3.f, 2.f, 3.f, 4.f));
      CHECK(vec("zywx"_swz) == fvec4(3.f, 2.f, 4.f, 1.f));
      CHECK(vec("zywy"_swz) == fvec4(3.f, 2.f, 4.f, 2.f));
      CHECK(vec("zywz"_swz) == fvec4(3.f, 2.f, 4.f, 3.f));
      CHECK(vec("zyww"_swz) == fvec4(3.f, 2.f, 4.f, 4.f));
      CHECK(vec("zzxx"_swz) == fvec4(3.f, 3.f, 1.f, 1.f));
      CHECK(vec("zzxy"_swz) == fvec4(3.f, 3.f, 1.f, 2.f));
      CHECK(vec("zzxz"_swz) == fvec4(3.f, 3.f, 1.f, 3.f));
      CHECK(vec("zzxw"_swz) == fvec4(3.f, 3.f, 1.f, 4.f));
      CHECK(vec("zzyx"_swz) == fvec4(3.f, 3.f, 2.f, 1.f));
      CHECK(vec("zzyy"_swz) == fvec4(3.f, 3.f, 2.f, 2.f));
      CHECK(vec("zzyz"_swz) == fvec4(3.f, 3.f, 2.f, 3.f));
      CHECK(vec("zzyw"_swz) == fvec4(3.f, 3.f, 2.f, 4.f));
      CHECK(vec("zzzx"_swz) == fvec4(3.f, 3.f, 3.f, 1.f));
      CHECK(vec("zzzy"_swz) == fvec4(3.f, 3.f, 3.f, 2.f));
      CHECK(vec("zzzz"_swz) == fvec4(3.f, 3.f, 3.f, 3.f));
      CHECK(vec("zzzw"_swz) == fvec4(3.f, 3.f, 3.f, 4.f));
      CHECK(vec("zzwx"_swz) == fvec4(3.f, 3.f, 4.f, 1.f));
      CHECK(vec("zzwy"_swz) == fvec4(3.f, 3.f, 4.f, 2.f));
      CHECK(vec("zzwz"_swz) == fvec4(3.f, 3.f, 4.f, 3.f));
      CHECK(vec("zzww"_swz) == fvec4(3.f, 3.f, 4.f, 4.f));
      CHECK(vec("zwxx"_swz) == fvec4(3.f, 4.f, 1.f, 1.f));
      CHECK(vec("zwxy"_swz) == fvec4(3.f, 4.f, 1.f, 2.f));
      CHECK(vec("zwxz"_swz) == fvec4(3.f, 4.f, 1.f, 3.f));
      CHECK(vec("zwxw"_swz) == fvec4(3.f, 4.f, 1.f, 4.f));
      CHECK(vec("zwyx"_swz) == fvec4(3.f, 4.f, 2.f, 1.f));
      CHECK(vec("zwyy"_swz) == fvec4(3.f, 4.f, 2.f, 2.f));
      CHECK(vec("zwyz"_swz) == fvec4(3.f, 4.f, 2.f, 3.f));
      CHECK(vec("zwyw"_swz) == fvec4(3.f, 4.f, 2.f, 4.f));
      CHECK(vec("zwzx"_swz) == fvec4(3.f, 4.f, 3.f, 1.f));
      CHECK(vec("zwzy"_swz) == fvec4(3.f, 4.f, 3.f, 2.f));
      CHECK(vec("zwzz"_swz) == fvec4(3.f, 4.f, 3.f, 3.f));
      CHECK(vec("zwzw"_swz) == fvec4(3.f, 4.f, 3.f, 4.f));
      CHECK(vec("zwwx"_swz) == fvec4(3.f, 4.f, 4.f, 1.f));
      CHECK(vec("zwwy"_swz) == fvec4(3.f, 4.f, 4.f, 2.f));
      CHECK(vec("zwwz"_swz) == fvec4(3.f, 4.f, 4.f, 3.f));
      CHECK(vec("zwww"_swz) == fvec4(3.f, 4.f, 4.f, 4.f));
      CHECK(vec("wxxx"_swz) == fvec4(4.f, 1.f, 1.f, 1.f));
      CHECK(vec("wxxy"_swz) == fvec4(4.f, 1.f, 1.f, 2.f));
      CHECK(vec("wxxz"_swz) == fvec4(4.f, 1.f, 1.f, 3.f));
      CHECK(vec("wxxw"_swz) == fvec4(4.f, 1.f, 1.f, 4.f));
      CHECK(vec("wxyx"_swz) == fvec4(4.f, 1.f, 2.f, 1.f));
      CHECK(vec("wxyy"_swz) == fvec4(4.f, 1.f, 2.f, 2.f));
      CHECK(vec("wxyz"_swz) == fvec4(4.f, 1.f, 2.f, 3.f));
      CHECK(vec("wxyw"_swz) == fvec4(4.f, 1.f, 2.f, 4.f));
      CHECK(vec("wxzx"_swz) == fvec4(4.f, 1.f, 3.f, 1.f));
      CHECK(vec("wxzy"_swz) == fvec4(4.f, 1.f, 3.f, 2.f));
      CHECK(vec("wxzz"_swz) == fvec4(4.f, 1.f, 3.f, 3.f));
      CHECK(vec("wxzw"_swz) == fvec4(4.f, 1.f, 3.f, 4.f));
      CHECK(vec("wxwx"_swz) == fvec4(4.f, 1.f, 4.f, 1.f));
      CHECK(vec("wxwy"_swz) == fvec4(4.f, 1.f, 4.f, 2.f));
      CHECK(vec("wxwz"_swz) == fvec4(4.f, 1.f, 4.f, 3.f));
      CHECK(vec("wxww"_swz) == fvec4(4.f, 1.f, 4.f, 4.f));
      CHECK(vec("wyxx"_swz) == fvec4(4.f, 2.f, 1.f, 1.f));
      CHECK(vec("wyxy"_swz) == fvec4(4.f, 2.f, 1.f, 2.f));
      CHECK(vec("wyxz"_swz) == fvec4(4.f, 2.f, 1.f, 3.f));
      CHECK(vec("wyxw"_swz) == fvec4(4.f, 2.f, 1.f, 4.f));
      CHECK(vec("wyyx"_swz) == fvec4(4.f, 2.f, 2.f, 1.f));
      CHECK(vec("wyyy"_swz) == fvec4(4.f, 2.f, 2.f, 2.f));
      CHECK(vec("wyyz"_swz) == fvec4(4.f, 2.f, 2.f, 3.f));
      CHECK(vec("wyyw"_swz) == fvec4(4.f, 2.f, 2.f, 4.f));
      CHECK(vec("wyzx"_swz) == fvec4(4.f, 2.f, 3.f, 1.f));
      CHECK(vec("wyzy"_swz) == fvec4(4.f, 2.f, 3.f, 2.f));
      CHECK(vec("wyzz"_swz) == fvec4(4.f, 2.f, 3.f, 3.f));
      CHECK(vec("wyzw"_swz) == fvec4(4.f, 2.f, 3.f, 4.f));
      CHECK(vec("wywx"_swz) == fvec4(4.f, 2.f, 4.f, 1.f));
      CHECK(vec("wywy"_swz) == fvec4(4.f, 2.f, 4.f, 2.f));
      CHECK(vec("wywz"_swz) == fvec4(4.f, 2.f, 4.f, 3.f));
      CHECK(vec("wyww"_swz) == fvec4(4.f, 2.f, 4.f, 4.f));
      CHECK(vec("wzxx"_swz) == fvec4(4.f, 3.f, 1.f, 1.f));
      CHECK(vec("wzxy"_swz) == fvec4(4.f, 3.f, 1.f, 2.f));
      CHECK(vec("wzxz"_swz) == fvec4(4.f, 3.f, 1.f, 3.f));
      CHECK(vec("wzxw"_swz) == fvec4(4.f, 3.f, 1.f, 4.f));
      CHECK(vec("wzyx"_swz) == fvec4(4.f, 3.f, 2.f, 1.f));
      CHECK(vec("wzyy"_swz) == fvec4(4.f, 3.f, 2.f, 2.f));
      CHECK(vec("wzyz"_swz) == fvec4(4.f, 3.f, 2.f, 3.f));
      CHECK(vec("wzyw"_swz) == fvec4(4.f, 3.f, 2.f, 4.f));
      CHECK(vec("wzzx"_swz) == fvec4(4.f, 3.f, 3.f, 1.f));
      CHECK(vec("wzzy"_swz) == fvec4(4.f, 3.f, 3.f, 2.f));
      CHECK(vec("wzzz"_swz) == fvec4(4.f, 3.f, 3.f, 3.f));
      CHECK(vec("wzzw"_swz) == fvec4(4.f, 3.f, 3.f, 4.f));
      CHECK(vec("wzwx"_swz) == fvec4(4.f, 3.f, 4.f, 1.f));
      CHECK(vec("wzwy"_swz) == fvec4(4.f, 3.f, 4.f, 2.f));
      CHECK(vec("wzwz"_swz) == fvec4(4.f, 3.f, 4.f, 3.f));
      CHECK(vec("wzww"_swz) == fvec4(4.f, 3.f, 4.f, 4.f));
      CHECK(vec("wwxx"_swz) == fvec4(4.f, 4.f, 1.f, 1.f));
      CHECK(vec("wwxy"_swz) == fvec4(4.f, 4.f, 1.f, 2.f));
      CHECK(vec("wwxz"_swz) == fvec4(4.f, 4.f, 1.f, 3.f));
      CHECK(vec("wwxw"_swz) == fvec4(4.f, 4.f, 1.f, 4.f));
      CHECK(vec("wwyx"_swz) == fvec4(4.f, 4.f, 2.f, 1.f));
      CHECK(vec("wwyy"_swz) == fvec4(4.f, 4.f, 2.f, 2.f));
      CHECK(vec("wwyz"_swz) == fvec4(4.f, 4.f, 2.f, 3.f));
      CHECK(vec("wwyw"_swz) == fvec4(4.f, 4.f, 2.f, 4.f));
      CHECK(vec("wwzx"_swz) == fvec4(4.f, 4.f, 3.f, 1.f));
      CHECK(vec("wwzy"_swz) == fvec4(4.f, 4.f, 3.f, 2.f));
      CHECK(vec("wwzz"_swz) == fvec4(4.f, 4.f, 3.f, 3.f));
      CHECK(vec("wwzw"_swz) == fvec4(4.f, 4.f, 3.f, 4.f));
      CHECK(vec("wwwx"_swz) == fvec4(4.f, 4.f, 4.f, 1.f));
      CHECK(vec("wwwy"_swz) == fvec4(4.f, 4.f, 4.f, 2.f));
      CHECK(vec("wwwz"_swz) == fvec4(4.f, 4.f, 4.f, 3.f));
      CHECK(vec("wwww"_swz) == fvec4(4.f, 4.f, 4.f, 4.f));
    }
  }
}
