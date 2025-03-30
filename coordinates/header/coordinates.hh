#pragma once

#include <core/tagged_type.hh>

#include <cstddef>

namespace flp {

struct DiscreteTag;
struct ContinuousTag;
struct WidthTag;
struct HeightTag;
struct XCoordinateTag;
struct YCoordinateTag;

template<typename Type>
using WidthImpl  = TaggedType<Type, WidthTag>;
template<typename Type>
using HeightImpl = TaggedType<Type, HeightTag>;
template<typename Type>
using XCoordinateImpl = TaggedType<Type, XCoordinateTag>;
template<typename Type>
using YCoordinateImpl = TaggedType<Type, YCoordinateTag>;

template<typename>
struct Width;
template<typename>
struct Height;
template<typename>
struct XCoordinate;
template<typename>
struct YCoordinate;

template<>
struct Width<DiscreteTag> : WidthImpl<size_t> {};

template<>
struct Height<DiscreteTag> : HeightImpl<size_t> {};

template<>
struct XCoordinate<DiscreteTag> : XCoordinateImpl<size_t> {};

template<>
struct YCoordinate<DiscreteTag> : YCoordinateImpl<size_t> {};

template<>
struct Width<ContinuousTag> : WidthImpl<float> {};

template<>
struct Height<ContinuousTag> : HeightImpl<float> {};

template<>
struct XCoordinate<ContinuousTag> : XCoordinateImpl<float> {};

template<>
struct YCoordinate<ContinuousTag> : YCoordinateImpl<float> {};

template<typename>
struct Dimensions;

template<typename Continuity>
struct Dimensions {
  using Width = Width<Continuity>;
  using Height = Height<Continuity>;

  constexpr Dimensions() noexcept = default;
  constexpr Dimensions(Width w, Height h) noexcept
    : width(w)
    , height(h)
  {}

  constexpr Dimensions(const Dimensions&) noexcept = default;
  constexpr Dimensions(Dimensions&&) noexcept      = default;

  constexpr Dimensions& operator=(const Dimensions&) noexcept = default;
  constexpr Dimensions& operator=(Dimensions&&) noexcept      = default;

  constexpr ~Dimensions() noexcept = default;

  constexpr friend auto operator<=>(const Dimensions&, const Dimensions&) noexcept = default;

  Width  width;
  Height height;
};

template<typename>
struct Coordinates;

template<typename Continuity>
struct Coordinates {
  using XCoord = XCoordinate<Continuity>;
  using YCoord = YCoordinate<Continuity>;

  constexpr Coordinates() noexcept = default;
  constexpr Coordinates(XCoord x, YCoord y) noexcept
    : x_coord(x)
    , y_coord(y)
  {}

  constexpr Coordinates(const Coordinates&) noexcept = default;
  constexpr Coordinates(Coordinates&&) noexcept      = default;

  constexpr Coordinates& operator=(const Coordinates&) noexcept = default;
  constexpr Coordinates& operator=(Coordinates&&) noexcept      = default;

  constexpr ~Coordinates() noexcept = default;

  constexpr friend auto operator<=>(const Coordinates&, const Coordinates&) noexcept = default;

  XCoord x_coord{};
  YCoord y_coord{};
};

using DiscreteWidth = Width<DiscreteTag>;
using DiscreteHeight = Height<DiscreteTag>;

using ContinuousWidth = Width<ContinuousTag>;
using ContinuousHeight = Height<ContinuousTag>;

using DiscreteXCoordinate = XCoordinate<DiscreteTag>;
using DiscreteYCoordinate = YCoordinate<DiscreteTag>;

using ContinuousXCoordinate = XCoordinate<ContinuousTag>;
using ContinuousYCoordinate = YCoordinate<ContinuousTag>;

using DiscreteDimensions = Dimensions<DiscreteTag>;
using ContinuousDimensions = Dimensions<ContinuousTag>;

using DiscreteCoordinates = Coordinates<DiscreteTag>;
using ContinuousCoordinates = Coordinates<ContinuousTag>;

static_assert(not std::same_as<DiscreteDimensions, ContinuousDimensions>);
static_assert(not std::same_as<DiscreteCoordinates, ContinuousCoordinates>);
static_assert(not std::same_as<DiscreteDimensions, DiscreteCoordinates>);
static_assert(not std::same_as<ContinuousDimensions, ContinuousCoordinates>);

static_assert(not std::is_same_v<DiscreteWidth, ContinuousWidth>);
static_assert(not std::is_same_v<DiscreteHeight, ContinuousHeight>);
static_assert(not std::is_same_v<DiscreteXCoordinate, ContinuousXCoordinate>);
static_assert(not std::is_same_v<DiscreteYCoordinate, ContinuousYCoordinate>);

static_assert(not std::is_same_v<DiscreteWidth, DiscreteHeight>);
static_assert(not std::is_same_v<DiscreteXCoordinate, DiscreteYCoordinate>);
static_assert(not std::is_same_v<ContinuousWidth, ContinuousHeight>);
static_assert(not std::is_same_v<ContinuousXCoordinate, ContinuousYCoordinate>);

} // namespace flp

