#pragma once

namespace flp {

struct Integer {
  template<std::integral Int>
  Integer(const Int& val)
    : value(val)
  {}

  Integer(const Integer&) noexcept = default;
  Integer(Integer&&) noexcept = default;
  Integer& operator=(const Integer&) noexcept = default;
  Integer& operator=(Integer&&) noexcept = default;
  ~Integer() noexcept = default;

  template<std::integral Int>
  explicit
  operator Int() const {
    return get<Int>();
  }

  template<std::integral Int>
  [[nodiscard]]
  Int get() const {
    if (value > std::numeric_limits<Int>::max() or value < std::numeric_limits<Int>::min()) {
      throw std::runtime_error("");
    }

    return static_cast<Int>(value);
  }

  Integer& operator+=(const Integer& other) noexcept {
    value += other.value;
    return *this;
  }

  [[nodiscard]]
  friend
  Integer operator+(const Integer& lhs, const Integer& rhs) noexcept {
    auto copy = lhs;
    return lhs += rhs;
  }

  //!@TODO switch to gmp
  uint64_t value{};
};

}
