#include <type_pack.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("`TypePack` equality") {
  STATIC_CHECK(TypePack<> {} == TypePack<> {});
  STATIC_CHECK(TypePack<int> {} == TypePack<int> {});
  STATIC_CHECK(TypePack<float> {} != TypePack<int> {});
  STATIC_CHECK(TypePack<int, float> {} == TypePack<int, float> {});
  STATIC_CHECK(TypePack<float, int> {} != TypePack<int, float> {});
  STATIC_CHECK(TypePack<> {} != TypePack<int, float> {});
  STATIC_CHECK(TypePack<> {} != TypePack<float> {});
}

TEST_CASE("`TypePack` transform") {}
