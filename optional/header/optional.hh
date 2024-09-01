#include <aligned_buffer.hh>
#include <error_help.hh>

#include <concepts>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <type_traits>

namespace flp {

struct NullOptional{};

template<typename Type>
class Optional {
public:
  Optional() noexcept = default;
  Optional(const Optional& other)
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
  Optional(const NullOptional)
    : Optional()
  {}
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
      initialized = true;
    }

    return *this;
  }

  [[nodiscard]]
  bool has_value() const noexcept {
    return initialized;
  }

  [[nodiscard]] operator bool() const noexcept {
    return has_value();
  }

  [[nodiscard]]
  decltype(auto) value(this auto&& self) {
    VERIFY(self.has_value(), "No value in optional");
    return self.buffer.get();
  }

  template<typename Functor>
  Optional<std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Type>>> and_then(Functor&& functor) {
    if (has_value()) {
      return std::forward<Functor>(functor)(value());
    } else {
      return {};
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

  template<std::invocable Functor>
  Optional or_else(Functor&& functor) {
    if (not has_value()) {
      return std::forward<Functor>(functor)();
    } else {
      return *this;
    }
  }

  template<typename ElseType>
    requires(not std::invocable<ElseType>)
  Optional or_else(ElseType&& value) {
    if (not has_value()) {
      return std::forward<ElseType>(value());
    } else {
      return *this;
    }
  }

  template<typename Functor>
  Optional<std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Type>>> transform(Functor&& functor) {
    if (has_value()) {
      return std::forward<Functor>(functor)(value());
    } else {
      return {};
    }
  }

  void clear() {
    initialized = false;
    buffer.destruct();
  }

private:
  AlignedBuffer<Type> buffer;
  bool                initialized = false;
};

} // namespace flp
