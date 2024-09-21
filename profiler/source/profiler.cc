#include "profiler.hh"

#include <nlohmann/json.hpp>

#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <thread>

// Design decision:
//  Use JSON library for simplicity of implementation
//  This profiler could instead immediately, and manually write the profiling data to the file
//  This would decrease the memory footprint of the profiler, but may decrease performance
//  The performance impact of writing this data immediately should be assessed
//  Another Impact of that implementation would be that all known profiling data would be logged in the event of a crash

namespace std {

static void to_json(nlohmann::json& json, const std::thread::id& id) {
  std::ostringstream ss;
  ss << id;
  json = ss.str();
}

// thread id deserialization should not be used
static void from_json(const nlohmann::json& json, std::thread::id& id);

template<typename Rep, typename Period>
static void to_json(nlohmann::json& json, const std::chrono::duration<Rep, Period>& duration) {
  json = duration.count();
}

template<typename Rep, typename Period>
static void from_json(const nlohmann::json& json, std::chrono::duration<Rep, Period>& duration);

}

namespace flp {

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(profile_event, cat, dur, name, ph, pid, tid, ts);

struct profiling_session {
  std::map<std::string, int> otherData;// not sure what can go in here
  std::vector<profile_event> traceEvents;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(profiling_session, otherData, traceEvents);
};

profile_timer::profile_timer(std::string name)
  : name(std::move(name))
{}

profile_timer::~profile_timer() {
  auto end_point = std::chrono::steady_clock::now();
  auto elapsed = end_point - start_point;
  profiler::THE().write_event({elapsed, name, start_point});
}

profiler::profiler(const std::filesystem::path& log_file_path)
  : profile_log(log_file_path)
{}

profiler::~profiler() {
  profile_log << nlohmann::json(profiling_session{{}, std::move(events)});
}

void profiler::write_event(const profile_event& event) {
  //! @FIXME thread safety
  events.push_back(event);
}

}

