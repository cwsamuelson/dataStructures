#include <sdf/2D.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`SDF`: 2D") {
  // float sdCircle(vec2 p, float r) noexcept 
  SECTION("`sdCircle(vec2 p, float r)`") {
    CHECK(sdCircle({ 2.f, 0.f }, 1.0f) > 0.f);
    CHECK(sdCircle({ 2.f, 2.f }, 1.0f) > 0.f);
    CHECK(sdCircle({ 0.f, 2.f }, 1.0f) > 0.f);
    CHECK(sdCircle({ 1.f, 1.f }, 1.0f) > 0.f);

    CHECK(sdCircle({ .7f, .7f }, 1.0f) < 0.f);
    CHECK(sdCircle({ .9f, 0.f }, 1.0f) < 0.f);
    CHECK(sdCircle({ 0.f, .9f }, 1.0f) < 0.f);
    CHECK(sdCircle({ 0.f, 0.f }, 1.0f) < 0.f);
  }

  // float sdRoundedBox(vec2 p, vec2 b, vec4 r) noexcept 
  SECTION("`sdRoundedBox(vec2 p, vec2 b, vec4 r)`") {
  }

  // float sdChamferBox(vec2 p, vec2 b, float chamfer) noexcept 
  SECTION("`sdChamferBox(vec2 p, vec2 b, float chamfer)`") {
  }

  // float sdBox(vec2 p, vec2 b) noexcept 
  SECTION("`sdBox(vec2 p, vec2 b)`") {
  }

  // float sdOrientedBox(vec2 p, vec2 a, vec2 b, float th) noexcept 
  SECTION("`sdOrientedBox(vec2 p, vec2 a, vec2 b, float th)`") {
  }

  // float sdSegment(vec2 p, vec2 a, vec2 b) noexcept 
  SECTION("`sdSegment(vec2 p, vec2 a, vec2 b)`") {
  }

  // float ndot(vec2 a, vec2 b ) noexcept 
  SECTION("`ndot(vec2 a, vec2 b )`") {
  }

  // float sdRhombus(vec2 p, vec2 b ) noexcept 
  SECTION("`sdRhombus(vec2 p, vec2 b )`") {
  }

  // float sdTrapezoid(vec2 p, float r1, float r2, float he ) noexcept 
  SECTION("`sdTrapezoid(vec2 p, float r1, float r2, float he )`") {
  }

  // float sdParallelogram(vec2 p, float wi, float he, float sk ) noexcept 
  SECTION("`sdParallelogram(vec2 p, float wi, float he, float sk )`") {
  }

  // float sdEquilateralTriangle(vec2 p, float r ) noexcept 
  SECTION("`sdEquilateralTriangle(vec2 p, float r )`") {
  }

  // float sdTriangleIsosceles(vec2 p, vec2 q ) noexcept 
  SECTION("`sdTriangleIsosceles(vec2 p, vec2 q )`") {
  }

  // float sdTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2 ) noexcept 
  SECTION("`sdTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2 )`") {
  }

  // float sdUnevenCapsule(vec2 p, float r1, float r2, float h ) noexcept 
  SECTION("`sdUnevenCapsule(vec2 p, float r1, float r2, float h )`") {
  }

  // float sdPentagon(vec2 p, float r ) noexcept 
  SECTION("`sdPentagon(vec2 p, float r )`") {
  }

  // float sdHexagon(vec2 p, float r ) noexcept 
  SECTION("`sdHexagon(vec2 p, float r )`") {
  }

  // float sdOctogon(vec2 p, float r ) noexcept 
  SECTION("`sdOctogon(vec2 p, float r )`") {
  }

  // float sdHexagram(vec2 p, float r ) noexcept 
  SECTION("`sdHexagram(vec2 p, float r )`") {
  }

  // float sdPentagram(vec2 p, float r ) noexcept 
  SECTION("`sdPentagram(vec2 p, float r )`") {
  }

  // float sdStar(vec2 p, float r, int n, float m) noexcept 
  SECTION("`sdStar(vec2 p, float r, int n, float m)`") {
  }

  // float sdPie(vec2 p, vec2 c, float r ) noexcept 
  SECTION("`sdPie(vec2 p, vec2 c, float r )`") {
  }

  // float sdCutDisk(vec2 p, float r, float h ) noexcept 
  SECTION("`sdCutDisk(vec2 p, float r, float h )`") {
  }

  // float sdArc(vec2 p, vec2 sc, float ra, float rb ) noexcept 
  SECTION("`sdArc(vec2 p, vec2 sc, float ra, float rb )`") {
  }

  // float sdRing(vec2 p, vec2 n, float r, float th ) noexcept 
  SECTION("`sdRing(vec2 p, vec2 n, float r, float th )`") {
  }

  // float sdHorseshoe(vec2 p, vec2 c, float r, vec2 w ) noexcept 
  SECTION("`sdHorseshoe(vec2 p, vec2 c, float r, vec2 w )`") {
  }

  // float sdVesica(vec2 p, float w, float h) noexcept 
  SECTION("`sdVesica(vec2 p, float w, float h)`") {
  }

  // float sdOrientedVesica(vec2 p, vec2 a, vec2 b, float w ) noexcept 
  SECTION("`sdOrientedVesica(vec2 p, vec2 a, vec2 b, float w )`") {
  }

  // float sdMoon(vec2 p, float d, float ra, float rb ) noexcept 
  SECTION("`sdMoon(vec2 p, float d, float ra, float rb )`") {
  }

  // float sdRoundedCross(vec2 p, float h ) noexcept 
  SECTION("`sdRoundedCross(vec2 p, float h )`") {
  }

  // float sdEgg(vec2 p, float ra, float rb ) noexcept 
  SECTION("`sdEgg(vec2 p, float ra, float rb )`") {
  }

  // float sdHeart(vec2 p ) noexcept 
  SECTION("`sdHeart(vec2 p )`") {
  }

  // float sdCross(vec2 p, vec2 b, float r ) noexcept  
  SECTION("`sdCross(vec2 p, vec2 b, float r )`") {
  }

  // float sdRoundedX(vec2 p, float w, float r ) noexcept 
  SECTION("`sdRoundedX(vec2 p, float w, float r )`") {
  }

  // float sdPolygon(vec2[N] v, vec2 p ) noexcept 
  SECTION("`sdPolygon(vec2[N] v, vec2 p )`") {
  }

  // float sdEllipse(vec2 p, vec2 ab ) noexcept 
  SECTION("`sdEllipse(vec2 p, vec2 ab )`") {
  }

  // float sdParabola(vec2 pos, float k ) noexcept 
  SECTION("`sdParabola(vec2 pos, float k )`") {
  }

  // float sdParabola(vec2 pos, float wi, float he ) noexcept 
  SECTION("`sdParabola(vec2 pos, float wi, float he )`") {
  }

  // float sdBezier(vec2 pos, vec2 A, vec2 B, vec2 C ) noexcept 
  SECTION("`sdBezier(vec2 pos, vec2 A, vec2 B, vec2 C )`") {
  }

  // float sdBlobbyCross(vec2 pos, float he ) noexcept 
  SECTION("`sdBlobbyCross(vec2 pos, float he )`") {
  }

  // float sdTunnel(vec2 p, vec2 wh ) noexcept 
  SECTION("`sdTunnel(vec2 p, vec2 wh )`") {
  }

  // float sdStairs(vec2 p, vec2 wh, float n ) noexcept 
  SECTION("`sdStairs(vec2 p, vec2 wh, float n )`") {
  }

  // float sdQuadraticCircle(vec2 p ) noexcept 
  SECTION("`sdQuadraticCircle(vec2 p )`") {
  }

  // float sdHyperbola(vec2 p, float k, float he ) noexcept 
  SECTION("`sdHyperbola(vec2 p, float k, float he )`") {
  }

  // float sdfCoolS(vec2 p ) noexcept 
  SECTION("`sdfCoolS(vec2 p )`") {
  }

  // float sdCircleWave(vec2 p, float tb, float ra ) noexcept 
  SECTION("`sdCircleWave(vec2 p, float tb, float ra )`") {
  }

  // float opRound(const vec2 p, const float r) noexcept 
  SECTION("`opRound(const vec2 p, const float r)`") {
  }

  // float opOnion(const vec2 p, const float r) noexcept 
  SECTION("`opOnion(const vec2 p, const float r)`") {
  }
}
