#include <sparse_set.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/catch.h>

#include <set>

using namespace flp;

TEST_CASE("`SparseSet`") {
  SparseSet<size_t> sparse_set;

  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.insert(1);
  CHECK(sparse_set.size() == 1);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(1));
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(5));
  CHECK(*sparse_set.begin() == 1);

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.insert(1);
  sparse_set.insert(2);

  CHECK(sparse_set.size() == 2);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(1));
  CHECK(sparse_set.contains(2));
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(5));
  CHECK(*sparse_set.begin() == 1);
  CHECK(*(++sparse_set.begin()) == 2);

  sparse_set.clear();
  CHECK(sparse_set.size() == 0);
  CHECK(sparse_set.empty());
  CHECK(sparse_set.begin() == sparse_set.end());
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.insert(3);
  sparse_set.insert(8);
  sparse_set.insert(15);
  CHECK(sparse_set.size() == 3);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(3));
  CHECK(sparse_set.contains(8));
  CHECK(sparse_set.contains(15));
  CHECK(*sparse_set.begin() == 3);
  CHECK(*(++sparse_set.begin()) == 8);
  CHECK(*(++(++sparse_set.begin())) == 15);
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));

  sparse_set.erase(8);
  CHECK(not sparse_set.contains(8));
  CHECK(sparse_set.size() == 2);
  CHECK(not sparse_set.empty());
  CHECK(sparse_set.begin() != sparse_set.end());
  CHECK(sparse_set.contains(3));
  CHECK(sparse_set.contains(15));
  CHECK(*sparse_set.begin() == 3);
  CHECK(*(++sparse_set.begin()) == 15);
  CHECK(not sparse_set.contains(0));
  CHECK(not sparse_set.contains(1));
  CHECK(not sparse_set.contains(5));
}

// `uint16_t` is used to prevent ridiculous memory allocation due to the values
// requested from rapidcheck.  Since the 'value' ends up treated as an index,
// `SparseSet` requires the sparse array to be allocated to that size at minimum.
TEST_CASE("`SparseSet`::Properties") {
  rc::prop("Contains all of a set of unique values", [] {
    const auto values = *rc::gen::unique<std::vector<uint16_t>>(rc::gen::arbitrary<uint16_t>());
    const SparseSet<uint16_t> sparse_set(values.begin(), values.end());

    RC_ASSERT(sparse_set.size() == values.size());
    RC_ASSERT(sparse_set.empty() == values.empty());

    size_t count{};
    for (const auto& value : sparse_set) {
      RC_ASSERT(sparse_set.contains(value));
      ++count;
    }

    RC_ASSERT(count == sparse_set.size());

    for (const auto& value : values) {
      RC_ASSERT(sparse_set.contains(value));
    }

    // test traits of the copy
    auto mutable_sparse_set = sparse_set;

    RC_ASSERT(mutable_sparse_set.size() == sparse_set.size());
    RC_ASSERT(mutable_sparse_set.empty() == sparse_set.empty());

    count = 0;
    for (const auto& value : sparse_set) {
      RC_ASSERT(mutable_sparse_set.contains(value));
      ++count;
    }

    RC_ASSERT(count == mutable_sparse_set.size());

    count = 0;
    for (const auto& value : mutable_sparse_set) {
      RC_ASSERT(sparse_set.contains(value));
      ++count;
    }

    RC_ASSERT(count == mutable_sparse_set.size());

    // test that clear works correctly
    mutable_sparse_set.clear();
    RC_ASSERT(mutable_sparse_set.empty());
    for (const auto& value : values) {
      RC_ASSERT(not mutable_sparse_set.contains(value));
    }

    count = 0;
    for (const auto& value : mutable_sparse_set) {
      RC_ASSERT(mutable_sparse_set.contains(value));
      ++count;
    }

    RC_ASSERT(count == 0);
  });

  rc::prop("Acts like a set", [](const std::vector<uint16_t>& values) {
    const SparseSet<uint16_t> sparse_set(values.begin(), values.end());
    const std::set<uint16_t> std_set(values.begin(), values.end());

    RC_ASSERT(sparse_set.size() == std_set.size());
    RC_ASSERT(sparse_set.empty() == std_set.empty());

    for (const auto& value : std_set) {
      RC_ASSERT(sparse_set.contains(value));
    }
  });

  rc::prop("Removing values from set", [] {
    const auto values = *rc::gen::nonEmpty(rc::gen::unique<std::vector<uint16_t>>(rc::gen::arbitrary<uint16_t>()));
    SparseSet<uint16_t> sparse_set(values.begin(), values.end());

    const auto remove = *rc::gen::elementOf(values);
    RC_ASSERT(sparse_set.contains(remove));
    sparse_set.erase(remove);
    RC_ASSERT(not sparse_set.contains(remove));
  });

  rc::prop("Adding and removing values from set", [] {
    const auto initial_values = *rc::gen::nonEmpty(rc::gen::unique<std::vector<uint16_t>>(rc::gen::arbitrary<uint16_t>()));
    SparseSet<uint16_t> sparse_set(initial_values.begin(), initial_values.end());

    const auto removal_values = *rc::gen::nonEmpty(rc::gen::unique<std::vector<uint16_t>>(rc::gen::arbitrary<uint16_t>()));

    for (const auto& value : removal_values) {
      sparse_set.erase(value);
      RC_ASSERT(not sparse_set.contains(value));
    }

    for (const auto& value : removal_values) {
      RC_ASSERT(not sparse_set.contains(value));
    }
  });
}

TEST_CASE("`SparseSet`::Regressions") {
  SparseSet<uint64_t> sparse_set;
  sparse_set.insert(2);
  sparse_set.insert(1);

  CHECK(sparse_set.contains(2));
  CHECK(sparse_set.contains(1));
}
