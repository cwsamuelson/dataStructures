#pragma once

#include <string>
#include <text/string.hh>

namespace flp::filesystem {

struct Path {
  [[nodiscard]]
  constexpr
  bool absolute() const noexcept {
    // this doesn't support windows...
    return components.front() == "/";
  }

  [[nodiscard]]
  constexpr
  bool relative() const noexcept {
    // this is likely incomplete
    return components.front() == "." or components.front() == "..";
  }

  [[nodiscard]]
  constexpr
  Path relative_to(Path) const noexcept;

  [[nodiscard]]
  constexpr
  bool empty() const noexcept {
    return extension.empty() and components.empty();
  }

  [[nodiscard]]
  constexpr
  decltype(auto) stem(this auto&& self) noexcept {
    return self.components.back();
  }

  [[nodiscard]]
  constexpr
  decltype(auto) extension(this auto&& self) noexcept {
    return extension;
  }

  constexpr
  void clear() {
    components.clear();
    extension.clear();
  }

  [[nodiscard]]
  constexpr
  String string() const;

  [[nodiscard]]
  constexpr
  Iterator begin();

  [[nodiscard]]
  constexpr
  Iterator end();

  [[nodiscard]]
  explicit
  constexpr
  operator String() const;

  [[nodiscard]]
  explicit
  constexpr
  operator std::string() const;

  [[nodiscard]]
  constexpr
  Path operator/(std::string_view components);

  [[nodiscard]]
  constexpr
  Path operator/(const Path& paths);

  [[nodiscard]]
  friend
  constexpr
  auto operator<=>(const Path&, const Path&) noexcept = default;

  String extension;
  std::vector<String> components;
};

} // namespace flp

namespace flp {
using namespace fs = filesystem;
}
