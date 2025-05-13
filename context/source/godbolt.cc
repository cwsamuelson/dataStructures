#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <ranges>
#include <span>
#include <stack>
#include <vector>


struct LoggerBase {
  enum class Noise {
  };

  enum class Severity {
    trace,
    info,
    warn,
    error,
  };

  virtual void log(Severity, Noise) = 0;
};

struct AllocatorBase : std::enable_shared_from_this<AllocatorBase> {
protected:
  virtual void* allocate(size_t size, size_t alignment) = 0;

  virtual void deallocate(void* pointer, size_t size) = 0;

  virtual void deallocate(void* pointer, std::align_val_t alignment) = 0;

  virtual void deallocate(void* pointer, size_t size, std::align_val_t alignment) = 0;

public:
  template<typename Type>
  Type* allocate(const size_t count){
    std::cout << "`AllocatorBase` `allocate` template wrapper\n";
    return static_cast<Type*>(allocate(count * sizeof(Type), alignof(Type)));
  }
  template<typename Type>
  void deallocate(Type* pointer) {
    std::cout << "`AllocatorBase` `deallocate(Type*)` template wrapper\n";
    deallocate(static_cast<void*>(pointer), static_cast<std::align_val_t>(alignof(Type)));
  }
  template<typename Type>
  void deallocate(Type* pointer, const size_t size) {
    std::cout << "`AllocatorBase` `deallocate(Type*, sz)` template wrapper\n";
    deallocate(static_cast<void*>(pointer), size);
  }
  template<typename Type>
  void deallocate(Type* pointer, const std::align_val_t alignment) {
    std::cout << "`AllocatorBase` `deallocate(Type*, al)` template wrapper\n";
    deallocate(static_cast<void*>(pointer), static_cast<std::align_val_t>(alignment));
  }
  template<typename Type>
  void deallocate(Type* pointer, const size_t size, const std::align_val_t alignment) {
    std::cout << "`AllocatorBase` `deallocate(Type*, sz, al)` template wrapper\n";
    deallocate(static_cast<void*>(pointer), size, alignment);
  }

  template<typename Type, typename ...Args>
  void construct(Type* pointer, Args&& ...args) {
    new (pointer) Type(std::forward<Args>(args)...);
  }
  template<typename Type, typename ...Args>
  void construct_n(Type* pointer, const size_t count, Args&& ...args) {
    // forward might do a move, making `args` invalid for subsequent iterations.
    // I feel like this is mostly the user's problem?
    for (auto* ptr = pointer; ptr != pointer + count; ++ptr) {
      construct(ptr, std::forward<Args>(args)...);
    }
  }

  template<typename Type>
  void destruct(Type* pointer) {
    pointer->~Type();
  }

  template<typename Type>
  void destruct_n(Type* pointer, const size_t count) {
    for(auto* ptr = pointer; ptr != pointer + count; ++ptr) {
      destruct(ptr);
    }
  }

  template<typename Type>
  struct Deleter {
    std::shared_ptr<AllocatorBase> allocator;

    void operator()(Type* pointer) {
      allocator->destruct(pointer);
      allocator->deallocate(pointer);
    }
  };

  template<typename Type, typename ...Args>
  std::unique_ptr<Type, Deleter<Type>> create(Args&& ...args) {
    auto* ptr = allocate<Type>(1);
    construct(ptr, std::forward<Args>(args)...);
    return {ptr, {shared_from_this()}};
  }
};

struct STDLogger : LoggerBase {
  void log(Severity, Noise) override {
  }
};

struct STDAllocator : AllocatorBase {
  size_t id{};
  STDAllocator(const size_t ID)
    : id(ID)
  {}
  STDAllocator(const STDAllocator&) = delete;
  void operator=(const STDAllocator&) = delete;

  void* allocate(const size_t size, const size_t alignment) override {
    std::cout << "STDAllocator " << id << " allocating\n";
    return operator new(size, static_cast<std::align_val_t>(alignment));
  }

  void deallocate(void* ptr, const size_t size) override {
    std::cout << "STDAllocator " << id << " deallocating\n";
    operator delete(ptr, size);
  }

  void deallocate(void* pointer, std::align_val_t alignment) {
    std::cout << "STDAllocator " << id << " deallocating\n";
    operator delete(pointer, alignment);
  }

  void deallocate(void* pointer, size_t size, std::align_val_t alignment) override {
    std::cout << "STDAllocator " << id << " deallocating\n";
    operator delete(pointer, size, alignment);
  }
};

struct PoolAllocator : AllocatorBase {
  struct MemoryPool {
    std::shared_ptr<unsigned char[]> memory;

    std::span<unsigned char> whole_block;
    std::span<unsigned char> remaining_block;
  };

  MemoryPool pool;

  PoolAllocator()
    : PoolAllocator(4096)
  {}

  PoolAllocator(const size_t block_size)
    : pool({
      std::shared_ptr<unsigned char[]>{new unsigned char[block_size]},
      {pool.memory.get(), block_size},
      {pool.whole_block}
    })
  {}

  PoolAllocator(const PoolAllocator&) = delete;
  void operator=(const PoolAllocator&) = delete;

  void* allocate(const size_t size, const size_t alignment) override {
    std::cout << "PoolAllocator allocating\n";
    const auto* rptr = pool.remaining_block.data();
    pool.remaining_block = pool.remaining_block.subspan(alignment - (reinterpret_cast<size_t>(rptr) % alignment));
    auto* pointer = pool.remaining_block.data();
    pool.remaining_block = pool.remaining_block.subspan(size);
    return pointer;
  }

