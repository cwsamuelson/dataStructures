#pragma once

#include <concepts>

namespace flp::ColorTheory {

// Color space strategy:
// Most (if not all) color spaces are derived from (or can be connected to) a
// central color space.  To convert to arbitrary color spaces we convert the
// input into that central space, and then convert back down to our destination.
//
// This can be visualized as color spaces forming a tree, with the central space
// at the root.  Therefore converting color spaces is a simple matter of
// traversing the tree.
//
// To achieve this graph traversal when color space types are not related and
// don't share a base type, every color space declares an 'edge' to a 'parent'
// color space which the the color space can convert to, and is closer to the
// root color space.
//
// `convert<To>(value)` walks `value` up toward the root until
// it reaches a common ancestor of `From` and `To`, then walks back down to `To`.
// This means N spaces only need N-1 edges (2*(N-1) functions) instead of defining
// N*(N-1) pairwise conversions that would otherwise be required.

template<typename Space>
struct ConversionEdge {
  using Parent = void;
};

template<typename Space>
concept IsRoot = std::same_as<typename ConversionEdge<Space>::Parent, void>;

template<typename Ancestor, typename Descendant>
constexpr bool is_ancestor_of() noexcept {
  if constexpr (std::same_as<Ancestor, Descendant>) {
    return true;
  } else if constexpr (IsRoot<Descendant>) {
    return false;
  } else {
    return is_ancestor_of<Ancestor, typename ConversionEdge<Descendant>::Parent>();
  }
}

template<typename Ancestor, typename Descendant>
concept IsAncestorOf = is_ancestor_of<Ancestor, Descendant>();

// Already traversed up to the common ancestor, now traversing down to target.
template<typename To, typename Ancestor>
constexpr To descend_to(const Ancestor value) noexcept {
  if constexpr (std::same_as<To, Ancestor>) {
    return value;
  } else {
    using Parent = typename ConversionEdge<To>::Parent;
    return ConversionEdge<To>::from_parent(descend_to<Parent>(value));
  }
}

// arbitrary color space conversion.
template<typename To, typename From>
constexpr To convert(From value) noexcept {
  static_assert(std::same_as<typename From::value_type, typename To::value_type>,
    "ColorTheory::convert: 'From' and 'To' must share the same underlying numeric type");

  if constexpr (std::same_as<To, From>) {
    return value;
  } else if constexpr (IsAncestorOf<From, To>) {
    return descend_to<To>(value);
  } else {
    using Parent = typename ConversionEdge<From>::Parent;
    static_assert(not std::same_as<Parent, void>,
      "ColorTheory::convert: no conversion path connects the requested color spaces "
      "(they belong to disconnected trees)");
    return convert<To>(ConversionEdge<From>::to_parent(value));
  }
}

} // namespace flp::ColorTheory
