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
    float x{};
    float y{};
  };

  struct Line {
    Point start;
    Point end;
  };

  struct AABB {
    Point corner;
    Point dimensions;

    [[nodiscard]]
    bool contains(const Point& point) const noexcept {
      return point.x >= corner.x
         and point.x < corner.x + dimensions.x
         and point.y >= corner.y
         and point.y < corner.y + dimensions.y;
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

    [[nodiscard]]
    bool intersects(const Point& point) const noexcept {
      return contains(point);
    }

    // [[nodiscard]]
    // bool intersects(const Line& point) const noexcept {
    //   return contains(point);
    // }
  };

  struct Node;

  using Children = std::array<Node, 4>;
  using ChildrenPtr = std::unique_ptr<Children>;
  using Entities = std::vector<std::tuple<Point, Type>>;
  using Objects = std::vector<Type>;

  struct Node {
    size_t& entity_limit;
    AABB boundaries;
    std::variant<Entities, ChildrenPtr> data = Entities{};

    bool insert(const Point& point, const Type& value) {
      if (not boundaries.contains(point)) {
        return false;
      }

      std::visit(Overloads {
        [this, &point, &value](Entities& entities) {
          entities.emplace_back(point, value);

          if (entities.size() > entity_limit) {
            subdivide();
          }
        },
        [&point, &value](const ChildrenPtr& children) {
          for (auto& child : *children) {
            child.insert(point, value);
          }
        }
      }, data);

      return true;
    }

    template<typename Primitive, typename Functor>
      requires ((std::invocable<Functor, std::tuple<Point, Type>>)
        or (std::invocable<Functor, Type, Point>)
        or (std::invocable<Functor, Type>)
      )
    void query(const Primitive& shape, Functor&& visitor) const {
      if (not boundaries.intersects(shape)) {
        return;
      }

      std::visit(Overloads {
        [&visitor](const Entities& entities) {
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
        [&shape, &visitor](const ChildrenPtr& children) {
          for (const auto& child : *children) {
            child.query(shape, visitor);
          }
        }
      }, data);
    }

    template<typename Primitive>
    std::vector<Type> query(const Primitive& shape) const noexcept {
      if (not boundaries.intersects(shape)) {
        return {};
      }

      return std::visit(Overloads {
        [&shape](const Entities& entities) {
          Objects results;

          for (const auto& [point, object] : entities) {
            if (shape.contains(point)) {
              results.push_back(object);
            }
          }

          return results;
        },
        [&shape](const ChildrenPtr& children) {
          Objects objects;

          for (const auto& child : *children) {
            objects.append_range(child.query(shape));
          }

          return objects;
        }
      }, data);
    }

    void subdivide() {
      Entities entities = std::move(std::get<Entities>(data));

      const Point sector_dims {
        boundaries.dimensions.x / 2,
        boundaries.dimensions.y / 2,
      };

      auto ptr = std::make_unique<Children>(Children {
        Node {
          entity_limit,
          {
            boundaries.corner,
            sector_dims
          },
        },
        Node {
          entity_limit,
          {
            {
              boundaries.corner.x + sector_dims.x,
              boundaries.corner.y + sector_dims.y
            },
            sector_dims
          },
        },
        Node {
          entity_limit,
          {
            {
              boundaries.corner.x,
              boundaries.corner.y + sector_dims.y
            },
            sector_dims
          },
        },
        Node {
          entity_limit,
          {
            {
              boundaries.corner.x + sector_dims.x,
              boundaries.corner.y
            },
            sector_dims
          },
        },
      });

      auto& children = *ptr;
      data = std::move(ptr);

      for (auto& child : children) {
        for (auto& [point, entity] : entities) {
          child.insert(point, std::move(entity));
        }
      }
    }

    std::vector<Objects> aggregate() const {
      return std::visit(Overloads {
        [](const Entities& entities) {
          Objects objects;

          for (const auto& [point, entity] : entities) {
            objects.push_back(entity);
          }

          return std::vector<Objects>{objects};
        },
        [](const ChildrenPtr& children) {
          std::vector<Objects> objects;

          for (const auto& child : *children) {
            objects.append_range(child.aggregate());
          }

          return objects;
        }
      },
      data);
    }

    template<typename Functor>
    void traverse(Functor&& functor) {
      std::visit(Overloads {
        [this, &functor](const Entities& entities) {
          functor(boundaries, entities);
        },
        [&functor](const ChildrenPtr& children) {
          for (const auto& child : *children) {
            child.traverse(functor);
          }
        },
      },
      data);
    }
  };

  QuadTree(AABB bounding_box)
    : root {
      entity_limit,
      std::move(bounding_box),
      Entities{}
    }
  {}

  template<typename Primitive, typename Functor>
  void query(const Primitive& shape, Functor&& visitor) const {
    root.query(shape, std::forward<Functor>(visitor));
  }

  template<typename Primitive>
  std::vector<Type> query(const Primitive& shape) const noexcept {
    return root.query(shape);
  }

  template<typename Functor>
  void query(const Point& point, Functor&& visitor) const {
    root.query(point, std::forward<Functor>(visitor));
  }

  std::vector<Type> query(const Point& point) const noexcept {
    return root.query(point);
  }

  bool insert(const Point& point, const Type& value) {
    if (not root.boundaries.contains(point)) {
      return false;
    }

    root.insert(point, value);

    ++entity_count;

    return true;
  }

  std::vector<Objects> aggregate() const {
    return root.aggregate();
  }

  template<typename Functor>
  void traverse(Functor&& functor) {
    root.traverse(functor);
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
