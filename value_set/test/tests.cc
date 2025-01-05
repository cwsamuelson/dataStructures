#include <value_set.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Value Set contains") {
  SECTION("Empty set") {
    STATIC_CHECK(not ValueSet<>::contains<4.2F>());
    STATIC_CHECK(not ValueSet<>::contains<-1138>());
    STATIC_CHECK(not ValueSet<>::contains<42>());
  }

  SECTION("Single value") {
    STATIC_CHECK(not ValueSet<4.2F>::contains<42>());
    STATIC_CHECK(not ValueSet<4.2F>::contains<-1138>());

    STATIC_CHECK(not ValueSet<42>::contains<-1138>());
    STATIC_CHECK(not ValueSet<42>::contains<4.2F>());

    STATIC_CHECK(not ValueSet<-1138>::contains<42>());
    STATIC_CHECK(not ValueSet<-1138>::contains<4.2F>());

    STATIC_CHECK(ValueSet<4.2F>::contains<4.2F>());
    STATIC_CHECK(ValueSet<42>::contains<42>());
    STATIC_CHECK(ValueSet<-1138>::contains<-1138>());
  }

  SECTION("Multiple values") {
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::contains<-1138>());
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::contains<42>());
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::contains<4.2F>());

    STATIC_CHECK(not ValueSet<42, 4.2F>::contains<-1138>());
    STATIC_CHECK(not ValueSet<-1138, 4.2F>::contains<42>());
    STATIC_CHECK(not ValueSet<-1138, 42>::contains<4.2F>());
  }
}

TEST_CASE("Value Set insert") {
  SECTION("Empty set") {
    STATIC_CHECK(ValueSet<>::insert<42>().contains<42>());
    STATIC_CHECK(ValueSet<>::insert<-1138>().contains<-1138>());
    STATIC_CHECK(ValueSet<>::insert<4.2F>().contains<4.2F>());

    STATIC_CHECK(not ValueSet<>::insert<42>().contains<-1138>());
    STATIC_CHECK(not ValueSet<>::insert<42>().contains<4.2F>());

    STATIC_CHECK(not ValueSet<>::insert<-1138>().contains<42>());
    STATIC_CHECK(not ValueSet<>::insert<-1138>().contains<4.2F>());

    STATIC_CHECK(not ValueSet<>::insert<4.2F>().contains<-1138>());
    STATIC_CHECK(not ValueSet<>::insert<4.2F>().contains<42>());
  }

  SECTION("Single value") {
    STATIC_CHECK(ValueSet<4.2F>::insert<42>().contains<42>());
    STATIC_CHECK(ValueSet<4.2F>::insert<-1138>().contains<-1138>());

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<4.2F>::insert<4.2F>().contains<4.2F>());
      STATIC_CHECK(ValueSet<-1138>::insert<-1138>().contains<-1138>());
      STATIC_CHECK(ValueSet<42>::insert<42>().contains<42>());

      STATIC_CHECK(not ValueSet<4.2F>::insert<4.2F>().contains<-1138>());
      STATIC_CHECK(not ValueSet<4.2F>::insert<4.2F>().contains<42>());

      STATIC_CHECK(not ValueSet<-1138>::insert<-1138>().contains<4.2F>());
      STATIC_CHECK(not ValueSet<-1138>::insert<-1138>().contains<42>());

      STATIC_CHECK(not ValueSet<42>::insert<42>().contains<4.2F>());
      STATIC_CHECK(not ValueSet<42>::insert<42>().contains<-1138>());
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(ValueSet<4.2F, 42>::insert<-1138>().contains<-1138>());
    STATIC_CHECK(ValueSet<4.2F, -1138>::insert<42>().contains<42>());
    STATIC_CHECK(ValueSet<-1138, 42>::insert<4.2F>().contains<4.2F>());

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<4.2F, 42>::insert<4.2F>().contains<4.2F>());
      STATIC_CHECK(ValueSet<4.2F, 42>::insert<42>().contains<42>());

      STATIC_CHECK(ValueSet<4.2F, -1138>::insert<-1138>().contains<-1138>());
      STATIC_CHECK(ValueSet<4.2F, -1138>::insert<4.2F>().contains<4.2F>());

      STATIC_CHECK(ValueSet<-1138, 42>::insert<-1138>().contains<-1138>());
      STATIC_CHECK(ValueSet<-1138, 42>::insert<42>().contains<42>());
    }
  }
}

