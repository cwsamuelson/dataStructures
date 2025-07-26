#include <hive.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct RAIITest {
  bool default_contsructor = false;
  bool copy_constructor = false;
  bool move_constructor = false;
  bool copy_assignment = false;
  bool move_assignment = false;
  bool destructor = false;
  bool with_args = false;

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
    destructor = true;
  }
};

TEST_CASE("Hive") {
  Hive<RAIITest> hive;

  CHECK(hive.empty());

  const RAIITest new_value;
  const auto iter = hive.insert(new_value);
  CHECK(iter->copy_constructor);
  CHECK(not iter->default_contsructor);
  CHECK(not iter->move_constructor);
  CHECK(not iter->copy_assignment);
  CHECK(not iter->move_assignment);
  CHECK(not iter->destructor);
  CHECK(not iter->with_args);

  CHECK(not hive.empty());

  hive.clear();
  CHECK(hive.empty());
}

TEST_CASE("Contained object lifetimes") {}

TEST_CASE("Iterator and reference validity") {}

TEST_CASE("Random erasure") {}

TEST_CASE("Only one object alive per chunk") {}
