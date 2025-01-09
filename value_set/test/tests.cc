#include <value_set.hh>

#include <catch2/catch_all.hpp>

#include <concepts>

using namespace flp;

TEST_CASE("Duplicate Value in ValueSet") {
  STATIC_CHECK(ValueSet<4.2F>::Insert<4.2F> {} == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<4.2F, 4.2F>::Erase<4.2F> {} != ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<4.2F, 4.2F>::Erase<4.2F> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F> {} == ValueSet<4.2F, -1138> {});
  STATIC_CHECK(ValueSet<1138, 1138> {} == ValueSet<1138> {});

  STATIC_CHECK(ValueSet<-1138, 4.2F, 42> {} == ValueSet<-1138, 4.2F, 42> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F, 42> {} == ValueSet<42, -1138, 4.2F> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F, 42> {} == ValueSet<4.2F, 42, -1138> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F, 42> {} == ValueSet<-1138, 42, 4.2F> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F, 42> {} == ValueSet<42, 4.2F, -1138> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F, 42> {} == ValueSet<4.2F, -1138, 42> {});
}

TEST_CASE("`ValueSet` equality") {
  STATIC_CHECK(ValueSet<> {} == ValueSet<> {});

  STATIC_CHECK(ValueSet<> {} != ValueSet<42> {});
  STATIC_CHECK(ValueSet<> {} != ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<> {} != ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<42> {} == ValueSet<42> {});
  STATIC_CHECK(ValueSet<-1138> {} == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<4.2F> {} == ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<4.2F> {} != ValueSet<42> {});
  STATIC_CHECK(ValueSet<4.2F> {} != ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<-1138> {} != ValueSet<42> {});

  STATIC_CHECK(ValueSet<-1138, 42> {} != ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F> {} != ValueSet<> {});

  STATIC_CHECK(ValueSet<-1138, 42> {} == ValueSet<-1138, 42> {});
  STATIC_CHECK(ValueSet<-1138, 42> {} == ValueSet<42, -1138> {});

  STATIC_CHECK(ValueSet<-1138, 42> {} != ValueSet<4.2F, 42> {});
  STATIC_CHECK(ValueSet<-1138, 42> {} != ValueSet<-1138, 4.2F> {});

  STATIC_CHECK(ValueSet<-1138, 42> {} != ValueSet<4.2F, -1138> {});
  STATIC_CHECK(ValueSet<-1138, 42> {} != ValueSet<42, 4.2F> {});

  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} != ValueSet<> {});

  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} == ValueSet<4.2F, -1138, 42> {});

  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} != ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} != ValueSet<42> {});
  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} != ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} != ValueSet<-1138, 42> {});
  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} != ValueSet<42, 42> {});
  STATIC_CHECK(ValueSet<-1138, 42, 4.2F> {} != ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<42> {} == ValueSet<42, 42> {});
  STATIC_CHECK(ValueSet<-1138> {} == ValueSet<-1138, -1138> {});
  STATIC_CHECK(ValueSet<4.2F> {} == ValueSet<4.2F, 4.2F> {});

  STATIC_CHECK(ValueSet<>::Insert<42> {} == ValueSet<42> {});
  STATIC_CHECK(ValueSet<>::Insert<-1138> {} == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<>::Insert<4.2F> {} == ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<42>::Insert<42> {} == ValueSet<42> {});
  STATIC_CHECK(ValueSet<-1138>::Insert<-1138> {} == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<4.2F>::Insert<4.2F> {} == ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<-1138>::Insert<42> {} == ValueSet<42, -1138> {});
  STATIC_CHECK(ValueSet<-1138>::Insert<4.2F> {} == ValueSet<4.2F, -1138> {});

  STATIC_CHECK(ValueSet<42>::Insert<-1138> {} == ValueSet<-1138, 42> {});
  STATIC_CHECK(ValueSet<42>::Insert<4.2F> {} == ValueSet<4.2F, 42> {});

  STATIC_CHECK(ValueSet<4.2F>::Insert<-1138> {} == ValueSet<4.2F, -1138> {});
  STATIC_CHECK(ValueSet<4.2F>::Insert<42> {} == ValueSet<4.2F, 42> {});

  STATIC_CHECK(ValueSet<4.2F, 42>::Erase<4.2F> {} == ValueSet<42> {});
  STATIC_CHECK(ValueSet<4.2F, 42>::Erase<42> {} == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<4.2F, 42>::Erase<-1138> {} == ValueSet<42, 4.2F> {});
}

