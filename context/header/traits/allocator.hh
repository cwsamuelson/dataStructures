#pragma once

// use functors and templated lambdas to capture by member function?
// this isn't great for performance, but neither is type erasure
namespace flp::trait {

struct Allocator {
  struct Interface {
    virtual ~Interface() noexcept = default;

    virtual std::byte* allocate_impl(size_t alignment, size_t total_size) = 0;
    virtual void deallocate_impl(std::byte* const pointer, size_t bytes) = 0;

    template<typename Type>
    Type* allocate(const size_t object_count) {
      return reinterpret_cast<Type*>(allocate_impl(alignof(Type), object_count * sizeof(Type)));
    }
    template<typename Type>
    void deallocate(Type* const pointer, const size_t object_count) {
      deallocate_impl(reinterpret_cast<std::byte* const>(pointer), object_count * sizeof(Type));
    }
  };

  template<typename Type>
  struct Implementation : Interface {
    Type allocator;

    template<typename T>
    explicit Implementation(T&& value)
      : allocator(std::forward<T>(value)) {}

    template<typename T>
    Implementation& operator=(T&& value) {
      allocator = std::forward<T>(value);
      return *this;
    }

    ~Implementation() override = default;

    std::byte* allocate_impl(const size_t alignment, const size_t total_size) override {
      return allocator.allocate(alignment, total_size);
    }

    void deallocate_impl(std::byte* const pointer, const size_t bytes) override {
      allocator.deallocate(pointer, bytes);
    }
  };

  Allocator()                     = default;
  Allocator(const Allocator&)     = default;
  Allocator(Allocator&&) noexcept = default;

  Allocator& operator=(const Allocator&)     = default;
  Allocator& operator=(Allocator&&) noexcept = default;

  ~Allocator() = default;

  template<typename Type>
    requires(not std::same_as<Type, Allocator>)
  Allocator(Type&& allocator)
    : implementation(std::make_shared<Implementation<Type>>(std::forward<Type>(allocator))) {}

  template<typename Type>
    requires(not std::same_as<Type, Allocator>)
  Allocator& operator=(Type&& allocator) {
    implementation = std::make_shared<Implementation<Type>>(std::forward<Type>(allocator));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    //implementation = std::make_shared<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  template<typename AllocationType>
  AllocationType* allocate(const size_t object_count) {
    return implementation->allocate<AllocationType>(object_count);
  }

  template<typename AllocationType>
  void deallocate(AllocationType* pointer, const size_t object_count) {
    implementation->deallocate(pointer, object_count);
  }

private:
  std::shared_ptr<Interface> implementation;
};

// manual allocators
// allocator wrappers
// stack
// arena

}
