#include <bind_scope.hh>

#include <catch2/catch_all.hpp>

#include <print>

using namespace flp;

struct BindScope {
  constexpr
  BindScope(Type& value) noexcept
    : resource(value) {
    resource.bind();
  }

  constexpr
  ~BindScope() noexcept {
    resource.unbind();
  }

  Type& resource;
};

template<typename Type>
struct ResImpl {
  constexpr
  void bind() noexcept {
    std::println("resource bind");
  }

  constexpr
  void unbind() noexcept {
    std::println("resource unbind");
  }
};

struct Resource {
  Resource(... /*parameters*/)
  {}

  void work(...) {
    // do things and stuff
  }

  constexpr
  BindScope bind() {
    return { hal };
  }

  ResImpl hal;
};

TEST_CASE("`BindScope`") {
  Resource resource;
}
