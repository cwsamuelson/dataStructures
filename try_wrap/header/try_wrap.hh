#pragma once

#include <iostream>
#include <optional>
#include <type_traits>

namespace flp {

template<typename Type>
using Ref = std::conditional_t<std::is_reference_v<Type>, std::reference_wrapper<std::remove_reference_t<Type>>, Type>;

template<typename Type>
decltype(auto) Forward(Type& argument) {
    return std::ref(argument);
}

template<typename Type>
decltype(auto) Forward(Type&& argument) {
    return std::move(argument);
}

template<typename Functor>
struct TryWrap {
    Functor functor;

    template<typename F>
    TryWrap(F&& func) noexcept
        : functor(std::forward<F>(func))
    {}

    TryWrap(Functor func) noexcept
        : functor(std::move(func))
    {}

    // auto functor(Args...) noexcept
    template<typename ...Args>
        requires (std::is_nothrow_invocable_v<Functor, Args...>
        and std::is_void_v<std::invoke_result_t<Functor, Args...>>)
    void operator()(Args&& ...args) && noexcept {
        std::move(functor)(std::forward<Args>(args)...);
    }

    // auto functor(Args...)
    template<typename ...Args>
        requires ((not std::is_nothrow_invocable_v<Functor, Args...>)
        and std::is_void_v<std::invoke_result_t<Functor, Args...>>)
        [[nodiscard]]
    const std::exception_ptr operator()(Args&& ...args) && noexcept {
        try {
            std::move(functor)(std::forward<Args>(args)...);
            return nullptr;
        } catch(...) {
            return std::current_exception();
        }
    }

    // auto functor(Args...) noexcept
    template<typename ...Args>
        requires (std::is_nothrow_invocable_v<Functor, Args...>
        and not std::is_void_v<std::invoke_result_t<Functor, Args...>>)
        [[nodiscard]]
    decltype(auto) operator()(Args&& ...args) && noexcept {
        return std::move(functor)(std::forward<Args>(args)...);
    }

    // auto functor(Args...)
    template<typename ...Args>
        requires ((not std::is_nothrow_invocable_v<Functor, Args...>)
        and not std::is_void_v<std::invoke_result_t<Functor, Args...>>)
        [[nodiscard]]
    std::tuple<std::optional<Ref<std::invoke_result_t<Functor, Args...>>>, const std::exception_ptr> operator()(Args&& ...args) && noexcept {
        try {
            return std::make_tuple(Forward(std::move(functor)(std::forward<Args>(args)...)), nullptr);
        } catch(...) {
            return std::make_tuple(std::nullopt, std::current_exception());
        }
    }
};

}
