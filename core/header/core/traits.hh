#pragma once

#include <type_traits>

namespace flp {

template<typename, template<typename...> class>
inline constexpr bool is_specialization_helper = false;

template<template<typename...> class Target, typename... Args>
inline constexpr bool is_specialization_helper<Target<Args...>, Target> = true;

// using the wrapper and decay handles refs and cv-qual
template<typename Query, template<typename...> typename Target>
inline constexpr bool is_specialization_of = is_specialization_helper<std::decay_t<Query>, Target>;

template<typename Type, template<typename...> typename Target>
concept instance_of = is_specialization_of<Type, Target>;

} // namespace flp