TEST_CASE("Value Set erase") {
  SECTION("Empty set") {
    STATIC_CHECK(ValueSet<>::erase<42>().empty());
    STATIC_CHECK(ValueSet<>::erase<-1138>().empty());
    STATIC_CHECK(ValueSet<>::erase<4.2F>().empty());

    STATIC_CHECK(not ValueSet<>::erase<42>().contains<42>());
    STATIC_CHECK(not ValueSet<>::erase<42>().contains<-1138>());
    STATIC_CHECK(not ValueSet<>::erase<42>().contains<4.2F>());

    STATIC_CHECK(not ValueSet<>::erase<-1138>().contains<-1138>());
    STATIC_CHECK(not ValueSet<>::erase<-1138>().contains<42>());
    STATIC_CHECK(not ValueSet<>::erase<-1138>().contains<4.2F>());

    STATIC_CHECK(not ValueSet<>::erase<4.2F>().contains<-1138>());
    STATIC_CHECK(not ValueSet<>::erase<4.2F>().contains<42>());
    STATIC_CHECK(not ValueSet<>::erase<4.2F>().contains<4.2F>());
  }

  SECTION("Single value") {
    STATIC_CHECK(ValueSet<4.2F>::erase<4.2F>().empty());
    STATIC_CHECK(ValueSet<42>::erase<42>().empty());
    STATIC_CHECK(ValueSet<-1138>::erase<-1138>().empty());

    STATIC_CHECK(not ValueSet<4.2F>::erase<4.2F>().contains<4.2F>());
    STATIC_CHECK(not ValueSet<-1138>::erase<-1138>().contains<-1138>());
    STATIC_CHECK(not ValueSet<42>::erase<42>().contains<42>());

    STATIC_CHECK(not ValueSet<4.2F>::erase<4.2F>().contains<-1138>());
    STATIC_CHECK(not ValueSet<4.2F>::erase<4.2F>().contains<42>());

    STATIC_CHECK(not ValueSet<-1138>::erase<-1138>().contains<4.2F>());
    STATIC_CHECK(not ValueSet<-1138>::erase<-1138>().contains<42>());

    STATIC_CHECK(not ValueSet<42>::erase<42>().contains<4.2F>());
    STATIC_CHECK(not ValueSet<42>::erase<42>().contains<-1138>());

    SECTION("Idempotent") {
      STATIC_CHECK(not ValueSet<4.2F>::erase<42>().contains<42>());
      STATIC_CHECK(not ValueSet<4.2F>::erase<-1138>().contains<-1138>());
      STATIC_CHECK(not ValueSet<4.2F>::erase<4.2F>().contains<4.2F>());
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(not ValueSet<4.2F, 42>::erase<42>().contains<42>());
    STATIC_CHECK(not ValueSet<4.2F, 42>::erase<4.2F>().contains<4.2F>());

    STATIC_CHECK(not ValueSet<4.2F, -1138>::erase<-1138>().contains<-1138>());
    STATIC_CHECK(not ValueSet<4.2F, -1138>::erase<4.2F>().contains<4.2F>());

    STATIC_CHECK(not ValueSet<-1138, 42>::erase<-1138>().contains<-1138>());
    STATIC_CHECK(not ValueSet<-1138, 42>::erase<42>().contains<42>());

    SECTION("Idempotent") {
      STATIC_CHECK(not ValueSet<4.2F, 42>::erase<-1138>().contains<-1138>());
      STATIC_CHECK(not ValueSet<4.2F, -1138>::erase<42>().contains<42>());
      STATIC_CHECK(not ValueSet<-1138, 42>::erase<4.2F>().contains<4.2F>());

      STATIC_CHECK(ValueSet<4.2F, 42>::insert<4.2F>().contains<4.2F>());
      STATIC_CHECK(ValueSet<4.2F, 42>::insert<42>().contains<42>());

      STATIC_CHECK(ValueSet<4.2F, -1138>::insert<-1138>().contains<-1138>());
      STATIC_CHECK(ValueSet<4.2F, -1138>::insert<4.2F>().contains<4.2F>());

      STATIC_CHECK(ValueSet<-1138, 42>::insert<-1138>().contains<-1138>());
      STATIC_CHECK(ValueSet<-1138, 42>::insert<42>().contains<42>());
    }
  }
}

TEST_CASE("Value Set size") {
  SECTION("Empty set") {
    STATIC_CHECK(ValueSet<>::size() == 0);

    STATIC_CHECK(ValueSet<>::insert<42>().size() == 1);
    STATIC_CHECK(ValueSet<>::insert<-1138>().size() == 1);
    STATIC_CHECK(ValueSet<>::insert<4.2F>().size() == 1);
  }

  SECTION("Single value") {
    STATIC_CHECK(ValueSet<42>::size() == 1);
    STATIC_CHECK(ValueSet<-1138>::size() == 1);
    STATIC_CHECK(ValueSet<4.2F>::size() == 1);

    STATIC_CHECK(ValueSet<42>::insert<-1138>().size() == 2);
    STATIC_CHECK(ValueSet<42>::insert<4.2F>().size() == 2);

    STATIC_CHECK(ValueSet<-1138>::insert<42>().size() == 2);
    STATIC_CHECK(ValueSet<-1138>::insert<4.2F>().size() == 2);

    STATIC_CHECK(ValueSet<4.2F>::insert<-1138>().size() == 2);
    STATIC_CHECK(ValueSet<4.2F>::insert<42>().size() == 2);

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<42>::insert<42>().size() == 1);
      STATIC_CHECK(ValueSet<-1138>::insert<-1138>().size() == 1);
      STATIC_CHECK(ValueSet<4.2F>::insert<4.2F>().size() == 1);
    }
  }

  SECTION("Multiple values") {
    STATIC_CHECK(ValueSet<-1138, 42, 4.2F>::size() == 3);

    STATIC_CHECK(ValueSet<-1138, 4.2F>::size() == 2);
    STATIC_CHECK(ValueSet<-1138, 42>::size() == 2);
    STATIC_CHECK(ValueSet<4.2F, 42>::size() == 2);

    STATIC_CHECK(ValueSet<-1138, 42>::insert<4.2F>().size() == 3);
    STATIC_CHECK(ValueSet<4.2F, 42>::insert<-1138>().size() == 3);
    STATIC_CHECK(ValueSet<-1138, 4.2F>::insert<42>().size() == 3);

    SECTION("Idempotent") {
      STATIC_CHECK(ValueSet<-1138, 42>::insert<-1138>().size() == 2);
      STATIC_CHECK(ValueSet<-1138, 42>::insert<42>().size() == 2);

      STATIC_CHECK(ValueSet<4.2F, 42>::insert<42>().size() == 2);
      STATIC_CHECK(ValueSet<4.2F, 42>::insert<4.2F>().size() == 2);

      STATIC_CHECK(ValueSet<-1138, 4.2F>::insert<-1138>().size() == 2);
      STATIC_CHECK(ValueSet<-1138, 4.2F>::insert<4.2F>().size() == 2);
    }
  }
}

