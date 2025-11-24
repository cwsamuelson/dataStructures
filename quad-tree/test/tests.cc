#include <quad-tree.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Arbitrary.h>
#include <rapidcheck/gen/Numeric.h>
#include <rapidcheck/gen/Predicate.h>
#include <rapidcheck/shrink/Shrink.h>

#include <string>

using namespace flp;

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

TEST_CASE("`QuadTree`") {
  QuadTree<int> quad_tree({{0.f, 0.f}, {1.f, 1.f}});

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  CHECK(quad_tree.insert({}, 0));

  CHECK(not quad_tree.empty());
  CHECK(quad_tree.size() == 1);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  CHECK(not quad_tree.insert({2.f, 2.f}, 0));

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);

  CHECK(quad_tree.insert({ .5f, .5f }, 0));
  CHECK(quad_tree.insert({ .1f, .1f }, 1));

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ 0.f, 0.f }, { 1.f, 1.f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ .1f, .1f }, { .5f, .5f }});
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ .6f, .6f }, { .9f, .9f }});
    CHECK(full_map_results.empty());
  }

  for (size_t i{2}; i < 10; ++i) {
    CHECK(quad_tree.insert({ .1f * i, .1f * i }, i));
    CHECK(quad_tree.size() == i + 1);
  }
  CHECK(quad_tree.size() == 10);

  {
    const auto full_map_results = quad_tree.query(QuadTree<int>::AABB{{ 0.f, 0.f }, { 1.f, 1.f }});
    CAPTURE(full_map_results);
    CHECK(full_map_results.size() == 10);
  }

  quad_tree.clear();

  CHECK(quad_tree.empty());
  CHECK(quad_tree.size() == 0);
}

TEST_CASE("`QuadTree`::properties") {
  rc::prop("Randomly configured quad-tree",
    [](const float x, const float y) {
      const float l = *rc::gen::positive<float>();
      const float w = *rc::gen::positive<float>();

      QuadTree<int> quad_tree({{x, y}, {l, w}});

      RC_ASSERT(quad_tree.empty());
      RC_ASSERT(quad_tree.size() == 0);

      quad_tree.clear();

      RC_ASSERT(quad_tree.empty());
      RC_ASSERT(quad_tree.size() == 0);

      const auto xs = *
        rc::gen::container<std::vector<float>>(
          rc::gen::inRange<float>(x, x + l)
        );

      const auto ys = *
        rc::gen::suchThat(
          rc::gen::container<std::vector<float>>(
            rc::gen::inRange<float>(y, y + w)
          ),
          [&xs](const std::vector<float>& values) {
            return values.size() == xs.size();
          }
        );

      const auto values = *
        rc::gen::suchThat(
          rc::gen::container<std::vector<int>>(
            rc::gen::arbitrary<int>()
          ),
          [&xs](const std::vector<int>& vals) {
            return vals.size() == xs.size();
          }
        );

      for (const auto&& [x, y, value] : std::views::zip(xs, ys, values)) {
        RC_ASSERT(quad_tree.insert({ x, y }, value));
      }

      RC_ASSERT(quad_tree.empty() == xs.empty());
      RC_ASSERT(quad_tree.size() == xs.size());
    }
  );
}
