#include <containers.hh>
#include <context.hh>

#include <catch2/catch_all.hpp>

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace flp;

struct RAIILogger {
  std::function<void()> func;
  std::string stub;

  template<typename Func>
  RAIILogger(Func&& f, std::string message)
    : func(std::forward<Func>(f))
    , stub(std::move(message))
  {}

  void operator()() const {
    std::cout << stub << " started\n";
    func();
    std::cout << stub << " ended\n";
  }
};

struct S {
  int i;

  S() {
    std::cout << "\tConstructing S\n";
    std::cout << '\t' << this << std::endl;
  }
  ~S() {
    std::cout << "\tDestructing S\n";
    std::cout << '\t' << this << std::endl;
  }
};

struct UseAllocBar {
  std::shared_ptr<AllocatorBase> allocator;

  std::shared_ptr<S> bar() {
    return allocator->create<S>();
  }
};

UseAllocBar get_bar() {
  return {allocator()};
}

struct UseAllocFoo {
  std::shared_ptr<AllocatorBase> allocator;

  std::shared_ptr<S> foo() {
    return allocator->create<S>();
  }
};

void stack1() {
  ScopedContext _ (std::make_shared<STDAllocator>(1));

  UseAllocFoo foo{allocator()};

  {
    ScopedContext _(std::make_shared<STDAllocator>(1138));

    UseAllocFoo bar{allocator()};

    const auto x = foo.foo();
    const auto y = bar.foo();
  }
}

void stack2() {
  ScopedContext _ (std::make_shared<STDAllocator>(1));

  auto bar1 = get_bar();

  auto bar2 = []{
    ScopedContext _ (std::make_shared<STDAllocator>(1138));

    return get_bar();
  }();

  auto bar3 = get_bar();

  auto s1 = bar1.bar();
  auto s2 = bar2.bar();
  auto s3 = bar3.bar();
}

void stack3() {
  auto bar = get_bar();
  auto _ = create_scoped_context<PoolAllocator>();

  bar.bar();

  auto bar2 = get_bar();

  bar2.bar();
}

void alloc1() {
  Contextual::Vector<int> v;

  v.reserve(43);

  v.push_back(1138);
}

void alloc2() {
  Contextual::Vector<int> v;

  v.reserve(43);
  v.push_back(1138);

  //! @TODO Fix this: something to do with rebind
  //v.shrink_to_fit();

  v.push_back(42);
}

void alloc3() {
  Contextual::Vector<int> v;

  v.reserve(43);
  v.push_back(1138);
  v.push_back(1139);

  auto u = v;

  v.clear();

  u.push_back(1);
}

TEST_CASE("Context Stack") {
  std::vector<RAIILogger> vec{
    {stack1, "stack1"},
    {stack2, "stack2"},
    {stack3, "stack3"}
  };

  std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;

  for (const auto& f : vec) {
    f();
    std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;
  }
}

TEST_CASE("Allocator") {
  std::vector<RAIILogger> vec{
    {alloc1, "alloc1"},
    {alloc2, "alloc2"},
    {alloc3, "alloc3"}
  };

  std::cout << "alloc_test start\n";

  for (const auto& f : vec) {
    f();
  }
  std::cout << "alloc_test end\n";
}
