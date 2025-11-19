#pragma once


namespace flp {

struct Any {
  Any() = default;
  Any(const Any&) = default;
  Any(Any&&) noexcept = default;
  Any& operator=(const Any&) = default;
  Any& operator=(Any&&) noexcept = default;
  ~Any() = default;

  template<typename Type>
  Any(Type&&) {}

  template<typename Type>
  Any& operator=(Type&&) {
    return *this;
  }
};

} // namespace flp
