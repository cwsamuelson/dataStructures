#include <core/application.hh>

#include <catch2/catch_all.hpp>

using namespace Core;

struct ApplicationThrows : ApplicationBase {
  using ApplicationBase::run;

  ApplicationThrows()
    : ApplicationBase("")
  {}

  void run() override {
    throw 42;
  }
};

struct ApplicationArgsThrows : ApplicationBase {
  using ApplicationBase::run;

  ApplicationArgsThrows()
    : ApplicationBase("")
  {}

  void run(const Arguments& arguments, const Environment& environment) override {
    throw 42;
  }
};

struct ApplicationArgs : ApplicationBase {
  using ApplicationBase::run;

  ApplicationArgs(const size_t expected_args, const size_t expected_env)
    : ApplicationBase("")
    , expected_args_count(expected_args)
    , expected_env_count(expected_env)
  {}

  void run(const Arguments& arguments, const Environment& environment) override {
    CHECK(arguments.size() == expected_args_count);
    CHECK(environment.size() == expected_env_count);
  }

  size_t expected_args_count{};
  size_t expected_env_count{};
};

TEST_CASE("core::`Application`") {
  SECTION("Base") {
    ApplicationBase application("");
    CHECK_NOTHROW(application.run());
  }

  SECTION("Exception canary") {
    ApplicationThrows application;
    CHECK_THROWS_AS(application.run(), int);
    CHECK_THROWS_AS(application.run(Arguments{}, Environment{}), int);
  }

  SECTION("Passing basic arguments") {
    ApplicationArgsThrows application;
    CHECK_NOTHROW(application.run());
    CHECK_THROWS_AS(application.run(Arguments{}, Environment{}), int);
  }

  SECTION("") {
    ApplicationArgs application(1, 1);
    application.run(Arguments{""}, Environment{{"", ""}});
  }
}