#pragma once

namespace flp {

struct LoggerBase {
  enum class Noise {
  };

  enum class Severity {
    trace,
    info,
    warn,
    error,
  };

  virtual void log(Severity, Noise) = 0;
};

}
