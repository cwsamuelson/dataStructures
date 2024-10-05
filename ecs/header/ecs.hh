#pragma once
#include <concepts>
#include <tuple>

namespace flp {

template<typename... Components>
struct View;

struct Registry {
  using EntityID = size_t;

  EntityID create();

  template<typename Component, typename... Args>
  void emplace(const EntityID id, Args&&... args) {}

  template<typename... Components>
  View<Components...> view() {
    return {};
  }
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
