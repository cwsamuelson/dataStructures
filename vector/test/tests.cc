#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>

#include <vector.hh>

#include <memory>

using namespace flp;

struct RAIISignaler {
  bool parameterized1_constructor = false;
  bool parameterized2_constructor = false;
  bool default_constructor = false;
  bool copy_constructor = false;
  bool move_constructor = false;
  bool copy_assignment = false;
  bool move_assignment = false;
  std::shared_ptr<bool> destructor = std::make_shared<bool>(false); // probably should be external?

  RAIISignaler(int)
    : parameterized1_constructor(true)
  {}
  RAIISignaler(int, int)
    : parameterized2_constructor(true)
  {}
  RAIISignaler()
    : default_constructor(true)
  {}
  RAIISignaler(const RAIISignaler&)
    : copy_constructor(true)
  {}
  RAIISignaler(RAIISignaler&&) noexcept
    : move_constructor(true)
  {}
  RAIISignaler& operator=(const RAIISignaler&) {
    copy_assignment = true;
    return *this;
  }
  RAIISignaler& operator=(RAIISignaler&&) noexcept {
    move_assignment = true;
    return *this;
  }
  ~RAIISignaler() {
    *destructor = true;
  }
};

TEST_CASE("Vectors will run constructors/destructors when appropriate") {
  SECTION("Constructor is run on emplace_back call") {
    Vector<RAIISignaler> vector;

    vector.emplace_back();
    vector.emplace_back(42);
    vector.emplace_back(42, 1138);

    CHECK(vector[0].default_constructor);
    CHECK(vector[1].parameterized1_constructor);
    CHECK(vector[2].parameterized2_constructor);
  }

  SECTION("Destructor is run on pop_back") {
    Vector<RAIISignaler> vector;

    vector.emplace_back();

    auto dtor_signal = vector.back().destructor;
    CHECK(not *dtor_signal);
    vector.pop_back();
    CHECK(*dtor_signal);

    CHECK(vector.size() == 0);
    CHECK(vector.empty());
  }
}

SCENARIO("Using emplace_back to create new elements") {
}

TEST_CASE("Vectors can be resized") {
  SECTION("Vector capacity can be initialized") {
    Vector<RAIISignaler> vector(12);

    CHECK(vector.empty());
    CHECK(vector.capacity() >= 12);
  }

  SECTION("Vector size increases with additions") {
    Vector<RAIISignaler> vector;
    CHECK(vector.size() == 0);
    CHECK(vector.empty());

    vector.push_back({});
    CHECK(vector.size() == 1);
    CHECK(not vector.empty());
    CHECK(vector.capacity() >= vector.size());

    vector.emplace_back();
    CHECK(vector.size() == 2);
    CHECK(not vector.empty());
    CHECK(vector.capacity() >= vector.size());

    vector.emplace_back(1);
    CHECK(vector.size() == 3);
    CHECK(not vector.empty());
    CHECK(vector.capacity() >= vector.size());

    vector.pop_back();
    CHECK(vector.size() == 2);
    CHECK(not vector.empty());
    CHECK(vector.capacity() >= vector.size());

    vector.emplace_back(1, 2);
    CHECK(vector.size() == 3);
    CHECK(not vector.empty());
    CHECK(vector.capacity() >= vector.size());
  }

  SECTION("Resizing bigger changes size and capacity") {
  }

  SECTION("Resizing smaller changes size but not capacity") {
  }

  SECTION("Reserving bigger changes capacity but not size") {
  }

  SECTION("Reserving smaller does not change size or capacity") {
    Vector<RAIISignaler> vector(100);
    const auto initial_capacity = vector.capacity();
    CHECK(vector.capacity() >= 100);

    vector.emplace_back();
    CHECK(vector.size() == 1);
    CHECK(not vector.empty());

    vector.reserve(12);
    CHECK(vector.capacity() == initial_capacity);

    CHECK(vector.size() == 1);
    CHECK(not vector.empty());
  }

  SECTION("Capacity increases immediately as size exceeds it") {
    Vector<RAIISignaler> vector;

    while (vector.size() < vector.capacity()) {
      vector.emplace_back();
    }

    CHECK(vector.size() == vector.capacity());

    const auto initial_capacity = vector.capacity();
    vector.emplace_back();
    CHECK(vector.capacity() > initial_capacity);
  }
}

TEST_CASE("Vectors can be iterated across using standard mechanisms") {
  SECTION("Vectors can participate in range-based for loops") {
  }

  SECTION("Vectors can be iterated like arrays") {
  }

  SECTION("Vectors can be iterated by iterators(begin, end)") {
  }
}

TEST_CASE("Constructors") {
  SECTION("Copy list") {
  }
}

struct NoDefault {
  NoDefault() = delete;
  explicit
  NoDefault(int) {}
  NoDefault(const NoDefault&) = default;
  NoDefault(NoDefault&&) = default;
  NoDefault& operator=(const NoDefault&) = default;
  NoDefault& operator=(NoDefault&&) = default;
  ~NoDefault() = default;
};

TEST_CASE("Holding type without default constructor") {
  Vector<NoDefault> vector;
  vector.emplace_back(42);

  const NoDefault value(1138);
  vector.push_back(value);
}

