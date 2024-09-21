#include <context.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("Logger type erasure") {
  SECTION("Constructor/assignment") {
    struct TestLogger {
      void log(const trait::Logger::LogMessage& message) {
        (void)message;
      }
    };

    TestLogger s;

    trait::Logger erased_logger  = TestLogger {};
    trait::Logger erased_logger2 = s;
    trait::Logger erased_logger3(TestLogger {});
    trait::Logger erased_logger4(s);

    erased_logger = s;
    erased_logger = TestLogger {};
  }

  SECTION("Using member functions") {
    struct S {
      bool& check;
            S(bool& b)
        : check(b) {}

      void log(const trait::Logger::LogMessage& message) {
        CHECK(message.level == trait::Logger::NoiseLevel::noisy);
        CHECK(message.category == trait::Logger::Category::trace);
        CHECK(message.message == "message");
        CHECK(message.location.file_name() == std::source_location::current().file_name());

        check = true;
      }
    };

    bool          test          = false;
    trait::Logger erased_logger = S { test };

    erased_logger.log(trait::Logger::NoiseLevel::noisy, trait::Logger::Category::trace, "message");
    CHECK(test);
  }
}

struct TestAllocator {
  size_t& allocation_pseudo_value_counter;
  size_t& last_allocate_count;

  size_t& last_deallocate_count;
  size_t& last_deallocate_pointer;

  size_t& last_construct_count;
  size_t& last_construct_pointer;

  size_t& last_deconstruct_count;
  size_t& last_deconstruct_pointer;

  static size_t& get_ref() {
    static size_t value {};
    return value;
  }

  TestAllocator()
    : TestAllocator(get_ref(), get_ref(), get_ref(), get_ref(), get_ref(), get_ref(), get_ref(), get_ref()) {}

  TestAllocator(size_t& a, size_t& b, size_t& c, size_t& d, size_t& e, size_t& f, size_t& g, size_t& h)
    : allocation_pseudo_value_counter(a)
    , last_allocate_count(b)
    , last_deallocate_count(c)
    , last_deallocate_pointer(d)
    , last_construct_count(e)
    , last_construct_pointer(f)
    , last_deconstruct_count(g)
    , last_deconstruct_pointer(h) {}

  std::byte* allocate(const size_t alignment, const size_t total_size) {
    auto* pointer = new std::byte[total_size];
    allocation_pseudo_value_counter = reinterpret_cast<size_t>(pointer);
    last_allocate_count = total_size;
    return pointer;
  }

  void deallocate(std::byte* const pointer, const size_t bytes) {
    last_deallocate_count = bytes;
    last_deallocate_pointer = reinterpret_cast<size_t>(pointer);
    delete[] pointer;
  }

  template<typename Type>
  void construct(this auto&& self, [[maybe_unused]] const Type* pointer, [[maybe_unused]] const size_t object_count) {
    self.last_construct_count   = object_count;
    self.last_construct_pointer = pointer;
  }

  template<typename Type>
  void destroy(this auto&& self, [[maybe_unused]] const Type* pointer, [[maybe_unused]] const size_t object_count) {
    self.last_deconstruct_count   = object_count;
    self.last_deconstruct_pointer = pointer;
  }
};

TEST_CASE("Allocator type erasure") {
  SECTION("Constructor/assignment") {
    TestAllocator s;

    trait::Allocator erased_allocator  = TestAllocator {};
    trait::Allocator erased_allocator2 = s;
    trait::Allocator erased_allocator3(TestAllocator {});
    trait::Allocator erased_allocator4(s);

    erased_allocator3 = s;
    erased_allocator3 = TestAllocator {};
  }

  //! @FIXME gotta figure out type-erased allocator interface to handle this
  SECTION("Using member functions") {
    size_t allocation_pseudo_value_counter {};
    size_t last_allocate_count {};
    size_t last_deallocate_count {};
    size_t last_deallocate_pointer {};
    size_t last_construct_count {};
    size_t last_construct_pointer {};
    size_t last_deconstruct_count {};
    size_t last_deconstruct_pointer {};

    trait::Allocator erased_allocator
      = TestAllocator { allocation_pseudo_value_counter, last_allocate_count,     last_deallocate_count,
                        last_deallocate_pointer,         last_construct_count,    last_construct_pointer,
                        last_deconstruct_count,          last_deconstruct_pointer };

    CHECK(last_allocate_count == 0);
    CHECK(last_deallocate_count == 0);
    CHECK(last_deallocate_pointer == 0);
    CHECK(last_construct_count == 0);
    CHECK(last_construct_pointer == 0);
    CHECK(last_deconstruct_count == 0);
    CHECK(last_deconstruct_pointer == 0);

    auto* const first_allocate = erased_allocator.allocate<int>(1);

    CHECK(allocation_pseudo_value_counter == reinterpret_cast<size_t>(first_allocate));
    CHECK(last_allocate_count == 1 * sizeof(int));
    CHECK(last_deallocate_count == 0);
    CHECK(last_deallocate_pointer == 0);
    CHECK(last_construct_count == 0);
    CHECK(last_construct_pointer == 0);
    CHECK(last_deconstruct_count == 0);
    CHECK(last_deconstruct_pointer == 0);

    erased_allocator.deallocate(first_allocate, 1);

    CHECK(allocation_pseudo_value_counter == reinterpret_cast<size_t>(first_allocate));
    CHECK(last_allocate_count == 1 * sizeof(int));
    CHECK(last_deallocate_count == 1 * sizeof(int));
    CHECK(last_deallocate_pointer == reinterpret_cast<size_t>(first_allocate));
    CHECK(last_construct_count == 0);
    CHECK(last_construct_pointer == 0);
    CHECK(last_deconstruct_count == 0);
    CHECK(last_deconstruct_pointer == 0);

  }
}

TEST_CASE("Error contracts type erasure") {}