TEST_CASE("Value Set empty") {
  SECTION("Static style") {
    STATIC_CHECK(ValueSet<>::empty());

    STATIC_CHECK(not ValueSet<>::insert<42>().empty());
    STATIC_CHECK(not ValueSet<>::insert<-1138>().empty());
    STATIC_CHECK(not ValueSet<>::insert<4.2F>().empty());

    STATIC_CHECK(not ValueSet<-1138>::empty());
    STATIC_CHECK(not ValueSet<42>::empty());
    STATIC_CHECK(not ValueSet<4.2F>::empty());

    STATIC_CHECK(not ValueSet<-1138>::insert<42>().empty());
    STATIC_CHECK(not ValueSet<-1138>::insert<-1138>().empty());
    STATIC_CHECK(not ValueSet<-1138>::insert<4.2F>().empty());

    STATIC_CHECK(not ValueSet<42>::insert<-1138>().empty());
    STATIC_CHECK(not ValueSet<42>::insert<42>().empty());
    STATIC_CHECK(not ValueSet<42>::insert<4.2F>().empty());

    STATIC_CHECK(not ValueSet<4.2F>::insert<42>().empty());
    STATIC_CHECK(not ValueSet<4.2F>::insert<-1138>().empty());
    STATIC_CHECK(not ValueSet<4.2F>::insert<4.2F>().empty());

    STATIC_CHECK(not ValueSet<-1138, -1138>::empty());
    STATIC_CHECK(not ValueSet<4.2F, 42>::empty());
    STATIC_CHECK(not ValueSet<4.2F, -1138>::empty());

    STATIC_CHECK(not ValueSet<-1138, 42>::insert<4.2F>().empty());
    STATIC_CHECK(not ValueSet<-1138, 42>::insert<-1138>().empty());
    STATIC_CHECK(not ValueSet<-1138, 42>::insert<42>().empty());

    STATIC_CHECK(not ValueSet<4.2F, 42>::insert<-1138>().empty());
    STATIC_CHECK(not ValueSet<4.2F, 42>::insert<42>().empty());
    STATIC_CHECK(not ValueSet<4.2F, 42>::insert<4.2F>().empty());

    STATIC_CHECK(not ValueSet<4.2F, -1138>::insert<42>().empty());
    STATIC_CHECK(not ValueSet<4.2F, -1138>::insert<-1138>().empty());
    STATIC_CHECK(not ValueSet<4.2F, -1138>::insert<4.2F>().empty());

    STATIC_CHECK(not ValueSet<4.2F, -1138, 42>::empty());
  }

  SECTION("Runtime style") {
    constexpr ValueSet<> empty_ts;
    STATIC_CHECK(empty_ts.empty());

    STATIC_CHECK(not empty_ts.insert<42>().empty());
    STATIC_CHECK(not empty_ts.insert<-1138>().empty());
    STATIC_CHECK(not empty_ts.insert<4.2F>().empty());

    constexpr ValueSet<-1138>   si_ts;
    constexpr ValueSet<42> ui_ts;
    constexpr ValueSet<4.2F>        f_ts;

    STATIC_CHECK(not si_ts.empty());

    STATIC_CHECK(not si_ts.insert<42>().empty());
    STATIC_CHECK(not si_ts.insert<-1138>().empty());
    STATIC_CHECK(not si_ts.insert<4.2F>().empty());

    STATIC_CHECK(not ui_ts.empty());

    STATIC_CHECK(not ui_ts.insert<-1138>().empty());
    STATIC_CHECK(not ui_ts.insert<42>().empty());
    STATIC_CHECK(not ui_ts.insert<4.2F>().empty());

    STATIC_CHECK(not f_ts.empty());

    STATIC_CHECK(not f_ts.insert<42>().empty());
    STATIC_CHECK(not f_ts.insert<-1138>().empty());
    STATIC_CHECK(not f_ts.insert<4.2F>().empty());

    constexpr ValueSet<-1138, 42> si_ui_ts;
    constexpr ValueSet<4.2F, 42>      f_ui_ts;
    constexpr ValueSet<4.2F, -1138>        f_si_ts;

    STATIC_CHECK(not si_ui_ts.empty());
    STATIC_CHECK(not f_ui_ts.empty());
    STATIC_CHECK(not f_si_ts.empty());

    STATIC_CHECK(not si_ui_ts.insert<4.2F>().empty());
    STATIC_CHECK(not si_ui_ts.insert<-1138>().empty());
    STATIC_CHECK(not si_ui_ts.insert<42>().empty());

    STATIC_CHECK(not f_ui_ts.insert<-1138>().empty());
    STATIC_CHECK(not f_ui_ts.insert<42>().empty());
    STATIC_CHECK(not f_ui_ts.insert<4.2F>().empty());

    STATIC_CHECK(not f_si_ts.insert<42>().empty());
    STATIC_CHECK(not f_si_ts.insert<-1138>().empty());
    STATIC_CHECK(not f_si_ts.insert<4.2F>().empty());

    constexpr ValueSet<4.2F, -1138, 42> all_ts;
    STATIC_CHECK(not all_ts.empty());
  }
}

