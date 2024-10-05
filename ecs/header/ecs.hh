#pragma once

#include <sparse_set.hh>

#include <any>
#include <concepts>
#include <map>
#include <tuple>
#include <vector>

namespace flp {

template<typename... Components>
struct View;

struct Registry {
  using EntityID = size_t;

  EntityID              create();
  std::vector<EntityID> create(size_t count);
  void                  destroy(EntityID entity_id);

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
  void emplace(const EntityID id, Args&&... args) {}

  template<typename Component>
  void remove(const EntityID id) {}

  template<typename Component>
  Component& get(const EntityID id) {
  }

  template<typename Component>
  const Component& get(const EntityID id) const {
  }

  template<typename ...Components>
  std::tuple<Components&...> get(const EntityID id) {
  }

  template<typename ...Components>
  std::tuple<const Components&...> get(const EntityID id) const {
  }

  template<typename... Components>
  View<Components...> view() {
    typeid(int).hash_code();
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
  bool has() const {
    return false;
  }

  template<typename... Components>
  [[nodiscard]]
  bool all_of(const EntityID entity_id) const {}

  template<typename... Components>
  [[nodiscard]]
  bool any_of(const EntityID entity_id) const {}

  template<typename Component>
  void clear() {}
  void clear();
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

  std::map<size_t, SparseSet<EntityID, std::any>> component_map;
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
