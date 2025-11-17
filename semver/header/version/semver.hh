#pragma once

#include <cstddef>
#include <format>
#include <string>
#include <variant>
#include <vector>

namespace flp::Version {

// https://semver.org/
// # REGEX
// ## With Named Groups
// `^(?P<major>0|[1-9]\d*)\.(?P<minor>0|[1-9]\d*)\.(?P<patch>0|[1-9]\d*)(?:-(?P<prerelease>(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\.(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?(?:\+(?P<buildmetadata>[0-9a-zA-Z-]+(?:\.[0-9a-zA-Z-]+)*))?$`
// ## Without Named Groups
// `^(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)(?:-((?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\.(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?(?:\+([0-9a-zA-Z-]+(?:\.[0-9a-zA-Z-]+)*))?$`
// X.Y.Z-pre(.pre)*+build(.build)*
struct Semantic {
  struct PreRelease {
    using Identifier = std::variant<std::string, size_t>;

    std::vector<Identifier> id_sequence;
  };
  struct Build {
    using Identifier = std::variant<std::string, size_t>;

    std::vector<Identifier> id_sequence;
  };

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

  explicit
  operator std::string() const noexcept {
    return std::format("{}.{}.{}", vmajor, vminor, vpatch);
  }

  [[nodiscard]]
  constexpr
  size_t major() const noexcept {
    return vmajor;
  }

  constexpr
  void major(const size_t value) noexcept {
    vmajor = value;
  }

  [[nodiscard]]
  constexpr
  size_t minor() const noexcept {
    return vminor;
  }

  constexpr
  void minor(const size_t value) noexcept {
    vminor = value;
  }

  [[nodiscard]]
  constexpr
  size_t patch() const noexcept {
    return vpatch;
  }

  constexpr
  void patch(const size_t value) noexcept {
    vpatch = value;
  }

  [[nodiscard]]
  constexpr
  PreRelease pre_release() const noexcept {
    return {};
  }

  constexpr
  void pre_release(const PreRelease& value) noexcept {
  }

  [[nodiscard]]
  constexpr
  Build build() const noexcept {
    return {};
  }

  constexpr
  void build(const Build& value) noexcept {
  }

  [[nodiscard]]
  constexpr
  friend
  auto operator<=>(const Semantic&, const Semantic&) noexcept = default;

  size_t vmajor{};
  size_t vminor{1};
  size_t vpatch{};
  PreRelease vpre_release;
  Build vbuild;
};

} // namespace flp
