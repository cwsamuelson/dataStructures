#pragma once

namespace flp {

struct TriBool {
  enum class State {
    True,
    False,
    Indeterminate,
    X = Indeterminate,
  };

  using enum State;

  constexpr
  TriBool() = default;

  constexpr
  TriBool(const bool value)
    : state(value ? True : False)
  {}

  constexpr
  TriBool(const TriBool&) noexcept = default;
  constexpr
  TriBool(TriBool&&) noexcept = default;
  constexpr
  TriBool& operator=(const TriBool&) noexcept = default;
  constexpr
  TriBool& operator=(TriBool&&) noexcept = default;

  ~TriBool() = default;

  [[nodiscard]]
  constexpr
  operator bool() const noexcept {
    return state == True;
  }

  [[nodiscard]]
  constexpr
  bool operator not() const noexcept {
    return state == False;
  }

  [[nodiscard]]
  constexpr
  bool operator==(const bool other) const noexcept {
    return (other and state == True) or (not other and state == False);
  }

  [[nodiscard]]
  constexpr friend
  auto operator<=>(const TriBool&, const TriBool&) noexcept = default;

  State state = X;
};

} // namespace flp
