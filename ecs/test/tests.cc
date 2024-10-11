#include <ecs.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct Position {
  float x;
  float y;

  friend auto operator<=>(const Position&, const Position&) noexcept = default;
};

struct Velocity {
  float dx;
  float dy;

  friend auto operator<=>(const Velocity&, const Velocity&) noexcept = default;
};

// this struct should maybe be put into a shared location?
TEST_CASE("ECS") {
  Registry registry;

  CHECK(not registry.valid(0));
  CHECK(not registry.valid(1));
  CHECK(not registry.valid(15));
  CHECK(not registry.valid(1500));

  const auto pos_only = registry.create();
  registry.emplace<Position>(pos_only, 1.2F, 3.4F);

  CHECK(registry.has<Position>(pos_only));
  CHECK(not registry.has<Velocity>(pos_only));

  CHECK(registry.get<Position>(pos_only).x == 1.2F);
  CHECK(registry.get<Position>(pos_only).y == 3.4F);

  registry.get<Position>(pos_only).x = 2.1F;
  registry.get<Position>(pos_only).y = 4.3F;

  CHECK(registry.get<Position>(pos_only).x == 2.1F);
  CHECK(registry.get<Position>(pos_only).y == 4.3F);

  const auto vel_only = registry.create();
  registry.emplace<Velocity>(vel_only, 2.3F, 4.5F);

  CHECK(not registry.has<Position>(vel_only));
  CHECK(registry.has<Velocity>(vel_only));

  CHECK(registry.get<Velocity>(pos_only).dx == 2.3F);
  CHECK(registry.get<Velocity>(pos_only).dy == 4.5F);

  const auto entity_id0 = registry.create();
  registry.emplace<Position>(entity_id0, 3.4F, 5.6F);
  registry.emplace<Velocity>(entity_id0, 4.5F, 6.7F);

  CHECK(registry.has<Position>(entity_id0));
  CHECK(registry.has<Velocity>(entity_id0));

  {
    auto [position, velocity] = registry.get<Position, Velocity>(entity_id0);
    CHECK(position == Position { 3.4F, 5.6F });
    CHECK(velocity == Velocity { 4.5F, 6.7F });
  }

  const auto entity_id1 = registry.create();
  registry.emplace<Position>(entity_id1, 5.6F, 7.8F);
  registry.emplace<Velocity>(entity_id1, 6.7F, 8.9F);

  CHECK(registry.has<Position>(entity_id1));
  CHECK(registry.has<Velocity>(entity_id1));

  {
    auto [position, velocity] = registry.get<Position, Velocity>(entity_id0);
    CHECK(position == Position { 5.6F, 7.8F });
    CHECK(velocity == Velocity { 6.7F, 8.9F });
  }

  SECTION("Iteration") {
    auto view = registry.view<const Position, Velocity>();

    view.each([](const Position&, Velocity&) {});

    view.each([](const auto, const Position&, Velocity&) {});

    for (auto&& [entity, position, velocity] : view) {
      (void)entity;
      (void)position;
      (void)velocity;
    }
  }
}
