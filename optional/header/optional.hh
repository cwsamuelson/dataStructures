#include <aligned_buffer.hh>
#include <error_help.hh>

#include <core/concepts.hh>

#include <concepts>
#include <cstring>
#include <mutex>
#include <optional>
#include <type_traits>

namespace flp {

struct NullOptional_t {};
constexpr NullOptional_t NullOptional {};

template<typename Type>
class Optional {
public:
           Optional() noexcept = default;
  explicit Optional(const Optional& other)
    requires std::copy_constructible<Type>
  {
    if (other.initialized) {
      buffer.construct(other.buffer.get());
    } else {
      buffer.destruct();
    }
    initialized = other.initialized;
  }
  Optional(Optional&& other)
    requires std::move_constructible<Type>
  {
    if (other.initialized) {
      buffer.construct(std::move(other.buffer.get()));
      other.buffer.destruct();
      other.initialized = false;
      initialized       = true;
    } else if (initialized) {
      buffer.destruct();
      initialized = false;
    }
  }
  Optional(const NullOptional_t)
    : Optional() {}
  Optional(const Type& value) {
    buffer.construct(value);
    initialized = true;
  }
  Optional(Type&& value) {
    buffer.construct(std::move(value));
    initialized = true;
  }
  ~Optional() {
    if (initialized) {
      buffer.destruct();
    }
  }

  // conditional noexcepts..
  Optional& operator=(const Optional& other) {
    if (initialized) {
      // does this need to bother respecting semantics of underlying types?
      buffer.get() = other.buffer.get();
    } else {
      buffer.construct(other.buffer.get());
      initialized = true;
    }
    return *this;
  }
  Optional& operator=(Optional&& other) noexcept {
    if (initialized) {
      initialized = false;
      buffer.destruct();
    }

    if (other.initialized) {
      std::memcpy(buffer.storage.data(), other.buffer.storage.data(), sizeof(buffer.storage));
      other.initialized = false;
      initialized       = true;
    }

    return *this;
  }
  Optional& operator=(const NullOptional_t) {
    if (initialized) {
      buffer.destruct();
      initialized = false;
    }
  }

  [[nodiscard]]
  bool has_value() const noexcept {
    return initialized;
  }

  [[nodiscard]]
  explicit
  operator bool() const noexcept {
    return has_value();
  }

  template<typename... Args>
  Type& emplace(Args&&... args) {
    if (initialized) {
      buffer.destruct();
      initialized = false;
    }

    buffer.construct(std::forward<Args>(args)...);
    initialized = true;

    return buffer.get();
  }

  [[nodiscard]]
  decltype(auto) value(this auto&& self) {
    VERIFY(self.has_value(), "No value in optional");
    return self.buffer.get();
  }

  template<typename T = Type>
    requires std::same_as<std::decay_t<T>, std::decay_t<Type>>
  T value_or(this auto&& self, T&& alternative) {
    if (self.initialized) {
      return self.value();
    } else {
      return std::forward<T>(alternative);
    }
  }

  /*template<typename T, T Type::*member>
      requires std::is_class_v<Type>
  Optional<T> and_then() {
      if (has_value()) {
          return value().*member;
      } else {
          return {};
      }
  }*/

  template<typename Functor>
    requires flp::IsSpecializationOf<
      std::invoke_result_t<std::decay_t<Functor>, std::add_lvalue_reference_t<std::decay_t<Type>>>,
      Optional>
  std::invoke_result_t<std::decay_t<Functor>, std::add_lvalue_reference_t<std::decay_t<Type>>>
  and_then(Functor&& functor) {
    if (has_value()) {
      return std::forward<Functor>(functor)(value());
    } else {
      return {};
    }
  }

  template<std::invocable Functor>
  Optional or_else(Functor&& functor) {
    if (not has_value()) {
      return std::forward<Functor>(functor)();
    } else {
      return value();
    }
  }

  template<typename Functor>
  Optional<std::invoke_result_t<std::decay_t<Functor>, std::add_lvalue_reference_t<std::decay_t<Type>>>>
  transform(Functor&& functor) {
    if (has_value()) {
      return std::forward<Functor>(functor)(value());
    } else {
      return {};
    }
  }

  void reset() {
    initialized = false;
    buffer.destruct();
  }

private:
  AlignedBuffer<Type> buffer;
  bool                initialized = false;
};

} // namespace flp
