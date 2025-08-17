#pragma once

namespace flp {

struct Less {
  constexpr
  bool operator()(const auto& a, const auto& b) const {
    return a < b;
  }
};

struct Greater {
  constexpr
  bool operator()(const auto& a, const auto& b) const {
    return a > b;
  }
};

struct LessEqual {
  constexpr
  bool operator()(const auto& a, const auto& b) const {
    return a <= b;
  }
};

struct GreaterEqual {
  constexpr
  bool operator()(const auto& a, const auto& b) const {
    return a >= b;
  }
};

struct Equal {
  constexpr
  bool operator()(const auto& a, const auto& b) const {
    return a == b;
  }
};

struct NotEqual {
  constexpr
  bool operator()(const auto& a, const auto& b) const {
    return a != b;
  }
};

}
