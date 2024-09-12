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
  enum class LogCategory {
  };

  struct LogMessage {
    LogNoise level;
    LogCategory category;
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

  LoggerTrait() = default;
  LoggerTrait(const LoggerTrait&) = delete;
  LoggerTrait(LoggerTrait&&) noexcept = default;
  LoggerTrait& operator=(const LoggerTrait&) = delete;
  LoggerTrait& operator=(LoggerTrait&&) noexcept = default;

  ~LoggerTrait() = default;

  template<typename Type>
  explicit LoggerTrait(Type&& logger)
    : implementation(std::make_unique<Implementation<Type>>(std::forward<Type>(logger)))
  {}

  template<typename Type>
  LoggerTrait& operator=(Type&& logger) {
    implementation = std::make_unique<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename ...Args>
  void emplace(Args&& ...args) {
    implementation = std::make_unique<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  void log(const LogMessage& message) {
    implementation->log(message);
  }

  void log(const LogNoise level, const LogCategory category, const std::string_view message) {
    implementation->log({level, category, message});
  }

  // asynchronous???
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
  };

  template<typename Type>
  struct Implementation : Interface {
    Type logger;
  };

  AllocatorTrait() = default;
  AllocatorTrait(const AllocatorTrait&) = delete;
  AllocatorTrait(AllocatorTrait&&) noexcept = default;
  AllocatorTrait& operator=(const AllocatorTrait&) = delete;
  AllocatorTrait& operator=(AllocatorTrait&&) noexcept = default;

  ~AllocatorTrait() = default;

  template<typename Type>
  explicit AllocatorTrait(Type&& logger)
    : implementation(std::make_unique<Implementation<Type>>(std::forward<Type>(logger)))
  {}

  template<typename Type>
  AllocatorTrait& operator=(Type&& logger) {
    implementation = std::make_unique<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename ...Args>
  void emplace(Args&& ...args) {
    implementation = std::make_unique<Implementation<Logger>>(std::forward<Args>(args)...);
  }

private:
  std::unique_ptr<Interface> implementation;
};

struct ErrorCategoryTrait {
  struct Interface {
    virtual ~Interface() noexcept = default;
  };

  template<typename Type>
  struct Implementation : Interface {
    Type logger;
  };

  ErrorCategoryTrait() = default;
  ErrorCategoryTrait(const ErrorCategoryTrait&) = delete;
  ErrorCategoryTrait(ErrorCategoryTrait&&) noexcept = default;
  ErrorCategoryTrait& operator=(const ErrorCategoryTrait&) = delete;
  ErrorCategoryTrait& operator=(ErrorCategoryTrait&&) noexcept = default;

  ~ErrorCategoryTrait() = default;

  template<typename Type>
  explicit ErrorCategoryTrait(Type&& logger)
    : implementation(std::make_unique<Implementation<Type>>(std::forward<Type>(logger)))
  {}

  template<typename Type>
  ErrorCategoryTrait& operator=(Type&& logger) {
    implementation = std::make_unique<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename ...Args>
  void emplace(Args&& ...args) {
    implementation = std::make_unique<Implementation<Logger>>(std::forward<Args>(args)...);
  }

private:
  std::unique_ptr<Interface> implementation;
};

struct Context {
  LoggerTrait logger;
  AllocatorTrait allocator;
  ErrorCategoryTrait default_error_category;
};

} // namespace flp
