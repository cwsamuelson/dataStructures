// #include <args.hh>

#include <catch2/catch_all.hpp>

#include <any>
#include <map>
#include <string>

#include <print>

// using namespace flp;

struct Arg {
  std::string name;
  std::any value;

  template<typename Type>
  void operator=(Type&& argument) {
    value = std::forward<Type>(argument);
  }
};

constexpr
Arg operator""_Arg(const char* string, const size_t length) noexcept {
  return {
    .name = {string, length}
  };
}

using TaggedArgumentSet = std::map<std::string, std::any>;

void foo(const TaggedArgumentSet& arg_set) {
}

template<typename...Args>
void foo(Args&&... args) {
  // foo(TaggedArgumentSet {
  //   args...
  // });
}

TEST_CASE("`TaggedArgs`::`Sandbox`") {
  foo(""_Arg, "A"_Arg);
}

struct S {
  struct A {
    int a;

    friend
    constexpr
    auto operator<=>(const A&, const A&) noexcept = default;

    friend
    constexpr
    bool operator==(const A&, const A&) noexcept = default;
  };

  struct B {
    double a;

    friend
    constexpr
    auto operator<=>(const B&, const B&) noexcept = default;

    friend
    constexpr
    bool operator==(const B&, const B&) noexcept = default;
  };

  A a;
  B b;

  void operator()(const A& x) {
    a = x;
  }

  void operator()(const B& x) {
    b = x;
  }

  template<typename ...Args>
    requires (sizeof...(Args) > 1)
  void operator()(Args&& ...args) {
    ((*this)(std::forward<Args>(args)), ...);
  }

  friend
  constexpr
  auto operator<=>(const S&, const S&) noexcept = default;

  friend
  constexpr
  bool operator==(const S&, const S&) noexcept = default;
};

TEST_CASE("`TaggedArgs`::`Idea`") {
  S s;

  s(S::A{1}, S::B{1.});

  S t;

  CHECK(s != t);

  t(S::B{1.}, S::A{1});

  CHECK(s == t);
}