TEST_CASE("Value Set equality") {
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

  STATIC_CHECK(ValueSet<>::insert<42>() == ValueSet<42> {});
  STATIC_CHECK(ValueSet<>::insert<-1138>() == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<>::insert<4.2F>() == ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<42>::insert<42>() == ValueSet<42> {});
  STATIC_CHECK(ValueSet<-1138>::insert<-1138>() == ValueSet<-1138> {});
  STATIC_CHECK(ValueSet<4.2F>::insert<4.2F>() == ValueSet<4.2F> {});

  STATIC_CHECK(ValueSet<-1138>::insert<42>() == ValueSet<42, -1138> {});
  STATIC_CHECK(ValueSet<-1138>::insert<4.2F>() == ValueSet<4.2F, -1138> {});

  STATIC_CHECK(ValueSet<42>::insert<-1138>() == ValueSet<-1138, 42> {});
  STATIC_CHECK(ValueSet<42>::insert<4.2F>() == ValueSet<4.2F, 42> {});

  STATIC_CHECK(ValueSet<4.2F>::insert<-1138>() == ValueSet<4.2F, -1138> {});
  STATIC_CHECK(ValueSet<4.2F>::insert<42>() == ValueSet<4.2F, 42> {});

  STATIC_CHECK(ValueSet<4.2F, 42>::erase<4.2F>() == ValueSet<42> {});
  STATIC_CHECK(ValueSet<4.2F, 42>::erase<42>() == ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<4.2F, 42>::erase<-1138>() == ValueSet<42, 4.2F> {});
}

TEST_CASE("Duplicate Value in ValueSet") {
  STATIC_CHECK(ValueSet<4.2F>::insert<4.2F>() == ValueSet<4.2F> {});

  STATIC_CHECK(not ValueSet<4.2F, 4.2F>::erase<4.2F>().contains<4.2F>());
  STATIC_CHECK(ValueSet<4.2F, 4.2F>::erase<4.2F>() != ValueSet<4.2F> {});
  STATIC_CHECK(ValueSet<4.2F, 4.2F>::erase<4.2F>() == ValueSet<> {});
  STATIC_CHECK(ValueSet<4.2F, 4.2F>::erase<4.2F>().empty());
}
