#include "core/forward-ref.hh"
#include "core/move-ref.hh"

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("core::MoveRef") {
  std::string string0;
  // MoveRef<std::string> ref0 = string0; // won't compile
  MoveRef<std::string> ref1(std::move(string0));
  // MoveRef<std::string> ref1 = std::move(string0); // won't build; should build?

  const std::string string1 = ref1; // move ctor
  // MoveRef<std::string> ref2 = std::move(string1); // won't compile (const)
}

void f1(auto&& param) {
  std::string mine = param; // type declared to prevent copying the ForwardRef
}

void f2(auto&& param) {
  f1(param); // 'Just Works tm'
}

template<typename Value>
void take(Value&& value) {
  auto mine = value;
}

template<typename Value>
void take_ref(ForwardRef<Value> value) {
  f2(value);
}

TEST_CASE("core::ForwardRef") {
  std::string local{"String info; big enough for SSO, just in case"};
  take(local);
  take(std::move(local));

  local = "String info; big enough for SSO, just in case";
  take_ref(ForwardRef{local});
  take_ref(ForwardRef{std::move(local)});
  // take_ref(local);
  // take_ref(std::move(local));
}
