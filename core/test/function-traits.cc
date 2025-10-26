#include <catch2/catch_all.hpp>

#include <core/traits/function.hh>

#include <concepts>

using namespace flp;

int foo();

int foo_ui(unsigned int);
int foo_si(signed int);
int foo_f(float);
int foo_d(double);

int foo_ui_ui(unsigned int, unsigned int);
int foo_ui_si(unsigned int, signed int);
int foo_ui_f(unsigned int, float);
int foo_ui_d(unsigned int, double);

int foo_si_ui(signed int, unsigned int);
int foo_si_si(signed int, signed int);
int foo_si_f(signed int, float);
int foo_si_d(signed int, double);

int foo_f_ui(float, unsigned int);
int foo_f_si(float, signed int);
int foo_f_f(float, float);
int foo_f_d(float, double);

int foo_d_ui(double, unsigned int);
int foo_d_si(double, signed int);
int foo_d_f(double, float);
int foo_d_d(double, double);

SCENARIO("core::function traits") {
  SECTION("Builds") {
    FunctionTraits<decltype(foo)>{};
    FunctionTraits<decltype(foo_ui)>{};
    FunctionTraits<decltype(foo_si)>{};
    FunctionTraits<decltype(foo_f)>{};
    FunctionTraits<decltype(foo_d)>{};
    FunctionTraits<decltype(foo_ui_ui)>{};
    FunctionTraits<decltype(foo_ui_si)>{};
    FunctionTraits<decltype(foo_ui_f)>{};
    FunctionTraits<decltype(foo_ui_d)>{};
    FunctionTraits<decltype(foo_si_ui)>{};
    FunctionTraits<decltype(foo_si_si)>{};
    FunctionTraits<decltype(foo_si_f)>{};
    FunctionTraits<decltype(foo_si_d)>{};
    FunctionTraits<decltype(foo_f_ui)>{};
    FunctionTraits<decltype(foo_f_si)>{};
    FunctionTraits<decltype(foo_f_f)>{};
    FunctionTraits<decltype(foo_f_d)>{};
    FunctionTraits<decltype(foo_d_ui)>{};
    FunctionTraits<decltype(foo_d_si)>{};
    FunctionTraits<decltype(foo_d_f)>{};
    FunctionTraits<decltype(foo_d_d)>{};
  }

  SECTION("Return type") {
    FunctionTraits<decltype(foo)>::result_type{};
    FunctionTraits<decltype(foo_ui)>::result_type{};
    FunctionTraits<decltype(foo_si)>::result_type{};
    FunctionTraits<decltype(foo_f)>::result_type{};
    FunctionTraits<decltype(foo_d)>::result_type{};
    FunctionTraits<decltype(foo_ui_ui)>::result_type{};
    FunctionTraits<decltype(foo_ui_si)>::result_type{};
    FunctionTraits<decltype(foo_ui_f)>::result_type{};
    FunctionTraits<decltype(foo_ui_d)>::result_type{};
    FunctionTraits<decltype(foo_si_ui)>::result_type{};
    FunctionTraits<decltype(foo_si_si)>::result_type{};
    FunctionTraits<decltype(foo_si_f)>::result_type{};
    FunctionTraits<decltype(foo_si_d)>::result_type{};
    FunctionTraits<decltype(foo_f_ui)>::result_type{};
    FunctionTraits<decltype(foo_f_si)>::result_type{};
    FunctionTraits<decltype(foo_f_f)>::result_type{};
    FunctionTraits<decltype(foo_f_d)>::result_type{};
    FunctionTraits<decltype(foo_d_ui)>::result_type{};
    FunctionTraits<decltype(foo_d_si)>::result_type{};
    FunctionTraits<decltype(foo_d_f)>::result_type{};
    FunctionTraits<decltype(foo_d_d)>::result_type{};
  }

  SECTION("Argument types") {
    SECTION("Basis") {
      FunctionTraits<decltype(foo)>::arguments{};
      FunctionTraits<decltype(foo_ui)>::arguments{};
      FunctionTraits<decltype(foo_si)>::arguments{};
      FunctionTraits<decltype(foo_f)>::arguments{};
      FunctionTraits<decltype(foo_d)>::arguments{};
      FunctionTraits<decltype(foo_ui_ui)>::arguments{};
      FunctionTraits<decltype(foo_ui_si)>::arguments{};
      FunctionTraits<decltype(foo_ui_f)>::arguments{};
      FunctionTraits<decltype(foo_ui_d)>::arguments{};
      FunctionTraits<decltype(foo_si_ui)>::arguments{};
      FunctionTraits<decltype(foo_si_si)>::arguments{};
      FunctionTraits<decltype(foo_si_f)>::arguments{};
      FunctionTraits<decltype(foo_si_d)>::arguments{};
      FunctionTraits<decltype(foo_f_ui)>::arguments{};
      FunctionTraits<decltype(foo_f_si)>::arguments{};
      FunctionTraits<decltype(foo_f_f)>::arguments{};
      FunctionTraits<decltype(foo_f_d)>::arguments{};
      FunctionTraits<decltype(foo_d_ui)>::arguments{};
      FunctionTraits<decltype(foo_d_si)>::arguments{};
      FunctionTraits<decltype(foo_d_f)>::arguments{};
      FunctionTraits<decltype(foo_d_d)>::arguments{};
    }

    SECTION("First argument") {
      // FunctionTraits<decltype(foo)>::arguments::get<0>{};
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_ui)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_si)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_f)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_d)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_ui_ui)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_ui_si)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_ui_f)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_ui_d)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_si_ui)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_si_si)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_si_f)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_si_d)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_f_ui)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_f_si)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_f_f)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_f_d)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_d_ui)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_d_si)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_d_f)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_d_d)>::arguments::get<0>>);
    }

    SECTION("Second argument") {
      // FunctionTraits<decltype(foo)>::arguments::get<0>>);
      // FunctionTraits<decltype(foo_ui)>::arguments::get<0>>);
      // FunctionTraits<decltype(foo_si)>::arguments::get<0>>);
      // FunctionTraits<decltype(foo_f)>::arguments::get<0>>);
      // FunctionTraits<decltype(foo_d)>::arguments::get<0>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_ui_ui)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_ui_si)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_ui_f)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_ui_d)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_si_ui)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_si_si)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_si_f)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_si_d)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_f_ui)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_f_si)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_f_f)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_f_d)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<unsigned int,
        FunctionTraits<decltype(foo_d_ui)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<signed int,
        FunctionTraits<decltype(foo_d_si)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<float,
        FunctionTraits<decltype(foo_d_f)>::arguments::get<1>>);
      STATIC_CHECK(
        std::same_as<double,
        FunctionTraits<decltype(foo_d_d)>::arguments::get<1>>);
    }
  }
}
