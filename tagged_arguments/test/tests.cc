// #include <args.hh>

#include <catch2/catch_all.hpp>

#include <any>
#include <map>
#include <string>

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
