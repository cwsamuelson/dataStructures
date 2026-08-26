#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/catch.h>

#include <core/vector.hh>

#include <memory>

using namespace flp;

// this struct should maybe be put into a shared location?
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

TEST_CASE("`Vector`::Lifetime management") {
  SECTION("`push_back` calls copy constructor") {
    Vector<RAIISignaler> vector;

    RAIISignaler original;
    vector.push_back(original);

    CHECK(vector[0].copy_constructor);
  }

  SECTION("`emplace_back` calls the appropriate constructor") {
    Vector<RAIISignaler> vector;

    CHECK(vector.empty());
    CHECK(vector.size() == 0);
    CHECK_THROWS(vector[0]);

    vector.emplace_back();
    vector.emplace_back(42);
    vector.emplace_back(42, 1138);

    CHECK(not vector.empty());
    CHECK(vector.size() == 3);

    CHECK(vector[0].default_constructor);
    CHECK(vector[1].parameterized1_constructor);
    CHECK(vector[2].parameterized2_constructor);
  }

  SECTION("Destructor is run on pop_back") {
    Vector<RAIISignaler> vector;

    CHECK(vector.size() == 0);
    CHECK(vector.empty());

    vector.emplace_back();

    auto dtor_signal = vector.back().destructor;
    CHECK(not *dtor_signal);

    vector.pop_back();
    CHECK(*dtor_signal);

    CHECK(vector.size() == 0);
    CHECK(vector.empty());
  }
}

SCENARIO("`Vector` Using emplace_back to create new elements") {
}

TEST_CASE("`Vector` resizing") {
  SECTION("Initialize with a capacity") {
    Vector<RAIISignaler> vector(12);

    CHECK(vector.empty());
    CHECK(vector.capacity() >= 12);
  }

  SECTION("Size increases as elements are added") {
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

    rc::prop("lifetime cycle", [](const std::vector<size_t>& values) {
      Vector<RAIISignaler> vector;
      RC_ASSERT(vector.size() == 0);
      RC_ASSERT(vector.empty());

      for (size_t count{}; const auto value : values) {
        vector.emplace_back(value);
        ++count;

        RC_ASSERT(not vector.empty());
        RC_ASSERT(vector.size() == count);
        RC_ASSERT(vector.capacity() >= vector.size());
        RC_ASSERT(vector.back().parameterized1_constructor);
      }

      const auto cap = vector.capacity();
      for (size_t count = vector.size(); not vector.empty();) {
        auto dtor_signal = vector.back().destructor;
        RC_ASSERT(not *dtor_signal);

        vector.pop_back();
        --count;

        RC_ASSERT(*dtor_signal);
        RC_ASSERT(vector.size() == count);
        RC_ASSERT(vector.capacity() == cap);
      }

      RC_ASSERT(vector.empty());
      RC_ASSERT(vector.size() == 0);
    });
  }

  // using uint16_t so as to not have unnecessarily gigantic allocations...
  rc::prop("Resizing increases capacity", [](const uint16_t new_size) {
    Vector<RAIISignaler> vector;

    vector.resize(new_size);

    RC_ASSERT(vector.size() == new_size);
    RC_ASSERT(vector.capacity() >= new_size);

    for (const auto& signaler : vector) {
      RC_ASSERT(signaler.default_constructor);
    }
  });

  SECTION("Shrinking doesn't affect capacity") {
    Vector<RAIISignaler> vector;
    constexpr size_t initial_size = 12;

    while (vector.size() < initial_size) {
      vector.emplace_back();
    }

    const auto initial_capacity = vector.capacity();

    CHECK(vector.size() == initial_size);

    constexpr size_t target_size = initial_size / 2;
    REQUIRE(target_size < initial_size);

    vector.resize(target_size);
    CHECK(vector.size() == target_size);
    CHECK(vector.capacity() == initial_capacity);
  }

  SECTION("Reserving will increase capacity") {
    Vector<RAIISignaler> vector;
    CHECK(vector.empty());

    const auto initial_capacity = vector.capacity();
    const auto target_capacity = initial_capacity + 100;

    vector.reserve(target_capacity);
    CHECK(vector.empty());
    CHECK(vector.capacity() >= target_capacity);
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

TEST_CASE("`Vector` iteration") {
  rc::prop("range-based for loops", [](const std::vector<size_t>& values) {
    const Vector<RAIISignaler> vector(values.begin(), values.end());

    RC_ASSERT(vector.size() == values.size());

    for (const auto& value : vector) {}
  });

  SECTION("Vectors can be iterated like arrays") {
  }

  SECTION("using begin/end iterators") {
  }
}

TEST_CASE("`Vector` constructors") {
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

TEST_CASE("`Vector` holding type without default constructor") {
  Vector<NoDefault> vector;
  vector.emplace_back(42);

  const NoDefault value(1138);
  vector.push_back(value);

  CHECK(vector.size() == 2);
  CHECK(vector.capacity() >= 2);

  vector.reserve(100);
  CHECK(vector.capacity() >= 100);
}

TEST_CASE("`Vector`::Accessors") {
  // at
  // []

  rc::prop("front/back/begin", [](const int value) {
    Vector<int> vector;
    vector.push_back(value);

    RC_ASSERT(vector.front() == value);
    RC_ASSERT(vector.back() == value);
    RC_ASSERT(*vector.begin() == value);
  });

  SECTION("from pre-filled containers") {
    SECTION("resize()") {
      // at
      // []

      rc::prop("front/back/begin", [](const uint16_t value) {
        const auto new_size = *rc::gen::nonZero<uint16_t>();

        Vector<uint16_t> vector;
        vector.resize(new_size, value);

        RC_ASSERT(vector.front() == value);
        RC_ASSERT(vector.back() == value);
        RC_ASSERT(*vector.begin() == value);
      });
    }

    SECTION("from std::vector") {
      // at
      // []

      rc::prop("front/back/begin", [] {
        const auto initial_values = *rc::gen::nonEmpty(
          rc::gen::container<std::vector<size_t>>(
            rc::gen::arbitrary<size_t>()
          )
        );

        const Vector<size_t> vector(initial_values.begin(), initial_values.end());

        RC_ASSERT(vector.front() == initial_values.front());
        RC_ASSERT(vector.back() == initial_values.back());
        RC_ASSERT(*vector.begin() == *initial_values.begin());
      });
    }
  }
}
