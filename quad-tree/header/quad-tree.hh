#pragma once

#include <core/overloads.hh>

#include <cstddef>
#include <memory>
#include <variant>
#include <vector>

namespace flp {

template<typename Type>
struct QuadTree {
  struct Point {
    float x;
    float y;
  };

  struct AABB {
    Point corner;
    Point dimensions;

    [[nodiscard]]
    bool contains(const Point& point) const noexcept {
      return point.x >= corner.x
         and point.x <= corner.x + dimensions.x
         and point.y >= corner.y
         and point.y <= corner.y + dimensions.y;
    }

    // https://mkirchner.github.io/libfbi/doc/html/index.html
    // https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
    // https://www.realtimerendering.com/intersections.html
    // https://www.geometrictools.com/Samples/Intersection.html
    // https://tavianator.com/2011/ray_box.html
    // https://github.com/gszauer/GamePhysicsCookbook
    // https://github.com/teikitu-rti/teikitu_release
    [[nodiscard]]
    bool intersects(const AABB& other) const noexcept {
      // https://github.com/gszauer/GamePhysicsCookbook/blob/master/Code/Geometry2D.cpp
      return ((other.corner.x <= (corner.x + dimensions.x))
         and  (corner.x <= (other.corner.x + other.dimensions.x)))
         and ((other.corner.x <= (corner.x + dimensions.x))
         and  (corner.x <= (other.corner.x + other.dimensions.x)));
    }
  };

  struct Node;

  using Children = std::unique_ptr<std::array<Node, 4>>;
  using Entities = std::vector<std::tuple<Point, Type>>;
  using Objects = std::vector<Type>;

  struct Node {
    size_t& entity_limit;
    AABB boundaries;
    std::variant<Entities, Children> data;

    void insert(const Point& point, const Type& value) {
      if (not boundaries.contains(point)) {
        return;
      }

      std::visit(Overloads {
        [this, &point, &value](Entities& entities) {
          entities.emplace_back(point, value);
          if (entities.size() > entity_limit) {
            subdivide();
          }
        },
        [&point, &value](const Children& children) {
          for (auto& child : *children) {
            child.insert(point, value);
          }
        }
      }, data);
    }

    template<typename Functor>
      requires ((std::invocable<Functor, std::tuple<Point, Type>>)
        or (std::invocable<Functor, Type, Point>)
        or (std::invocable<Functor, Type>)
      )
    void query(const AABB& box, Functor&& visitor) const {
      if (not boundaries.intersects(box)) {
        return;
      }

      std::visit(Overloads {
        [&visitor](const Entities& entities){
          for (const auto& entity : entities) {
            if constexpr (std::invocable<Functor, std::tuple<Point, Type>>) {
              visitor(entity);
            } else if constexpr (std::invocable<Functor, Type, Point>) {
              visitor(std::get<1>(entity), std::get<0>(entity));
            } else if constexpr (std::invocable<Functor, Type>) {
              visitor(std::get<1>(entity));
            }
          }
        },
        [&box, &visitor](const Children& children){
          for (const auto& child : *children) {
            child.query(box, visitor);
          }
        }
      }, data);
    }

    std::vector<Type> query(const AABB& box) const noexcept {
      if (not boundaries.intersects(box)) {
        return {};
      }

      return std::visit(Overloads {
        [&box](const Entities& entities){
          Objects results;

          for (const auto& [point, object] : entities) {
            if (box.contains(point)) {
              results.push_back(object);
            }
          }

          return results;
        },
        [&box](const Children& children){
          Objects objects;
          for (const auto& child : *children) {
            objects.append_range(child.query(box));
          }
          return objects;
        }
      }, data);
    }

    void subdivide() {
    }
  };

  QuadTree(AABB bounding_box)
    : root{
      entity_limit,
      std::move(bounding_box),
      Entities{}
    }
  {}

  template<typename Functor>
  void query(const AABB& box, Functor&& visitor) const {
    root.query(box, visitor);
  }

  std::vector<Type> query(const AABB& box) const noexcept {
    return root.query(box);
  }

  bool insert(const Point& point, const Type& value) {
    if (not root.boundaries.contains(point)) {
      return false;
    }

    root.insert(point, value);

    ++entity_count;
    return true;
  }

  void clear() {
    root.data = Entities{};
    entity_count = 0;
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return entity_count == 0;
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return entity_count;
  }

  size_t entity_limit{2};
  Node root;
  size_t entity_count{};
};

} // namespace flp
