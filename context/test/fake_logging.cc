#include <catch2/catch_all.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <source_location>
#include <string>
#include <thread>
#include <vector>

// Python's design seems pretty good
// https://www.youtube.com/watch?v=9L77QExPmI0

//! @TODO sync/async/coroutines
// sync:
//   - Be normal
// async:
//   - use a separate thread and queue messages
//   - or just queue messages and allow some other piece to handle them
// coroutines:
//   - channel
//   - queue coroutine work on executor
// how is the choice above selected

// There should be one global logger, from which subsystems should fork
// That way subsystems can be configured on/off

/*!
 */
enum class NoiseLevel : uint8_t {
  low,
  medium,
  high,
  quiet = low,
  noisy = high,
};

/*!
 */
enum class Category : uint8_t {
  trace,
  info,
  debug,
  warn,
  error,
};

/*!
 * https://hsutter.github.io/cppfront/cpp2/contracts/
 * rename to 'system' or 'subsystem'?
 */
struct LogCategory {
  std::string name = "Unnamed";
  bool active = true;

  [[nodiscard]]
  bool is_active() const;
  
  [[nodiscard]]
  std::string N() const;
};

/*!
 */
struct LogMessage {
  using TimePoint = std::chrono::steady_clock::time_point;

  NoiseLevel           level = NoiseLevel::medium;
  Category             category = Category::info;
  LogCategory          system;
  std::string_view     message = "";
  std::source_location location = std::source_location::current();
  TimePoint            time_stamp;
  std::thread::id      thread_id = std::this_thread::get_id();
};

/*!
 * JSONl (JSON lines)
 * YAML documents
 * human-readable
 */
using Formatter = std::function<std::string(const LogMessage&)>;

using Filter = std::function<bool(const LogMessage&)>;

/*!
 * stdout/stderr
 * file
 * logging server
 * email
 * @NOTE In order to handle asynchrony, Handlers should be re-entrant.
 */
struct Handler {
  NoiseLevel          level = NoiseLevel::medium;
  Formatter           formatter;
  std::vector<Filter> filter[];

  void log(LogMessage message) {
    if message.level > level {
      return;
    }
    if (not all_of(filters, filter.test(message))) {
      return;
    }

    do_log(formatter(message));
  }

  void do_log(const std::string&);
};

/*!
 * regex
 * string match
 */
using Filter = std::function<bool(const LogMessage&)>;

/*!
 */
struct Logger : std::enable_shared_from_this<Logger> {
private:
  std::shared_ptr<Logger> parent;
  NoiseLevel              level;
  Category                category;
  std::vector<Handler>    handlers;
  std::vector<Filter>     filters;

  // used to help force shared_ptrs
  struct Private{};

  Logger() = default;

  Logger(const Logger&) = default;
  Logger(Logger&&) noexcept = default;

  Logger& operator=(const Logger&) = default;
  Logger& operator=(Logger&&) noexcept = default;

  ~Logger() = default;

public:
  // just forwarding to the 'real' constructors in private section
  template<typename ...Args>
  Logger(Private, Args&& ...args)
    : Logger(std::forward<Args>(args)...)
  {}

  // intended public interface; forces shared_ptrs
  template<typename ...Args>
  static std::shared_ptr<Logger> create(Args&& ...args) {
    return std::make_shared<Logger>(Private{}, std::forward<Args>(args)...);
  }

  void log(LogMessage message) {
    if message.level > level {
      return;
    }

    if (not all_of(filters, [](const auto& filter) { return filter.test(message); })) {
      return;
    }

    for (handler : handlers) {
      handler.log(message);
    }

    parent.log(message);
  }

  Logger fork() {
    return {
      parent;
      level;
      category;
      handlers;
      filters;
      .parent = shared_from_this()
    };
  }
};

/*!
 */
struct Config {
  std::vector<std::string> filters;
  std::vector<std::string> formatters;
  std::vector<std::string> fandlers;
  std::vector<std::string> foggers;
};

/*! General flexible, and configurable logging system
 * It is expected for there to be a single global logger, and for developers not to touch it directly.  Developers should create 'sub' loggers forked from the primary one to create subsystems.
 * Concepts:
 * # Synchrony
 * Run synchronously, asynchronously, or using coroutines
 * # Noise Level
 * Each message can be given a noise level.  In general noisier messages appear more often, are more detailed, and are less useful to an end user.
 * On principle: WARN logs MUST be actionable by the user, and something they likely want to change.
 * # Configuration
 * The system should be highly configurable by developers and users.
 * # Log Categories
 * A log category is something defined per code base by developers.  They can be things like 'network activity' or 'sensor reading', more likely they will be a subsystem, as defined by the developers.
 * Some of this idea is handled by there being a 'tree' of loggers, and different systems 'owning' a different logger.  However, those loggers are more likely at the class level, and the log category is at the more abstract 'system' level.
 * This name must be disambiguated from 'categories'
 * # Categories
 *  trace
 *  info
 *  debug
 *  warn
 *  error
 * This name must be disambiguated from 'log categories'
 * # Handlers
 * Do the 'actual' logging i.e. writing to a file or network socket etc.
 * # Loggers
 * The primary developer interface to log a message.  Will contain a log level it will respect, filters, and handlers.  It does no logging itself, but ensures log messages are sent where they need to go.
 * # Formatters
 * Formats log message data members into whatever useful content is desired.
 */

Config read_config() {
  // simulate real access
  return {
    Filters[];
    Formatters[];
    Handlers[];
    Loggers[];
  };
}

TEST_CASE("Test fake logging system") {
  config = read_config();

  Logger global;
  A = global.fork();
  B = global.fork();
}
