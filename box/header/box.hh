#pragma once

#include <memory>

namespace flp {

/*! Much like a unique_ptr, but considers itself a wrapper, not a pointer.
 *
 * A pointer's value is independent of the value of the object it points to.
 * This is made clear when you realize `char const *` and `char * const` have
 * different meanings. `char const *` reflects the constness of the pointer
 * value while `char * const` reflects constness of the underlying object.
 * Likewise `std::unique_ptr` and `std::shared_ptr` have the same issue where
 * `const std::unique_ptr<Type>` and `std::unique_ptr<const Type>` have different
 * semantics.  `Box` does not distinguish in this way.  The value of Box is tied
 * to the underlying object.  This is reflected in the dereference operator
 * returning a const value when Box is const; additionally Box doesn't allow
 * itself to be null; the underlying unique_ptr always has a value.
 *
 * This is mostly pulled from:
 * @ref https://www.foonathan.net/2022/05/recursive-variant-box/
 * Which takes inspiration from Rust.
 *
 * Box enables a recursive variant:
 * @code{.cpp}
 * struct AddExpression;
 * using Expression = std::variant<..., Box<AddExpression>>;
 * struct AddExpression {
 *   Expression lhs;
 *   Expression rhs;
 * };
 * @endcode
 *
 * Since Box is implemented as a pointer, a recursive type such as `Expression`
 * is possible, since its type doesn't inflate infinitely, but is nicer to work
 * with than `using Expression = std::variant<..., std::unique_ptr<AddExpression>>;`,
 * and preserves `const`ness of the underlying object with the `const`ness of
 * the `Box` itself.
 */
template<typename Type>
struct Box {
public:
  // requires default constructible
  Box() // noexcept move constructible
    : value(std::make_unique<Type>())
  {}

  // requires copy constructible
  Box(const Type& input) // noexcept copy constructible
    : value(std::make_unique<Type>(input))
  {}

  // requires move constructible
  Box(Type&& input) noexcept // noexcept move constructible
    : value(std::make_unique<Type>(std::move(input)))
  {}

  Box(const Box& other)
    : Box(*other)
  {}

  // Movable `Box` introduces nullability of `Box`, which we don't want. If
  // that's of interest an `OptionalBox` or `NullableBox` should be written instead.
  // if a `bool Nullable` nttp was created, the existence of the move operations
  // could be contingent on the value of `Nullable`
  //  requires Nullable
  //Box(Box&&) ...
  //  requires Nullable
  //Box& operator=(Box&&) ...

  Box& operator=(const Box& other) {
    *value = *other.value;
    return *this;
  }

  Box& operator=(const Type& input) {
    value = std::make_unique<Type>(input);
    return *this;
  }

  Box& operator=(Type&& input) noexcept {
    value = std::make_unique<Type>(std::move(input));
    return *this;
  }

  ~Box() = default;

        Type& operator*()       { return *value; }
  const Type& operator*() const { return *value; }

        Type* operator->()       { return value.get(); }
  const Type* operator->() const { return value.get(); }

  template<typename ...Args>
  void emplace(Args&& ...args) {
    value = std::make_unique<Type>(std::forward<Args>(args)...);
  }

  friend auto operator<=>(const Box& lhs, const Box& rhs) noexcept {
    return *lhs <=> *rhs;
  }

  friend auto operator==(const Box& lhs, const Box& rhs) noexcept {
    return *lhs == *rhs;
  }

private:
  std::unique_ptr<Type> value;
};

} // namespace flp

