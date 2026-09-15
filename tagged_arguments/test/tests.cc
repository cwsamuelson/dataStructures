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

TEST_CASE("`TaggedArgs`::Template-based") {
  struct Function {
    template<typename Type>
    struct ArgBase {
      Type value;

      template<typename NType = Type>
      ArgBase(NType&& val)
        : value(std::forward<NType>(val))
      {}

      template<typename ...Args>
      ArgBase(Args&& ...args)
        : value(std::forward<Args>(args)...)
      {}

      template<typename OType>
        requires (not std::same_as<OType, Type>)
      operator OType() const {
        return value;
      }

      operator Type() && {
        return std::move(value);
      }
    };

    struct Arg1 : ArgBase<int> {
      using ArgBase<int>::ArgBase;
    };
    struct Arg2 : ArgBase<int> {
      using ArgBase<int>::ArgBase;
    };

    struct ArgConfig {
      int arg1{12};
      int arg2{12};
    };

    void set(ArgConfig& config, Arg1 value) {
      config.arg1 = std::move(value);
    }

    void set(ArgConfig& config, Arg2 value) {
      config.arg2 = std::move(value);
    }

    template<typename ...Args>
    void operator()(Args&& ...args) {
      ArgConfig config;

      (set(config, args), ...);

      return run(config);
    }

    void run(const ArgConfig& config) {
      // do the work
      std::println("do work!! {}", config.arg1);
    }
  };

  Function function;
  function(Function::Arg1{42});
  function(42);
}
