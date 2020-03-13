#ifndef GALACTICSTRUCTURES_LOGGER_HH
#define GALACTICSTRUCTURES_LOGGER_HH

#include <mutex>
#include <string>

namespace gsw{

//! @todo enable output to different streams?
class logger{
public:
  enum class level{
    INFO,
    WARN,
    ERROR,
    TRACE,
    DIGANOSTIC,
  };

private:
  level mLogLevel;
  static std::mutex sConsoleMutex;

  //! @todo maybe use magic_enum?
  static std::string level_string(level l){
    switch(l){
    case level::INFO:
      return "INFO";
    case level::DIGANOSTIC:
      return "DIAG";
    case level::ERROR:
      return "ERROR";
    case level::TRACE:
      return "TRACE";
    case level::WARN:
      return "WARN";
    default:
      return "UNK";
    }
  }

public:
  explicit
  logger(level log_level = level::INFO)
    : mLogLevel(log_level)
  {}

  template<typename LOGGABLE>
  logger& operator<<(const LOGGABLE& loggable){
    std::unique_lock lk(sConsoleMutex);

    std::cout << std::setw(10) << '[' << level_string(mLogLevel) << "]\t" << loggable;
    return *this;
  }
};

}

#endif //GALACTICSTRUCTURES_LOGGER_HH
