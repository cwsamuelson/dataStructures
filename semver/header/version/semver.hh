#pragma once

#include <cstddef>
#include <format>
#include <optional>
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
  Semantic() = default;

  constexpr
  Semantic(const size_t major, const PreRelease& pre_release, const Build& build)
    : Semantic(major, 0, pre_release, build)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const PreRelease& pre_release, const Build& build)
    : Semantic(major, minor, 0, pre_release, build)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const size_t patch, const PreRelease& pre_release, const Build& build)
    : Semantic(major, minor, patch, std::optional(pre_release), std::optional(build))
  {}

  constexpr
  Semantic(const size_t major, const PreRelease& pre_release)
    : Semantic(major, 0, pre_release)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const PreRelease& pre_release)
    : Semantic(major, minor, 0, pre_release)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const size_t patch, const PreRelease& pre_release)
    : Semantic(major, minor, patch, pre_release, std::nullopt)
  {}

  constexpr
  Semantic(const size_t major, const Build& build)
    : Semantic(major, 0, build)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const Build& build)
    : Semantic(major, minor, 0, build)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const size_t patch, const Build& build)
    : Semantic(major, minor, patch, std::nullopt, build)
  {}

  constexpr
  Semantic(const size_t major)
    : Semantic(major, 0)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor)
    : Semantic(major, minor, 0)
  {}

  constexpr
  Semantic(const size_t major, const size_t minor, const size_t patch)
    : Semantic(major, minor, patch, std::nullopt, std::nullopt)
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
  std::optional<PreRelease> pre_release() const noexcept {
    return vpre_release;
  }

  constexpr
  void pre_release(const PreRelease& value) noexcept {
    vpre_release = value;
  }

  constexpr
  void pre_release(const std::optional<PreRelease>& value) noexcept {
    vpre_release = value;
  }

  [[nodiscard]]
  constexpr
  std::optional<Build> build() const noexcept {
    return vbuild;
  }

  constexpr
  void build(const std::optional<Build>& value) noexcept {
    vbuild = value;
  }

  [[nodiscard]]
  constexpr
  friend
  auto operator<=>(const Semantic& lhs, const Semantic& rhs) noexcept {
    if (lhs.vmajor != rhs.vmajor) {
      return lhs.vmajor <=> rhs.vmajor;
    }

    if (lhs.vminor != rhs.vminor) {
      return lhs.vminor <=> rhs.vminor;
    }

    if (lhs.vpatch != rhs.vpatch) {
      return lhs.vpatch <=> rhs.vpatch;
    }

    if (lhs.vpre_release.has_value() and rhs.vpre_release.has_value()) {
      throw std::runtime_error("Unimplemented");
      // return lhs.vpre_release.value() <=> rhs.vpre_release.value();
    } else if (lhs.vpre_release.has_value()) {
      return std::strong_ordering::less;
    } else if (rhs.vpre_release.has_value()) {
      return std::strong_ordering::greater;
    }

    if (lhs.vbuild.has_value() and rhs.vbuild.has_value()) {
      throw std::runtime_error("Unimplemented");
      // return lhs.vbuild.value() <=> rhs.vbuild.value();
    } else if (lhs.vbuild.has_value()) {
      return std::strong_ordering::less;
    } else if (rhs.vbuild.has_value()) {
      return std::strong_ordering::greater;
    }

    return std::strong_ordering::equal;
  }

  [[nodiscard]]
  constexpr
  friend
  bool operator==(const Semantic& lhs, const Semantic& rhs) noexcept {
    return
          lhs.vmajor       == rhs.vmajor
      and lhs.vminor       == rhs.vminor
      and lhs.vpatch       == rhs.vpatch
      // and lhs.vpre_release == rhs.vpre_release
      // and lhs.vbuild       == rhs.vbuild
    ;
  }

  size_t vmajor{};
  size_t vminor{1};
  size_t vpatch{};
  std::optional<PreRelease> vpre_release;
  std::optional<Build> vbuild;

private:
  constexpr
  Semantic(const size_t major, const size_t minor, const size_t patch, std::optional<PreRelease> pre_release, std::optional<Build> build)
    : vmajor(major)
    , vminor(minor)
    , vpatch(patch)
    , vpre_release(std::move(pre_release))
    , vbuild(std::move(build))
  {}
};

} // namespace flp
