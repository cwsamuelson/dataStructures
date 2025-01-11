#pragma once

#include <dimension_pack.hh>
#include <value_pack.hh>

#include <core/concepts.hh>

#include <concepts>
#include <cstddef>
#include <tuple>

namespace flp {

struct DimensionBase {
  signed long long int order;

  template<typename Self>
  [[nodiscard]]
  constexpr auto operator<=>(this const Self& self, const Self& other) noexcept {
    return self.order <=> other.order;
  }

  template<typename Self>
  [[nodiscard]]
  constexpr auto operator==(this const Self& self, const Self& other) noexcept {
    return self.order == other.order;
  }

  template<typename Self, std::derived_from<DimensionBase> Other>
  [[nodiscard]]
  constexpr auto operator==(this const Self&, const Other&) noexcept {
    return false;
  }

  template<typename Self>
  [[nodiscard]]
  constexpr Self operator+(this const Self& self, const Self& other) noexcept {
    return {self.order + other.order};
  }

  template<typename Self>
  [[nodiscard]]
  constexpr Self operator-(this const Self& self, const Self& other) noexcept {
    return {self.order - other.order};
  }

  template<typename Self>
  [[nodiscard]]
  constexpr Self operator-(this const Self& self) noexcept {
    return {-self.order};
  }
};

template<auto... Dimensions>
  requires(std::derived_from<decltype(Dimensions), DimensionBase> && ...)
      and ((not std::same_as<decltype(Dimensions), DimensionBase>) && ...)
struct Dimension;

namespace {

template<auto... Dimensions>
struct DimensionImpl {
  template<auto ...OtherDimensions>
    requires (sizeof...(Dimensions) == sizeof...(OtherDimensions))
  [[nodiscard]]
  constexpr friend bool operator==(const DimensionImpl& lhs, const DimensionImpl<OtherDimensions...>& rhs) noexcept {
    return ValuePack<Dimensions...>{} == ValuePack<OtherDimensions...>{};
  }

  template<auto ...OtherDimensions>
    requires (sizeof...(Dimensions) != sizeof...(OtherDimensions))
  [[nodiscard]]
  constexpr friend bool operator==(const DimensionImpl& lhs, const DimensionImpl<OtherDimensions...>& rhs) noexcept {
    return false;
  }

  template<auto... OtherDimensions>
  constexpr auto operator*(const DimensionImpl<OtherDimensions...>& other) noexcept {
    constexpr auto f = []<typename Dim>(const Dim& Dimension, const DimensionImpl<OtherDimensions...>&) {
      if constexpr (DimensionPack<OtherDimensions...>::template Has<Dim>) {
        return Dim{Dimension + DimensionPack<OtherDimensions...>::template Select<Dim>};
      } else {
        return Dimension;
      }
    };

    constexpr auto g = []<typename Dim>(const Dim& dimension, const DimensionImpl<Dimensions...>&) {
      if constexpr (DimensionPack<Dimensions...>::template Has<Dim>) {
        return Dim{0};
      } else {
        return dimension;
      }
    };

    return Dimension<g(OtherDimensions, *this)..., f(Dimensions, other)...> {};
  }

  template<auto... OtherDimensions>
  constexpr auto operator/(const DimensionImpl<OtherDimensions...>& other) noexcept {
    constexpr auto f = []<typename Dim>(const Dim& dimension, const DimensionImpl<OtherDimensions...>&) {
      if constexpr (DimensionPack<OtherDimensions...>::template Has<Dim>) {
        return Dim{dimension - DimensionPack<OtherDimensions...>::template Select<Dim>};
      } else {
        return dimension;
      }
    };

    constexpr auto g = []<typename Dim>(const Dim& dimension, const DimensionImpl<Dimensions...>&) {
      if constexpr (DimensionPack<Dimensions...>::template Has<Dim>) {
        return Dim{0};
      } else {
        return -dimension;
      }
    };

    return Dimension<g(OtherDimensions, *this)..., f(Dimensions, other)...> {};
  }
};

template<auto Value>
struct EmptyFilter {
  static constexpr auto value = Value.order != 0;
};

}

// must derive from, but not be `DimensionBase`
template<auto... Dimensions>
  requires(std::derived_from<decltype(Dimensions), DimensionBase> && ...)
      and ((not std::same_as<decltype(Dimensions), DimensionBase>) && ...)
struct Dimension : DimensionPack<Dimensions...>::UniqueTypes::Filter<EmptyFilter>::template Rebind<DimensionImpl>{};

} // namespace flp

