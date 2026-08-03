#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>

namespace flp::Random {

template<typename Type>
concept Source = requires(Type source) {
  Type();
  typename Type::Result;
  { Type::min() } -> std::same_as<typename Type::Result>;
  { Type::max() } -> std::same_as<typename Type::Result>;
  { source() };
};

template<typename Type>
concept Engine = Source<Type> and requires(Type engine, typename Type::Seed seed, size_t count) {
  typename Type::Seed;
  Type(seed);

  { engine.seed() };
  { engine.seed(seed) };

  { engine.discard() };
  { engine.discard(count) };

  { engine.template get<uint8_t>() } -> std::same_as<uint8_t>;
};

template<typename Type>
concept Distribution = requires(Type distribution, Type::Result value) {
  { distribution.reset() };
  { distribution.min() };
  { distribution.max() };
  { distribution(value) };
};

}
