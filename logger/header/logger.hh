#ifndef GALACTICSTRUCTURES_LOGGER_HH
#define GALACTICSTRUCTURES_LOGGER_HH

#include <mutex>
#include <string>
#include <vector>

namespace gsw{

//! @todo enable output to different streams?
// it might not actually be testable without this..
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
  friend class LoggingContext;
  level mLogLevel;
  std::vector<std::string> mContexts;
  inline static std::mutex sConsoleMutex;

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
    std::unique_lock lk(logger::sConsoleMutex);

    std::cout << '[' << level_string(mLogLevel) << "]\t" << std::setw(14);
    for(auto& context : mContexts){
      std::cout << context << "\t";
    }
    std::cout << loggable << '\n';

    return *this;
  }
};

}

#endif //GALACTICSTRUCTURES_LOGGER_HH
