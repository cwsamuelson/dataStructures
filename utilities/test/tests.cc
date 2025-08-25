//#include <memory.hh>
#include <file_io/file_handling.hh>
#include <static_loops.hh>

#include <catch2/catch_all.hpp>

#include <memory>

using namespace flp;

/*TEST_CASE("`utilities`: memory") {
  GIVEN("`boost::shared_ptr`") {
    auto pointer = boost::make_shared<int>(42);

    WHEN("Using the pointer is used with a std::shared_ptr interface") {
      auto sptr = make_shared_ptr(pointer);

      THEN("The managed memory is managed correctly") {
        CHECK(pointer.use_count() == 2);
        CHECK(sptr.use_count() == 2);
      }
    }
  }

  GIVEN("`std::shared_ptr`") {
    auto pointer = std::make_shared<int>(42);

    WHEN("Using the pointer is used with a boost::shared_ptr interface") {
      auto bptr = make_shared_ptr(pointer);

      THEN("The managed memory is managed correctly") {
        CHECK(pointer.use_count() == 2);
        CHECK(bptr.use_count() == 2);
      }
    }
  }
}*/

TEST_CASE("`utilities`: static_loops") {
}

TEST_CASE("`utilities`: file reading") {
}
