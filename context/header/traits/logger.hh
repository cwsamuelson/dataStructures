#pragma once

namespace flp::trait {

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
    NoiseLevel           level = NoiseLevel::medium;
    Category             category = Category::info;
    std::string          message = "";
    std::source_location location = std::source_location::current();
    // time stamp
    // thread id
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

    // NoiseLevel           level
    // Category             category
    // std::string_view     message
    // std::source_location location
    /*template<NoiseLevel Level, Category Cat, typename ...Args>
    void log(std::string_view fmt, Args&& ...args) {
      log(LogMessage{
        .level = Level,
        .category = Cat,
        .message = std::format(fmt, std::forward<Args>(args)...),
        //.location = ...,
      });
    }*/
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

}
