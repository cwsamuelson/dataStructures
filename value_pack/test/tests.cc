#include <value_pack.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Value Pack") {
  STATIC_CHECK(ValuePack<> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<0> {} == ValuePack<0> {});
  STATIC_CHECK(ValuePack<0, 1> {} == ValuePack<0, 1> {});

  STATIC_CHECK(ValuePack<0, 1> {} != ValuePack<1> {});
  STATIC_CHECK(ValuePack<0, 1> {} != ValuePack<1, 0> {});

  STATIC_CHECK(ValuePack<>::Prepend<0> {} == ValuePack<0> {});
  STATIC_CHECK(ValuePack<>::Append<0> {} == ValuePack<0> {});

  STATIC_CHECK(ValuePack<1>::Prepend<0> {} == ValuePack<0, 1> {});
  STATIC_CHECK(ValuePack<0>::Append<1> {} == ValuePack<0, 1> {});

  STATIC_CHECK(ValuePack<1, 2>::Prepend<0> {} == ValuePack<0, 1, 2> {});
  STATIC_CHECK(ValuePack<0, 1>::Append<2> {} == ValuePack<0, 1, 2> {});
}

template<auto Value>
struct Identity {
  static constexpr auto value = Value;
};

TEST_CASE("ValuePack Equality") {
  STATIC_CHECK(ValuePack<> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<-1138> {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<4.2F> {} != ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F> {} == ValuePack<-1138, 4.2F> {});
  STATIC_CHECK(ValuePack<4.2F, -1138> {} != ValuePack<-1138, 4.2F> {});
  STATIC_CHECK(ValuePack<> {} != ValuePack<-1138, 4.2F> {});
  STATIC_CHECK(ValuePack<> {} != ValuePack<4.2F> {});
}

TEST_CASE("ValuePack Size") {
  STATIC_CHECK(ValuePack<>::Size == 0);
  STATIC_CHECK(ValuePack<-1138>::Size == 1);
  STATIC_CHECK(ValuePack<4.2F>::Size == 1);
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Size == 2);
}

TEST_CASE("ValuePack Empty") {
  STATIC_CHECK(ValuePack<>::Empty);
  STATIC_CHECK(not ValuePack<-1138>::Empty);
  STATIC_CHECK(not ValuePack<4.2F>::Empty);
  STATIC_CHECK(not ValuePack<-1138, 4.2F>::Empty);
}

TEST_CASE("ValuePack Contains") {
}

TEST_CASE("ValuePack Front") {
  // STATIC_CHECK(typename ValuePack<>::Front); // doesn't compile
  STATIC_CHECK(ValuePack<-1138>::Front<> == -1138);
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Front<> == -1138);
  STATIC_CHECK(ValuePack<4.2F, -1138>::Front<> == 4.2F);
}

TEST_CASE("ValuePack Back") {
  // STATIC_CHECK(std::is_void_v<typename ValuePack<>::Back>); // doesn't compile
  STATIC_CHECK(ValuePack<-1138>::Back<> == -1138);
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Back<> == 4.2F);
  STATIC_CHECK(ValuePack<4.2F, -1138>::Back<> == -1138);
}

TEST_CASE("ValuePack Prepend") {
  STATIC_CHECK(typename ValuePack<>::Prepend<-1138> {} == ValuePack<-1138> {});
  STATIC_CHECK(typename ValuePack<-1138>::Prepend<4.2F> {} == ValuePack<4.2F, -1138> {});
  STATIC_CHECK(typename ValuePack<4.2F, -1138>::Prepend<42> {} == ValuePack<42, 4.2F, -1138> {});
}

TEST_CASE("ValuePack Append") {
  STATIC_CHECK(typename ValuePack<>::Append<-1138> {} == ValuePack<-1138> {});
  STATIC_CHECK(typename ValuePack<-1138>::Append<4.2F> {} == ValuePack<-1138, 4.2F> {});
  STATIC_CHECK(typename ValuePack<4.2F, -1138>::Append<42> {} == ValuePack<4.2F, -1138, 42> {});
}

template<auto>
struct TruePredicate {
  static constexpr bool value = true;
};

template<auto>
struct FalsePredicate {
  static constexpr bool value = false;
};

template<auto Value>
struct TestPredicate {
  static constexpr bool value = Value == -1138;
};

TEST_CASE("ValuePack AnyOf") {
  STATIC_CHECK(not ValuePack<>::AnyOf<FalsePredicate>);
  STATIC_CHECK(not ValuePack<>::AnyOf<TestPredicate>);
  STATIC_CHECK(ValuePack<-1138>::AnyOf<TestPredicate>);
  STATIC_CHECK(ValuePack<-1138, 4.2F>::AnyOf<TestPredicate>);
  STATIC_CHECK(not ValuePack<42, 4.2F>::AnyOf<TestPredicate>);
}

TEST_CASE("ValuePack AllOf") {
  STATIC_CHECK(ValuePack<>::AllOf<FalsePredicate>);
  STATIC_CHECK(ValuePack<>::AllOf<TestPredicate>);
  STATIC_CHECK(ValuePack<-1138>::AllOf<TestPredicate>);
  STATIC_CHECK(not ValuePack<-1138, 4.2F>::AllOf<TestPredicate>);
  STATIC_CHECK(not ValuePack<42, 4.2F>::AllOf<TestPredicate>);
  STATIC_CHECK(ValuePack<-1138, -1138, -1138>::AllOf<TestPredicate>);
}

