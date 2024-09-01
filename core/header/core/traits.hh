#pragma once

namespace flp {

template<typename Type, template<typename...> class Target>
static constexpr bool is_specialization_of = false;

template<template<typename...> class Target, typename... Args>
static constexpr bool is_specialization_of<Target<Args...>, Target> = true;

}

