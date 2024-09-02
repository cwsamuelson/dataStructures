#include <matrix.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("using a matrix") {
  SECTION("Dynamic dimensions") {
    Matf<Dynamic, Dynamic> matrix;
    CHECK(matrix.width() == 0);
    CHECK(matrix.height() == 0);

    matrix.resize(5, 5);
    CHECK(matrix.width() == 5);
    CHECK(matrix.height() == 5);

    for (size_t i {}; i < 5; ++i) {
      for (size_t j {}; j < 5; ++j) {
        matrix[i, j] = (i * 5) + j;
      }
    }

    for (size_t i {}; i < 5; ++i) {
      for (size_t j {}; j < 5; ++j) {
        CHECK(matrix[i, j] == (i * 5) + j);
      }
    }
  }

  SECTION("Static dimensions") {
    Matf<5, 5> matrix;
    CHECK(matrix.width() == 5);
    CHECK(matrix.height() == 5);
    // matrix.resize(10, 10);// not a thing

    for (size_t i {}; i < 5; ++i) {
      for (size_t j {}; j < 5; ++j) {
        matrix[i, j] = (i * 5) + j;
      }
    }

    for (size_t i {}; i < 5; ++i) {
      for (size_t j {}; j < 5; ++j) {
        CHECK(matrix[i, j] == (i * 5) + j);
      }
    }
  }
}
