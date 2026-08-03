#include <core/rb-tree.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>

using namespace flp;

TEST_CASE("`RB-Tree`") {
  rc::prop("Key insertion", [](const int key, const int value) {
    RBTree<int, int> rb_tree;
    rb_tree.insert(key, value);

    RC_ASSERT(not rb_tree.empty());
    RC_ASSERT(rb_tree.size() == 1);
    RC_ASSERT(rb_tree.contains(key));
    RC_ASSERT(rb_tree.find(key) == value);
  });

  rc::prop("Multiple values", [] {
    const auto keys = *
      rc::gen::unique<std::vector<int>>(
        rc::gen::arbitrary<int>()
      );

    RBTree<int, int> rb_tree;

    int value_counter{};
    for (const auto key : keys) {
      rb_tree.insert(key, value_counter++);
    }

    RC_ASSERT(rb_tree.empty() == keys.empty());
    RC_ASSERT(rb_tree.size() == keys.size());

    for (const auto key : keys) {
      RC_ASSERT(rb_tree.contains(key));
    }
  });
}
