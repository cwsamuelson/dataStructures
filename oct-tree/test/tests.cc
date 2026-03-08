#include <oct-tree.hh>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Arbitrary.h>
#include <rapidcheck/gen/Predicate.h>
#include <test-utils/test-utils.hh>

#include <catch2/catch_all.hpp>

#include <ranges>
#include <vector>

using namespace flp;

TEST_CASE("`OctTree`") {
  OctTree<int> oct_tree({
    { 0.f, 0.f, 0.f },
    { 1.f, 1.f, 1.f }
  });

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  CHECK(oct_tree.insert({}, 0));

  CHECK(not oct_tree.empty());
  CHECK(oct_tree.size() == 1);

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  CHECK(not oct_tree.insert({ 2.f, 2.f, .2f }, 0));

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);

  CHECK(oct_tree.insert({ .5f, .5f, .5f }, 0));
  CHECK(oct_tree.insert({ .1f, .1f, .1f }, 1));

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB {
      { 0.f, 0.f, 0.f },
      { 1.f, 1.f, 1.f }
    });
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB {
      { .1f, .1f, .1f },
      { .5f, .5f, .5f }
    });
    REQUIRE(full_map_results.size() == 2);
    CHECK((full_map_results.at(0) == 0) xor (full_map_results.at(0) == 1));
  }

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB {
      { .6f, .6f, .6f },
      { .9f, .9f, .9f }
    });
    CHECK(full_map_results.empty());
  }

  for (size_t i { 2 }; i < 10; ++i) {
    CHECK(oct_tree.insert({ .1f * i, .1f * i, .1f * i }, i));
    CHECK(oct_tree.size() == i + 1);
  }
  CHECK(oct_tree.size() == 10);

  {
    const auto full_map_results = oct_tree.query(OctTree<int>::AABB {
      { 0.f, 0.f, 0.f },
      { 1.f, 1.f, 1.f }
    });
    CAPTURE(full_map_results);
    CHECK(full_map_results.size() == oct_tree.size());
    CHECK(oct_tree.size() == 10);
  }

  oct_tree.clear();

  CHECK(oct_tree.empty());
  CHECK(oct_tree.size() == 0);
}

TEST_CASE("`OctTree`::properties") {
  rc::prop("Randomly configured oct-tree", [](const float x, const float y, const float z) {
    const float l = *rc::gen::positive<float>();
    const float w = *rc::gen::positive<float>();
    const float h = *rc::gen::positive<float>();

    OctTree<int> oct_tree({
      { x, y, z },
      { l, w, h }
    });

    RC_ASSERT(oct_tree.empty());
    RC_ASSERT(oct_tree.size() == 0);

    oct_tree.clear();

    RC_ASSERT(oct_tree.empty());
    RC_ASSERT(oct_tree.size() == 0);

    const auto xs = *rc::gen::container<std::vector<float>>(rc::gen::inRange<float>(x, x + l));

    const auto ys = *rc::gen::suchThat(rc::gen::container<std::vector<float>>(rc::gen::inRange<float>(y, y + w)),
                                       [&xs](const std::vector<float>& values) {
                                         return values.size() == xs.size();
                                       });

    const auto zs = *rc::gen::suchThat(rc::gen::container<std::vector<float>>(rc::gen::inRange<float>(z, z + h)),
                                       [&xs](const std::vector<float>& values) {
                                         return values.size() == xs.size();
                                       });

    const auto values = *rc::gen::suchThat(rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>()),
                                           [&xs](const std::vector<int>& vals) {
                                             return vals.size() == xs.size();
                                           });

    for (const auto&& [x, y, z, value] : std::views::zip(xs, ys, zs, values)) {
      RC_ASSERT(oct_tree.insert({ x, y, z }, value));
    }

    RC_ASSERT(oct_tree.empty() == xs.empty());
    RC_ASSERT(oct_tree.size() == xs.size());
  });
}