TEST_CASE("`ValueSet` size") {
  SECTION("Empty set") {
    STATIC_CHECK(ValueSet<>::Size == 0);

    STATIC_CHECK(ValueSet<>::Insert<42>::Size == 1);
    STATIC_CHECK(ValueSet<>::Insert<-1138>::Size == 1);
    STATIC_CHECK(ValueSet<>::Insert<4.2F>::Size == 1);
  }

  SECTION("Single value") {
    STATIC_CHECK(ValueSet<42>::Size == 1);
    STATIC_CHECK(ValueSet<-1138>::Size == 1);
    STATIC_CHECK(ValueSet<4.2F>::Size == 1);

    STATIC_CHECK(ValueSet<42>::Insert<-1138>::Size == 2);
    STATIC_CHECK(ValueSet<42>::Insert<4.2F>::Size == 2);

    STATIC_CHECK(ValueSet<-1138>::Insert<42>::Size == 2);
    STATIC_CHECK(ValueSet<-1138>::Insert<4.2F>::Size == 2);

    STATIC_CHECK(ValueSet<4.2F>::Insert<-1138>::Size == 2);
    STATIC_CHECK(ValueSet<4.2F>::Insert<42>::Size == 2);

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<42>::Insert<42>::Size == 1);
      STATIC_CHECK(ValueSet<-1138>::Insert<-1138>::Size == 1);
      STATIC_CHECK(ValueSet<4.2F>::Insert<4.2F>::Size == 1);
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::Size == 3);

    STATIC_CHECK(ValueSet<-1138, 4.2F>::Size == 2);
    STATIC_CHECK(ValueSet<-1138, 42>::Size == 2);
    STATIC_CHECK(ValueSet<4.2F, 42>::Size == 2);

    STATIC_CHECK(ValueSet<-1138, 42>::Insert<4.2F>::Size == 3);
    STATIC_CHECK(ValueSet<4.2F, 42>::Insert<-1138>::Size == 3);
    STATIC_CHECK(ValueSet<-1138, 4.2F>::Insert<42>::Size == 3);

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<-1138, 42>::Insert<-1138>::Size == 2);
      STATIC_CHECK(ValueSet<-1138, 42>::Insert<42>::Size == 2);

      STATIC_CHECK(ValueSet<4.2F, 42>::Insert<42>::Size == 2);
      STATIC_CHECK(ValueSet<4.2F, 42>::Insert<4.2F>::Size == 2);

      STATIC_CHECK(ValueSet<-1138, 4.2F>::Insert<-1138>::Size == 2);
      STATIC_CHECK(ValueSet<-1138, 4.2F>::Insert<4.2F>::Size == 2);
    }
  }
}

