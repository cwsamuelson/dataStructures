#include <try_wrap.hh>

#include <catch2/catch_all.hpp>

#include <utility>

using namespace flp;

void nodata_nothrow() noexcept {}

void nodata_could_throw() {}

void nodata_throws() {
  throw std::runtime_error("nodata");
}

int withdata_nothrow() noexcept {
  return 42;
}

int withdata_could_throw() {
  return 1138;
}

int withdata_throws() {
  throw std::runtime_error("with_data");
}

int& static_data_could_throw() {
  static int i = 42;
  if (42 % 69 == 0) {
    throw std::runtime_error("static_data");
  }
  return i;
}

template<bool Throwing, typename Return, typename... Args>
struct Functor {
  Return operator()(Args&&... args) noexcept(not Throwing) {
    if constexpr (Throwing) {
      throw std::runtime_error("Throwing Functor");
    }
    return {};
  }

  // noexcept etc variations?
  static Return static_member() noexcept(not Throwing) {
    if constexpr (Throwing) {
      throw std::runtime_error("Throwing Static Functor");
    }
    return {};
  }

  Return member_function() noexcept(not Throwing) {
    if constexpr (Throwing) {
      throw std::runtime_error("Throwing Static Functor");
    }
    return {};
  }
};

TEST_CASE("try_wrap") {
  SECTION("No exceptions thrown") {
    STATIC_CHECK(std::is_nothrow_invocable_v<decltype(TryWrap { nodata_nothrow })>);
    STATIC_CHECK(std::is_nothrow_invocable_v<decltype(TryWrap { nodata_could_throw })>);
    STATIC_CHECK(std::is_nothrow_invocable_v<decltype(TryWrap { nodata_throws })>);
    STATIC_CHECK(std::is_nothrow_invocable_v<decltype(TryWrap { withdata_nothrow })>);
    STATIC_CHECK(std::is_nothrow_invocable_v<decltype(TryWrap { withdata_could_throw })>);
    STATIC_CHECK(std::is_nothrow_invocable_v<decltype(TryWrap { withdata_throws })>);
    STATIC_CHECK(std::is_nothrow_invocable_v<decltype(TryWrap { static_data_could_throw })>);

    CHECK_NOTHROW(TryWrap { nodata_nothrow }());
    CHECK_NOTHROW(TryWrap { nodata_could_throw }());
    CHECK_NOTHROW(TryWrap { nodata_throws }());
    CHECK_NOTHROW(TryWrap { withdata_nothrow }());
    CHECK_NOTHROW(TryWrap { withdata_could_throw }());
    CHECK_NOTHROW(TryWrap { withdata_throws }());
    CHECK_NOTHROW(TryWrap { static_data_could_throw }());
  }

  SECTION("References forwarded") {
    SECTION("LValue return value") {
      STATIC_CHECK(not std::is_nothrow_invocable_v<decltype(static_data_could_throw)>);
      STATIC_CHECK(not std::is_void_v<std::invoke_result_t<decltype(static_data_could_throw)>>);

      {
        auto [value, error] = TryWrap { static_data_could_throw }();
        CHECK(error == nullptr);
        REQUIRE(value.has_value());
        CHECK(*value == 42);
        ++*value;
      }

      {
        auto&& [value, error] = TryWrap { static_data_could_throw }();
        CHECK(error == nullptr);
        REQUIRE(value.has_value());
        CHECK(*value == 43);
      }
    }

    SECTION("LValue ref argument") {
      auto f = [](int& x) {
        x = 42;
      };
      int x = 0;
      TryWrap { f }(x);
      CHECK(x == 42);
    }

    SECTION("RValue ref argument") {
      const auto f = [](int&& x) {
        x = 42;
      };
      int x = 0;
      TryWrap { f }(std::move(x));
      CHECK(x == 42);
    }
  }

  SECTION("Handling thrown exceptions") {
    {
      auto&& [value, error] = TryWrap { withdata_could_throw }();
      CHECK(error == nullptr);
      REQUIRE(value.has_value());
      CHECK(*value == 1138);
    }

    {
      auto&& [value, error] = TryWrap { withdata_throws }();
      CHECK(error != nullptr);
      CHECK(not value.has_value());
    }
  }

  CHECK(TryWrap { withdata_nothrow }() == 42);

  SECTION("Functor") {
    SECTION("no throw") {
      Functor<false, int> functor;
      CHECK_NOTHROW(TryWrap { functor }());
    }

    SECTION("throws") {
      Functor<true, int> functor;
      CHECK_NOTHROW(TryWrap { functor }());
    }

    SECTION("member function") {
      SECTION("no throw") {
        Functor<false, int> functor;
        CHECK_NOTHROW(TryWrap { &Functor<false, int>::member_function }(functor));
      }

      SECTION("throws") {
        Functor<true, int> functor;
        CHECK_NOTHROW(TryWrap { &Functor<true, int>::member_function }(functor));
      }
    }

    SECTION("static member") {
      SECTION("no throw") {
        CHECK_NOTHROW(TryWrap { Functor<false, int>::static_member }());
      }

      SECTION("throws") {
        CHECK_NOTHROW(TryWrap { Functor<true, int>::static_member }());
      }
    }
  }
}
