#include <sparse_map.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/catch.h>

#include <ranges>
#include <set>

using namespace flp;

struct S {
  int x;

  friend auto operator<=>(const S&, const S&) noexcept = default;
};

TEST_CASE("`SparseMap`::Basics") {
  SparseMap<size_t, S> sparse_map;

  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.clear();
  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.insert(5, { 6 });
  CHECK(sparse_map.size() == 1);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(*sparse_map.begin() == S { 6 });

  sparse_map.clear();
  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.insert(5, { 6 });
  sparse_map.insert(10, { 12 });
  CHECK(sparse_map.size() == 2);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(sparse_map.contains(10));
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(*sparse_map.begin() == S { 6 });

  sparse_map.clear();
  CHECK(sparse_map.size() == 0);
  CHECK(sparse_map.empty());
  CHECK(sparse_map.begin() == sparse_map.end());
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
  CHECK(not sparse_map.contains(5));

  sparse_map.insert(5, { 6 });
  sparse_map.insert(10, { 12 });
  sparse_map.insert(15, { 18 });
  CHECK(sparse_map.size() == 3);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(sparse_map.contains(10));
  CHECK(sparse_map.contains(15));
  CHECK(*sparse_map.begin() == S { 6 });
  CHECK(*(++sparse_map.begin()) == S { 12 });
  CHECK(*(++(++sparse_map.begin())) == S { 18 });
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));

  sparse_map.erase(10);
  CHECK(not sparse_map.contains(10));
  CHECK(sparse_map.size() == 2);
  CHECK(not sparse_map.empty());
  CHECK(sparse_map.begin() != sparse_map.end());
  CHECK(sparse_map.contains(5));
  CHECK(sparse_map.contains(15));
  CHECK(*sparse_map.begin() == S { 6 });
  CHECK(*(++sparse_map.begin()) == S { 18 });
  CHECK(not sparse_map.contains(0));
  CHECK(not sparse_map.contains(1));
}

// `uint16_t` is used to prevent ridiculous memory allocation due to the values
// requested from rapidcheck.  Since the 'key' ends up treated as an index,
// `SparseMap` requires the sparse array to be allocated to that size at minimum.
TEST_CASE("`SparseMap`::Properties") {
  static int MapValueCounter{};

  rc::prop("Contains all of a set of unique values", [] {
    const auto values = *
      rc::gen::unique<std::vector<uint16_t>>(
        rc::gen::arbitrary<uint16_t>()
      );
    SparseMap<uint16_t, S> sparse_map;
    for (const auto& key : values) {
      sparse_map.insert(key, {MapValueCounter++});
    }

    RC_ASSERT(sparse_map.size() == values.size());
    RC_ASSERT(sparse_map.empty() == values.empty());

    size_t count{};
    for (const auto& value : sparse_map) {
      RC_ASSERT(sparse_map.contains(value));
      ++count;
    }

    RC_ASSERT(count == sparse_map.size());

    for (const auto& value : values) {
      RC_ASSERT(sparse_map.contains(value));
    }

    // test traits of the copy
    auto sparse_map_copy = sparse_map;

    RC_ASSERT(sparse_map_copy.size() == sparse_map.size());
    RC_ASSERT(sparse_map_copy.empty() == sparse_map.empty());

    count = 0;
    for (const auto& value : sparse_map) {
      RC_ASSERT(sparse_map_copy.contains(value));
      ++count;
    }

    RC_ASSERT(count == sparse_map_copy.size());

    count = 0;
    for (const auto& value : sparse_map_copy) {
      RC_ASSERT(sparse_map.contains(value));
      ++count;
    }

    RC_ASSERT(count == sparse_map_copy.size());

    // test that clear works correctly
    sparse_map_copy.clear();
    RC_ASSERT(sparse_map_copy.empty());
    for (const auto& value : values) {
      RC_ASSERT(not sparse_map_copy.contains(value));
    }

    count = 0;
    for (const auto& value : sparse_map_copy) {
      RC_ASSERT(sparse_map_copy.contains(value));
      ++count;
    }

    RC_ASSERT(count == 0);
  });

  rc::prop("Acts like a set", [](const std::vector<uint16_t>& values) {
    const SparseMap<uint16_t, S> sparse_map(values.begin(), values.end());
    const std::set<uint16_t> std_set(values.begin(), values.end());

    RC_ASSERT(sparse_map.size() == std_set.size());
    RC_ASSERT(sparse_map.empty() == std_set.empty());

    for (const auto& value : std_set) {
      RC_ASSERT(sparse_map.contains(value));
    }
  });

  rc::prop("Removing values from set", [] {
    const auto values = *
      rc::gen::nonEmpty(
        rc::gen::unique<std::vector<uint16_t>>(
          rc::gen::arbitrary<uint16_t>()
        )
      );
    SparseMap<uint16_t, S> sparse_map(values.begin(), values.end());

    const auto remove = *rc::gen::elementOf(values);
    RC_ASSERT(sparse_map.contains(remove));
    sparse_map.erase(remove);
    RC_ASSERT(not sparse_map.contains(remove));
  });

  SECTION("Adding and removing values from set") {
    rc::prop("Totally random removal", [] {
      const auto initial_values = *
        rc::gen::nonEmpty(
          rc::gen::unique<std::vector<uint16_t>>(
            rc::gen::arbitrary<uint16_t>()
          )
        );
      SparseMap<uint16_t, S> sparse_map(initial_values.begin(), initial_values.end());

      const auto removal_values = *
        rc::gen::nonEmpty(
          rc::gen::unique<std::vector<uint16_t>>(
            rc::gen::arbitrary<uint16_t>()
          )
        );

      for (const auto& value : removal_values) {
        sparse_map.erase(value);
        RC_ASSERT(not sparse_map.contains(value));
      }

      for (const auto& value : removal_values) {
        RC_ASSERT(not sparse_map.contains(value));
      }
    });

    rc::prop("Remove values from the input", [] {
      const auto initial_values = *rc::gen::nonEmpty(
        rc::gen::unique<std::vector<uint16_t>>(
          rc::gen::arbitrary<uint16_t>()
        )
      );

      SparseMap<uint16_t, S> sparse_map(initial_values.begin(), initial_values.end());

      const auto removal_values = *
        rc::gen::nonEmpty(
          rc::gen::container<std::vector<uint16_t>>(
            rc::gen::elementOf(initial_values)
          )
        );

      for (const auto& value : removal_values) {
        sparse_map.erase(value);
        RC_ASSERT(not sparse_map.contains(value));
      }

      for (const auto& value : removal_values) {
        RC_ASSERT(not sparse_map.contains(value));
      }
    });
  }
}