TEST_CASE("`ValueSet` empty") {
  STATIC_CHECK(ValueSet<>::Empty);

  STATIC_CHECK(not ValueSet<>::Insert<42>::Empty);
  STATIC_CHECK(not ValueSet<>::Insert<-1138>::Empty);
  STATIC_CHECK(not ValueSet<>::Insert<4.2F>::Empty);

  STATIC_CHECK(not ValueSet<-1138>::Empty);
  STATIC_CHECK(not ValueSet<42>::Empty);
  STATIC_CHECK(not ValueSet<4.2F>::Empty);

  STATIC_CHECK(not ValueSet<-1138>::Insert<42>::Empty);
  STATIC_CHECK(not ValueSet<-1138>::Insert<-1138>::Empty);
  STATIC_CHECK(not ValueSet<-1138>::Insert<4.2F>::Empty);

  STATIC_CHECK(not ValueSet<42>::Insert<-1138>::Empty);
  STATIC_CHECK(not ValueSet<42>::Insert<42>::Empty);
  STATIC_CHECK(not ValueSet<42>::Insert<4.2F>::Empty);

  STATIC_CHECK(not ValueSet<4.2F>::Insert<42>::Empty);
  STATIC_CHECK(not ValueSet<4.2F>::Insert<-1138>::Empty);
  STATIC_CHECK(not ValueSet<4.2F>::Insert<4.2F>::Empty);

  STATIC_CHECK(not ValueSet<-1138, -1138>::Empty);
  STATIC_CHECK(not ValueSet<4.2F, 42>::Empty);
  STATIC_CHECK(not ValueSet<4.2F, -1138>::Empty);

  STATIC_CHECK(not ValueSet<-1138, 42>::Insert<4.2F>::Empty);
  STATIC_CHECK(not ValueSet<-1138, 42>::Insert<-1138>::Empty);
  STATIC_CHECK(not ValueSet<-1138, 42>::Insert<42>::Empty);

  STATIC_CHECK(not ValueSet<4.2F, 42>::Insert<-1138>::Empty);
  STATIC_CHECK(not ValueSet<4.2F, 42>::Insert<42>::Empty);
  STATIC_CHECK(not ValueSet<4.2F, 42>::Insert<4.2F>::Empty);

  STATIC_CHECK(not ValueSet<4.2F, -1138>::Insert<42>::Empty);
  STATIC_CHECK(not ValueSet<4.2F, -1138>::Insert<-1138>::Empty);
  STATIC_CHECK(not ValueSet<4.2F, -1138>::Insert<4.2F>::Empty);

  STATIC_CHECK(not ValueSet<4.2F, -1138, 42>::Empty);
}

TEST_CASE("`ValueSet` Contains") {
  SECTION("Empty set") {
    STATIC_CHECK(not ValueSet<>::Contains<4.2F>);
    STATIC_CHECK(not ValueSet<>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<>::Contains<42>);
  }

  SECTION("Single value") {
    STATIC_CHECK(not ValueSet<4.2F>::Contains<42>);
    STATIC_CHECK(not ValueSet<4.2F>::Contains<-1138>);

    STATIC_CHECK(not ValueSet<42>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<42>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<-1138>::Contains<42>);
    STATIC_CHECK(not ValueSet<-1138>::Contains<4.2F>);

    STATIC_CHECK(ValueSet<4.2F>::Contains<4.2F>);
    STATIC_CHECK(ValueSet<42>::Contains<42>);
    STATIC_CHECK(ValueSet<-1138>::Contains<-1138>);
  }

  SECTION("Multiple values") {
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::Contains<-1138>);
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::Contains<42>);
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<42, 4.2F>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<-1138, 4.2F>::Contains<42>);
    STATIC_CHECK(not ValueSet<-1138, 42>::Contains<4.2F>);
  }
}

TEST_CASE("`ValueSet` Insert") {
  SECTION("Empty set") {
    STATIC_CHECK(ValueSet<>::Insert<42>::Contains<42>);
    STATIC_CHECK(ValueSet<>::Insert<-1138>::Contains<-1138>);
    STATIC_CHECK(ValueSet<>::Insert<4.2F>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<>::Insert<42>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<>::Insert<42>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<>::Insert<-1138>::Contains<42>);
    STATIC_CHECK(not ValueSet<>::Insert<-1138>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<>::Insert<4.2F>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<>::Insert<4.2F>::Contains<42>);
  }

  SECTION("Single value") {
    STATIC_CHECK(ValueSet<4.2F>::Insert<42>::Contains<42>);
    STATIC_CHECK(ValueSet<4.2F>::Insert<-1138>::Contains<-1138>);

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<4.2F>::Insert<4.2F>::Contains<4.2F>);
      STATIC_CHECK(ValueSet<-1138>::Insert<-1138>::Contains<-1138>);
      STATIC_CHECK(ValueSet<42>::Insert<42>::Contains<42>);

      STATIC_CHECK(not ValueSet<4.2F>::Insert<4.2F>::Contains<-1138>);
      STATIC_CHECK(not ValueSet<4.2F>::Insert<4.2F>::Contains<42>);

      STATIC_CHECK(not ValueSet<-1138>::Insert<-1138>::Contains<4.2F>);
      STATIC_CHECK(not ValueSet<-1138>::Insert<-1138>::Contains<42>);

      STATIC_CHECK(not ValueSet<42>::Insert<42>::Contains<4.2F>);
      STATIC_CHECK(not ValueSet<42>::Insert<42>::Contains<-1138>);
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(ValueSet<4.2F, 42>::Insert<-1138>::Contains<-1138>);
    STATIC_CHECK(ValueSet<4.2F, -1138>::Insert<42>::Contains<42>);
    STATIC_CHECK(ValueSet<-1138, 42>::Insert<4.2F>::Contains<4.2F>);

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<4.2F, 42>::Insert<4.2F>::Contains<4.2F>);
      STATIC_CHECK(ValueSet<4.2F, 42>::Insert<42>::Contains<42>);

      STATIC_CHECK(ValueSet<4.2F, -1138>::Insert<-1138>::Contains<-1138>);
      STATIC_CHECK(ValueSet<4.2F, -1138>::Insert<4.2F>::Contains<4.2F>);

      STATIC_CHECK(ValueSet<-1138, 42>::Insert<-1138>::Contains<-1138>);
      STATIC_CHECK(ValueSet<-1138, 42>::Insert<42>::Contains<42>);
    }
  }
}

