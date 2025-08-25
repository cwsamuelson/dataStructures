#pragma once

#include <error_help.hh>

#include <algorithm>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace flp {

#define SMART_ENUM_DEFINE(Name, Type, ...) \
struct Name { \
  enum class Value : Type { \
    __VA_ARGS__ \
  }; \
  static constexpr const char* names[] = { \
    #__VA_ARGS__ \
  }; \
 \
  Name(const Value val) \
    : value(val) \
  {} \
 \
  Name(const Name&) noexcept = default; \
  Name(Name&&) noexcept = default; \
 \
  Name& operator=(const Name&) noexcept = default; \
  Name& operator=(Name&&) noexcept = default; \
 \
  explicit operator Type() const noexcept { \
    return static_cast<Type>(value); \
  } \
 \
  Value value; \
 \
  friend constexpr auto operator<=>(const Name&, const Name&) noexcept = default; \
};

#define SMART_ENUM_SUB_DEFINE(Name, Base, ...) \
struct Name { \
  using Type = std::underlying_type_t<Base::Value>; \
  enum class Value : Type { \
    __VA_ARGS__ = static_cast<Type>(Base::Value::__VA_ARGS__), \
  }; \
  static constexpr Value values[] = { \
    Value::__VA_ARGS__ \
  }; \
 \
  static size_t count() noexcept { \
    return sizeof(values) / sizeof(Value); \
  } \
  Name(const Base val) \
    : value(static_cast<Value>(val.value)) { \
    bool found = false; \
    for (size_t i{}; i < count(); ++i) { \
      if (values[i] == value) { \
        found = true; \
        break; \
      } \
    } \
    VERIFY(found, "Base value not available in sub-enum"); \
  } \
 \
  Name(const Value val) \
    : value(val) \
  {} \
 \
  Name(const Name&) noexcept = default; \
  Name(Name&&) noexcept = default; \
 \
  Name& operator=(const Name&) noexcept = default; \
  Name& operator=(Name&&) noexcept = default; \
 \
  explicit operator Type() const noexcept { \
    return static_cast<Type>(value); \
  } \
 \
  operator Base() const noexcept { \
    return static_cast<Base::Value>(value); \
  } \
 \
  Value value; \
};

} // namespace flp
