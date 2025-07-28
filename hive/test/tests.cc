#include <hive.hh>

#include <catch2/catch_all.hpp>

#include <optional>
#include <set>

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
  SECTION("Lifetimes and observable state") {
    Hive<RAIITest> hive;

    CHECK(hive.empty());
    CHECK(hive.size() == 0);
    CHECK(hive.capacity() == 0);

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
    CHECK(hive.size() == 1);
    CHECK(hive.capacity() == 10);

    count = 0;
    for (auto& _ : hive) {
      ++count;
    }
    CHECK(count == 1);

    hive.clear();
    CHECK(hive.empty());
    CHECK(hive.size() == 0);
    CHECK(hive.capacity() == 0);
    CHECK(destructor_called);

    count = 0;
    for (auto& _ : hive) {
      ++count;
    }
    CHECK(count == 0);
  }

  SECTION("Element reuse") {
    Hive<RAIITest> hive;

    auto iter1 = hive.emplace();
    auto iter2 = hive.emplace();
    CHECK(hive.size() == 2);
    CHECK(hive.capacity() == 10);

    auto* ptr1 = &*iter1;
    auto* ptr2 = &*iter2;

    CHECK(ptr1 != ptr2);

    SECTION("First element") {
      hive.erase(iter1);
      auto new_iter = hive.emplace();
      CHECK(hive.size() == 2);
      CHECK(hive.capacity() == 10);

      CHECK(ptr1 == &*new_iter);
    }

    SECTION("Later element") {
      auto iter3 = hive.emplace();
      CHECK(hive.size() == 3);
      CHECK(hive.capacity() == 10);
      auto* ptr3 = &*iter3;

      CHECK(ptr2 != ptr3);

      hive.erase(iter2);
      auto new_iter = hive.emplace();
      CHECK(hive.size() == 3);
      CHECK(hive.capacity() == 10);

      CHECK(ptr2 == &*new_iter);
    }
  }

  SECTION("handling various empty regions") {
    Hive<RAIITest> hive;

    auto iter1 = hive.emplace();
    auto iter2 = hive.emplace();
    auto iter3 = hive.emplace();
    CHECK(hive.size() == 3);
    CHECK(hive.capacity() == 10);

    SECTION("Empty region after erased point") {
      auto ptr3 = &*iter3;

      hive.erase(iter3);
      auto new_iter = hive.emplace();
      CHECK(hive.size() == 3);
      CHECK(hive.capacity() == 10);
      auto new_ptr = &*new_iter;
      CHECK(ptr3 == new_ptr);
    }

    SECTION("Empty region before erased point") {
      auto ptr1 = &*iter1;

      hive.erase(iter1);
      auto new_iter = hive.emplace();
      CHECK(hive.size() == 3);
      CHECK(hive.capacity() == 10);
      auto new_ptr = &*new_iter;
      CHECK(ptr1 == new_ptr);
    }

    SECTION("Empty region before and after erased point") {
      hive.emplace(); // prevent block from being deleted

      auto* ptr1 = &*iter1;
      auto* ptr2 = &*iter2;
      auto* ptr3 = &*iter3;

      hive.erase(iter1);
      hive.erase(iter3);
      hive.erase(iter2);

      auto new_iter1 = hive.emplace();
      auto new_iter2 = hive.emplace();
      auto new_iter3 = hive.emplace();
      CHECK(hive.size() == 4);
      CHECK(hive.capacity() == 10);
      auto* new_ptr1 = &*new_iter1;
      auto* new_ptr2 = &*new_iter2;
      auto* new_ptr3 = &*new_iter3;

      CHECK(ptr1 == new_ptr1);
      CHECK(ptr2 == new_ptr2);
      CHECK(ptr3 == new_ptr3);
    }
  }

  SECTION("Standard algorithms and containers") {
    Hive<int> hive;

    hive.emplace(42);
    hive.emplace(1138);

    std::set<int> set;
    set.insert_range(hive);
    CHECK(set.size() == 2);
    CHECK(hive.capacity() == 10);
    CHECK(set.contains(42));
    CHECK(set.contains(1138));

    auto filtered = std::ranges::filter_view(hive, [](const int i) {
      return i > 100;
    });
    std::set<int> filtered_set;
    filtered_set.insert_range(filtered);
    CHECK(filtered_set.size() == 1);
    CHECK(hive.capacity() == 10);
    CHECK(filtered_set.contains(1138));
  }
}

TEST_CASE("Contained object lifetimes") {}

TEST_CASE("Iterator and reference validity") {}

TEST_CASE("Random erasure") {}

TEST_CASE("Only one object alive per chunk") {}

TEST_CASE("Evaluate each member function") {
  SECTION("emplace") {}
  SECTION("insert") {
    SECTION("value copy") {}
    SECTION("value move") {}
    SECTION("range") {}
  }
  SECTION("erase") {
    SECTION("single element") {}
    SECTION("range") {}
  }
  SECTION("splice") {}
  SECTION("empty") {}
  SECTION("size") {}
  SECTION("clear") {}
  SECTION("begin") {}
  SECTION("end") {}
}

TEST_CASE("Hive formatter") {
  //Hive<int> hive;
  //CHECK(std::format("{}", hive) == "[ ]");
}
