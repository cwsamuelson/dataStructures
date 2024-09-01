#include <catch2/catch_all.hpp>

#include <aligned_buffer.hh>

using namespace flp;

struct S {
  size_t storage[500];
};

// this struct should maybe be put into a shared location?
struct RAIISignaler {
  bool parameterized1_constructor = false;
  bool parameterized2_constructor = false;
  bool default_constructor = false;
  bool copy_constructor = false;
  bool move_constructor = false;
  bool copy_assignment = false;
  bool move_assignment = false;
  std::shared_ptr<bool> destructed = std::make_shared<bool>(false); // probably should be external?

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
    *destructed = true;
  }

  [[nodiscard]]
  bool constructed() const noexcept {
    return parameterized1_constructor
        or parameterized2_constructor
        or default_constructor
        or copy_constructor
        or move_constructor;
  }
};

TEST_CASE("Aligned buffer alignment and size") {
  STATIC_CHECK(alignof(AlignedBuffer<size_t>) == alignof(size_t));
  STATIC_CHECK(sizeof(AlignedBuffer<size_t>) == sizeof(size_t));

  STATIC_CHECK(alignof(AlignedBuffer<S>) == alignof(S));
  STATIC_CHECK(sizeof(AlignedBuffer<S>) == sizeof(S));
}

TEST_CASE("Aligned buffer construct/destruct") {
  AlignedBuffer<RAIISignaler> buffer;

  // technically UB, since the signaler lifetime hasn't started yet..
  // but this is what we want to be able to say..
  //CHECK(not buffer.get().constructed());
  buffer.construct();

  auto destructed = buffer.get().destructed;
  CHECK(buffer.get().constructed());
  CHECK(not *destructed);

  buffer.destruct();
  CHECK(*destructed);
}

