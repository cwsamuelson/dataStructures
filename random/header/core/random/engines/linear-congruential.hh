#pragma once

// https://en.cppreference.com/w/cpp/numeric/random/linear_congruential_engine.html
// https://en.wikipedia.org/wiki/Linear_congruential_generator

// The generator is defined by the recurrence relation:
//  X(n + 1) = ( a * X(n) + c ) mod m
// where:
//  - m, 0 < m : modulus
//  - a, 0 < a < m : multiplier
//  - c, 0 ≤ c < m : increment
//  - X(0), 0 ≤ X(0) < m : seed

namespace flp::Random {

size_t relation(const size_t seed, const size_t a, const size_t c) {
  return a * seed + c;
}

size_t relation(const size_t seed) {
  return relation(seed, 0, 0);
}

}
