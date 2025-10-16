#include <type_set.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct LengthTag {};

struct MassTag {};

template<typename Tag>
struct Dimension {
  static constexpr size_t Order{};
};

template<typename ...>
struct MergeHelper {
  template<typename ...>
  struct Helper {
  };

  template<typename ...A>
  using Merge = Helper<A...>;
};

template<typename ...Dimensions>
struct EqualsHelper {
  template<typename ...ODimensions>
  static constexpr bool value = false;
};

template<typename ...Dimensions>
struct DimensionPack {
  // template<typename ...ODimensions>
  // using Merge = MergeHelper<Dimensions...>::Merge<ODimensions...>;

  // template<typename ...ODimensions>
  // using Equals = EqualsHelper<Dimensions...>::Equals<Dimensions...>;

  template<typename ...A, typename ...B>
  friend
  constexpr
  auto operator+(const DimensionPack<A...>&, const DimensionPack<B...>&) noexcept {
    // merge A..., B...
    return {};
  }
};

TEST_CASE("`Units`::Sandbox") {
}
