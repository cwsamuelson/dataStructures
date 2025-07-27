#include <hive.hh>

#include <catch2/catch_all.hpp>

#include <optional>

using namespace flp;

struct RAIITest {
  bool default_contsructor = false;
  bool copy_constructor = false;
  bool move_constructor = false;
  bool copy_assignment = false;
  bool move_assignment = false;
  bool with_args = false;
  std::optional<std::reference_wrapper<bool>> destructor;

  template<typename ...Args>
  RAIITest(Args&& ...args)
    : with_args(true)
  {}
  RAIITest()
    : default_contsructor(true)
  {}
  RAIITest(const RAIITest&)
    : copy_constructor(true)
  {}
  RAIITest(RAIITest&&)
    : move_constructor(true)
  {}

  RAIITest& operator=(const RAIITest&) {
    copy_assignment = true;
    return *this;
  }
  RAIITest& operator=(RAIITest&&) {
    move_assignment = true;
    return *this;
  }

  ~RAIITest() {
    if (destructor.has_value()) {
      destructor.value().get() = true;
    }
  }
};

TEST_CASE("Hive") {
  Hive<RAIITest> hive;

  CHECK(hive.empty());

  size_t count{};
  for (auto& _ : hive) {
    ++count;
  }
  CHECK(count == 0);

  RAIITest new_value;
  bool destructor_called = false;
  const auto iter = hive.insert(new_value);

  iter->destructor = destructor_called;

  CHECK(iter->copy_constructor);
  CHECK(not iter->default_contsructor);
  CHECK(not iter->move_constructor);
  CHECK(not iter->copy_assignment);
  CHECK(not iter->move_assignment);
  CHECK(not iter->with_args);
  CHECK(not destructor_called);

  CHECK(not hive.empty());

  count = 0;
  for (auto& _ : hive) {
    ++count;
  }
  CHECK(count == 1);

  hive.clear();
  CHECK(hive.empty());
  CHECK(destructor_called);

  count = 0;
  for (auto& _ : hive) {
    ++count;
  }
  CHECK(count == 0);
}

TEST_CASE("Contained object lifetimes") {}

TEST_CASE("Iterator and reference validity") {}

TEST_CASE("Random erasure") {}

TEST_CASE("Only one object alive per chunk") {}
