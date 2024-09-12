#pragma once

#include <error_help.hh>

#include <memory>

namespace flp {
struct LoggerTrait {
  enum class LogNoise {
    low,
    medium,
    high,
    quiet = low,
    noisy = high,
  };
  enum class LogCategory {};

  struct LogMessage {
    LogNoise         level;
    LogCategory      category;
    std::string_view message;
  };

  struct Interface {
    virtual ~Interface() noexcept = default;

    virtual void log(const LogMessage& message) = 0;
  };

  template<typename Type>
  struct Implementation : Interface {
    Type logger;

    void log(const LogMessage& message) override {
      logger.log(message);
    }
  };

  LoggerTrait()                       = default;
  LoggerTrait(const LoggerTrait&)     = delete;
  LoggerTrait(LoggerTrait&&) noexcept = default;

  LoggerTrait& operator=(const LoggerTrait&)     = delete;
  LoggerTrait& operator=(LoggerTrait&&) noexcept = default;

  ~LoggerTrait() = default;

  template<typename Type>
  explicit LoggerTrait(Type&& logger)
    : implementation(std::make_unique<Implementation<Type>>(std::forward<Type>(logger))) {}

  template<typename Type>
  LoggerTrait& operator=(Type&& logger) {
    implementation = std::make_unique<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    implementation = std::make_unique<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  // similar to contracts, we could have logger categories that are asked whether they're active
  // and then an actual logger handles dispatching the results, but not necessarily controlling whether it's sent, or it's content?
  // perhaps all 3 of these (allocator, logger, contracts) should have similar semantics

  void log(const LogMessage& message) {
    implementation->log(message);
  }

  void log(const LogNoise level, const LogCategory category, const std::string_view message) {
    implementation->log({ level, category, message });
  }

  // asynchronous???
  //  - due to forking, a context may be cleaned up while a given scope continues to hold a handle to it
  //  - to prevent this, a shared_ptr could be used.  I'd rather use the heap less, but this  may be unavoidable
  // co_await log?
  // co_spawn log? to make it less-blocking

private:
  std::unique_ptr<Interface> implementation;
};

// Log wrappers
// buffered logger
// timestamped logger

struct AllocatorTrait {
  struct Interface {
    virtual ~Interface() noexcept = default;

    // cpp std::allocators have only allocate + deallocate
    // I think having a construct/create + destruct/destroy allows things like using an aligned buffer to manage
    // allocation cpp2 allocators use 'new', and returns custom pointers I'm unsure where between these the solution
    // lies

    template<typename Type>
    Type* allocate(this auto&& self, const size_t object_count) {
      return self.allocate_impl(object_count);
    }

    template<typename Type>
    void deallocate(this auto&& self, const Type* pointer, const size_t object_count) {
      return self.deallocate_impl(pointer, object_count);
    }

    template<typename Type>
    void construct(this auto&& self, const Type* pointer, const size_t object_count) {
      return self.construct_impl(pointer, object_count);
    }

    template<typename Type>
    void destroy(this auto&& self, const Type* pointer, const size_t object_count) {
      return self.destroy_impl(pointer, object_count);
    }
  };

  template<typename Type>
  struct Implementation : Interface {
    Type allocator;

    template<typename AllocationType>
    AllocationType* allocate_impl(const size_t object_count) {
      return allocator.allocate(object_count);
    }

    template<typename AllocationType>
    void deallocate_impl(const AllocationType* pointer, const size_t object_count) {
      allocator.deallocate_impl(pointer, object_count);
    }
  };

  AllocatorTrait()                          = default;
  AllocatorTrait(const AllocatorTrait&)     = delete;
  AllocatorTrait(AllocatorTrait&&) noexcept = default;

  AllocatorTrait& operator=(const AllocatorTrait&)     = delete;
  AllocatorTrait& operator=(AllocatorTrait&&) noexcept = default;

  ~AllocatorTrait() = default;

  template<typename Type>
  explicit AllocatorTrait(Type&& logger)
    : implementation(std::make_unique<Implementation<Type>>(std::forward<Type>(logger))) {}

  template<typename Type>
  AllocatorTrait& operator=(Type&& logger) {
    implementation = std::make_unique<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    implementation = std::make_unique<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  template<typename AllocationType>
  AllocationType* allocate(const size_t object_count) {
    return implementation->allocate<AllocationType>(object_count);
  }

  template<typename AllocationType>
  void deallocate(const AllocationType* pointer, const size_t object_count) {
    implementation->deallocate(pointer, object_count);
  }

private:
  std::unique_ptr<Interface> implementation;
};

struct ErrorContractTrait {
  struct Interface {
    virtual ~Interface() noexcept = default;

    [[nodiscard]]
    virtual bool is_active() const
      = 0;
    virtual void report_violation() const                 = 0;
    virtual void report_violation(std::string_view) const = 0;
  };

  template<typename Type>
  struct Implementation : Interface {
    Type contract;

    [[nodiscard]]
    bool is_active() const override {
      return contract.is_active();
    }

    void report_violation() const override {
      contract.report_violation();
    }

    void report_violation(std::string_view message) const override {
      contract.report_violation(message);
    }
  };

  ErrorContractTrait()                              = default;
  ErrorContractTrait(const ErrorContractTrait&)     = delete;
  ErrorContractTrait(ErrorContractTrait&&) noexcept = default;

  ErrorContractTrait& operator=(const ErrorContractTrait&)     = delete;
  ErrorContractTrait& operator=(ErrorContractTrait&&) noexcept = default;

  ~ErrorContractTrait() = default;

  template<typename Type>
  explicit ErrorContractTrait(Type&& logger)
    : implementation(std::make_unique<Implementation<Type>>(std::forward<Type>(logger))) {}

  template<typename Type>
  ErrorContractTrait& operator=(Type&& logger) {
    implementation = std::make_unique<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    implementation = std::make_unique<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  [[nodiscard]]
  bool is_active() const {
    return implementation->is_active();
  }

  void report_violation() const {
    implementation->report_violation();
  }

  void report_violation(std::string_view message) const {
    implementation->report_violation(message);
  }

private:
  std::unique_ptr<Interface> implementation;
};

// should the context be a trait, too?
// just expecting getters to be available?
// that prevents editing the context
struct Context {
  LoggerTrait        logger;
  AllocatorTrait     allocator;
  ErrorContractTrait error_contract;
};

struct ScopedContext {
  explicit ScopedContext(Context context);

  ScopedContext(const ScopedContext&) = delete;
  ScopedContext(ScopedContext&&)      = delete;

  ScopedContext& operator=(const ScopedContext&) = delete;
  ScopedContext& operator=(ScopedContext&&)      = delete;

  ~ScopedContext();
};

void           PushContext(Context context);
void           PopContext();
const Context& GetContext();

} // namespace flp
