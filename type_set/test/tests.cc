#include <type_set.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Duplicate Type in TypeSet") {
  STATIC_CHECK(TypeSet<float>::Insert<float>{} == TypeSet<float> {});
  STATIC_CHECK(TypeSet<float, float>::Erase<float>{} != TypeSet<float> {});
  STATIC_CHECK(TypeSet<float, float>::Erase<float>{} == TypeSet<> {});
  STATIC_CHECK(TypeSet<int, float>{} == TypeSet<float, int> {});

  STATIC_CHECK(TypeSet<signed int, float, unsigned int>{} == TypeSet<signed int, float, unsigned int> {});
  STATIC_CHECK(TypeSet<signed int, float, unsigned int>{} == TypeSet<unsigned int, signed int, float> {});
  STATIC_CHECK(TypeSet<signed int, float, unsigned int>{} == TypeSet<float, unsigned int, signed int> {});
  STATIC_CHECK(TypeSet<signed int, float, unsigned int>{} == TypeSet<signed int, unsigned int, float> {});
  STATIC_CHECK(TypeSet<signed int, float, unsigned int>{} == TypeSet<unsigned int, float, signed int> {});
  STATIC_CHECK(TypeSet<signed int, float, unsigned int>{} == TypeSet<float, signed int, unsigned int> {});
}

TEST_CASE("`TypeSet` equality") {
  STATIC_CHECK(TypeSet<> {} == TypeSet<> {});

  STATIC_CHECK(TypeSet<> {} != TypeSet<unsigned int> {});
  STATIC_CHECK(TypeSet<> {} != TypeSet<signed int> {});
  STATIC_CHECK(TypeSet<> {} != TypeSet<float> {});

  STATIC_CHECK(TypeSet<unsigned int> {} == TypeSet<unsigned int> {});
  STATIC_CHECK(TypeSet<signed int> {} == TypeSet<signed int> {});
  STATIC_CHECK(TypeSet<float> {} == TypeSet<float> {});

  STATIC_CHECK(TypeSet<float> {} != TypeSet<unsigned int> {});
  STATIC_CHECK(TypeSet<float> {} != TypeSet<signed int> {});
  STATIC_CHECK(TypeSet<signed int> {} != TypeSet<unsigned int> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int> {} != TypeSet<> {});
  STATIC_CHECK(TypeSet<signed int, float> {} != TypeSet<> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int> {} == TypeSet<signed int, unsigned int> {});
  STATIC_CHECK(TypeSet<signed int, unsigned int> {} == TypeSet<unsigned int, signed int> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int> {} != TypeSet<float, unsigned int> {});
  STATIC_CHECK(TypeSet<signed int, unsigned int> {} != TypeSet<signed int, float> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int> {} != TypeSet<float, signed int> {});
  STATIC_CHECK(TypeSet<signed int, unsigned int> {} != TypeSet<unsigned int, float> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} != TypeSet<> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} == TypeSet<float, signed int, unsigned int> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} != TypeSet<signed int> {});
  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} != TypeSet<unsigned int> {});
  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} != TypeSet<float> {});

  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} != TypeSet<signed int, unsigned int> {});
  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} != TypeSet<unsigned int, unsigned int> {});
  STATIC_CHECK(TypeSet<signed int, unsigned int, float> {} != TypeSet<float> {});

  STATIC_CHECK(TypeSet<unsigned int> {} == TypeSet<unsigned int, unsigned int> {});
  STATIC_CHECK(TypeSet<signed int> {} == TypeSet<signed int, signed int> {});
  STATIC_CHECK(TypeSet<float> {} == TypeSet<float, float> {});

  STATIC_CHECK(TypeSet<>::Insert<unsigned int>{} == TypeSet<unsigned int> {});
  STATIC_CHECK(TypeSet<>::Insert<signed int>{} == TypeSet<signed int> {});
  STATIC_CHECK(TypeSet<>::Insert<float>{} == TypeSet<float> {});

  STATIC_CHECK(TypeSet<unsigned int>::Insert<unsigned int>{} == TypeSet<unsigned int> {});
  STATIC_CHECK(TypeSet<signed int>::Insert<signed int>{} == TypeSet<signed int> {});
  STATIC_CHECK(TypeSet<float>::Insert<float>{} == TypeSet<float> {});

  STATIC_CHECK(TypeSet<signed int>::Insert<unsigned int>{} == TypeSet<unsigned int, signed int> {});
  STATIC_CHECK(TypeSet<signed int>::Insert<float>{} == TypeSet<float, signed int> {});

  STATIC_CHECK(TypeSet<unsigned int>::Insert<signed int>{} == TypeSet<signed int, unsigned int> {});
  STATIC_CHECK(TypeSet<unsigned int>::Insert<float>{} == TypeSet<float, unsigned int> {});

  STATIC_CHECK(TypeSet<float>::Insert<signed int>{} == TypeSet<float, signed int> {});
  STATIC_CHECK(TypeSet<float>::Insert<unsigned int>{} == TypeSet<float, unsigned int> {});

  STATIC_CHECK(TypeSet<float, unsigned int>::Erase<float>{} == TypeSet<unsigned int> {});
  STATIC_CHECK(TypeSet<float, unsigned int>::Erase<unsigned int>{} == TypeSet<float> {});
  STATIC_CHECK(TypeSet<float, unsigned int>::Erase<signed int>{} == TypeSet<unsigned int, float> {});
}