TEST_CASE("`ValueSet` Erase") {
  SECTION("Empty set") {
    STATIC_CHECK(ValueSet<>::Erase<42>::Empty);
    STATIC_CHECK(ValueSet<>::Erase<-1138>::Empty);
    STATIC_CHECK(ValueSet<>::Erase<4.2F>::Empty);

    STATIC_CHECK(not ValueSet<>::Erase<42>::Contains<42>);
    STATIC_CHECK(not ValueSet<>::Erase<42>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<>::Erase<42>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<>::Erase<-1138>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<>::Erase<-1138>::Contains<42>);
    STATIC_CHECK(not ValueSet<>::Erase<-1138>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<>::Erase<4.2F>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<>::Erase<4.2F>::Contains<42>);
    STATIC_CHECK(not ValueSet<>::Erase<4.2F>::Contains<4.2F>);
  }

  SECTION("Single value") {
    STATIC_CHECK(ValueSet<4.2F>::Erase<4.2F>::Empty);
    STATIC_CHECK(ValueSet<42>::Erase<42>::Empty);
    STATIC_CHECK(ValueSet<-1138>::Erase<-1138>::Empty);

    STATIC_CHECK(not ValueSet<4.2F>::Erase<4.2F>::Contains<4.2F>);
    STATIC_CHECK(not ValueSet<-1138>::Erase<-1138>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<42>::Erase<42>::Contains<42>);

    STATIC_CHECK(not ValueSet<4.2F>::Erase<4.2F>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<4.2F>::Erase<4.2F>::Contains<42>);

    STATIC_CHECK(not ValueSet<-1138>::Erase<-1138>::Contains<4.2F>);
    STATIC_CHECK(not ValueSet<-1138>::Erase<-1138>::Contains<42>);

    STATIC_CHECK(not ValueSet<42>::Erase<42>::Contains<4.2F>);
    STATIC_CHECK(not ValueSet<42>::Erase<42>::Contains<-1138>);

    SECTION("Idempotent") {
      STATIC_CHECK(not ValueSet<4.2F>::Erase<42>::Contains<42>);
      STATIC_CHECK(not ValueSet<4.2F>::Erase<-1138>::Contains<-1138>);
      STATIC_CHECK(not ValueSet<4.2F>::Erase<4.2F>::Contains<4.2F>);
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(not ValueSet<4.2F, 42>::Erase<42>::Contains<42>);
    STATIC_CHECK(not ValueSet<4.2F, 42>::Erase<4.2F>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<4.2F, -1138>::Erase<-1138>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<4.2F, -1138>::Erase<4.2F>::Contains<4.2F>);

    STATIC_CHECK(not ValueSet<-1138, 42>::Erase<-1138>::Contains<-1138>);
    STATIC_CHECK(not ValueSet<-1138, 42>::Erase<42>::Contains<42>);

    SECTION("Idempotent") {
      STATIC_CHECK(not ValueSet<4.2F, 42>::Erase<-1138>::Contains<-1138>);
      STATIC_CHECK(not ValueSet<4.2F, -1138>::Erase<42>::Contains<42>);
      STATIC_CHECK(not ValueSet<-1138, 42>::Erase<4.2F>::Contains<4.2F>);

      STATIC_CHECK(ValueSet<4.2F, 42>::Insert<4.2F>::Contains<4.2F>);
      STATIC_CHECK(ValueSet<4.2F, 42>::Insert<42>::Contains<42>);

      STATIC_CHECK(ValueSet<4.2F, -1138>::Insert<-1138>::Contains<-1138>);
      STATIC_CHECK(ValueSet<4.2F, -1138>::Insert<4.2F>::Contains<4.2F>);

      STATIC_CHECK(ValueSet<-1138, 42>::Insert<-1138>::Contains<-1138>);
      STATIC_CHECK(ValueSet<-1138, 42>::Insert<42>::Contains<42>);
    }
  }
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
struct IsIntPredicate {
  static constexpr bool value = std::same_as<decltype(Value), int>;
};

template<auto Value>
struct IsFloatPredicate {
  static constexpr bool value = std::same_as<decltype(Value), float>;
};

TEST_CASE("`ValueSet` AnyOf") {
  STATIC_CHECK(not ValueSet<>::AnyOf<TruePredicate>);
  STATIC_CHECK(ValueSet<-1138>::AnyOf<TruePredicate>);
  STATIC_CHECK(ValueSet<-1138, 4.2F>::AnyOf<TruePredicate>);

  STATIC_CHECK(not ValueSet<>::AnyOf<FalsePredicate>);
  STATIC_CHECK(not ValueSet<-1138>::AnyOf<FalsePredicate>);
  STATIC_CHECK(not ValueSet<-1138, 4.2F>::AnyOf<FalsePredicate>);

  STATIC_CHECK(not ValueSet<>::AnyOf<IsIntPredicate>);
  STATIC_CHECK(ValueSet<-1138>::AnyOf<IsIntPredicate>);
  STATIC_CHECK(not ValueSet<4.2F>::AnyOf<IsIntPredicate>);
  STATIC_CHECK(ValueSet<-1138, 4.2F>::AnyOf<IsIntPredicate>);

  STATIC_CHECK(not ValueSet<>::AnyOf<IsFloatPredicate>);
  STATIC_CHECK(not ValueSet<-1138>::AnyOf<IsFloatPredicate>);
  STATIC_CHECK(ValueSet<4.2F>::AnyOf<IsFloatPredicate>);
  STATIC_CHECK(ValueSet<-1138, 4.2F>::AnyOf<IsFloatPredicate>);
}

TEST_CASE("`ValueSet` AllOf") {
  STATIC_CHECK(not ValueSet<>::AllOf<TruePredicate>);
  STATIC_CHECK(ValueSet<-1138>::AllOf<TruePredicate>);
  STATIC_CHECK(ValueSet<-1138, 4.2F>::AllOf<TruePredicate>);

  STATIC_CHECK(not ValueSet<>::AllOf<FalsePredicate>);
  STATIC_CHECK(not ValueSet<-1138>::AllOf<FalsePredicate>);
  STATIC_CHECK(not ValueSet<-1138, 4.2F>::AllOf<FalsePredicate>);

  STATIC_CHECK(not ValueSet<>::AllOf<IsIntPredicate>);
  STATIC_CHECK(ValueSet<-1138>::AllOf<IsIntPredicate>);
  STATIC_CHECK(not ValueSet<4.2F>::AllOf<IsIntPredicate>);
  STATIC_CHECK(not ValueSet<-1138, 4.2F>::AllOf<IsIntPredicate>);
  STATIC_CHECK(ValueSet<-1138, -1138>::AllOf<IsIntPredicate>);

  STATIC_CHECK(not ValueSet<>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(not ValueSet<-1138>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(ValueSet<4.2F>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(not ValueSet<-1138, 4.2F>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(ValueSet<4.2F, 4.2F>::AllOf<IsFloatPredicate>);
}

template<auto>
struct TransformPredicate;

template<>
struct TransformPredicate<-1138> {
  static constexpr auto value = 4.2F;
};

template<>
struct TransformPredicate<4.2F> {
  static constexpr auto value = 42;
};

template<auto>
struct FloatPredicate {
  static constexpr auto value = 4.2F;
};

template<auto>
struct IntPredicate {
  static constexpr auto value = -1138;
};

template<auto Value>
struct IdentityPredicate {
  static constexpr auto value = Value;
};

TEST_CASE("`ValueSet` Transform") {
  STATIC_CHECK(ValueSet<>::Transform<IdentityPredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138>::Transform<IdentityPredicate> {} == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<4.2F>::Transform<IdentityPredicate> {} == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F>::Transform<IdentityPredicate> {} == ValueSet<-1138, 4.2F> {});

  STATIC_CHECK(ValueSet<>::Transform<IntPredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138>::Transform<IntPredicate> {} == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<4.2F>::Transform<IntPredicate> {} == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F>::Transform<IntPredicate> {} == ValueSet<-1138> {});

  STATIC_CHECK(ValueSet<>::Transform<FloatPredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138>::Transform<FloatPredicate> {} == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<4.2F>::Transform<FloatPredicate> {} == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F>::Transform<FloatPredicate> {} == ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<>::Transform<TransformPredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138>::Transform<TransformPredicate> {} == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<4.2F>::Transform<TransformPredicate> {} == ValueSet<42> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F>::Transform<TransformPredicate> {} == ValueSet<42, 4.2F> {});
}

template<auto... Values>
struct TestPack {
  template<auto... OtherValues>
  constexpr bool operator==(const TestPack<OtherValues...>&) const {
    return ((Values == OtherValues) and ...);
  }
};

TEST_CASE("`ValueSet` Rebind") {
  STATIC_CHECK(ValueSet<>::Rebind<TestPack> {} == TestPack<> {});
  STATIC_CHECK(ValueSet<-1138>::Rebind<TestPack> {} == TestPack<-1138> {});
  STATIC_CHECK(ValueSet<4.2F>::Rebind<TestPack> {} == TestPack<4.2F> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F>::Rebind<TestPack> {} == TestPack<-1138, 4.2F> {});
}

template<auto Value>
struct FilterTestPredicate {
  static constexpr bool value = std::integral<decltype(Value)>;
};

TEST_CASE("`ValueSet` Filter") {
  STATIC_CHECK(ValueSet<>::Filter<TruePredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138>::Filter<TruePredicate> {} == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<4.2F>::Filter<TruePredicate> {} == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F>::Filter<TruePredicate> {} == ValueSet<-1138, 4.2F> {});

  STATIC_CHECK(ValueSet<>::Filter<FalsePredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138>::Filter<FalsePredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<4.2F>::Filter<FalsePredicate> {} == ValueSet<> {});
  STATIC_CHECK(ValueSet<-1138, 4.2F>::Filter<FalsePredicate> {} == ValueSet<> {});

  STATIC_CHECK(ValueSet<-1138, 4.2F, 42>::Filter<FilterTestPredicate> {} == ValueSet<-1138, 42> {});
}

TEST_CASE("`ValueSet` Intersection") {
  STATIC_CHECK(ValueSet<>::Intersection<>{} == ValueSet<>{});
  STATIC_CHECK(ValueSet<42>::Intersection<>{} == ValueSet<>{});
  STATIC_CHECK(ValueSet<>::Intersection<42>{} == ValueSet<>{});
  STATIC_CHECK(ValueSet<42>::Intersection<1138>{} == ValueSet<>{});
  STATIC_CHECK(ValueSet<42, 4.2F>::Intersection<1138, -1138>{} == ValueSet<>{});

  STATIC_CHECK(ValueSet<-1138, 4.2F, 42>::Intersection<>{} == ValueSet<>{});
  STATIC_CHECK(ValueSet<>::Intersection<-1138, 4.2F, 42>{} == ValueSet<>{});

  STATIC_CHECK(ValueSet<-1138, 4.2F, 42>::Intersection<-1138>{} == ValueSet<-1138>{});
  STATIC_CHECK(ValueSet<-1138, 4.2F, 42>::Intersection<-1138, 4.2F>{} == ValueSet<-1138, 4.2F>{});
  STATIC_CHECK(ValueSet<-1138, 4.2F, 42>::Intersection<4.2F, -1138>{} == ValueSet<-1138, 4.2F>{});

  STATIC_CHECK(ValueSet<-1138, 42>::Intersection<4.2F, -1138>{} == ValueSet<-1138>{});
}

TEST_CASE("`ValueSet` Difference") {
}

TEST_CASE("`ValueSet` Symmetric Difference") {
}

TEST_CASE("`ValueSet` Union") {
}

