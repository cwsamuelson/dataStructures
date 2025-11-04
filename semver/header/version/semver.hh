#pragma once

#include <cstddef>
#include <string>

namespace flp::Version {

struct Semantic {
  struct PreRelease {};
  struct Build {};

  constexpr
  Semantic(const size_t major)
    : Semantic(major, 0, 0)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor)
    : Semantic(major, minor, 0)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const size_t patch)
  {}

  constexpr
  Semantic(const std::string_view rev_string) {}

  // constexpr
  // Semantic(const Semantic&) noexcept = default;
  // constexpr
  // Semantic(Semantic&&) noexcept = default;

  // constexpr
  // Semantic& operator=(const Semantic&) noexcept = default;
  // constexpr
  // Semantic& operator=(Semantic&&) noexcept = default;

  [[nodiscard]]
  constexpr
  size_t major() const noexcept {
    return {};
  }

  [[nodiscard]]
  constexpr
  void major(const size_t value) noexcept {
  }

  [[nodiscard]]
  constexpr
  size_t minor() const noexcept {
    return {};
  }

  [[nodiscard]]
  constexpr
  void minor(const size_t value) noexcept {
  }

  [[nodiscard]]
  constexpr
  size_t patch() const noexcept {
    return {};
  }

  [[nodiscard]]
  constexpr
  void patch(const size_t value) noexcept {
  }

  [[nodiscard]]
  constexpr
  PreRelease pre_release() const noexcept {
    return {};
  }

  [[nodiscard]]
  constexpr
  void pre_release(const PreRelease& value) noexcept {
  }

  [[nodiscard]]
  constexpr
  Build build() const noexcept {
    return {};
  }

  [[nodiscard]]
  constexpr
  void build(const Build& value) noexcept {
  }

  [[nodiscard]]
  constexpr
  friend
  auto operator<=>(const Semantic&, const Semantic&) noexcept = default;
};

} // namespace flp
