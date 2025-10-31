#pragma once

#include <concepts>

namespace flp::Random {

template<typename Type>
concept Source = requires(Type source) {
  Type::Result;
  { Type::min() } -> std::same_as<typename Type::Result>;
  { Type::max() } -> std::same_as<typename Type::Result>;
  { source() };
};

template<typename Type>
concept Engine = Source<Type> and requires(Type engine) {
  Type::Seed;
  Type(Type::Seed);
  { engine.seed() };
  { engine.discard() };
  { engine.engine() };
};

template<typename Type>
concept Distribution = requires(Type distribution, Type::Result value) {
  { distribution.reset() };
  { distribution.min() };
  { distribution.max() };
  { distribution(value) };
};

}
