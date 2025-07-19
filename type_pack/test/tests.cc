#include <type_pack.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`TypePack` equality") {
  SECTION("Value equality") {
    STATIC_CHECK(TypePack<> {} == TypePack<> {});
    STATIC_CHECK(TypePack<int> {} == TypePack<int> {});
    STATIC_CHECK(TypePack<float> {} != TypePack<int> {});
    STATIC_CHECK(TypePack<int, float> {} == TypePack<int, float> {});
    STATIC_CHECK(TypePack<float, int> {} != TypePack<int, float> {});
    STATIC_CHECK(TypePack<> {} != TypePack<int, float> {});
    STATIC_CHECK(TypePack<> {} != TypePack<float> {});
  }

  SECTION("Type-oriented") {
    STATIC_CHECK(TypePack<>::Equal<>);
    STATIC_CHECK(TypePack<int>::Equal<int>);
    STATIC_CHECK(not TypePack<float>::Equal<int>);
    STATIC_CHECK(TypePack<int, float>::Equal<int, float>);
    STATIC_CHECK(not TypePack<float, int>::Equal<int, float>);
    STATIC_CHECK(not TypePack<>::Equal<int, float>);
    STATIC_CHECK(not TypePack<>::Equal<float>);
  }
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
  STATIC_CHECK(typename TypePack<>::Prepend<int> {} == TypePack<int> {});
  STATIC_CHECK(typename TypePack<int>::Prepend<float> {} == TypePack<float, int> {});
  STATIC_CHECK(typename TypePack<float, int>::Prepend<unsigned int> {} == TypePack<unsigned int, float, int> {});
}

TEST_CASE("`TypePack` Append") {
  STATIC_CHECK(typename TypePack<>::Append<int> {} == TypePack<int> {});
  STATIC_CHECK(typename TypePack<int>::Append<float> {} == TypePack<int, float> {});
  STATIC_CHECK(typename TypePack<float, int>::Append<unsigned int> {} == TypePack<float, int, unsigned int> {});
}

template<typename Type>
struct TruePredicate {
  static constexpr bool value = true;
};

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
  STATIC_CHECK(TypePack<>::Transform<Transformer> {} == TypePack<> {});
  STATIC_CHECK(TypePack<float>::Transform<Transformer> {} == TypePack<int> {});
  STATIC_CHECK(TypePack<float, unsigned int>::Transform<Transformer> {} == TypePack<int, int> {});
}

TEST_CASE("`TypePack` Unique") {
  STATIC_CHECK(TypePack<>::Unique {} == TypePack<> {});
  STATIC_CHECK(TypePack<int>::Unique {} == TypePack<int> {});
  STATIC_CHECK(TypePack<int, float>::Unique {} == TypePack<int, float> {});
  STATIC_CHECK(TypePack<int, int>::Unique {} == TypePack<int> {});
}

template<typename Type>
struct IsInt {
  static constexpr bool value = std::same_as<Type, int>;
};

template<typename Type>
struct IsFloat {
  static constexpr bool value = std::same_as<Type, float>;
};

TEST_CASE("`TypePack` Filter") {
  STATIC_CHECK(TypePack<>::Filter<TruePredicate> {} == TypePack<> {});
  STATIC_CHECK(TypePack<>::Filter<FalsePredicate> {} == TypePack<> {});

  STATIC_CHECK(TypePack<int>::Filter<TruePredicate> {} == TypePack<int> {});
  STATIC_CHECK(TypePack<int>::Filter<FalsePredicate> {} == TypePack<> {});

  STATIC_CHECK(TypePack<int, float>::Filter<TruePredicate> {} == TypePack<int, float> {});
  STATIC_CHECK(TypePack<int, float>::Filter<FalsePredicate> {} == TypePack<> {});

  STATIC_CHECK(TypePack<int, float>::Filter<IsInt> {} == TypePack<int> {});
  STATIC_CHECK(TypePack<int, float>::Filter<IsFloat> {} == TypePack<float> {});
}