TEST_CASE("`TypeSet` size") {
  SECTION("Empty set") {
    STATIC_CHECK(TypeSet<>::Size == 0);

    STATIC_CHECK(TypeSet<>::Insert<unsigned int>::Size == 1);
    STATIC_CHECK(TypeSet<>::Insert<signed int>::Size == 1);
    STATIC_CHECK(TypeSet<>::Insert<float>::Size == 1);
  }

  SECTION("Single value") {
    STATIC_CHECK(TypeSet<unsigned int>::Size == 1);
    STATIC_CHECK(TypeSet<signed int>::Size == 1);
    STATIC_CHECK(TypeSet<float>::Size == 1);

    STATIC_CHECK(TypeSet<unsigned int>::Insert<signed int>::Size == 2);
    STATIC_CHECK(TypeSet<unsigned int>::Insert<float>::Size == 2);

    STATIC_CHECK(TypeSet<signed int>::Insert<unsigned int>::Size == 2);
    STATIC_CHECK(TypeSet<signed int>::Insert<float>::Size == 2);

    STATIC_CHECK(TypeSet<float>::Insert<signed int>::Size == 2);
    STATIC_CHECK(TypeSet<float>::Insert<unsigned int>::Size == 2);

    SECTION("Idempotent") {
      STATIC_CHECK(TypeSet<unsigned int>::Insert<unsigned int>::Size == 1);
      STATIC_CHECK(TypeSet<signed int>::Insert<signed int>::Size == 1);
      STATIC_CHECK(TypeSet<float>::Insert<float>::Size == 1);
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(TypeSet<signed int, unsigned int, float>::Size == 3);

    STATIC_CHECK(TypeSet<signed int, float>::Size == 2);
    STATIC_CHECK(TypeSet<signed int, unsigned int>::Size == 2);
    STATIC_CHECK(TypeSet<float, unsigned int>::Size == 2);

    STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<float>::Size == 3);
    STATIC_CHECK(TypeSet<float, unsigned int>::Insert<signed int>::Size == 3);
    STATIC_CHECK(TypeSet<signed int, float>::Insert<unsigned int>::Size == 3);

    SECTION("Idempotent") {
      STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<signed int>::Size == 2);
      STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<unsigned int>::Size == 2);

      STATIC_CHECK(TypeSet<float, unsigned int>::Insert<unsigned int>::Size == 2);
      STATIC_CHECK(TypeSet<float, unsigned int>::Insert<float>::Size == 2);

      STATIC_CHECK(TypeSet<signed int, float>::Insert<signed int>::Size == 2);
      STATIC_CHECK(TypeSet<signed int, float>::Insert<float>::Size == 2);
    }
  }
}

