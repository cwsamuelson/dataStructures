#include <coroutine>
#include <functional>
#include <optional>
#include <memory>
#include <concepts>
#include <mutex>
#include <condition_variable>
#include <type_traits>

template<typename Type, size_t alignment = alignof(Type)>
struct AlignedBuffer {
    static constexpr size_t Size = sizeof(Type);

    alignas(alignment)
    std::byte storage[Size];

    template<typename ...Args>
    void construct(Args&& ...args) {
        new (&storage) Type(std::forward<Args>(args)...);
    }
    void destruct() {
        reinterpret_cast<Type*>(&storage)->~Type();
    }

    [[nodiscard]]
    Type& get() noexcept {
        return *reinterpret_cast<Type*>(&storage);
    }

    [[nodiscard]]
    const Type& get() const noexcept {
        return *reinterpret_cast<Type*>(&storage);
    }
};

template<typename Type>
class Optional {
public:
    Optional() noexcept = default;
    Optional(const Optional& other)
    requires std::copy_constructible<Type> {
        if (other.initialized) {
            buffer.construct(other.buffer.get());
        } else {
            buffer.destruct();
        }
        initialized = other.initialized;
    }
    Optional(Optional&& other)
    requires std::move_constructible<Type> {
        if (other.initialized) {
            buffer.construct(std::move(other.buffer.get()));
            other.buffer.destruct();
            other.initialized = false;
            initialized = true;
        } else if (initialized) {
            buffer.destruct();
            initialized = false;
        }
    }
    ~Optional() {
        if (initialized) {
            buffer.destruct();
        }
    }

    [[nodiscard]]
    bool has_value() const noexcept {
        return initialized;
    }

    [[nodiscard]]
    operator bool() const noexcept {
        return has_value();
    }

    [[nodiscard]]
    Type& value() {
        if (not has_value()) {
            throw 42;
        } else {
            return buffer.get();
        }
    }

    [[nodiscard]]
    const Type& value() const {
        if (not has_value()) {
            throw 42;
        } else {
            return buffer.get();
        }
    }

    template<typename Functor>
    Optional<std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Type>>>
    and_then(Functor&& functor) {
        if (has_value()) {
            return std::forward<Functor>(functor)(value());
        } else {
            return {};
        }
    }

    template<typename T, T Type::*member>
    requires std::is_class_v<Type>
    Optional<T>
    and_then() {
        if (has_value()) {
            return value().*member;
        } else {
            return {};
        }
    }

    template<std::invocable Functor>
    Optional or_else(Functor&& functor) {
        if (not has_value()) {
            return std::forward<Functor>(functor)();
        } else {
            return *this;
        }
    }

    template<typename ElseType>
    requires (not std::invocable<ElseType>)
    Optional or_else(ElseType&& value) {
        if (not has_value()) {
            return std::forward<ElseType>(value());
        } else {
            return *this;
        }
    }

    template<typename Functor>
    Optional<std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Type>>>
    transform(Functor&& functor) {
        if (has_value()) {
            return std::forward<Functor>(functor)(value());
        } else {
            return {};
        }
    }

private:
    AlignedBuffer<Type> buffer;
    bool initialized = false;
};

int main() {
    Optional<int> o;
    return 0;
}
