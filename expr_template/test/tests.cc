#include <expr_template.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

struct S {
  friend
  S operator+(const S&, const S&) noexcept {
    CHECK(false);
    return {};
  }
};

template<>
struct flp::EnableExprTempl<S> {};

TEST_CASE("Expression-Templates") {
  S a;
  S b;
  a + b;

  int x;
  int y;
  x + y;
}
