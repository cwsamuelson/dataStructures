#include <type_set.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("Type Set") {
  SECTION("Contains") {
    SECTION("Empty set") {
      STATIC_CHECK(not TypeSet<>::contains<float>());
      STATIC_CHECK(not TypeSet<>::contains<signed int>());
      STATIC_CHECK(not TypeSet<>::contains<unsigned int>());
    }

    SECTION("Single value") {
      STATIC_CHECK(not TypeSet<float>::contains<unsigned int>());
      STATIC_CHECK(not TypeSet<float>::contains<signed int>());

      STATIC_CHECK(not TypeSet<unsigned int>::contains<signed int>());
      STATIC_CHECK(not TypeSet<unsigned int>::contains<float>());

      STATIC_CHECK(not TypeSet<signed int>::contains<unsigned int>());
      STATIC_CHECK(not TypeSet<signed int>::contains<float>());

      STATIC_CHECK(TypeSet<float>::contains<float>());
      STATIC_CHECK(TypeSet<unsigned int>::contains<unsigned int>());
      STATIC_CHECK(TypeSet<signed int>::contains<signed int>());
    }

    SECTION("Multiple values") {
      STATIC_CHECK(TypeSet<signed int, unsigned int, float>::contains<signed int>());
      STATIC_CHECK(TypeSet<signed int, unsigned int, float>::contains<unsigned int>());
      STATIC_CHECK(TypeSet<signed int, unsigned int, float>::contains<float>());

      STATIC_CHECK(not TypeSet<unsigned int, float>::contains<signed int>());
      STATIC_CHECK(not TypeSet<signed int, float>::contains<unsigned int>());
      STATIC_CHECK(not TypeSet<signed int, unsigned int>::contains<float>());
    }
  }

  SECTION("insert") {
    SECTION("Empty set") {
      STATIC_CHECK(TypeSet<>::insert<unsigned int>().contains<unsigned int>());
      STATIC_CHECK(TypeSet<>::insert<signed int>().contains<signed int>());
      STATIC_CHECK(TypeSet<>::insert<float>().contains<float>());

      STATIC_CHECK(not TypeSet<>::insert<unsigned int>().contains<signed int>());
      STATIC_CHECK(not TypeSet<>::insert<unsigned int>().contains<float>());

      STATIC_CHECK(not TypeSet<>::insert<signed int>().contains<unsigned int>());
      STATIC_CHECK(not TypeSet<>::insert<signed int>().contains<float>());

      STATIC_CHECK(not TypeSet<>::insert<float>().contains<signed int>());
      STATIC_CHECK(not TypeSet<>::insert<float>().contains<unsigned int>());
    }

    SECTION("Single value") {
      STATIC_CHECK(TypeSet<float>::insert<unsigned int>().contains<unsigned int>());
      STATIC_CHECK(TypeSet<float>::insert<signed int>().contains<signed int>());

      SECTION("Idempotent") {
        STATIC_CHECK(TypeSet<float>::insert<float>().contains<float>());
        STATIC_CHECK(TypeSet<signed int>::insert<signed int>().contains<signed int>());
        STATIC_CHECK(TypeSet<unsigned int>::insert<unsigned int>().contains<unsigned int>());

        STATIC_CHECK(not TypeSet<float>::insert<float>().contains<signed int>());
        STATIC_CHECK(not TypeSet<float>::insert<float>().contains<unsigned int>());

        STATIC_CHECK(not TypeSet<signed int>::insert<signed int>().contains<float>());
        STATIC_CHECK(not TypeSet<signed int>::insert<signed int>().contains<unsigned int>());

        STATIC_CHECK(not TypeSet<unsigned int>::insert<unsigned int>().contains<float>());
        STATIC_CHECK(not TypeSet<unsigned int>::insert<unsigned int>().contains<signed int>());
      }
    }

    SECTION("Multiple values") {
      STATIC_CHECK(TypeSet<float, unsigned int>::insert<signed int>().contains<signed int>());
      STATIC_CHECK(TypeSet<float, signed int>::insert<unsigned int>().contains<unsigned int>());
      STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<float>().contains<float>());

      SECTION("Idempotent") {
        STATIC_CHECK(TypeSet<float, unsigned int>::insert<float>().contains<float>());
        STATIC_CHECK(TypeSet<float, unsigned int>::insert<unsigned int>().contains<unsigned int>());

        STATIC_CHECK(TypeSet<float, signed int>::insert<signed int>().contains<signed int>());
        STATIC_CHECK(TypeSet<float, signed int>::insert<float>().contains<float>());

        STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<signed int>().contains<signed int>());
        STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<unsigned int>().contains<unsigned int>());
      }
    }
  }

  SECTION("erase") {
    SECTION("Empty set") {
      STATIC_CHECK(TypeSet<>::erase<unsigned int>().empty());
      STATIC_CHECK(TypeSet<>::erase<signed int>().empty());
      STATIC_CHECK(TypeSet<>::erase<float>().empty());

      STATIC_CHECK(not TypeSet<>::erase<unsigned int>().contains<unsigned int>());
      STATIC_CHECK(not TypeSet<>::erase<unsigned int>().contains<signed int>());
      STATIC_CHECK(not TypeSet<>::erase<unsigned int>().contains<float>());

      STATIC_CHECK(not TypeSet<>::erase<signed int>().contains<signed int>());
      STATIC_CHECK(not TypeSet<>::erase<signed int>().contains<unsigned int>());
      STATIC_CHECK(not TypeSet<>::erase<signed int>().contains<float>());

      STATIC_CHECK(not TypeSet<>::erase<float>().contains<signed int>());
      STATIC_CHECK(not TypeSet<>::erase<float>().contains<unsigned int>());
      STATIC_CHECK(not TypeSet<>::erase<float>().contains<float>());
    }

    SECTION("Single value") {
      STATIC_CHECK(TypeSet<float>::erase<float>().empty());
      STATIC_CHECK(TypeSet<unsigned int>::erase<unsigned int>().empty());
      STATIC_CHECK(TypeSet<signed int>::erase<signed int>().empty());

      STATIC_CHECK(not TypeSet<float>::erase<float>().contains<float>());
      STATIC_CHECK(not TypeSet<signed int>::erase<signed int>().contains<signed int>());
      STATIC_CHECK(not TypeSet<unsigned int>::erase<unsigned int>().contains<unsigned int>());

      STATIC_CHECK(not TypeSet<float>::erase<float>().contains<signed int>());
      STATIC_CHECK(not TypeSet<float>::erase<float>().contains<unsigned int>());

      STATIC_CHECK(not TypeSet<signed int>::erase<signed int>().contains<float>());
      STATIC_CHECK(not TypeSet<signed int>::erase<signed int>().contains<unsigned int>());

      STATIC_CHECK(not TypeSet<unsigned int>::erase<unsigned int>().contains<float>());
      STATIC_CHECK(not TypeSet<unsigned int>::erase<unsigned int>().contains<signed int>());

      SECTION("Idempotent") {
        STATIC_CHECK(not TypeSet<float>::erase<unsigned int>().contains<unsigned int>());
        STATIC_CHECK(not TypeSet<float>::erase<signed int>().contains<signed int>());
        STATIC_CHECK(not TypeSet<float>::erase<float>().contains<float>());
      }
    }

    SECTION("Multiple values") {
      STATIC_CHECK(not TypeSet<float, unsigned int>::erase<unsigned int>().contains<unsigned int>());
      STATIC_CHECK(not TypeSet<float, unsigned int>::erase<float>().contains<float>());

      STATIC_CHECK(not TypeSet<float, signed int>::erase<signed int>().contains<signed int>());
      STATIC_CHECK(not TypeSet<float, signed int>::erase<float>().contains<float>());

      STATIC_CHECK(not TypeSet<signed int, unsigned int>::erase<signed int>().contains<signed int>());
      STATIC_CHECK(not TypeSet<signed int, unsigned int>::erase<unsigned int>().contains<unsigned int>());

      SECTION("Idempotent") {
        STATIC_CHECK(not TypeSet<float, unsigned int>::erase<signed int>().contains<signed int>());
        STATIC_CHECK(not TypeSet<float, signed int>::erase<unsigned int>().contains<unsigned int>());
        STATIC_CHECK(not TypeSet<signed int, unsigned int>::erase<float>().contains<float>());

        STATIC_CHECK(TypeSet<float, unsigned int>::insert<float>().contains<float>());
        STATIC_CHECK(TypeSet<float, unsigned int>::insert<unsigned int>().contains<unsigned int>());

        STATIC_CHECK(TypeSet<float, signed int>::insert<signed int>().contains<signed int>());
        STATIC_CHECK(TypeSet<float, signed int>::insert<float>().contains<float>());

        STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<signed int>().contains<signed int>());
        STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<unsigned int>().contains<unsigned int>());
      }
    }
  }

  SECTION("size") {
    SECTION("Empty set") {
      STATIC_CHECK(TypeSet<>::size() == 0);

      STATIC_CHECK(TypeSet<>::insert<unsigned int>().size() == 1);
      STATIC_CHECK(TypeSet<>::insert<signed int>().size() == 1);
      STATIC_CHECK(TypeSet<>::insert<float>().size() == 1);
    }

    SECTION("Single value") {
      STATIC_CHECK(TypeSet<unsigned int>::size() == 1);
      STATIC_CHECK(TypeSet<signed int>::size() == 1);
      STATIC_CHECK(TypeSet<float>::size() == 1);

      STATIC_CHECK(TypeSet<unsigned int>::insert<signed int>().size() == 2);
      STATIC_CHECK(TypeSet<unsigned int>::insert<float>().size() == 2);

      STATIC_CHECK(TypeSet<signed int>::insert<unsigned int>().size() == 2);
      STATIC_CHECK(TypeSet<signed int>::insert<float>().size() == 2);

      STATIC_CHECK(TypeSet<float>::insert<signed int>().size() == 2);
      STATIC_CHECK(TypeSet<float>::insert<unsigned int>().size() == 2);

      SECTION("Idempotent") {
        STATIC_CHECK(TypeSet<unsigned int>::insert<unsigned int>().size() == 1);
        STATIC_CHECK(TypeSet<signed int>::insert<signed int>().size() == 1);
        STATIC_CHECK(TypeSet<float>::insert<float>().size() == 1);
      }
    }

    SECTION("Multiple values") {
      STATIC_CHECK(TypeSet<signed int, unsigned int, float>::size() == 3);

      STATIC_CHECK(TypeSet<signed int, float>::size() == 2);
      STATIC_CHECK(TypeSet<signed int, unsigned int>::size() == 2);
      STATIC_CHECK(TypeSet<float, unsigned int>::size() == 2);

      STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<float>().size() == 3);
      STATIC_CHECK(TypeSet<float, unsigned int>::insert<signed int>().size() == 3);
      STATIC_CHECK(TypeSet<signed int, float>::insert<unsigned int>().size() == 3);

      SECTION("Idempotent") {
        STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<signed int>().size() == 2);
        STATIC_CHECK(TypeSet<signed int, unsigned int>::insert<unsigned int>().size() == 2);

        STATIC_CHECK(TypeSet<float, unsigned int>::insert<unsigned int>().size() == 2);
        STATIC_CHECK(TypeSet<float, unsigned int>::insert<float>().size() == 2);

        STATIC_CHECK(TypeSet<signed int, float>::insert<signed int>().size() == 2);
        STATIC_CHECK(TypeSet<signed int, float>::insert<float>().size() == 2);
      }
    }
  }

  SECTION("empty") {
    SECTION("Static style") {
      STATIC_CHECK(TypeSet<>::empty());

      STATIC_CHECK(not TypeSet<>::insert<unsigned int>().empty());
      STATIC_CHECK(not TypeSet<>::insert<signed int>().empty());
      STATIC_CHECK(not TypeSet<>::insert<float>().empty());

      STATIC_CHECK(not TypeSet<signed int>::empty());
      STATIC_CHECK(not TypeSet<unsigned int>::empty());
      STATIC_CHECK(not TypeSet<float>::empty());

      STATIC_CHECK(not TypeSet<signed int>::insert<unsigned int>().empty());
      STATIC_CHECK(not TypeSet<signed int>::insert<signed int>().empty());
      STATIC_CHECK(not TypeSet<signed int>::insert<float>().empty());

      STATIC_CHECK(not TypeSet<unsigned int>::insert<signed int>().empty());
      STATIC_CHECK(not TypeSet<unsigned int>::insert<unsigned int>().empty());
      STATIC_CHECK(not TypeSet<unsigned int>::insert<float>().empty());

      STATIC_CHECK(not TypeSet<float>::insert<unsigned int>().empty());
      STATIC_CHECK(not TypeSet<float>::insert<signed int>().empty());
      STATIC_CHECK(not TypeSet<float>::insert<float>().empty());

      STATIC_CHECK(not TypeSet<signed int, signed int>::empty());
      STATIC_CHECK(not TypeSet<float, unsigned int>::empty());
      STATIC_CHECK(not TypeSet<float, signed int>::empty());

      STATIC_CHECK(not TypeSet<signed int, unsigned int>::insert<float>().empty());
      STATIC_CHECK(not TypeSet<signed int, unsigned int>::insert<signed int>().empty());
      STATIC_CHECK(not TypeSet<signed int, unsigned int>::insert<unsigned int>().empty());

      STATIC_CHECK(not TypeSet<float, unsigned int>::insert<signed int>().empty());
      STATIC_CHECK(not TypeSet<float, unsigned int>::insert<unsigned int>().empty());
      STATIC_CHECK(not TypeSet<float, unsigned int>::insert<float>().empty());

      STATIC_CHECK(not TypeSet<float, signed int>::insert<unsigned int>().empty());
      STATIC_CHECK(not TypeSet<float, signed int>::insert<signed int>().empty());
      STATIC_CHECK(not TypeSet<float, signed int>::insert<float>().empty());

      STATIC_CHECK(not TypeSet<float, signed int, unsigned int>::empty());
    }

    SECTION("Runtime style") {
      constexpr TypeSet<> empty_ts;
      STATIC_CHECK(empty_ts.empty());

      STATIC_CHECK(not empty_ts.insert<unsigned int>().empty());
      STATIC_CHECK(not empty_ts.insert<signed int>().empty());
      STATIC_CHECK(not empty_ts.insert<float>().empty());

      constexpr TypeSet<signed int>   si_ts;
      constexpr TypeSet<unsigned int> ui_ts;
      constexpr TypeSet<float>        f_ts;

      STATIC_CHECK(not si_ts.empty());

      STATIC_CHECK(not si_ts.insert<unsigned int>().empty());
      STATIC_CHECK(not si_ts.insert<signed int>().empty());
      STATIC_CHECK(not si_ts.insert<float>().empty());

      STATIC_CHECK(not ui_ts.empty());

      STATIC_CHECK(not ui_ts.insert<signed int>().empty());
      STATIC_CHECK(not ui_ts.insert<unsigned int>().empty());
      STATIC_CHECK(not ui_ts.insert<float>().empty());

      STATIC_CHECK(not f_ts.empty());

      STATIC_CHECK(not f_ts.insert<unsigned int>().empty());
      STATIC_CHECK(not f_ts.insert<signed int>().empty());
      STATIC_CHECK(not f_ts.insert<float>().empty());

      constexpr TypeSet<signed int, unsigned int> si_ui_ts;
      constexpr TypeSet<float, unsigned int>      f_ui_ts;
      constexpr TypeSet<float, signed int>        f_si_ts;

      STATIC_CHECK(not si_ui_ts.empty());
      STATIC_CHECK(not f_ui_ts.empty());
      STATIC_CHECK(not f_si_ts.empty());

      STATIC_CHECK(not si_ui_ts.insert<float>().empty());
      STATIC_CHECK(not si_ui_ts.insert<signed int>().empty());
      STATIC_CHECK(not si_ui_ts.insert<unsigned int>().empty());

      STATIC_CHECK(not f_ui_ts.insert<signed int>().empty());
      STATIC_CHECK(not f_ui_ts.insert<unsigned int>().empty());
      STATIC_CHECK(not f_ui_ts.insert<float>().empty());

      STATIC_CHECK(not f_si_ts.insert<unsigned int>().empty());
      STATIC_CHECK(not f_si_ts.insert<signed int>().empty());
      STATIC_CHECK(not f_si_ts.insert<float>().empty());

      constexpr TypeSet<float, signed int, unsigned int> all_ts;
      STATIC_CHECK(not all_ts.empty());
    }
  }

  SECTION("equality") {
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

    STATIC_CHECK(TypeSet<>::insert<unsigned int>() == TypeSet<unsigned int> {});
    STATIC_CHECK(TypeSet<>::insert<signed int>() == TypeSet<signed int> {});
    STATIC_CHECK(TypeSet<>::insert<float>() == TypeSet<float> {});

    STATIC_CHECK(TypeSet<unsigned int>::insert<unsigned int>() == TypeSet<unsigned int> {});
    STATIC_CHECK(TypeSet<signed int>::insert<signed int>() == TypeSet<signed int> {});
    STATIC_CHECK(TypeSet<float>::insert<float>() == TypeSet<float> {});

    STATIC_CHECK(TypeSet<signed int>::insert<unsigned int>() == TypeSet<unsigned int, signed int> {});
    STATIC_CHECK(TypeSet<signed int>::insert<float>() == TypeSet<float, signed int> {});

    STATIC_CHECK(TypeSet<unsigned int>::insert<signed int>() == TypeSet<signed int, unsigned int> {});
    STATIC_CHECK(TypeSet<unsigned int>::insert<float>() == TypeSet<float, unsigned int> {});

    STATIC_CHECK(TypeSet<float>::insert<signed int>() == TypeSet<float, signed int> {});
    STATIC_CHECK(TypeSet<float>::insert<unsigned int>() == TypeSet<float, unsigned int> {});

    STATIC_CHECK(TypeSet<float, unsigned int>::erase<float>() == TypeSet<unsigned int> {});
    STATIC_CHECK(TypeSet<float, unsigned int>::erase<unsigned int>() == TypeSet<float> {});
    STATIC_CHECK(TypeSet<float, unsigned int>::erase<signed int>() == TypeSet<unsigned int, float> {});
  }
}
