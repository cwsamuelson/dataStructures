#include <box.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/catch.h>

#include <variant>

using namespace flp;

TEST_CASE("`Box`") {
  rc::prop("Default Constructed", [](const int initial, const int final) {
    Box<int> box;
    RC_ASSERT(*box == 0);

    *box = initial;
    RC_ASSERT(*box == initial);

    *box = final;
    RC_ASSERT(*box == final);
  });

  rc::prop("Mutable", [](const int initial, const int final) {
    Box<int> box = initial;
    RC_ASSERT(*box == initial);

    *box = final;
    RC_ASSERT(*box == final);
  });

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

    // Expression e = 42;
    // REQUIRE(std::holds_alternative<int>(e));
    // CHECK(std::get<int>(e) == 42);

    // e = AddExpression{ 1138, 42 };

    // REQUIRE(std::holds_alternative<flp::Box<AddExpression>>(e));
    // auto lhs = std::get<flp::Box<AddExpression>>(e)->lhs;
    // REQUIRE(std::holds_alternative<int>(lhs));
    // CHECK(std::get<int>(lhs) == 1138);
    // auto rhs = std::get<flp::Box<AddExpression>>(e)->rhs;
    // REQUIRE(std::holds_alternative<int>(rhs));
    // CHECK(std::get<int>(rhs) == 42);
  }

  SECTION("Test recursion") {
    // struct X;
    // struct Y {
    //   std::variant<int, flp::Box<X>> x;
    // };
    // struct X {
    //   flp::Box<Y> y;
    // };

    // X x;
    // Y y;
  }

  SECTION("Direct recursion") {
    // struct Expression : std::variant<std::monostate, int, flp::Box<Expression>> {
    //   using Base = std::variant<std::monostate, int, flp::Box<Expression>>;
    //   using Base::Base;

    //   Box<Expression> lhs{};
    // };

    // //Box<Expression> y ;
    // //*y = 1138;
  }

  rc::prop("Value comparison", [](const uint32_t input1) {
    const uint32_t input2 = *rc::gen::nonZero<uint32_t>();
    const uint64_t base = input1;
    const uint64_t difference = input2;

    const Box<uint64_t> x{ base };
    const Box<uint64_t> y{ base + difference };
    const Box<uint64_t> z{ base };

    RC_ASSERT(x == z);
    RC_ASSERT(not (x != z));
    RC_ASSERT(x <= z);
    RC_ASSERT(x >= z);

    RC_ASSERT(x <  y);
    RC_ASSERT(x <= y);
    RC_ASSERT(y >  x);
    RC_ASSERT(y >= x);

    RC_ASSERT(*x == *z);
    RC_ASSERT(not (*x != *z));
    RC_ASSERT(*x <= *z);
    RC_ASSERT(*x >= *z);

    RC_ASSERT(*x <  *y);
    RC_ASSERT(*x <= *y);
    RC_ASSERT(*y >  *x);
    RC_ASSERT(*y >= *x);
  });
}

struct Base {
  virtual ~Base() noexcept = default;

  [[nodiscard]]
  virtual int magic() const {
    return 42;
  }
};

struct Derived : Base {
  [[nodiscard]]
  int magic() const override {
    return 1138;
  }
};

TEST_CASE("`Box`::polymorphic") {
  flp::Box<Base> bptr;
  flp::Box<Base> ptr(std::make_unique<Derived>());
  auto dptr = flp::Box<Base>::create<Derived>();

  CHECK(bptr->magic() == 42);
  CHECK(ptr->magic() == 1138);
  CHECK(dptr->magic() == 1138);
}