TEST_CASE("`TypeSet` empty") {
  STATIC_CHECK(TypeSet<>::Empty);

  STATIC_CHECK(not TypeSet<>::Insert<unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<>::Insert<signed int>::Empty);
  STATIC_CHECK(not TypeSet<>::Insert<float>::Empty);

  STATIC_CHECK(not TypeSet<signed int>::Empty);
  STATIC_CHECK(not TypeSet<unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<float>::Empty);

  STATIC_CHECK(not TypeSet<signed int>::Insert<unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<signed int>::Insert<signed int>::Empty);
  STATIC_CHECK(not TypeSet<signed int>::Insert<float>::Empty);

  STATIC_CHECK(not TypeSet<unsigned int>::Insert<signed int>::Empty);
  STATIC_CHECK(not TypeSet<unsigned int>::Insert<unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<unsigned int>::Insert<float>::Empty);

  STATIC_CHECK(not TypeSet<float>::Insert<unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<float>::Insert<signed int>::Empty);
  STATIC_CHECK(not TypeSet<float>::Insert<float>::Empty);

  STATIC_CHECK(not TypeSet<signed int, signed int>::Empty);
  STATIC_CHECK(not TypeSet<float, unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<float, signed int>::Empty);

  STATIC_CHECK(not TypeSet<signed int, unsigned int>::Insert<float>::Empty);
  STATIC_CHECK(not TypeSet<signed int, unsigned int>::Insert<signed int>::Empty);
  STATIC_CHECK(not TypeSet<signed int, unsigned int>::Insert<unsigned int>::Empty);

  STATIC_CHECK(not TypeSet<float, unsigned int>::Insert<signed int>::Empty);
  STATIC_CHECK(not TypeSet<float, unsigned int>::Insert<unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<float, unsigned int>::Insert<float>::Empty);

  STATIC_CHECK(not TypeSet<float, signed int>::Insert<unsigned int>::Empty);
  STATIC_CHECK(not TypeSet<float, signed int>::Insert<signed int>::Empty);
  STATIC_CHECK(not TypeSet<float, signed int>::Insert<float>::Empty);

  STATIC_CHECK(not TypeSet<float, signed int, unsigned int>::Empty);
}

TEST_CASE("`TypeSet` Contains") {
  SECTION("Empty set") {
    STATIC_CHECK(not TypeSet<>::Contains<float>);
    STATIC_CHECK(not TypeSet<>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<>::Contains<unsigned int>);
  }

  SECTION("Single value") {
    STATIC_CHECK(not TypeSet<float>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<float>::Contains<signed int>);

    STATIC_CHECK(not TypeSet<unsigned int>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<unsigned int>::Contains<float>);

    STATIC_CHECK(not TypeSet<signed int>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<signed int>::Contains<float>);

    STATIC_CHECK(TypeSet<float>::Contains<float>);
    STATIC_CHECK(TypeSet<unsigned int>::Contains<unsigned int>);
    STATIC_CHECK(TypeSet<signed int>::Contains<signed int>);
  }

  SECTION("Multiple values") {
    STATIC_CHECK(TypeSet<signed int, unsigned int, float>::Contains<signed int>);
    STATIC_CHECK(TypeSet<signed int, unsigned int, float>::Contains<unsigned int>);
    STATIC_CHECK(TypeSet<signed int, unsigned int, float>::Contains<float>);

    STATIC_CHECK(not TypeSet<unsigned int, float>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<signed int, float>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<signed int, unsigned int>::Contains<float>);
  }
}

