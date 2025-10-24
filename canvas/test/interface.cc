#include <canvas/canvas.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

SCENARIO("Test canvas interface") {
  flp::Canvas canvas(10, 10);

  constexpr flp::ColorRGBA32 black{0, 0, 0, 0};
  constexpr flp::ColorRGBA32 white{1, 1, 1, 0};

  canvas.clear(black);

  CHECK(canvas.canvas.at(0).at(0) == black);
  CHECK(canvas.canvas.at(5).at(5) == black);
  CHECK(canvas.canvas.at(6).at(9) == black);
  CHECK(canvas.canvas.at(9).at(6) == black);

  canvas.draw({0, 0}, white);
  canvas.draw({5, 5}, white);
  canvas.draw({6, 9}, white);
  canvas.draw({9, 6}, white);

  CHECK(canvas.canvas.at(0).at(0) == white);
  CHECK(canvas.canvas.at(5).at(5) == white);
  CHECK(canvas.canvas.at(6).at(9) == white);
  CHECK(canvas.canvas.at(9).at(6) == white);

  CHECK(canvas.canvas.at(9).at(9) == black);
}
