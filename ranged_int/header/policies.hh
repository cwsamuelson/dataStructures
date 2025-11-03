#pragma once

namespace flp {

template<typename Type>
concept BoundsPolicy = requires(Type policy) {
  true;
};

struct AssumeInRangePolicy {
};
static_assert(BoundsPolicy<AssumeInRangePolicy>);

struct WrapPolicy {
};
static_assert(BoundsPolicy<WrapPolicy>);

struct ClampPolicy {
};
static_assert(BoundsPolicy<ClampPolicy>);

struct ErrorPolicy {
};
static_assert(BoundsPolicy<ErrorPolicy>);

using AssumePolicy = AssumeInRangePolicy;

}
