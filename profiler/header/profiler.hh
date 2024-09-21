#pragma once

#include <fstream>
#include <filesystem>
#include <thread>
#include <vector>

namespace flp {

struct profile_event {
  using duration_t = std::chrono::duration<double, std::micro>;
  using time_point_t = std::chrono::time_point<std::chrono::steady_clock>;

  std::string cat = "function";
  duration_t dur{};
  std::string name;
  std::string ph = "X";
  size_t pid = 0;
  std::thread::id tid = std::this_thread::get_id();
  duration_t ts{};

  profile_event() = default;

  profile_event(duration_t duration, std::string name, time_point_t ts)
    : dur(duration)
    , name(std::move(name))
    , ts(ts.time_since_epoch())
  {}

  profile_event(const profile_event&) = default;
  profile_event(profile_event&&) = default;
  profile_event& operator=(const profile_event&) = default;
  profile_event& operator=(profile_event&&) = default;

  ~profile_event() = default;
};

class profile_timer {
public:
  explicit
  profile_timer(std::string name);

  ~profile_timer();

private:
  std::string name;
  std::chrono::time_point<std::chrono::steady_clock> start_point = std::chrono::steady_clock::now();
};

// the generated file can be opened using chrome://tracing and using click/drag
//! @FIXME I think the times expressed in the log are the incorrect units.
// the log appears to report ms, but I think it's actually us
class profiler {
public:
  explicit
  profiler(const std::filesystem::path& log_file_path);

  profiler(const profiler&) = delete;
  profiler(profiler&&) = delete;
  profiler& operator=(const profiler&) = delete;
  profiler& operator=(profiler&&) = delete;

  ~profiler();

  void write_event(const profile_event& event);

  static profiler& THE(const std::filesystem::path& logpath = "profile.json") {
    //! @TODO make path name configurable
    static profiler instance(logpath);
    return instance;
  }

private:
  std::ofstream profile_log;
  std::vector<profile_event> events;
};

#if defined(PROFILING) && PROFILING==1
  #define PROFILE_SESSION_BEGIN(filepath) profiler::THE(filepath);
  #define PROFILE_SESSION_END()

  #define PROFILE_SCOPE(name) profile_timer fixed_unique_name##__LINE__(name);
  #define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
  #define PROFILE_SESSION_BEGIN(name, filepath)
  #define PROFILE_SESSION_END()

  #define PROFILE_SCOPE(name)
  #define PROFILE_FUNCTION()
#endif

} // namespace flp
