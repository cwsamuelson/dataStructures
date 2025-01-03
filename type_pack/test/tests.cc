#include <type_pack.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`TypePack` equality") {
  STATIC_CHECK(TypePack<> {} == TypePack<> {});
  STATIC_CHECK(TypePack<int> {} == TypePack<int> {});
  STATIC_CHECK(TypePack<float> {} != TypePack<int> {});
  STATIC_CHECK(TypePack<int, float> {} == TypePack<int, float> {});
  STATIC_CHECK(TypePack<float, int> {} != TypePack<int, float> {});
  STATIC_CHECK(TypePack<> {} != TypePack<int, float> {});
  STATIC_CHECK(TypePack<> {} != TypePack<float> {});
}

TEST_CASE("`TypePack` Size") {
  STATIC_CHECK(TypePack<>::Size == 0);
  STATIC_CHECK(TypePack<int>::Size == 1);
  STATIC_CHECK(TypePack<float>::Size == 1);
  STATIC_CHECK(TypePack<int, float>::Size == 2);
}

TEST_CASE("`TypePack` Empty") {
  STATIC_CHECK(TypePack<>::Empty);
  STATIC_CHECK(not TypePack<int>::Empty);
  STATIC_CHECK(not TypePack<float>::Empty);
  STATIC_CHECK(not TypePack<int, float>::Empty);
}

TEST_CASE("`TypePack` Front") {
  STATIC_CHECK(std::is_void_v<typename TypePack<>::Front>);
  STATIC_CHECK(std::same_as<typename TypePack<int>::Front, int>);
  STATIC_CHECK(std::same_as<typename TypePack<int, float>::Front, int>);
  STATIC_CHECK(std::same_as<typename TypePack<float, int>::Front, float>);
}

TEST_CASE("`TypePack` Back") {
  STATIC_CHECK(std::is_void_v<typename TypePack<>::Back>);
  STATIC_CHECK(std::same_as<typename TypePack<int>::Back, int>);
  STATIC_CHECK(std::same_as<typename TypePack<int, float>::Back, float>);
  STATIC_CHECK(std::same_as<typename TypePack<float, int>::Back, int>);
}

TEST_CASE("`TypePack` Prepend") {
  STATIC_CHECK(typename TypePack<>::Prepend<int>{} == TypePack<int>{});
  STATIC_CHECK(typename TypePack<int>::Prepend<float>{} == TypePack<float, int>{});
  STATIC_CHECK(typename TypePack<float, int>::Prepend<unsigned int>{} == TypePack<unsigned int, float, int>{});
}

TEST_CASE("`TypePack` Append") {
  STATIC_CHECK(typename TypePack<>::Append<int>{} == TypePack<int>{});
  STATIC_CHECK(typename TypePack<int>::Append<float>{} == TypePack<int, float>{});
  STATIC_CHECK(typename TypePack<float, int>::Append<unsigned int>{} == TypePack<float, int, unsigned int>{});
}

template<typename Type>
struct FalsePredicate {
  static constexpr bool value = false;
};

template<typename Type>
struct TestPredicate {
  static constexpr bool value = std::is_same_v<Type, int>;
};

TEST_CASE("`TypePack` AnyOf") {
  STATIC_CHECK(not TypePack<>::AnyOf<FalsePredicate>);
  STATIC_CHECK(not TypePack<>::AnyOf<TestPredicate>);
  STATIC_CHECK(TypePack<int>::AnyOf<TestPredicate>);
  STATIC_CHECK(TypePack<int, float>::AnyOf<TestPredicate>);
  STATIC_CHECK(not TypePack<unsigned int, float>::AnyOf<TestPredicate>);
}

TEST_CASE("`TypePack` AllOf") {
  STATIC_CHECK(TypePack<>::AllOf<FalsePredicate>);
  STATIC_CHECK(TypePack<>::AllOf<TestPredicate>);
  STATIC_CHECK(TypePack<int>::AllOf<TestPredicate>);
  STATIC_CHECK(not TypePack<int, float>::AllOf<TestPredicate>);
  STATIC_CHECK(not TypePack<unsigned int, float>::AllOf<TestPredicate>);
  STATIC_CHECK(TypePack<int, int, int>::AllOf<TestPredicate>);
}

TEST_CASE("`TypePack` Rebind") {
  STATIC_CHECK(std::same_as<TypePack<>::Rebind<std::tuple>, std::tuple<>>);
  STATIC_CHECK(std::same_as<TypePack<int>::Rebind<std::tuple>, std::tuple<int>>);
  STATIC_CHECK(std::same_as<TypePack<int, float>::Rebind<std::tuple>, std::tuple<int, float>>);
}

template<typename Type>
struct Transformer {
  using type = int;
};

TEST_CASE("`TypePack` Transform") {
  STATIC_CHECK(TypePack<>::Transform<Transformer>{} == TypePack<>{});
  STATIC_CHECK(TypePack<float>::Transform<Transformer>{} == TypePack<int>{});
  STATIC_CHECK(TypePack<float, unsigned int>::Transform<Transformer>{} == TypePack<int, int>{});
}

TEST_CASE("`TypePack` Unique") {
  STATIC_CHECK(TypePack<>::Unique{} == TypePack<>{});
  STATIC_CHECK(TypePack<int>::Unique{} == TypePack<int>{});
  STATIC_CHECK(TypePack<int, float>::Unique{} == TypePack<int, float>{});
  STATIC_CHECK(TypePack<int, int>::Unique{} == TypePack<int>{});
}

