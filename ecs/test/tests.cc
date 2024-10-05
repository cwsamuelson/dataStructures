#include <ecs.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct Position {
  float x;
  float y;
};

struct Velocity {
  float dx;
  float dy;
};

// this struct should maybe be put into a shared location?
TEST_CASE("ECS") {
  Registry   registry;
  const auto pos_only = registry.create();
  registry.emplace<Position>(pos_only, 1.2F, 3.4F);
  const auto vel_only = registry.create();
  registry.emplace<Velocity>(vel_only, 2.3F, 4.5F);

  const auto entity_id0 = registry.create();
  registry.emplace<Position>(pos_only, 3.4F, 5.6F);
  registry.emplace<Velocity>(vel_only, 4.5F, 6.7F);
  const auto entity_id1 = registry.create();
  registry.emplace<Position>(pos_only, 5.6F, 7.8F);
  registry.emplace<Velocity>(vel_only, 6.7F, 8.9F);

  SECTION("Iteration") {
    auto view = registry.view<const Position, Velocity>();

    view.each([](const Position&, Velocity&) {});

    view.each([](const auto, const Position&, Velocity&) {});

    for (auto&& [entity, position, velocity] : view) {
    }
  }
}