TEST_CASE("`TypeSet` Insert") {
  SECTION("Empty set") {
    STATIC_CHECK(TypeSet<>::Insert<unsigned int>::Contains<unsigned int>);
    STATIC_CHECK(TypeSet<>::Insert<signed int>::Contains<signed int>);
    STATIC_CHECK(TypeSet<>::Insert<float>::Contains<float>);

    STATIC_CHECK(not TypeSet<>::Insert<unsigned int>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<>::Insert<unsigned int>::Contains<float>);

    STATIC_CHECK(not TypeSet<>::Insert<signed int>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<>::Insert<signed int>::Contains<float>);

    STATIC_CHECK(not TypeSet<>::Insert<float>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<>::Insert<float>::Contains<unsigned int>);
  }

  SECTION("Single value") {
    STATIC_CHECK(TypeSet<float>::Insert<unsigned int>::Contains<unsigned int>);
    STATIC_CHECK(TypeSet<float>::Insert<signed int>::Contains<signed int>);

    SECTION("Idempotent") {
      STATIC_CHECK(TypeSet<float>::Insert<float>::Contains<float>);
      STATIC_CHECK(TypeSet<signed int>::Insert<signed int>::Contains<signed int>);
      STATIC_CHECK(TypeSet<unsigned int>::Insert<unsigned int>::Contains<unsigned int>);

      STATIC_CHECK(not TypeSet<float>::Insert<float>::Contains<signed int>);
      STATIC_CHECK(not TypeSet<float>::Insert<float>::Contains<unsigned int>);

      STATIC_CHECK(not TypeSet<signed int>::Insert<signed int>::Contains<float>);
      STATIC_CHECK(not TypeSet<signed int>::Insert<signed int>::Contains<unsigned int>);

      STATIC_CHECK(not TypeSet<unsigned int>::Insert<unsigned int>::Contains<float>);
      STATIC_CHECK(not TypeSet<unsigned int>::Insert<unsigned int>::Contains<signed int>);
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(TypeSet<float, unsigned int>::Insert<signed int>::Contains<signed int>);
    STATIC_CHECK(TypeSet<float, signed int>::Insert<unsigned int>::Contains<unsigned int>);
    STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<float>::Contains<float>);

    SECTION("Idempotent") {
      STATIC_CHECK(TypeSet<float, unsigned int>::Insert<float>::Contains<float>);
      STATIC_CHECK(TypeSet<float, unsigned int>::Insert<unsigned int>::Contains<unsigned int>);

      STATIC_CHECK(TypeSet<float, signed int>::Insert<signed int>::Contains<signed int>);
      STATIC_CHECK(TypeSet<float, signed int>::Insert<float>::Contains<float>);

      STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<signed int>::Contains<signed int>);
      STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<unsigned int>::Contains<unsigned int>);
    }
  }
}

TEST_CASE("`TypeSet` Erase") {
  SECTION("Empty set") {
    STATIC_CHECK(TypeSet<>::Erase<unsigned int>::Empty);
    STATIC_CHECK(TypeSet<>::Erase<signed int>::Empty);
    STATIC_CHECK(TypeSet<>::Erase<float>::Empty);

    STATIC_CHECK(not TypeSet<>::Erase<unsigned int>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<>::Erase<unsigned int>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<>::Erase<unsigned int>::Contains<float>);

    STATIC_CHECK(not TypeSet<>::Erase<signed int>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<>::Erase<signed int>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<>::Erase<signed int>::Contains<float>);

    STATIC_CHECK(not TypeSet<>::Erase<float>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<>::Erase<float>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<>::Erase<float>::Contains<float>);
  }

  SECTION("Single value") {
    STATIC_CHECK(TypeSet<float>::Erase<float>::Empty);
    STATIC_CHECK(TypeSet<unsigned int>::Erase<unsigned int>::Empty);
    STATIC_CHECK(TypeSet<signed int>::Erase<signed int>::Empty);

    STATIC_CHECK(not TypeSet<float>::Erase<float>::Contains<float>);
    STATIC_CHECK(not TypeSet<signed int>::Erase<signed int>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<unsigned int>::Erase<unsigned int>::Contains<unsigned int>);

    STATIC_CHECK(not TypeSet<float>::Erase<float>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<float>::Erase<float>::Contains<unsigned int>);

    STATIC_CHECK(not TypeSet<signed int>::Erase<signed int>::Contains<float>);
    STATIC_CHECK(not TypeSet<signed int>::Erase<signed int>::Contains<unsigned int>);

    STATIC_CHECK(not TypeSet<unsigned int>::Erase<unsigned int>::Contains<float>);
    STATIC_CHECK(not TypeSet<unsigned int>::Erase<unsigned int>::Contains<signed int>);

    SECTION("Idempotent") {
      STATIC_CHECK(not TypeSet<float>::Erase<unsigned int>::Contains<unsigned int>);
      STATIC_CHECK(not TypeSet<float>::Erase<signed int>::Contains<signed int>);
      STATIC_CHECK(not TypeSet<float>::Erase<float>::Contains<float>);
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(not TypeSet<float, unsigned int>::Erase<unsigned int>::Contains<unsigned int>);
    STATIC_CHECK(not TypeSet<float, unsigned int>::Erase<float>::Contains<float>);

    STATIC_CHECK(not TypeSet<float, signed int>::Erase<signed int>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<float, signed int>::Erase<float>::Contains<float>);

    STATIC_CHECK(not TypeSet<signed int, unsigned int>::Erase<signed int>::Contains<signed int>);
    STATIC_CHECK(not TypeSet<signed int, unsigned int>::Erase<unsigned int>::Contains<unsigned int>);

    SECTION("Idempotent") {
      STATIC_CHECK(not TypeSet<float, unsigned int>::Erase<signed int>::Contains<signed int>);
      STATIC_CHECK(not TypeSet<float, signed int>::Erase<unsigned int>::Contains<unsigned int>);
      STATIC_CHECK(not TypeSet<signed int, unsigned int>::Erase<float>::Contains<float>);

      STATIC_CHECK(TypeSet<float, unsigned int>::Insert<float>::Contains<float>);
      STATIC_CHECK(TypeSet<float, unsigned int>::Insert<unsigned int>::Contains<unsigned int>);

      STATIC_CHECK(TypeSet<float, signed int>::Insert<signed int>::Contains<signed int>);
      STATIC_CHECK(TypeSet<float, signed int>::Insert<float>::Contains<float>);

      STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<signed int>::Contains<signed int>);
      STATIC_CHECK(TypeSet<signed int, unsigned int>::Insert<unsigned int>::Contains<unsigned int>);
    }
  }
}

