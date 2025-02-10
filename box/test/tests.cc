#include <box.hh>

#include <catch2/catch_all.hpp>

#include <optional>
#include <variant>

using namespace flp;

TEST_CASE("box") {
  SECTION("Mutable") {
    Box<int> box;
    CHECK(*box == 0);
    *box = 42;
    CHECK(*box == 42);
  }

  SECTION("Immutable") {
    const Box<int> box = 42;
    CHECK(*box == 42);
    //box = 1138; // doesn't compile
    CHECK(*box != 1138);
  }

  SECTION("Indirect Recursion") {
    struct AddExpression;
    using Expression = std::variant<int, flp::Box<AddExpression>>;
    struct AddExpression {
      Expression lhs;
      Expression rhs;
    };

    Expression e = 42;
    REQUIRE(std::holds_alternative<int>(e));
    CHECK(std::get<int>(e) == 42);

    e = AddExpression{ 1138, 42 };

    REQUIRE(std::holds_alternative<flp::Box<AddExpression>>(e));
    auto lhs = std::get<flp::Box<AddExpression>>(e)->lhs;
    REQUIRE(std::holds_alternative<int>(lhs));
    CHECK(std::get<int>(lhs) == 1138);
    auto rhs = std::get<flp::Box<AddExpression>>(e)->rhs;
    REQUIRE(std::holds_alternative<int>(rhs));
    CHECK(std::get<int>(rhs) == 42);
  }

  SECTION("Direct recursion") {
    struct Expression : std::variant<std::monostate, int, flp::Box<Expression>> {
      using Base = std::variant<std::monostate, int, flp::Box<Expression>>;
      using Base::Base;

      Box<Expression> lhs{};
    };

    Expression y ;
    //y = 1138;
  }
}

