#ifndef GALACTICSTRUCTURES_SCOPED_LOGGER_HH
#define GALACTICSTRUCTURES_SCOPED_LOGGER_HH

#include <logger.hh>

#include <string>

namespace gsw{

class LoggingContext{
private:
  logger& mLogger;

public:
  LoggingContext(logger& lgr, std::string prefix)
    : mLogger(lgr)
  {
    mLogger.mContexts.emplace_back(std::move(prefix));
  }

  ~LoggingContext(){
    mLogger.mContexts.pop_back();
  }
};

}

#endif //GALACTICSTRUCTURES_SCOPED_LOGGER_HH
