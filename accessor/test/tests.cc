#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <accessor.hh>

using namespace gsw;

class bar {
public:
  using value_type = int;

private:
  value_type i;
  int j;

public:
  bar()
          : i(0)
          , j(0) {
  }

  accessor<value_type> getInternal() {
    return accessor<value_type>(i, [&](value_type t)
      {
        if(t == 12) {
          ++j;
          return true;
        } else {
          return false;
        }
      });
  }

  int getj() {
    return j;
  }
};

TEST_CASE("Accessor can be assigned to, but only if permitted by callback", "[accessor]") {
  bar b;

  CHECK(b.getInternal() == 0);

  b.getInternal() = 13;
  CHECK(b.getInternal() == 0);

  b.getInternal() = 12;
  CHECK(b.getInternal() == 12);
  CHECK(b.getj() == 1);

  b.getInternal() = 11;
  CHECK(b.getInternal() == 12);
  CHECK(b.getj() == 1);
}

TEST_CASE("Accessor can be used as a reference proxy", "[accessor]") {
  bar b;
  auto a = b.getInternal();
  const auto c = b.getInternal();

  CHECK(a == 0);
  CHECK(c == 0);

  a = 11;
  CHECK(a == 0);
  CHECK(c == 0);

  a = 12;
  CHECK(a == 12);
  CHECK(c == 12);

  a = 13;
  CHECK(a == 12);
  CHECK(c == 12);
}