template<typename>
struct TruePredicate {
  static constexpr bool value = true;
};

template<typename>
struct FalsePredicate {
  static constexpr bool value = false;
};

template<typename Type>
struct IsIntPredicate {
  static constexpr bool value = std::same_as<Type, int>;
};

template<typename Type>
struct IsFloatPredicate {
  static constexpr bool value = std::same_as<Type, float>;
};

TEST_CASE("`TypeSet` AnyOf") {
  STATIC_CHECK(not TypeSet<>::AnyOf<TruePredicate>);
  STATIC_CHECK(TypeSet<int>::AnyOf<TruePredicate>);
  STATIC_CHECK(TypeSet<int, float>::AnyOf<TruePredicate>);

  STATIC_CHECK(not TypeSet<>::AnyOf<FalsePredicate>);
  STATIC_CHECK(not TypeSet<int>::AnyOf<FalsePredicate>);
  STATIC_CHECK(not TypeSet<int, float>::AnyOf<FalsePredicate>);

  STATIC_CHECK(not TypeSet<>::AnyOf<IsIntPredicate>);
  STATIC_CHECK(TypeSet<int>::AnyOf<IsIntPredicate>);
  STATIC_CHECK(not TypeSet<float>::AnyOf<IsIntPredicate>);
  STATIC_CHECK(TypeSet<int, float>::AnyOf<IsIntPredicate>);

  STATIC_CHECK(not TypeSet<>::AnyOf<IsFloatPredicate>);
  STATIC_CHECK(not TypeSet<int>::AnyOf<IsFloatPredicate>);
  STATIC_CHECK(TypeSet<float>::AnyOf<IsFloatPredicate>);
  STATIC_CHECK(TypeSet<int, float>::AnyOf<IsFloatPredicate>);
}