TEST_CASE("`TypePack` LeftShift") {
  STATIC_CHECK(TypePack<>::LeftShift {} == TypePack<> {});
  STATIC_CHECK(TypePack<signed int>::LeftShift {} == TypePack<signed int> {});
  STATIC_CHECK(TypePack<unsigned int>::LeftShift {} == TypePack<unsigned int> {});
  STATIC_CHECK(TypePack<float>::LeftShift {} == TypePack<float> {});
  STATIC_CHECK(TypePack<signed int, float>::LeftShift {} == TypePack<float, signed int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::LeftShift {} == TypePack<signed int, float, unsigned int> {});
}

TEST_CASE("`TypePack` RightShift") {
  STATIC_CHECK(TypePack<>::LeftShift {} == TypePack<> {});
  STATIC_CHECK(TypePack<signed int>::LeftShift {} == TypePack<signed int> {});
  STATIC_CHECK(TypePack<unsigned int>::LeftShift {} == TypePack<unsigned int> {});
  STATIC_CHECK(TypePack<float>::LeftShift {} == TypePack<float> {});
  STATIC_CHECK(TypePack<signed int, float>::LeftShift {} == TypePack<float, signed int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::LeftShift {} == TypePack<signed int, float, unsigned int> {});
}

TEST_CASE("`TypePack` Take") {
  STATIC_CHECK(TypePack<>::Take<0> {} == TypePack<> {});
  STATIC_CHECK(TypePack<unsigned int>::Take<0> {} == TypePack<> {});
  STATIC_CHECK(TypePack<unsigned int>::Take<1> {} == TypePack<unsigned int> {});
  STATIC_CHECK(TypePack<unsigned int, float>::Take<0> {} == TypePack<> {});
  STATIC_CHECK(TypePack<unsigned int, float>::Take<1> {} == TypePack<unsigned int> {});
  STATIC_CHECK(TypePack<unsigned int, float>::Take<2> {} == TypePack<unsigned int, float> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Take<0> {} == TypePack<> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Take<1> {} == TypePack<unsigned int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Take<2> {} == TypePack<unsigned int, signed int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Take<3> {} == TypePack<unsigned int, signed int, float> {});
}

TEST_CASE("`TypePack` Drop") {
  STATIC_CHECK(TypePack<>::Drop<0> {} == TypePack<> {});
  STATIC_CHECK(TypePack<unsigned int>::Drop<0> {} == TypePack<unsigned int> {});
  STATIC_CHECK(TypePack<unsigned int>::Drop<1> {} == TypePack<> {});
  STATIC_CHECK(TypePack<unsigned int, signed int>::Drop<0> {} == TypePack<unsigned int, signed int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int>::Drop<1> {} == TypePack<signed int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int>::Drop<2> {} == TypePack<> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Drop<0> {} == TypePack<unsigned int, signed int, float> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Drop<1> {} == TypePack<signed int, float> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Drop<2> {} == TypePack<float> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Drop<3> {} == TypePack<> {});
}

TEST_CASE("`TypePack` Reverse") {
  STATIC_CHECK(TypePack<>::Reverse {} == TypePack<> {});
  STATIC_CHECK(TypePack<signed int>::Reverse {} == TypePack<signed int> {});
  STATIC_CHECK(TypePack<signed int, float>::Reverse {} == TypePack<float, signed int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float>::Reverse {} == TypePack<float, signed int, unsigned int> {});
  STATIC_CHECK(TypePack<unsigned int, signed int, float, double>::Reverse {}
               == TypePack<double, float, signed int, unsigned int> {});
}

template<size_t>
struct Foo {};

TEST_CASE("`TypePack` SubPack") {
  STATIC_CHECK(TypePack<Foo<0>, Foo<1>, Foo<2>, Foo<3>>::SubPack<0, 4>{} == TypePack<Foo<0>, Foo<1>, Foo<2>, Foo<3>>{});

  STATIC_CHECK(TypePack<Foo<0>, Foo<1>, Foo<2>, Foo<3>>::SubPack<1, 3>{} == TypePack<Foo<1>, Foo<2>>{});
  STATIC_CHECK(TypePack<Foo<0>, Foo<1>, Foo<2>, Foo<3>>::SubPack<1, 2>{} == TypePack<Foo<1>>{});
}
