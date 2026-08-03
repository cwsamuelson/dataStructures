#pragma once

#include  "core/overloads.hh"

#include <functional>
#include <optional>
#include <type_traits>
#include <variant>

namespace flp {

template<typename Error>
struct Unexpected;

template<typename Type, typename Error>
struct Expected {
  using value_type = Type;
  using error_type = Error;

  constexpr
  Expected() = default;

  constexpr
  Expected(const Expected& other)
    : data(other.data)
  {}

  constexpr
  Expected(Expected&& other) noexcept
    : data(std::move(other.data))
  {}

  constexpr
  Expected(const Type& val)
    : data(val)
  {}

  constexpr
  Expected(Type&& val) noexcept
    : data(std::move(val))
  {}

  constexpr
  Expected(const Error& err)
    : data(err)
  {}

  constexpr
  Expected(Error&& err) noexcept
    : data(std::move(err))
  {}

  constexpr
  Expected(const Unexpected<Error>& unexpected)
    : data(unexpected.error)
  {}

  constexpr
  Expected(Unexpected<Error>&& unexpected) noexcept
    : data(std::move(unexpected.error))
  {}

  constexpr
  Expected& operator=(const Expected& other) {
    data = other.data;
    return *this;
  }

  constexpr
  Expected& operator=(Expected&& other) noexcept {
    data = std::move(other.data);
    return *this;
  }

  constexpr
  Expected& operator=(const Type& val) {
    data = val;
    return *this;
  }

  constexpr
  Expected& operator=(Type&& val) noexcept {
    data = std::move(val);
    return *this;
  }

  constexpr
  Expected& operator=(const Error& err) {
    data = err;
    return *this;
  }

  constexpr
  Expected& operator=(Error&& err) noexcept {
    data = std::move(err);
    return *this;
  }

  constexpr
  ~Expected() = default;

  [[nodiscard]]
  constexpr
  explicit
  operator Type() const {
    return value().value();
  }

  [[nodiscard]]
  constexpr
  explicit
  operator Error() const {
    return error().value();
  }

  [[nodiscard]]
  constexpr
  bool has_value() const noexcept {
    return std::visit(Overloads {
      [](const Type&) {
        return true;
      },
      [](const auto&) {
        return false;
      },
    }, data);
  }

  [[nodiscard]]
  constexpr
  bool has_error() const noexcept {
    return std::visit(Overloads {
      [](const Error&) {
        return true;
      },
      [](const auto&) {
        return false;
      },
    }, data);
  }

  constexpr
  const Type& value() const {
    return std::visit(Overloads {
      [](Type& value) {
        return value;
      },
      [](const auto&) {
        return std::nullopt;
      },
    }, data);
  }

  constexpr
  const Error& error() const {
    return std::visit(Overloads {
      [](Error& error) {
        return error;
      },
      [](const auto&) {
        return std::nullopt;
      },
    }, data);
  }

  /* Apply functor
   * @param functor A functor with signature `T(Type)`
   * @return `Expected<T, Error>` where `T` is deduced from `Functor` return type
   */
  template<typename Functor>
  constexpr
  auto transform(Functor&& functor) {
    using T = std::invoke_result_t<Functor, Type>;
    using Result = Expected<T, Error>;

    if (has_value()) {
      return Result(std::invoke(std::forward<Functor>(functor), value().value()));
    }

    return Result(error().value());
  }

  template<typename Functor>
  constexpr
  auto transform_error(Functor&& functor) {
    using E = std::invoke_result_t<Functor, Error>;
    using Result = Expected<Type, E>;

    if (has_error()) {
      return Result(std::invoke(std::forward<Functor>(functor), value().value()));
    }

    return Result(value().value());
  }

  /* Apply functor
   * @param functor A functor with signature `Expected<T, Error>(Type)`
   * @return `Expected<T, Error>` as deduced from `Functor`.  Error type should remain the same.
   */
  template<typename Functor>
    requires std::same_as<typename std::invoke_result_t<Functor, Type>::error_type, Error>
  constexpr
  auto and_then(Functor&& functor) {
    // Functor: Expected<T, Error>(Type);
    // Result: Expected<T, Error>
    if (has_value()) {
      return std::invoke(std::forward<Functor>(functor), value().value());
    }
  }

  /* Apply functor
   * @param functor A functor with signature `Expected<Type, E>(Error)`
   * @return `Expected<Type, E>` as deduced from `Functor`.  Value type should remain the same.
   */
  template<typename Functor>
    requires std::same_as<typename std::invoke_result_t<Functor, Type>::value_type, Type>
  constexpr
  auto or_else(Functor&& functor) {
    // Functor: Expected<Type, E>(Type);
    // Result: Expected<Type, E>
    if (not has_value()) {
      return std::invoke(std::forward<Functor>(functor), error());
    }
  }

  std::variant<std::monostate, Type, Error> data;
};

template<typename Error>
struct Expected<void, Error> {
  constexpr
  Expected() = default;

  constexpr
  Expected(const Expected& other)
    : data(other.data)
  {}

  constexpr
  Expected(Expected&& other) noexcept
    : data(std::move(other.data))
  {}

  constexpr
  Expected(const Error& err)
    : data(err)
  {}

  constexpr
  Expected(Error&& err) noexcept
    : data(std::move(err))
  {}

  constexpr
  Expected(const Unexpected<Error>& unexpected)
    : data(unexpected.error)
  {}

  constexpr
  Expected(Unexpected<Error>&& unexpected) noexcept
    : data(std::move(unexpected.error))
  {}

  constexpr
  Expected& operator=(const Expected& other) {
    data = other.data;
    return *this;
  }

  constexpr
  Expected& operator=(Expected&& other) noexcept {
    data = std::move(other.data);
    return *this;
  }

  constexpr
  Expected& operator=(const Error& err) {
    data = err;
    return *this;
  }

  constexpr
  Expected& operator=(Error&& err) noexcept {
    data = std::move(err);
    return *this;
  }

  constexpr
  ~Expected() = default;

  [[nodiscard]]
  constexpr
  explicit
  operator bool() const {
    return has_value();
  }

  [[nodiscard]]
  constexpr
  explicit
  operator Error() const {
    return error().value();
  }

  [[nodiscard]]
  constexpr
  bool has_value() const noexcept {
    return not data.has_value();
  }

  [[nodiscard]]
  constexpr
  bool has_error() const noexcept {
    return data.has_value();
  }

  [[nodiscard]]
  constexpr
  std::optional<Error> error() const noexcept {
    return data;
  }

  std::optional<Error> data;
};

template<typename Error>
struct Unexpected {
  Error error;
};

}
