#pragma once

#include <sparse_map.hh>
#include <sparse_set.hh>

#include <any>
#include <concepts>
#include <map>
#include <tuple>
#include <vector>

namespace flp {

namespace {
// trying to avoid RTTI

size_t pseudo_hash_counter {};

template<typename T>
struct PseudoTypeHash {
  static inline size_t hash = pseudo_hash_counter++;
};

} // namespace

template<typename... Components>
struct View;

struct Registry {
  using EntityID = size_t;

  EntityID              create();
  std::vector<EntityID> create(size_t count);
  // destroys all components, and makes id invalid
  void destroy(EntityID entity_id);

  template<typename Iterator>
  void destroy(Iterator begin, Iterator end) {
    for (Iterator it = begin; it != end; ++it) {
      destroy(*it);
    }
  }

  template<typename Range>
  void destroy(Range&& range) {
    for (const auto entity_id : std::forward<Range>(range)) {
      destroy(entity_id);
    }
  }

  template<typename Component, typename... Args>
  void emplace(const EntityID entity_id, Args&&... args) {
    component_maps[PseudoTypeHash<Component>::hash].insert(entity_id, Component { std::forward<Args>(args)... });
  }

  template<typename Component>
  void remove(const EntityID entity_id) {
    component_maps[PseudoTypeHash<Component>::hash].erase(entity_id);
  }

  template<typename Component>
  Component& get(const EntityID entity_id) {
    return std::any_cast<Component&>(component_maps.at(PseudoTypeHash<Component>::hash).at(entity_id));
  }

  template<typename Component>
  const Component& get(const EntityID entity_id) const {
    return std::any_cast<Component&>(component_maps.at(PseudoTypeHash<Component>::hash).at(entity_id));
  }

  template<typename... Components>
    requires(sizeof...(Components) > 1)
  std::tuple<Components&...> get(const EntityID entity_id) {
    return std::make_tuple(get<std::forward<Components>>(entity_id)...);
  }

  template<typename... Components>
    requires(sizeof...(Components) > 1)
  std::tuple<const Components&...> get(const EntityID entity_id) const {
    return std::make_tuple(get<std::forward<Components>>(entity_id)...);
  }

  template<typename... Components>
  View<Components...> view() {
    return {};
  }

  //  check if current entity is valid
  [[nodiscard]]
  bool valid(EntityID entity_id);

  // entities can have versions; get the current one
  [[nodiscard]]
  EntityID current(EntityID entity_id);

  template<typename Component>
  [[nodiscard]]
  bool has(const EntityID entity_id) const {
    const auto hash = PseudoTypeHash<Component>::hash;
    return component_maps.contains(hash) and component_maps.at(hash).contains(entity_id);
  }

  template<typename... Components>
  [[nodiscard]]
  bool all_of(const EntityID entity_id) const {}

  template<typename... Components>
  [[nodiscard]]
  bool any_of(const EntityID entity_id) const {}

  template<typename Component>
  void clear() {
    component_maps[PseudoTypeHash<Component>::hash].clear();
  }
  void clear();
  // remove all components for id
  void clear(EntityID entity_id);

  template<typename Component, typename Functor>
    requires std::invocable<Functor, EntityID, Component&>
  void on_construct(Functor&& functor) {}
  template<typename Component, typename Functor>
    requires std::invocable<Functor, EntityID, Component&>
  void on_update(Functor&& functor) {}
  template<typename Component, typename Functor>
    requires std::invocable<Functor, EntityID>
  void on_destroy(Functor&& functor) {}

  SparseSet<EntityID>                             valid_entities;
  std::map<size_t, SparseMap<EntityID, std::any>> component_maps;
};

template<typename... Components>
struct View {
  template<typename Functor>
    requires std::invocable<Functor, Registry::EntityID, Components&...>
  void each(Functor&& functor) {}

  template<typename Functor>
    requires std::invocable<Functor, Components&...>
  void each(Functor&& functor) {}

  struct Iterator {
    Iterator operator++() {
      return {};
    }
    Iterator operator--() {
      return {};
    }

    std::tuple<Registry::EntityID, Components /*&*/...> operator*() {
      return {};
    }

    friend auto operator<=>(const Iterator& lhs, const Iterator& rhs) noexcept = default;
    friend bool operator==(const Iterator&, const Iterator&) noexcept          = default;
  };

  Iterator begin() {
    return {};
  }
  Iterator end() {
    return {};
  }
};

} // namespace flp