template<auto...>
struct RebindTarget {
  friend constexpr auto operator<=>(const RebindTarget&, const RebindTarget&) noexcept = default;
};

TEST_CASE("ValuePack Rebind") {
  STATIC_CHECK(ValuePack<>::Rebind<RebindTarget> {} == RebindTarget<> {});
  STATIC_CHECK(ValuePack<-1138>::Rebind<RebindTarget> {} == RebindTarget<-1138> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Rebind<RebindTarget> {} == RebindTarget<-1138, 4.2F> {});
}

template<auto Value>
struct Transformer {
  static constexpr auto value = -1138;
};

TEST_CASE("ValuePack Transform") {
  STATIC_CHECK(ValuePack<>::Transform<Transformer> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<4.2F>::Transform<Transformer> {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<4.2F, 42>::Transform<Transformer> {} == ValuePack<-1138, -1138> {});
}

TEST_CASE("ValuePack Unique") {
  STATIC_CHECK(ValuePack<>::Unique {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<-1138>::Unique {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Unique {} == ValuePack<-1138, 4.2F> {});
  STATIC_CHECK(ValuePack<-1138, -1138>::Unique {} == ValuePack<-1138> {});
}

template<auto Value>
struct IsTHX {
  static constexpr bool value = Value == -1138;
};

template<auto Value>
struct IsLife {
  static constexpr bool value = Value == 4.2F;
};

TEST_CASE("ValuePack Filter") {
  STATIC_CHECK(ValuePack<>::Filter<TruePredicate> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<>::Filter<FalsePredicate> {} == ValuePack<> {});

  STATIC_CHECK(ValuePack<-1138>::Filter<TruePredicate> {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<-1138>::Filter<FalsePredicate> {} == ValuePack<> {});

  STATIC_CHECK(ValuePack<-1138, 4.2F>::Filter<TruePredicate> {} == ValuePack<-1138, 4.2F> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Filter<FalsePredicate> {} == ValuePack<> {});

  STATIC_CHECK(ValuePack<-1138, 4.2F>::Filter<IsTHX> {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Filter<IsLife> {} == ValuePack<4.2F> {});
}

TEST_CASE("ValuePack Left Shift") {
  STATIC_CHECK(ValuePack<>::LeftShift {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<-1138>::LeftShift {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<1138>::LeftShift {} == ValuePack<1138> {});
  STATIC_CHECK(ValuePack<4.2F>::LeftShift {} == ValuePack<4.2F> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F>::LeftShift {} == ValuePack<4.2F, -1138> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::LeftShift {} == ValuePack<-1138, 4.2F, 1138> {});
}

TEST_CASE("ValuePack Right Shift") {
  STATIC_CHECK(ValuePack<>::LeftShift {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<-1138>::LeftShift {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<1138>::LeftShift {} == ValuePack<1138> {});
  STATIC_CHECK(ValuePack<4.2F>::LeftShift {} == ValuePack<4.2F> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F>::LeftShift {} == ValuePack<4.2F, -1138> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::LeftShift {} == ValuePack<-1138, 4.2F, 1138> {});
}

TEST_CASE("ValuePack Take") {
  STATIC_CHECK(ValuePack<>::Take<0> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<1138>::Take<0> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<1138>::Take<1> {} == ValuePack<1138> {});
  STATIC_CHECK(ValuePack<1138, 4.2F>::Take<0> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<1138, 4.2F>::Take<1> {} == ValuePack<1138> {});
  STATIC_CHECK(ValuePack<1138, 4.2F>::Take<2> {} == ValuePack<1138, 4.2F> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Take<0> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Take<1> {} == ValuePack<1138> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Take<2> {} == ValuePack<1138, -1138> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Take<3> {} == ValuePack<1138, -1138, 4.2F> {});
}

TEST_CASE("ValuePack Drop") {
  STATIC_CHECK(ValuePack<>::Drop<0> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<1138>::Drop<0> {} == ValuePack<1138> {});
  STATIC_CHECK(ValuePack<1138>::Drop<1> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<1138, -1138>::Drop<0> {} == ValuePack<1138, -1138> {});
  STATIC_CHECK(ValuePack<1138, -1138>::Drop<1> {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<1138, -1138>::Drop<2> {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Drop<0> {} == ValuePack<1138, -1138, 4.2F> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Drop<1> {} == ValuePack<-1138, 4.2F> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Drop<2> {} == ValuePack<4.2F> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Drop<3> {} == ValuePack<> {});
}

TEST_CASE("ValuePack Reverse") {
  STATIC_CHECK(ValuePack<>::Reverse {} == ValuePack<> {});
  STATIC_CHECK(ValuePack<-1138>::Reverse {} == ValuePack<-1138> {});
  STATIC_CHECK(ValuePack<-1138, 4.2F>::Reverse {} == ValuePack<4.2F, -1138> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F>::Reverse {} == ValuePack<4.2F, -1138, 1138> {});
  STATIC_CHECK(ValuePack<1138, -1138, 4.2F, 11.38>::Reverse {} == ValuePack<11.38, 4.2F, -1138, 1138> {});
}