TEST_CASE("`TypeSet` AllOf") {
  STATIC_CHECK(not TypeSet<>::AllOf<TruePredicate>);
  STATIC_CHECK(TypeSet<int>::AllOf<TruePredicate>);
  STATIC_CHECK(TypeSet<int, float>::AllOf<TruePredicate>);

  STATIC_CHECK(not TypeSet<>::AllOf<FalsePredicate>);
  STATIC_CHECK(not TypeSet<int>::AllOf<FalsePredicate>);
  STATIC_CHECK(not TypeSet<int, float>::AllOf<FalsePredicate>);

  STATIC_CHECK(not TypeSet<>::AllOf<IsIntPredicate>);
  STATIC_CHECK(TypeSet<int>::AllOf<IsIntPredicate>);
  STATIC_CHECK(not TypeSet<float>::AllOf<IsIntPredicate>);
  STATIC_CHECK(not TypeSet<int, float>::AllOf<IsIntPredicate>);
  STATIC_CHECK(TypeSet<int, int>::AllOf<IsIntPredicate>);

  STATIC_CHECK(not TypeSet<>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(not TypeSet<int>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(TypeSet<float>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(not TypeSet<int, float>::AllOf<IsFloatPredicate>);
  STATIC_CHECK(TypeSet<float, float>::AllOf<IsFloatPredicate>);
}

template<typename>
struct TransformPredicate;

template<>
struct TransformPredicate<int> {
  using type = float;
};

template<>
struct TransformPredicate<float> {
  using type = unsigned int;
};

template<typename Type>
struct FloatPredicate {
  using type = float;
};

template<typename Type>
struct IntPredicate {
  using type = int;
};

template<typename Type>
struct IdentityPredicate {
  using type = Type;
};

TEST_CASE("`TypeSet` Transform") {
  STATIC_CHECK(TypeSet<>::Transform<IdentityPredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<int>::Transform<IdentityPredicate>{} == TypeSet<int>{});
  STATIC_CHECK(TypeSet<float>::Transform<IdentityPredicate>{} == TypeSet<float>{});
  STATIC_CHECK(TypeSet<int, float>::Transform<IdentityPredicate>{} == TypeSet<int, float>{});

  STATIC_CHECK(TypeSet<>::Transform<IntPredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<int>::Transform<IntPredicate>{} == TypeSet<int>{});
  STATIC_CHECK(TypeSet<float>::Transform<IntPredicate>{} == TypeSet<int>{});
  STATIC_CHECK(TypeSet<int, float>::Transform<IntPredicate>{} == TypeSet<int>{});

  STATIC_CHECK(TypeSet<>::Transform<FloatPredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<int>::Transform<FloatPredicate>{} == TypeSet<float>{});
  STATIC_CHECK(TypeSet<float>::Transform<FloatPredicate>{} == TypeSet<float>{});
  STATIC_CHECK(TypeSet<int, float>::Transform<FloatPredicate>{} == TypeSet<float>{});

  STATIC_CHECK(TypeSet<>::Transform<TransformPredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<int>::Transform<TransformPredicate>{} == TypeSet<float>{});
  STATIC_CHECK(TypeSet<float>::Transform<TransformPredicate>{} == TypeSet<unsigned int>{});
  STATIC_CHECK(TypeSet<int, float>::Transform<TransformPredicate>{} == TypeSet<unsigned int, float>{});
}

TEST_CASE("`TypeSet` Rebind") {
  STATIC_CHECK(TypeSet<>::Rebind<std::tuple>{} == std::tuple<>{});
  STATIC_CHECK(TypeSet<int>::Rebind<std::tuple>{} == std::tuple<int>{});
  STATIC_CHECK(TypeSet<float>::Rebind<std::tuple>{} == std::tuple<float>{});
  STATIC_CHECK(TypeSet<int, float>::Rebind<std::tuple>{} == std::tuple<int, float>{});
}

template<typename Type>
struct FilterTestPredicate {
  static constexpr bool value = std::integral<Type>;
};

TEST_CASE("`TypeSet` Filter") {
  STATIC_CHECK(TypeSet<>::Filter<TruePredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<int>::Filter<TruePredicate>{} == TypeSet<int>{});
  STATIC_CHECK(TypeSet<float>::Filter<TruePredicate>{} == TypeSet<float>{});
  STATIC_CHECK(TypeSet<int, float>::Filter<TruePredicate>{} == TypeSet<int, float>{});

  STATIC_CHECK(TypeSet<>::Filter<FalsePredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<int>::Filter<FalsePredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<float>::Filter<FalsePredicate>{} == TypeSet<>{});
  STATIC_CHECK(TypeSet<int, float>::Filter<FalsePredicate>{} == TypeSet<>{});

  STATIC_CHECK(TypeSet<signed int, float, unsigned int>::Filter<FilterTestPredicate>{} == TypeSet<signed int, unsigned int>{});
}

TEST_CASE("`TypeSet` Intersection") {
}

TEST_CASE("`TypeSet` Difference") {
}

TEST_CASE("`TypeSet` Symmetric Difference") {
}

TEST_CASE("`TypeSet` Union") {
}