  void deallocate([[maybe_unused]]void* ptr, [[maybe_unused]]const size_t alignment) override {
    std::cout << "PoolAllocator deallocating\n";
  }

  void deallocate([[maybe_unused]]void* pointer, [[maybe_unused]]const std::align_val_t alignment) {
    std::cout << "PoolAllocator deallocating\n";
  }

  void deallocate([[maybe_unused]]void* pointer, [[maybe_unused]]const size_t size, [[maybe_unused]]const std::align_val_t alignment) override {
    std::cout << "PoolAllocator deallocating\n";
  }
};

struct ContextFrame {
  std::shared_ptr<AllocatorBase> allocator;
  std::shared_ptr<LoggerBase> logger;
  // error handling
  // contracts
  // concurrency
  // parallelism # auto parallel for loops?
};

struct ContextStack {
  std::stack<ContextFrame> stack;

  ContextStack() {
    stack.push({
      std::make_shared<STDAllocator>(42),
      std::make_shared<STDLogger>(),
    });
  }

  void push(ContextFrame frame) {
    std::cout << "pushing context " << stack.size() << std::endl;
    stack.push(frame);
  }

  void pop() {
    std::cout << "popping context " << stack.size() << std::endl;
    stack.pop();
  }

  const ContextFrame& context() const {
    return stack.top();
  }
};

thread_local inline ContextStack GlobalCtxStack{};

void push_context(ContextFrame frame) {
  GlobalCtxStack.push(frame);
}

void push_context(std::shared_ptr<AllocatorBase> allocator) {
  push_context(ContextFrame{
    .allocator = allocator,
    .logger = GlobalCtxStack.stack.top().logger,
  });
}

void push_context(std::shared_ptr<LoggerBase> logger) {
  push_context(ContextFrame{
    .allocator = GlobalCtxStack.stack.top().allocator,
    .logger = logger,
  });
}

void pop_context() {
  GlobalCtxStack.pop();
}

const ContextFrame& context() {
  return GlobalCtxStack.context();
}

auto allocator() {
  return context().allocator;
}

auto logger() {
  return context().logger;
}

struct ScopedContext {
  template<typename ...Args>
  ScopedContext(Args&& ...args) {
    push_context(std::forward<Args>(args)...);
  }
  ~ScopedContext() {
    pop_context();
  }
};

template<typename Type, typename ...Args>
auto create_scoped_context(Args&& ...args) {
  return ScopedContext(std::make_shared<Type>(std::forward<Args>(args)...));
}

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

struct UseAllocFoo {
  std::shared_ptr<AllocatorBase> allocator;

  std::shared_ptr<S> foo() {
    return allocator->create<S>();
  }
};

struct UseAllocBar {
  std::shared_ptr<AllocatorBase> allocator;

  std::shared_ptr<S> bar() {
    return allocator->create<S>();
  }
};

template<typename Type>
struct StdAllocWrapper {
  using value_type = Type;
  using pointer = Type*;

  std::shared_ptr<AllocatorBase> allocator;

  StdAllocWrapper()
    : allocator(::allocator())
  {}

  pointer allocate(const size_t n) {
    return allocator->allocate<Type>(n);
  }

  /*pointer allocate(const size_t n, const pointer) {
    return nullptr;
  }*/

  /*pointer allocate_at_least(const size_t n) {
    return nullptr;
  }*/

  void deallocate(pointer p, size_t n) {
    allocator->deallocate<Type>(p, n);
  }

  size_t max_size() const {
    return -1;
  }

  void construct(){}
  void destroy() {}
};

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

UseAllocBar get_bar() {
  return {allocator()};
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

void context_stack_test() {
  std::vector<RAIILogger> vec{
    // runs without additional context of its own
    {stack1, "stack1"},
    {stack2, "stack2"},
    {stack3, "stack3"}
  };

  std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;

  stack1();

  for (const auto& f : vec) {
    f();
    std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;
  }
}

namespace Contextual {
  // basic_string
  template<typename Char, typename Traits = std::char_traits<Char>, typename Allocator = StdAllocWrapper<Char>>
      // requires Allocator is context aware
  using BasicString = std::basic_string<Char, Traits, Allocator>;
  using String = BasicString<char>;
  //using WString = BasicString<wchar>;
  // deque
  template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  using Deque = std::deque<Type, Allocator>;
  // forward_list
  //template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  //using ForwardList = std::forward_list<Type, Allocator>;
  // list
  //template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  //using List = std::list<Type, Allocator>;
  // vector
  template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  using Vector = std::vector<Type, Allocator>;
  // map
  //template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using Map = std::map<Key, Value, Compare, Allocator>;
  // multimap
  //template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using MultiMap = std::multimap<Key, Value, Compare, Allocator>;
  // set
  //template<typename Key, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using Set = std::set<Key, Compare, Allocator>;
  // multiset
  //template<typename Key, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using MultiSet = std::multiset<Key, Compare, Allocator>;
  // unordered_map
  //template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedMap = std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>;
  // unordered_multimap
  //template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedMultiMap = std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>;
  // unordered_set
  //template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;
  // unordered_multiset
  //template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedMultiSet = std::unordered_multiset<Key, Hash, KeyEqual, Allocator>;
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

void alloc_test() {
  std::vector<RAIILogger> vec{
    {alloc1, "alloc1"},
      {alloc2, "alloc2"},
      {alloc3, "alloc3"}
  };

  std::cout << "alloc_test start\n";

  stack1();
  for (const auto& f : vec) {
    f();
  }
  std::cout << "alloc_test end\n";
}

int main() {
  context_stack_test();

  alloc_test();
}
