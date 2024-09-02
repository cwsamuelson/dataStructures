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

    matrix[0, 0] = 10;
    CHECK(matrix[0, 0] == 10);
  }

  SECTION("Static dimensions") {
    Matf<5, 5> matrix;
    CHECK(matrix.width() == 5);
    CHECK(matrix.height() == 5);
    // matrix.resize(10, 10);// not a thing
  }

  Matrix<size_t>                         int_mat;
  Matrix<float>                          float_mat;
  Matrix<int, { 5, 5 }, StaticAllocator> s_mat;
  // s_mat.resize(1,1);
  s_mat[0];
  // s_mat[100];

  int_mat.resize(1, 2);

  int_mat[0] = 5;
  int_mat[1] = 5;

  (void)(int_mat[0] * int_mat[1]);
}
