#pragma once

#include <rapidcheck/gen/Numeric.h>
#include <rapidcheck/gen/Predicate.h>
#include <rapidcheck/shrink/Shrink.h>

template<typename Type>
  requires std::floating_point<Type>
class rc::shrink::detail::TowardsSeq<Type> {
public:
  TowardsSeq(const Type value, const Type target)
      : m_value(value)
      , m_target(target) {}

  rc::Maybe<Type> operator()() {
    if (m_value == m_target) {
      return rc::Nothing;
    }
    
    // Go half-way towards the target value.
    Type new_value = (m_value / 2) + (m_target / 2);

    // When m_value and m_target differ by only 1 it may get stuck
    // so just push it the final distance.
    if (new_value == m_value)
        new_value = m_target;

    m_value = new_value;

    return m_value;
  }

private:
  Type m_value;
  Type m_target;
};

template<typename Type>
  requires std::floating_point<Type>
rc::Gen<Type> rc::gen::inRange(const Type min, const Type max) {
  return [=](const rc::Random &random, const int size) {
    if (max <= min) {
      throw rc::GenerationFailure(std::format("Invalid range [{}, {})", min, max));
    }

    const auto rangeSize = max - min;
    const auto normalized =
      static_cast<float>(rc::Random(random).next()) / std::numeric_limits<rc::Random::Number>::max();

    const auto value = (normalized * rangeSize) + min;
    assert(value >= min && value < max);
    return rc::shrinkable::shrinkRecur(
      value, [=](const Type x) {
        return rc::shrink::towards<Type>(x, std::max(min, std::min(static_cast<Type>(0), max)));
      }
    );
  };
}
