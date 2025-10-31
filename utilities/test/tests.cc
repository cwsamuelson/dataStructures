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

// std::string read_text(const std::filesystem::path& file_path);
// std::vector<std::byte> read_binary(const std::filesystem::path& file_path);
// std::generator<std::string> read_lines(const std::filesystem::path& file_path);
TEST_CASE("`utilities`: file reading") {
  const auto file_name = "input_file.txt";

  SECTION("Throws with insufficient buffer") {
    std::vector<std::byte> buffer;
    const auto buffer_size = GENERATE(range(0, 37));
    buffer.resize(buffer_size);
    CHECK_THROWS(read_file(file_name, buffer));
  }

  // sounds trivial, but valuable to counter the previous block
  SECTION("No throw with sufficiently sized buffer") {
    std::vector<std::byte> buffer;
    const auto buffer_size = GENERATE(range(38, 100));
    buffer.resize(buffer_size);
    CHECK_NOTHROW(read_file(file_name, buffer));
  }

  SECTION("The entire file is read") {
    const auto buffer = read_file(file_name);
    CHECK(buffer.size() == 38);
    // check content
  }

  SECTION("The correct chunk size is always returned") {
    const auto chunk_size = GENERATE(range(1, 38));
    auto chunk_gen = read_chunks(file_name, chunk_size);
    size_t disparity_counter{};
    for (const auto chunk : chunk_gen) {
      CHECK(chunk.size() <= chunk_size);

      if (chunk.size() != chunk_size) {
        ++disparity_counter;
      }
    }
    CHECK(disparity_counter <= 1);
  }
}
