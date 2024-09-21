#pragma once

#include <memory>
#include <source_location>

namespace flp {
namespace trait {
// type erasure is probably not great for logger performance
// this can be important if lots of logs are made
// that's not an unreasonable expectation either
struct Logger {
  enum class NoiseLevel : uint8_t {
    low,
    medium,
    high,
    quiet = low,
    noisy = high,
  };

  enum class Category : uint8_t {
    trace,
    info,
    debug,
    warn,
    error,
  };

  struct LogMessage {
    NoiseLevel           level;
    Category             category;
    std::string_view     message;
    std::source_location location = std::source_location::current();
  };

  struct Interface {
    virtual ~Interface() noexcept = default;

    virtual void log(const LogMessage& message) = 0;
  };

  template<typename Type>
  struct Implementation : Interface {
    Type logger;

    template<typename T>
    explicit Implementation(T&& value)
      : logger(std::forward<T>(value)) {}

    template<typename T>
    Implementation& operator=(T&& value) {
      logger = std::forward<T>(value);
      return *this;
    }

    ~Implementation() override = default;

    void log(const LogMessage& message) override {
      logger.log(message);
    }
  };

  Logger()                  = default;
  Logger(const Logger&)     = default;
  Logger(Logger&&) noexcept = default;

  Logger& operator=(const Logger&)     = default;
  Logger& operator=(Logger&&) noexcept = default;

  ~Logger() = default;

  template<typename Type>
    requires(not std::same_as<Type, Logger>)
  Logger(Type&& logger)
    : implementation(std::make_shared<Implementation<std::decay_t<Type>>>(std::forward<Type>(logger))) {}

  template<typename Type>
    requires(not std::same_as<Type, Logger>)
  Logger& operator=(Type&& logger) {
    implementation = std::make_shared<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    implementation = std::make_shared<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  // similar to contracts, we could have logger categories that are asked whether they're active
  // and then an actual logger handles dispatching the results, but not necessarily controlling whether it's sent, or
  // it's content? perhaps all 3 of these (allocator, logger, contracts) should have similar semantics

  void log(const NoiseLevel           level,
           const Category             category,
           const std::string_view     message,
           const std::source_location location = std::source_location::current()) {
    implementation->log({ level, category, message, location });
  }

  // asynchronous???
  //  - due to forking, a context may be cleaned up while a given scope continues to hold a handle to it
  //  - to prevent this, a shared_ptr could be used.  I'd rather use the heap less, but this  may be unavoidable
  //  - this is, of course, incredibly ironic
  //  - we could also decouple the return type and allocation scheme..?
  // co_await log?
  // co_spawn log? to make it less-blocking

private:
  std::shared_ptr<Interface> implementation;
};

// Log wrappers
// buffered logger
// timestamped logger

template<size_t AllocationBufferSize>
struct DesiredAllocatorStyle {
  alignas(alignof(max_align_t))
  std::array<std::byte, AllocationBufferSize> buffer;

  size_t cursor{};

  template<typename Type>
  Type* allocate(const size_t object_count) {
    Type* result = buffer.data();
    cursor += object_count * sizeof(Type);
    return result;
  }

  template<typename Type>
  void deallocate(const size_t object_count) {
    // do nothing, lol
  }
};

struct Unique/*?*/ {

};

// use functors and templated lambdas to capture by member function?
// this isn't great for performance, but neither is type erasure
struct Allocator {
  struct Interface {
    virtual ~Interface() noexcept = default;

    // cpp std::allocators have only allocate + deallocate
    // I think having a construct/create + destruct/destroy allows things like using an aligned buffer to manage
    // allocation cpp2 allocators use 'new', and returns custom pointers I'm unsure where between these the solution
    // lies

    /*template<typename Type>
    Type* allocate(this auto&& self, const size_t object_count) {
      return self.allocate_impl(object_count);
    }

    template<typename Type>
    void deallocate(this auto&& self, const Type* pointer, const size_t object_count) {
      self.deallocate_impl(pointer, object_count);
    }

    template<typename Type>
    void construct(this auto&& self, const Type* pointer, const size_t object_count) {
      self.construct_impl(pointer, object_count);
    }

    template<typename Type>
    void destroy(this auto&& self, const Type* pointer, const size_t object_count) {
      self.destroy_impl(pointer, object_count);
    }*/
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

    template<typename AllocationType>
    AllocationType* allocate_impl(const size_t object_count) {
      return allocator.allocate(object_count);
    }

    template<typename AllocationType>
    void deallocate_impl(const AllocationType* pointer, const size_t object_count) {
      allocator.deallocate_impl(pointer, object_count);
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
    : implementation(std::make_shared<Implementation<std::decay_t<Type>>>(std::forward<Type>(allocator))) {}

  template<typename Type>
    requires(not std::same_as<Type, Allocator>)
  Allocator& operator=(Type&& allocator) {
    implementation = std::make_shared<Implementation<Type>>(std::forward<Type>(allocator));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    implementation = std::make_shared<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  /*template<typename AllocationType>
  AllocationType* allocate(const size_t object_count) {
    return implementation->allocate<AllocationType>(object_count);
  }*/

  /*template<typename AllocationType>
  void deallocate(const AllocationType* pointer, const size_t object_count) {
    implementation->deallocate(pointer, object_count);
  }*/

private:
  std::shared_ptr<Interface> implementation;
};

// manual allocators
// allocator wrappers
// stack
// arena

struct ErrorContract {
  enum class Category : uint8_t {
    verbose,
    strict,
    permissive,
  };

  // capture file location?
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

  ErrorContract()                         = default;
  ErrorContract(const ErrorContract&)     = default;
  ErrorContract(ErrorContract&&) noexcept = default;

  ErrorContract& operator=(const ErrorContract&)     = default;
  ErrorContract& operator=(ErrorContract&&) noexcept = default;

  ~ErrorContract() = default;

  template<typename Type>
    requires(not std::same_as<Type, ErrorContract>)
  explicit ErrorContract(Type&& logger)
    : implementation(std::make_shared<Implementation<Type>>(std::forward<Type>(logger))) {}

  template<typename Type>
  ErrorContract& operator=(Type&& logger) {
    implementation = std::make_shared<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    implementation = std::make_shared<Implementation<Logger>>(std::forward<Args>(args)...);
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
  std::shared_ptr<Interface> implementation;
};
} // namespace trait

// should the context be a trait, too?
// just expecting getters to be available?
// that prevents editing the context
struct Context {
  Context();

  trait::Logger    logger;
  trait::Allocator allocator;
  // temporary allocator?
  trait::ErrorContract error_contract;
};

struct ScopedContext {
           ScopedContext();
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